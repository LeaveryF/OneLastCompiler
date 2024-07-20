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
struct Function;
struct Instruction;

struct Value {
  enum Tag {
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
    Const,
    Global,
    Param,
    FunctionVal,
    BasicBlockVal,
    Undef
  } tag;
  Value(Tag tag) : tag(tag) {}
  virtual ~Value() = default;

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

  BasicBlock(Function *parent) : Value(Tag::BasicBlockVal), parent(parent) {}

  template <typename InstT, typename... Args> InstT *create(Args &&...args) {
    auto *inst = new InstT(this, std::forward<Args>(args)...);
    instructions.push_back(inst);
    return inst;
  }
};

struct Argument : Value {
  std::string argName;

  Argument(std::string const &argName) : Value(Tag::Param), argName(argName) {}

  static bool classof(const Value *V) { return V->tag == Value::Param; }
};

struct Function : User {
  bool isBuiltin;
  std::string fnName;
  std::list<Argument *> args;
  std::list<BasicBlock *> basicBlocks;

  Function(std::string const &fnName) : User(Tag::FunctionVal), fnName(fnName) {
    basicBlocks.push_back(new BasicBlock(this));
  }

  static bool classof(const Value *V) { return V->tag == Value::FunctionVal; }

  BasicBlock *getEntryBlock() { return basicBlocks.front(); }
};

struct Instruction : User {
  BasicBlock *parent;
  Instruction(BasicBlock *bb, Tag tag, std::vector<Value *> operands)
      : User(tag, std::move(operands)), parent(bb) {}
};

struct BinaryInst : Instruction {
  BinaryInst(BasicBlock *bb, Tag tag, Value *lhs, Value *rhs)
      : Instruction(bb, tag, {lhs, rhs}) {
    assert(tag >= Tag::Add && tag <= Tag::Or);
  }
  constexpr static const char *LLVM_OPS[14] = {
      /* Add = */ "add",
      /* Sub = */ "sub",
      /* Mul = */ "mul",
      /* Div = */ "sdiv",
      /* Mod = */ "srem",
      /* Lt = */ "icmp slt",
      /* Le = */ "icmp sle",
      /* Ge = */ "icmp sge",
      /* Gt = */ "icmp sgt",
      /* Eq = */ "icmp eq",
      /* Ne = */ "icmp ne",
      /* And = */ "and",
      /* Or = */ "or",
  };
};

struct BranchInst : Instruction {
  BranchInst(
      BasicBlock *bb, Value *cond, BasicBlock *ifTrue, BasicBlock *ifFalse)
      : Instruction(bb, Tag::Branch, {cond, ifTrue, ifFalse}) {}
};

struct JumpInst : Instruction {
  JumpInst(BasicBlock *bb, BasicBlock *target)
      : Instruction(bb, Tag::Jump, {target}) {}
};

struct ReturnInst : Instruction {
  ReturnInst(BasicBlock *bb, Value *val)
      : Instruction(bb, Tag::Return, {val}) {}
};

struct Constant : Value {
  // just a base class, no actual features
  Constant(Value::Tag tag) : Value(tag) {}

  static bool classof(const Value *V) { return isa<ConstantValue>(V); }
};

struct ConstantValue : Constant {
  std::variant<int, float> value;

  ConstantValue(std::variant<int, float> value)
      : Constant(Tag::Const), value(value) {}

  bool isInt() const { return value.index() == 0; }
  bool isFloat() const { return value.index() == 1; }
  int getInt() const { return std::get<int>(value); }
  float getFloat() const { return std::get<float>(value); }
};

struct GlobalValue : User {
  GlobalValue() : User(Tag::Global) {}
};

} // namespace olc
