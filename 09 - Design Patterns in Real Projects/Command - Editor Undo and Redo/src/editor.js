'use strict';
// INVOKER — runs commands and keeps undo/redo stacks. It doesn't know what any
// command *does*, only that it has execute()/undo() — that decoupling is what
// makes generic undo/redo possible.
class Editor {
  constructor(doc) { this.doc = doc; this.undoStack = []; this.redoStack = []; }
  run(c, label) { c.execute(); this.undoStack.push(c); this.redoStack = []; this.report(label); }
  undo() {
    if (!this.undoStack.length) return console.log('  (nothing to undo)');
    const c = this.undoStack.pop(); c.undo(); this.redoStack.push(c); this.report('undo');
  }
  redo() {
    if (!this.redoStack.length) return console.log('  (nothing to redo)');
    const c = this.redoStack.pop(); c.execute(); this.undoStack.push(c); this.report('redo');
  }
  report(label) { console.log(`  ${label} -> "${this.doc.text}"`); }
}

module.exports = { Editor };
