#include <olc/ir/IR.h>

namespace olc {

void Value::removeUse(Use const &u) {
  uses.remove_if([=](Use const &use) { return use == u; });
}

void Value::replaceAllUseWith(Value *v) {
  for (auto u : uses) {
    u.user->setOperand(u.index, v);
  }
}

Value *User::getOperand(unsigned i) const {
  assert(i < getNumOperands());
  return operands[i];
}

void User::setOperand(unsigned i, Value *v) {
  assert(i < getNumOperands());
  Value *oldValue = operands[i];
  if (oldValue) {
    oldValue->removeUse(Use(this, i));
  }
  operands[i] = v;
  if (v) {
    v->addUse(Use(this, i));
  }
}

void User::addOperand(Value *v) {
  auto new_idx = operands.size();
  operands.push_back(v);
  if (v) {
    v->addUse(Use(this, new_idx));
  }
}

} // namespace olc
