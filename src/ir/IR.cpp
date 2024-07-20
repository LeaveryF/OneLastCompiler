#include <olc/ir/IR.h>

void Value::replaceAllUseWith(Value *v) {
  for (auto *u : uses) {
    u->setValue(v);
  }
}

Value *User::getOperand(unsigned i) {
  assert(i < NumOperands);
  return operands[i];
}

void User::setOperand(unsigned i, Value *v) {
  assert(i < NumOperands);
  Value *oldValue = operands[i];
  if (oldValue) {
    oldValue->removeUse(new Use(oldValue, this, i));
  }
  operands[i] = v;
  if (v) {
    v->addUse(new Use(v, this, i));
  }
}

void User::addOperand(Value *v) {
  operands.push_back(v);
  if (v) {
    v->addUse(new Use(v, this, operands.size() - 1));
  }
  NumOperands++;
}
// FIXME:
User::~User() = default;
