#pragma once

#include <memory>
#include <string>
#include <vector>
#include <list>

struct Value {
    enum Tag { Add, Sub, Rsb, Mul, Div, Mod, Lt, Le, Ge, Gt, Eq, Ne, And, Or, Branch, Jump, Return, GetElementPtr, Load, Store, Call, Alloca, Phi, MemOp, MemPhi, Const, Global, Param, Undef, } tag;
    Value(Tag tag) : tag(tag) {}

    std::string name;
    std::list<Use*> uses;

    void addUse(Use *u);
    void removeUse(Use *u);

    void replaceAllUseWith(Value *v) {
        for (auto u : uses) {
            u->set(v);
        }
    }
};

struct User : public Value {
    std::list<Use*> uses;
    unsigned NumOperands;

    User(Tag tag) : Value(tag) {}
};

struct Use {
    Value *value;
    User *user;

    Use() {}
    Use(Value *v, User *u) : value(v), user(u) {
        if(v) v->addUse(this);
    }
    void set(Value *v) {
        if (value) value->removeUse(this);
        value = v;
        if (v) v->addUse(this);
    }

    ~Use() {
        if (value) value->removeUse(this);
    }
};

struct BasicBlock : Value {
    std::list<Instruction*> instructions;
    std::list<BasicBlock*> predecessors;
    std::list<BasicBlock*> successors;
    BasicBlock() : Value(Tag::Undef) {}
};

struct Constant : User {
    //
};

struct GlobalValue : User {
    //
};

struct Function : Value {
    bool isBuiltin;
    std::list<BasicBlock*> basicBlocks;
    // caller, callee
    std::list<Function*> caller;
    std::list<Function*> callee;
    Function() : Value(Tag::Undef) {}
};

struct Instruction : User {
    BasicBlock *parent;
    Instruction *prev;
    Instruction *next;
    Instruction() : User(Tag::Undef) {}
};

struct BinaryInstruction : Instruction {
    // Use lhs;
    // Use rhs;
    // 应写为辅助函数
    BinaryInstruction(Tag tag) : Instruction() {}
};

struct BranchInstruction : Instruction {
    Use cond;
    BasicBlock *ifTrue;
    BasicBlock *ifFalse;
    BranchInstruction() : Instruction() {}
};

struct JumpInstruction : Instruction {
    BasicBlock *target;
    JumpInstruction() : Instruction() {}
};

struct ReturnInstruction : Instruction {
    Use ret;
    ReturnInstruction() : Instruction() {}
};

struct Function : User {
    //
};