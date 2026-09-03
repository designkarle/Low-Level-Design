// =============================================================================
// STATE (Java twin of example.cpp) — a vending machine delegates to its current
// state object, which also decides the next state.
//
// Build & run:
//   javac Main.java
//   java Main
// =============================================================================

// ---------- State interface ----------
interface State {
    void insertCoin(VendingMachine m);
    void selectProduct(VendingMachine m);
    String name();
}

// ---------- Context ----------
class VendingMachine {
    private State state;
    private int stockValue;
    VendingMachine(int stock) {
        this.stockValue = stock;
        this.state = new IdleState();
    }
    void setState(State s) { this.state = s; }
    void insertCoin()    { System.out.print("[" + this.state.name() + "] "); this.state.insertCoin(this); }
    void selectProduct() { System.out.print("[" + this.state.name() + "] "); this.state.selectProduct(this); }
    int stock() { return this.stockValue; }
    void decrementStock() { this.stockValue = this.stockValue - 1; }
}

// ---------- Concrete states ----------
class IdleState implements State {
    public void insertCoin(VendingMachine m) {
        System.out.println("coin accepted");
        m.setState(new HasCoinState());           // Idle -> HasCoin
    }
    public void selectProduct(VendingMachine m) { System.out.println("insert a coin first"); }
    public String name() { return "Idle"; }
}

class HasCoinState implements State {
    public void insertCoin(VendingMachine m) { System.out.println("coin already inserted"); }
    public void selectProduct(VendingMachine m) {
        m.decrementStock();
        System.out.println("dispensing... (" + m.stock() + " left)");
        if (m.stock() == 0) m.setState(new SoldOutState());
        else                m.setState(new IdleState());
    }
    public String name() { return "HasCoin"; }
}

class SoldOutState implements State {
    public void insertCoin(VendingMachine m) { System.out.println("machine sold out - coin returned"); }
    public void selectProduct(VendingMachine m) { System.out.println("machine sold out"); }
    public String name() { return "SoldOut"; }
}

public class Main {
    public static void main(String[] args) {
        VendingMachine m = new VendingMachine(2);
        m.selectProduct();     // Idle: needs a coin
        m.insertCoin();        // Idle -> HasCoin
        m.selectProduct();     // dispense, 1 left -> Idle
        m.insertCoin();        // Idle -> HasCoin
        m.selectProduct();     // dispense, 0 left -> SoldOut
        m.insertCoin();        // SoldOut: coin returned
    }
}
