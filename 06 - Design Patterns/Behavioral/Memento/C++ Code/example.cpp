// =============================================================================
// MEMENTO — capture an object's internal state in a separate object (the
// memento) so it can be restored later, WITHOUT exposing the object's internals.
// This is how undo / checkpoint features are built.
//
// Domain: a text editor. It can save snapshots and undo back to them. The
// snapshot (Memento) is opaque to everyone except the editor — the history
// keeper stores it but can't read or tamper with the editor's private state.
//
// Build & run:
//   g++ -std=c++14 example.cpp -o example
//   ./example
// =============================================================================
#include <iostream>
#include <stack>
#include <string>

using namespace std;

// ---------- Memento: opaque state holder ----------
// Only the TextEditor (its friend) can build a memento and read its content.
// The caretaker can hold/copy a memento but cannot inspect or modify it.
class EditorMemento {
private:
    friend class TextEditor;
    string state;
    EditorMemento(string state) { this->state = state; }
    string getState() { return this->state; }
};

// ---------- Originator: the object whose state we snapshot ----------
class TextEditor {
private:
    string content;
public:
    void type(string words) { this->content += words; }
    string getContent() { return this->content; }

    EditorMemento save() { return EditorMemento(this->content); }   // create snapshot
    void restore(EditorMemento m) { this->content = m.getState(); } // roll back
};

// ---------- Caretaker: keeps the history, never peeks inside a memento ----------
class History {
private:
    stack<EditorMemento> snapshots;
public:
    void push(EditorMemento m) { this->snapshots.push(m); }
    EditorMemento pop() {
        EditorMemento m = this->snapshots.top();
        this->snapshots.pop();
        return m;
    }
    bool empty() { return this->snapshots.empty(); }
};

int main() {
    TextEditor editor;
    History history;

    editor.type("Hello");
    history.push(editor.save());           // checkpoint 1

    editor.type(", world");
    history.push(editor.save());           // checkpoint 2

    editor.type("!!! (oops, too much)");
    cout << "  current : " << editor.getContent() << endl;

    editor.restore(history.pop());         // undo to checkpoint 2
    cout << "  undo -> : " << editor.getContent() << endl;

    editor.restore(history.pop());         // undo to checkpoint 1
    cout << "  undo -> : " << editor.getContent() << endl;
    return 0;
}
