#include <olc/ir/IR.h>

namespace olc {

bool Value::isDefVar() const {
  if (auto *inst = dyn_cast<Instruction>(this)) {
    return !inst->getType()->isVoidTy();
  } else {
    return isa<Argument>(this);
  }
}

void Value::addUse(User *user, int index) { uses.push_back(Use(user, index)); }

void Value::removeUse(User *user, int index) {
  auto u = Use(user, index);
  uses.remove_if([=](Use const &use) { return use == u; });
}

void Value::replaceAllUseWith(Value *v) {
  for (auto u : uses) {
    // delay the remove to avoid invalidation of iterator
    u.user->setOperandWithoutRemoveUse(u.index, v);
  }
  // clear uses now
  uses.clear();
}

Value *User::getOperand(unsigned i) const {
  assert(i < getNumOperands());
  return operands[i];
}

void User::setOperand(unsigned i, Value *v) {
  assert(i < getNumOperands());
  if (Value *oldValue = operands[i])
    oldValue->removeUse(this, i);

  setOperandWithoutRemoveUse(i, v);
}

void User::setOperandWithoutRemoveUse(unsigned i, Value *v) {
  assert(i < getNumOperands());
  operands[i] = v;
  if (v)
    v->addUse(this, i);
}

void User::addOperand(Value *v) {
  auto newIndex = operands.size();
  operands.push_back(v);
  if (v) {
    v->addUse(this, newIndex);
  }
}

} // namespace olc
