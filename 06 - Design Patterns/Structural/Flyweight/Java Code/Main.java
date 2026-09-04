// =============================================================================
// FLYWEIGHT (Java twin of example.cpp) — many trees share a few heavy TreeType
// objects (intrinsic state); only x/y is stored per tree (extrinsic state).
//
// Build & run:
//   javac Main.java
//   java Main
// =============================================================================
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

// ---------- Flyweight: the heavy, SHARED, intrinsic state ----------
class TreeType {
    private String name;
    private String texture;
    private String color;
    TreeType(String name, String texture, String color) {
        this.name = name;
        this.texture = texture;
        this.color = color;
    }
    void render(int x, int y) {                  // extrinsic x/y supplied by the caller
        System.out.println("  draw " + this.color + " " + this.name
                + " [tex:" + this.texture + "] at (" + x + "," + y + ")");
    }
}

// ---------- Flyweight factory: returns shared instances, creating on demand ----
class TreeTypeFactory {
    private Map<String, TreeType> pool = new HashMap<String, TreeType>();
    TreeType get(String name, String texture, String color) {
        String key = name + "|" + texture + "|" + color;
        if (this.pool.containsKey(key)) return this.pool.get(key);   // reuse
        TreeType tt = new TreeType(name, texture, color);
        this.pool.put(key, tt);                                      // store once
        return tt;
    }
    int distinctTypes() { return this.pool.size(); }
}

// ---------- Context: the lightweight per-object part ----------
class Tree {
    int x;
    int y;
    TreeType type;   // reference to a shared flyweight
    Tree(int x, int y, TreeType type) { this.x = x; this.y = y; this.type = type; }
    void render() { this.type.render(this.x, this.y); }
}

public class Main {
    public static void main(String[] args) {
        TreeTypeFactory factory = new TreeTypeFactory();
        List<Tree> forest = new ArrayList<Tree>();

        // Plant 5 trees but only 2 *kinds* — so only 2 heavy TreeType objects exist.
        TreeType oak = factory.get("Oak", "oak.png", "green");
        TreeType pine = factory.get("Pine", "pine.png", "dark-green");

        forest.add(new Tree(10, 20, oak));
        forest.add(new Tree(15, 25, oak));     // reuses the SAME TreeType
        forest.add(new Tree(30, 12, pine));
        forest.add(new Tree(33, 18, pine));
        forest.add(new Tree(40, 40, factory.get("Oak", "oak.png", "green")));   // reuse again

        for (Tree t : forest) t.render();
        System.out.println(forest.size() + " trees rendered using only "
                + factory.distinctTypes() + " shared TreeType objects.");
    }
}
