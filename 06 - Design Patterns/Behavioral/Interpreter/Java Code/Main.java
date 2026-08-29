// =============================================================================
// INTERPRETER (Java twin of example.cpp) — build (3 + (10 - 4)) * 2 as a tree of
// Expression objects and evaluate it.
//
// Build & run:
//   javac Main.java
//   java Main
// =============================================================================

// ---------- Abstract expression ----------
interface Expression {
    int interpret();
    String toString();
}

// ---------- Terminal expression ----------
class Number implements Expression {
    private int v;
    Number(int v) { this.v = v; }
    public int interpret() { return this.v; }
    public String toString() { return String.valueOf(this.v); }
}

// ---------- Non-terminal expressions ----------
class Add implements Expression {
    private Expression l;
    private Expression r;
    Add(Expression l, Expression r) { this.l = l; this.r = r; }
    public int interpret() { return this.l.interpret() + this.r.interpret(); }
    public String toString() { return "(" + this.l.toString() + " + " + this.r.toString() + ")"; }
}

class Subtract implements Expression {
    private Expression l;
    private Expression r;
    Subtract(Expression l, Expression r) { this.l = l; this.r = r; }
    public int interpret() { return this.l.interpret() - this.r.interpret(); }
    public String toString() { return "(" + this.l.toString() + " - " + this.r.toString() + ")"; }
}

class Multiply implements Expression {
    private Expression l;
    private Expression r;
    Multiply(Expression l, Expression r) { this.l = l; this.r = r; }
    public int interpret() { return this.l.interpret() * this.r.interpret(); }
    public String toString() { return "(" + this.l.toString() + " * " + this.r.toString() + ")"; }
}

public class Main {
    public static void main(String[] args) {
        // Build the tree for: (3 + (10 - 4)) * 2
        Expression expr =
            new Multiply(
                new Add(new Number(3), new Subtract(new Number(10), new Number(4))),
                new Number(2));

        System.out.println("  expression: " + expr.toString());
        System.out.println("  result:     " + expr.interpret());
    }
}
