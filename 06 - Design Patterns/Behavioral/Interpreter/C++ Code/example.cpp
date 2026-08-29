// =============================================================================
// INTERPRETER — given a language, define a representation for its grammar plus an
// interpreter that evaluates sentences. Each grammar rule becomes a class;
// evaluating = walking the resulting tree.
//
// Domain: a tiny arithmetic evaluator. We build (3 + (10 - 4)) * 2 as a tree of
// Expression objects and evaluate it. This is how calculators, rule engines, and
// query languages work internally.
//
// Build & run:
//   g++ -std=c++14 example.cpp -o example
//   ./example
// =============================================================================
#include <iostream>
#include <string>

using namespace std;

// ---------- Abstract expression ----------
class Expression {
public:
    virtual int interpret() = 0;
    virtual string toString() = 0;
    virtual ~Expression() {}
};

// ---------- Terminal expression: a literal number ----------
class Number : public Expression {
private:
    int v;
public:
    Number(int v) { this->v = v; }
    int interpret() { return this->v; }
    string toString() { return to_string(this->v); }
};

// ---------- Non-terminal expressions: combine sub-expressions ----------
class Add : public Expression {
private:
    Expression* l;
    Expression* r;
public:
    Add(Expression* l, Expression* r) { this->l = l; this->r = r; }
    int interpret() { return this->l->interpret() + this->r->interpret(); }
    string toString() { return "(" + this->l->toString() + " + " + this->r->toString() + ")"; }
    ~Add() { delete this->l; delete this->r; }
};

class Subtract : public Expression {
private:
    Expression* l;
    Expression* r;
public:
    Subtract(Expression* l, Expression* r) { this->l = l; this->r = r; }
    int interpret() { return this->l->interpret() - this->r->interpret(); }
    string toString() { return "(" + this->l->toString() + " - " + this->r->toString() + ")"; }
    ~Subtract() { delete this->l; delete this->r; }
};

class Multiply : public Expression {
private:
    Expression* l;
    Expression* r;
public:
    Multiply(Expression* l, Expression* r) { this->l = l; this->r = r; }
    int interpret() { return this->l->interpret() * this->r->interpret(); }
    string toString() { return "(" + this->l->toString() + " * " + this->r->toString() + ")"; }
    ~Multiply() { delete this->l; delete this->r; }
};

int main() {
    // Build the tree for: (3 + (10 - 4)) * 2
    Expression* expr =
        new Multiply(
            new Add(new Number(3), new Subtract(new Number(10), new Number(4))),
            new Number(2));

    cout << "  expression: " << expr->toString() << endl;
    cout << "  result:     " << expr->interpret() << endl;

    delete expr;   // recursively deletes the whole tree
    return 0;
}
