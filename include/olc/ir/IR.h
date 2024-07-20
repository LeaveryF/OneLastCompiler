#pragma once

#include <cassert>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>

// 前向声明
struct Use;
struct User;

struct Value {
  enum Tag {
    Add,
    Sub,
    Rsb,
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
    Undef
  } tag;
  Value(Tag tag) : tag(tag) {}
  virtual ~Value() = default;

  std::string name;
  std::list<Use *> uses;

  void addUse(Use *u) { uses.push_back(u); }

  void removeUse(Use *u) { uses.remove(u); }

  void replaceAllUseWith(Value *v);
};

struct User : public Value {
  std::vector<Value *> operands;
  unsigned NumOperands;

  User(Tag tag) : Value(tag), NumOperands(0) {}
  User(Tag tag, std::vector<Value *> operands)
      : Value(tag), operands(std::move(operands)),
        NumOperands(this->operands.size()) {}

  Value *getOperand(unsigned i);
  void setOperand(unsigned i, Value *v);
  void addOperand(Value *v);
  virtual ~User();
};

struct Use {
  Value *value;
  User *user;
  int index;

  Use() : value(nullptr), user(nullptr), index(-1) {}
  Use(Value *v, User *u, int index) : value(v), user(u), index(index) {
    if (v)
      v->addUse(this);
    if (u)
      u->operands.push_back(v);
  }

  void setValue(Value *v) {
    if (value)
      value->removeUse(this);
    value = v;
    if (v)
      v->addUse(this);
  }

  ~Use() {
    if (value)
      value->removeUse(this);
  }
};

struct BasicBlock;

struct Function : User {
  bool isBuiltin;
  std::string name;
  std::list<BasicBlock *> basicBlocks;
  std::list<Function *> caller;
  std::list<Function *> callee;
  Function() : User(Tag::Undef), isBuiltin(false) {}
};

struct Instruction : User {
  BasicBlock *parent;
  Instruction *prev;
  Instruction *next;
  Instruction(Tag tag)
      : User(tag), parent(nullptr), prev(nullptr), next(nullptr) {}
};

struct BinaryInstruction : Instruction {
  BinaryInstruction(Tag tag) : Instruction(tag) {}
  constexpr static const char *LLVM_OPS[14] = {
      /* Add = */ "add",
      /* Sub = */ "sub",
      /* Rsb = */ nullptr,
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

struct BranchInstruction : Instruction {
  Use cond;
  BasicBlock *ifTrue;
  BasicBlock *ifFalse;
  BranchInstruction()
      : Instruction(Tag::Branch), cond(), ifTrue(nullptr), ifFalse(nullptr) {}
};

struct JumpInstruction : Instruction {
  BasicBlock *target;
  JumpInstruction() : Instruction(Tag::Jump), target(nullptr) {}
};

struct ReturnInstruction : Instruction {
  Use ret;
  ReturnInstruction() : Instruction(Tag::Return), ret() {}
};

struct BasicBlock : Value {
  std::list<Instruction *> instructions;
  std::list<BasicBlock *> predecessors;
  std::list<BasicBlock *> successors;
  BasicBlock() : Value(Tag::Undef) {}
};

struct Constant : User {
  int value;
  Constant() : User(Tag::Const) {}
  Constant(int value) : User(Tag::Const), value(value) {}
};

struct GlobalValue : User {
  GlobalValue() : User(Tag::Global) {}
};
