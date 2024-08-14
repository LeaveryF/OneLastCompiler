#pragma once

#include <olc/Support.h>

#include <olc/backend/MachineIR.h>
#include <olc/ir/IR.h>

#include <map>

namespace olc {

struct ArmGen {

  std::ostream &os;
  AsmModule *module = nullptr;
  AsmFunc *curFunc = nullptr;

  ArmGen(std::ostream &os, AsmModule *module) : os(os), module(module) {}

  void printArmInstr(
      const std::string &op, const std::vector<std::string> &operands) {

    // indent for instructions
    os << "  ";

    os << op;
    os << " ";
    for (int i = 0; i < operands.size(); ++i) {
      if (i > 0) {
        os << ", ";
      }
      os << operands[i];
    }
    os << '\n';
  }

  void runRegAlloc() {
    std::map<AsmValue *, AsmValue *> regMap;

    for (auto *func : module->funcs) {
      std::map<AsmType, int> pregCounter;
      std::map<AsmType, int> pregSize{
          {AsmType::I32, 13},
          {AsmType::F32, 32},
      };
      if (func->isBuiltin)
        continue;
      for (auto *label : func->labels) {
        for (auto *inst : label->insts) {
          for (auto refdef : inst->getDefs()) {
            auto &def = *refdef;
            assert(isa<AsmReg>(def) && "Non-reg def!");
            if (auto *preg = dyn_cast<PReg>(def)) {
              continue;
            } else if (auto *vreg = dyn_cast<VReg>(def)) {
              // allocate preg naively
              auto type = vreg->type;
              if (pregCounter[type] >= pregSize[type]) {
                olc_unreachable("No enough preg");
              }
              auto *preg = AsmReg::makePReg(type, pregCounter[type]++);
              regMap[vreg] = preg;
              // update MachineIR
              def = preg;
            } else {
              olc_unreachable("???");
            }
          }

          for (auto refuse : inst->getUses()) {
            auto &use = *refuse;
            if (auto *vreg = dyn_cast<VReg>(use)) {
              if (regMap.find(vreg) == regMap.end()) {
                olc_unreachable("Use before def");
              }
              // update MachineIR
              use = regMap[vreg];
            }
          }
        }
      }
    }
  }

  void run() {
    os << ".text\n";
    for (auto *func : module->funcs) {
      os << ".global " << func->name << "\n";
    }

    for (auto *func : module->funcs) {
      if (func->isBuiltin)
        continue;
      os << func->name << ":\n";
      curFunc = func;

      // function prologue
      printArmInstr("push", {"{lr}"});

      // TODO: stack
      // printArmInstr("sub", {"sp", "sp", 0});

      for (auto *label : func->labels) {
        // TODO: label name uniquer
        os << "." << label->name << ":\n";
        for (auto *inst : label->insts) {
          if (auto *retInst = dyn_cast<AsmReturnInst>(inst)) {
            // TODO: stack
            // printArmInstr("add", {"sp", "sp", 0});

            printArmInstr("pop", {"{lr}"});
            printArmInstr("bx", {"lr"});
            // TODO: constant pool ltorg?
          } else if (auto *movInst = dyn_cast<AsmMoveInst>(inst)) {
            auto reg_dst = cast<PReg>(movInst->dst);
            if (auto *imm = dyn_cast<AsmImm>(movInst->src)) {
              union {
                uint32_t i;
                struct {
                  uint16_t lo;
                  uint16_t hi;
                };
              } u;
              u.i = imm->hexValue;
              printArmInstr("movw", {reg_dst->abiName(), std::to_string(u.lo)});
              if (u.hi > 0)
                printArmInstr(
                    "movt", {reg_dst->abiName(), std::to_string(u.hi)});
            } else {
              olc_unreachable("NYI");
            }
          } else if (auto *binInst = dyn_cast<AsmBinaryInst>(inst)) {
            std::string op;
            switch (binInst->tag) {
            case AsmInst::Add:
              op = "add";
              break;
            case AsmInst::Sub:
              op = "sub";
              break;
            case AsmInst::Mul:
              op = "mul";
              break;
            case AsmInst::Div:
            case AsmInst::Mod:
              olc_unreachable("NYI");
              break;
            default:
              olc_unreachable("Unknown");
            }
            auto reg_dst = cast<PReg>(binInst->dst);
            auto reg_lhs = cast<PReg>(binInst->lhs);
            auto reg_rhs = cast<PReg>(binInst->rhs);
            // os << op << "\t" << x->dst << ", " << x->lhs << ", " << x->rhs;
            printArmInstr(
                op,
                {reg_dst->abiName(), reg_lhs->abiName(), reg_rhs->abiName()});
          } else {
            olc_unreachable("NYI");
          }
        }
      }
    }
  }
};

} // namespace olc
