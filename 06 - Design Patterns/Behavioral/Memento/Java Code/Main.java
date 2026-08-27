// =============================================================================
// MEMENTO (Java twin of example.cpp) — the editor saves opaque snapshots; a
// history caretaker stores them and restores on undo.
//
// Build & run:
//   javac Main.java
//   java Main
// =============================================================================
import java.util.ArrayDeque;
import java.util.Deque;

// ---------- Memento: opaque state holder ----------
class EditorMemento {
    private final String state;
    EditorMemento(String state) { this.state = state; }
    String getState() { return this.state; }
}

// ---------- Originator ----------
class TextEditor {
    private String content = "";
    void type(String words) { this.content += words; }
    String getContent() { return this.content; }
    EditorMemento save() { return new EditorMemento(this.content); }   // create snapshot
    void restore(EditorMemento m) { this.content = m.getState(); }     // roll back
}

// ---------- Caretaker ----------
class History {
    private Deque<EditorMemento> snapshots = new ArrayDeque<EditorMemento>();
    void push(EditorMemento m) { this.snapshots.push(m); }
    EditorMemento pop() { return this.snapshots.pop(); }
    boolean isEmpty() { return this.snapshots.isEmpty(); }
}

public class Main {
    public static void main(String[] args) {
        TextEditor editor = new TextEditor();
        History history = new History();

        editor.type("Hello");
        history.push(editor.save());           // checkpoint 1

        editor.type(", world");
        history.push(editor.save());           // checkpoint 2

        editor.type("!!! (oops, too much)");
        System.out.println("  current : " + editor.getContent());

        editor.restore(history.pop());         // undo to checkpoint 2
        System.out.println("  undo -> : " + editor.getContent());

        editor.restore(history.pop());         // undo to checkpoint 1
        System.out.println("  undo -> : " + editor.getContent());
    }
}
