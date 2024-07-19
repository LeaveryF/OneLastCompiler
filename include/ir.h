#pragma once

#include <memory>
#include <string>
#include <vector>
#include <list>

// 前向声明
struct Use;
struct User;

struct Value {
    enum Tag { Add, Sub, Rsb, Mul, Div, Mod, Lt, Le, Ge, Gt, Eq, Ne, And, Or, Branch, Jump, Return, GetElementPtr, Load, Store, Call, Alloca, Phi, MemOp, MemPhi, Const, Global, Param, Undef, } tag;
    Value(Tag tag) : tag(tag) {}
    virtual ~Value() = default;

    std::string name;
    std::list<Use*> uses;

    void addUse(Use *u) {
        uses.push_back(u);
    }

    void removeUse(Use *u) {
        uses.remove(u);
    }

    void replaceAllUseWith(Value *v);
};

struct User : public Value {
    std::vector<Value *> operands;
    unsigned NumOperands;

    User(Tag tag) : Value(tag) {}
    User(Tag tag, std::vector<Value *> operands) : Value(tag), operands(operands), NumOperands(operands.size()) {
        //
    }
    Value *getOperand(unsigned i);
    void setOperand(unsigned i, Value *v);
    void addOperand(Value *v);
    virtual ~User() = default;
};

struct Use {
    Value *value;
    User *user;
    int index;

    Use() : value(nullptr), user(nullptr) {}
    Use(Value *v, User *u, int index) : value(v), user(u), index(index) {
        if (v) v->addUse(this);
        u->addOperand(u);
    }
    void setValue(Value *v) {
        if (value) value->removeUse(this);
        value = v;
        if (v) v->addUse(this);
    }

    ~Use() {
        if (value) value->removeUse(this);
    }
};

void Value::replaceAllUseWith(Value *v) {
    for (auto u : uses) {
        u->setValue(v);
    }
}
Value *User::getOperand(unsigned i) {
    return operands[i];
}

void User::setOperand(unsigned i, Value *v) {
    // assert i < NumOperands && i >= 0;
    //从原Value中删去这条use
    for (auto u : operands[i]->uses) {
        if (u->user == this) {
            operands[i]->removeUse(u);
        }
    }
    operands[i] = v;
    v->addUse(new Use(v, this, i));
}

void User::addOperand(Value *v) {
    operands.push_back(v);
    v->addUse(new Use(v, this, operands.size() - 1));
}

struct BasicBlock;

struct Function : User {
    bool isBuiltin;
    std::list<BasicBlock*> basicBlocks;
    // caller, callee
    std::list<Function*> caller;
    std::list<Function*> callee;
    Function() : User(Tag::Undef), isBuiltin(false) {}
};

struct Instruction : User {
    BasicBlock *parent;
    Instruction *prev;
    Instruction *next;
    Instruction(Tag tag) : User(tag), parent(nullptr), prev(nullptr), next(nullptr) {}
};

struct BinaryInstruction : Instruction {
    BinaryInstruction(Tag tag) : Instruction(tag) {}
};

struct BranchInstruction : Instruction {
    Use cond;
    BasicBlock *ifTrue;
    BasicBlock *ifFalse;
    BranchInstruction() : Instruction(Tag::Branch), cond(), ifTrue(nullptr), ifFalse(nullptr) {}
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
    std::list<Instruction*> instructions;
    std::list<BasicBlock*> predecessors;
    std::list<BasicBlock*> successors;
    BasicBlock() : Value(Tag::Undef) {}
};

struct Constant : User {
    Constant() : User(Tag::Const) {}
};

struct GlobalValue : User {
    GlobalValue() : User(Tag::Global) {}
};