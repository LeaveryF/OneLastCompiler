#pragma once

#include <cassert>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <variant>
#include <vector>

#include <olc/Support.h>

namespace olc {

// 前向声明
struct Use;
struct User;
struct ConstantValue;
struct ConstantArray;
struct Function;
struct Instruction;

struct Value {
  enum class Tag {
    // constant
    ConstValue,
    ConstArray,
    Global,
    Function,

    // misc
    Undef,
    Param,
    BasicBlock,

    // instructions
    Add,
    Sub,
    Mul,
    Div,
    Mod,
    Lt,
    Le,
    Ge,
    Gt,
    Eq,
    Ne,
    And,
    Or,
    Rsb,
    Branch,
    Jump,
    Return,
    GetElementPtr,
    Load,
    Store,
    Call,
    Alloca,
    Phi,
    MemOp,
    MemPhi,

    // anchors
    BeginConst = ConstValue,
    EndConst = Global,
    BeginInst = Add,
    EndInst = MemPhi,
    BeginBinOp = Add,
    EndBinOp = Or,
  } tag;
  Value(Tag tag) : tag(tag) {}

  std::list<Use> uses;

  void addUse(User *user, int index);

  void removeUse(User *user, int index);

  void replaceAllUseWith(Value *v);
};

struct User : public Value {
  std::vector<Value *> operands;

  User(Tag tag, std::vector<Value *> operands = {})
      : Value(tag), operands(std::move(operands)) {
    for (auto i = 0u; i < this->operands.size(); ++i)
      if (auto &operand = this->operands[i])
        operand->addUse(this, i);
  }

  static bool classof(const Value *V) { return isa<Instruction>(V); }

  Value *getOperand(unsigned i) const;
  void setOperand(unsigned i, Value *v);
  void addOperand(Value *v);
  size_t getNumOperands() const { return operands.size(); }

private:
  void setOperandWithoutRemoveUse(unsigned i, Value *v);
  friend struct Value;
};

struct Use {
  User *user;
  int index;

  Use(User *u, int index) : user(u), index(index) {}
  bool operator==(Use const &rhs) const {
    return user == rhs.user && index == rhs.index;
  }
};

struct BasicBlock : Value {
  Function *parent;
  std::list<Instruction *> instructions;
  // TODO: maintain pred succ states
  std::list<BasicBlock *> predecessors;
  std::list<BasicBlock *> successors;

  BasicBlock(Function *parent) : Value(Tag::BasicBlock), parent(parent) {}

  template <typename InstT, typename... Args> InstT *create(Args &&...args) {
    auto *inst = new InstT(this, std::forward<Args>(args)...);
    instructions.push_back(inst);
    return inst;
  }
};

struct Argument : Value {
  std::string argName;

  Argument(std::string const &argName) : Value(Tag::Param), argName(argName) {}

  static bool classof(const Value *V) { return V->tag == Tag::Param; }
};

struct Function : User {
  bool isBuiltin;
  std::string fnName;
  std::list<Argument *> args;
  std::list<BasicBlock *> basicBlocks;

  Function(std::string const &fnName) : User(Tag::Function), fnName(fnName) {
    basicBlocks.push_back(new BasicBlock(this));
  }

  static bool classof(const Value *V) { return V->tag == Tag::Function; }

  BasicBlock *getEntryBlock() { return basicBlocks.front(); }
};

struct Instruction : User {
  BasicBlock *parent;
  Instruction(BasicBlock *bb, Tag tag, std::vector<Value *> operands)
      : User(tag, std::move(operands)), parent(bb) {}

  static bool classof(const Value *V) {
    return V->tag >= Tag::BeginInst && V->tag <= Tag::EndInst;
  }
};

struct BinaryInst : Instruction {
  BinaryInst(BasicBlock *bb, Tag tag, Value *lhs, Value *rhs)
      : Instruction(bb, tag, {lhs, rhs}) {
    assert(tag >= Tag::Add && tag <= Tag::Or);
  }

  static bool classof(const Value *V) {
    return V->tag >= Tag::BeginBinOp && V->tag <= Tag::EndBinOp;
  }
};

struct BranchInst : Instruction {
  BranchInst(
      BasicBlock *bb, Value *cond, BasicBlock *ifTrue, BasicBlock *ifFalse)
      : Instruction(bb, Tag::Branch, {cond, ifTrue, ifFalse}) {}

  static bool classof(const Value *V) { return V->tag == Tag::Branch; }
};

struct JumpInst : Instruction {
  JumpInst(BasicBlock *bb, BasicBlock *target)
      : Instruction(bb, Tag::Jump, {target}) {}

  static bool classof(const Value *V) { return V->tag == Tag::Jump; }
};

struct ReturnInst : Instruction {
  ReturnInst(BasicBlock *bb, Value *val)
      : Instruction(bb, Tag::Return, {val}) {}

  static bool classof(const Value *V) { return V->tag == Tag::Return; }
};

struct Constant : Value {
  // just a base class, no actual features
  Constant(Value::Tag tag) : Value(tag) {}

  static bool classof(const Value *V) {
    return V->tag >= Tag::BeginConst && V->tag <= Tag::EndConst;
  }
};

struct ConstantValue : Constant {
  std::variant<int, float> value;

  ConstantValue(std::variant<int, float> value)
      : Constant(Tag::ConstValue), value(value) {}

  bool isInt() const { return value.index() == 0; }
  bool isFloat() const { return value.index() == 1; }
  int getInt() const { return std::get<int>(value); }
  float getFloat() const { return std::get<float>(value); }

  static bool classof(const Value *V) { return V->tag == Tag::ConstValue; }
};

struct ConstantArray : Constant {
  std::vector<ConstantValue *> values;

  ConstantArray(std::vector<ConstantValue *> values)
      : Constant(Tag::ConstArray), values(std::move(values)) {}

  static bool classof(const Value *V) { return V->tag == Tag::ConstArray; }
};

// TODO: model globals
struct GlobalValue : User {
  GlobalValue() : User(Tag::Global) {}

  static bool classof(const Value *V) { return V->tag == Tag::Global; }
};

} // namespace olc
