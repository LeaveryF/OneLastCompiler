#include <olc/ir/IR.h>
#include <olc/passes/Pass.h>
#include <olc/passes/Utils.h>

#include <unordered_map>

namespace olc {

class CanonicalizePass : public FunctionPass {
public:
  CanonicalizePass() : FunctionPass(&ID) {}

  // [C, V] -> [V, C]
  // Sub[V, C] -> Add[V, -C]
  // Add[V, 0] -> V
  //
  Value *canonicalizeBinary(BinaryInst *inst) const {
    auto tag = inst->tag;
    auto *lhs = inst->getLHS(), *rhs = inst->getRHS();
    bool lhsConst = isa<ConstantValue>(lhs), rhsConst = isa<ConstantValue>(rhs);
    assert((!lhsConst || !rhsConst) && "should run constfold first");
    if (lhsConst && inst->isCommutable()) {
      std::swap(lhs, rhs);
      std::swap(lhsConst, rhsConst);
    }

    if (tag == Value::Tag::Sub) {
      if (rhsConst) {
        tag = Value::Tag::Add;
        rhs = cast<ConstantValue>(rhs)->map([](auto &&arg) { return -arg; });
      }
    } else if (tag == Value::Tag::Add) {
      if (rhsConst && cast<ConstantValue>(lhs)->getInt() == 0) {
        return rhs;
      }
    }

    inst->setOperand(0, lhs);
    inst->setOperand(1, rhs);
  }

  Value *canonicalizePhi(PhiInst *inst) const {
    std::vector<Value *> incomingValues;
    for (unsigned i = 0; i < inst->getNumIncomingValues(); i++)
      // NOTE: To use with GCM, the Phi with undef should not be simplified.
      // if (auto val = inst->getIncomingValue(i); !isa<Undef>(val))
      if (auto val = inst->getIncomingValue(i); true)
        incomingValues.push_back(val);
    for (auto *val : incomingValues) {
      if (val != incomingValues.front()) {
        return inst;
      }
    }
    return incomingValues.front();
  }

  Value *canonicalize(Instruction *inst) const {
    if (auto *binInst = dyn_cast<BinaryInst>(inst)) {
      return canonicalizeBinary(binInst);
    } else if (auto *phiInst = dyn_cast<PhiInst>(inst)) {
      return canonicalizePhi(phiInst);
    }
    return inst;
  }

  bool runOnFunction(Function &function) override {
    bool changed = false;

    auto rpo = getFunctionRPO(&function);

    for (auto *bb : rpo) {
      for (auto itInst = bb->instructions.begin();
           itInst != bb->instructions.end();) {
        auto itInstNext = std::next(itInst);
        auto *inst = *itInst;

        if (auto *newInst = canonicalize(inst); newInst == inst) {
          inst->replaceAllUseWith(newInst);
          itInst = bb->instructions.erase(itInst);
          changed = true;
        }

        itInst = itInstNext;
      }
    }

    return changed;
  }

  std::string getName() const override { return "CanonicalizePass"; }

private:
  static const void *ID;
};

const void *CanonicalizePass::ID = reinterpret_cast<void *>(0xCA7071C0);

} // namespace olc
