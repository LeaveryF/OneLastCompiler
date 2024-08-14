#pragma once

#include <olc/Support.h>
#include <olc/ir/IR.h>

#include <list>
#include <set>
#include <string>
#include <vector>

namespace olc {

enum class AsmPredicate {
  Al, // All the time
  Eq,
  Ne,
  Lt,
  Le,
  Gt,
  Ge,
};

enum class AsmType : bool {
  I32,
  F32,
};

struct AsmValue {
  enum class Tag {
    VReg,
    PReg,
    Imm,
  } tag;

  AsmValue(Tag tag) : tag(tag) {}
};

struct PReg;
struct VReg;

struct AsmReg : AsmValue {
  AsmType type;
  int id;
  AsmReg(Tag tag, AsmType type, int id) : AsmValue(tag), type(type), id(id) {}

  static bool classof(const AsmValue *v) {
    return v->tag == Tag::VReg || v->tag == Tag::PReg;
  }

  static VReg *makeVReg(AsmType type);
  static PReg *makePReg(AsmType type, int id);

  static PReg *sp() { return makePReg(AsmType::I32, 13); }
  static PReg *lr() { return makePReg(AsmType::I32, 14); }
  static PReg *pc() { return makePReg(AsmType::I32, 15); }
};

struct VReg : AsmReg {
  VReg(AsmType type, int id) : AsmReg(Tag::VReg, type, id) {}

  static bool classof(const AsmValue *v) { return v->tag == Tag::VReg; }
};

struct PReg : AsmReg {
  PReg(AsmType type, int id) : AsmReg(Tag::PReg, type, id) {}

  static bool classof(const AsmValue *v) { return v->tag == Tag::PReg; }

  std::string abiName() const {
    assert(id >= 0 && "Invalid reg!");
    if (type == AsmType::F32) {
      return "s" + std::to_string(id);
    } else {
      return "r" + std::to_string(id);
    }
  }
};

struct AsmImm : AsmValue {
  uint32_t hexValue;

  AsmImm(uint32_t hexValue) : AsmValue(Tag::Imm), hexValue(hexValue) {}

  static bool classof(const AsmValue *v) { return v->tag == Tag::Imm; }
};

struct AsmInst : IListNode<AsmInst> {
  enum class Tag {
    Add,
    Sub,
    Mul,
    Div,
    Mod,
    Cmp,
    Branch,
    Jump,
    Return,
    Move,
    Load,
    Store,
    Call,
    LoadGlobal,
    String,
  } tag;

  AsmInst(Tag tag) : tag(tag) {}

  virtual std::vector<AsmValue **> getDefs() = 0;
  virtual std::vector<AsmValue **> getUses() = 0;
};

struct AsmLabel : IList<AsmInst> {
  std::string name;
  // other informations
  std::vector<AsmLabel *> preds, succs;

  AsmLabel(std::string name) : name(name) {}
};

struct AsmBinaryInst : AsmInst {
  AsmValue *dst = nullptr, *lhs = nullptr, *rhs = nullptr;

  AsmBinaryInst(Tag tag) : AsmInst(tag) {
    assert(tag == Tag::Add || tag == Tag::Sub || tag == Tag::Mul || tag == Tag::Div || tag == Tag::Mod);
  }
  static bool classof(const AsmInst *v) {
    return v->tag == Tag::Add || v->tag == Tag::Sub || v->tag == Tag::Mul ||
           v->tag == Tag::Div || v->tag == Tag::Mod;
  }

  std::vector<AsmValue **> getDefs() override { return {&dst}; }
  std::vector<AsmValue **> getUses() override { return {&lhs, &rhs}; }
};

struct AsmCompareInst : AsmInst {
  AsmValue *lhs = nullptr, *rhs = nullptr;

  AsmCompareInst() : AsmInst(Tag::Cmp) {}
  static bool classof(const AsmInst *v) { return v->tag == Tag::Cmp; }

  std::vector<AsmValue **> getDefs() override { return {}; }
  std::vector<AsmValue **> getUses() override { return {&lhs, &rhs}; }
};

struct AsmBranchInst : AsmInst {
  AsmPredicate pred = AsmPredicate::Al;
  AsmLabel *trueTarget = nullptr;
  AsmLabel *falseTarget = nullptr;

  AsmBranchInst() : AsmInst(Tag::Branch) {}
  static bool classof(const AsmInst *v) { return v->tag == Tag::Branch; }

  std::vector<AsmValue **> getDefs() override { return {}; }
  std::vector<AsmValue **> getUses() override { return {}; }
};

struct AsmJumpInst : AsmInst {
  AsmLabel *target = nullptr;

  AsmJumpInst(AsmLabel *target) : AsmInst(Tag::Jump), target(target) {}
  static bool classof(const AsmInst *v) { return v->tag == Tag::Jump; }

  std::vector<AsmValue **> getDefs() override { return {}; }
  std::vector<AsmValue **> getUses() override { return {}; }
};

struct AsmReturnInst : AsmInst {
  AsmReturnInst() : AsmInst(Tag::Return) {}
  static bool classof(const AsmInst *v) { return v->tag == Tag::Return; }

  std::vector<AsmValue **> getDefs() override { return {}; }
  std::vector<AsmValue **> getUses() override { return {}; }
};

struct AsmAccess : AsmInst {
  AsmValue *addr = nullptr, *offset = nullptr;
  int32_t shift = 0;
  AsmPredicate pred = AsmPredicate::Al;

  AsmAccess(AsmInst::Tag tag) : AsmInst(tag) {}
  static bool classof(const AsmInst *v) {
    return v->tag == Tag::Load || v->tag == Tag::Store;
  }
};

struct AsmLoadInst : AsmAccess {
  AsmValue *dst = nullptr;

  AsmLoadInst() : AsmAccess(Tag::Load) {}
  static bool classof(const AsmInst *v) { return v->tag == Tag::Load; }

  std::vector<AsmValue **> getDefs() override { return {&dst}; }
  std::vector<AsmValue **> getUses() override { return {&addr, &offset}; }
};

struct AsmStoreInst : AsmAccess {
  AsmValue *src = nullptr;

  AsmStoreInst() : AsmAccess(Tag::Store) {}
  static bool classof(const AsmInst *v) { return v->tag == Tag::Store; }

  std::vector<AsmValue **> getDefs() override { return {}; }
  std::vector<AsmValue **> getUses() override { return {&src, &addr, &offset}; }
};

struct AsmMoveInst : AsmInst {
  AsmValue *src = nullptr, *dst = nullptr;
  // TODO: shift

  AsmMoveInst() : AsmInst(Tag::Move) {}
  static bool classof(const AsmInst *v) { return v->tag == Tag::Move; }

  std::vector<AsmValue **> getDefs() override { return {&dst}; }
  std::vector<AsmValue **> getUses() override { return {&src}; }
};

struct AsmCallInst : AsmInst {
  std::string callee;
  std::set<PReg *> callDefs, callUses;

  AsmCallInst(std::string callee) : AsmInst(Tag::Call), callee(callee) {}
  static bool classof(const AsmInst *v) { return v->tag == Tag::Call; }

  std::vector<AsmValue **> getDefs() override { return {}; }
  std::vector<AsmValue **> getUses() override { return {}; }
};

struct AsmFunc {
  std::string name;
  std::list<AsmLabel *> labels;
  bool isBuiltin;

  // other states
  int stackSize = 0;

  AsmFunc(std::string const &name) : name(name) {}
};

struct AsmModule {
  std::list<AsmFunc *> funcs;
  // Uses IR constructs to pass through
  std::list<GlobalVariable *> globals;

  AsmFunc *getFunction(std::string const &name) const {
    for (auto *func : funcs) {
      if (func->name == name) {
        return func;
      }
    }
    return nullptr;
  }
};

} // namespace olc
