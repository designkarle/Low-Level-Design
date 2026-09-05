'use strict';
// COMMAND — text-editor operations as objects with execute()/undo(). The
// receiver (Document) does the work; each command records just enough to
// reverse itself. A MacroCommand groups commands and undoes them in reverse.

// ---- Receiver ----
class Document {
  constructor() { this.text = ''; }
  insert(s) { this.text += s; }
  removeLast(n) { this.text = this.text.slice(0, Math.max(0, this.text.length - n)); }
  tail(n) { return this.text.slice(-n); }
}

// ---- Commands ----
class InsertCommand {
  constructor(doc, text) { this.doc = doc; this.textVal = text; }
  execute() { this.doc.insert(this.textVal); }
  undo() { this.doc.removeLast(this.textVal.length); }
}

class DeleteLastCommand {
  constructor(doc, n) { this.doc = doc; this.n = n; this.removed = ''; }
  execute() { this.removed = this.doc.tail(this.n); this.doc.removeLast(this.n); }
  undo() { this.doc.insert(this.removed); }
}

class MacroCommand {
  constructor() { this.cmds = []; }
  add(c) { this.cmds.push(c); }
  execute() { for (const c of this.cmds) c.execute(); }
  undo() { for (let i = this.cmds.length - 1; i >= 0; i--) this.cmds[i].undo(); }
}

module.exports = { Document, InsertCommand, DeleteLastCommand, MacroCommand };
