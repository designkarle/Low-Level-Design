// =============================================================================
// STATE — allow an object to alter its behaviour when its internal state
// changes; the object appears to change its class. Each state is a class; the
// context delegates to the current state, which also decides the next state.
// This replaces a tangle of if/else on a "status" field.
//
// Domain: a vending machine. Its behaviour for insertCoin()/selectProduct()
// depends entirely on whether it's idle, has a coin, or is sold out.
//
// Build & run:
//   g++ -std=c++14 example.cpp -o example
//   ./example
// =============================================================================
#include <iostream>
#include <string>

using namespace std;

class VendingMachine;   // forward declaration

// ---------- State interface ----------
class State {
public:
    virtual void insertCoin(VendingMachine* m) = 0;
    virtual void selectProduct(VendingMachine* m) = 0;
    virtual string name() = 0;
    virtual ~State() {}
};

// ---------- Context ----------
class VendingMachine {
private:
    State* state;
    int stockValue;
public:
    VendingMachine(int stock);
    void setState(State* s) {
        if (this->state != nullptr) delete this->state;
        this->state = s;
    }
    void insertCoin()    { cout << "[" << this->state->name() << "] "; this->state->insertCoin(this); }
    void selectProduct() { cout << "[" << this->state->name() << "] "; this->state->selectProduct(this); }
    int stock() { return this->stockValue; }
    void decrementStock() { this->stockValue = this->stockValue - 1; }
    ~VendingMachine() { if (this->state != nullptr) delete this->state; }
};

// ---------- Concrete states ----------
class IdleState : public State {
public:
    void insertCoin(VendingMachine* m);
    void selectProduct(VendingMachine* m) { cout << "insert a coin first" << endl; }
    string name() { return "Idle"; }
};

class HasCoinState : public State {
public:
    void insertCoin(VendingMachine* m) { cout << "coin already inserted" << endl; }
    void selectProduct(VendingMachine* m);
    string name() { return "HasCoin"; }
};

class SoldOutState : public State {
public:
    void insertCoin(VendingMachine* m) { cout << "machine sold out - coin returned" << endl; }
    void selectProduct(VendingMachine* m) { cout << "machine sold out" << endl; }
    string name() { return "SoldOut"; }
};

// ---- transitions (defined out-of-line now that all states are known) ----
void IdleState::insertCoin(VendingMachine* m) {
    cout << "coin accepted" << endl;
    m->setState(new HasCoinState());          // Idle -> HasCoin
}

void HasCoinState::selectProduct(VendingMachine* m) {
    m->decrementStock();
    cout << "dispensing... (" << m->stock() << " left)" << endl;
    if (m->stock() == 0) m->setState(new SoldOutState());
    else                 m->setState(new IdleState());
}

VendingMachine::VendingMachine(int stock) {
    this->stockValue = stock;
    this->state = new IdleState();
}

int main() {
    VendingMachine m(2);
    m.selectProduct();     // Idle: needs a coin
    m.insertCoin();        // Idle -> HasCoin
    m.selectProduct();     // dispense, 1 left -> Idle
    m.insertCoin();        // Idle -> HasCoin
    m.selectProduct();     // dispense, 0 left -> SoldOut
    m.insertCoin();        // SoldOut: coin returned
    return 0;
}
