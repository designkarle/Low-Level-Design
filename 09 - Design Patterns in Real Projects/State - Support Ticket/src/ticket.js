'use strict';
// The CONTEXT. Each action is delegated to the current state; the ticket adopts
// whatever state comes back, or reports the action as illegal.
const { OpenState } = require('./ticketState');

class Ticket {
  constructor(id) { this.id = id; this.state = new OpenState(); }
  _apply(next, action) {
    if (!next) { console.log(`  ticket ${this.id}: cannot '${action}' from ${this.state.name()}`); return; }
    console.log(`  ticket ${this.id}: ${action} -> ${next.name()}`);
    this.state = next;
  }
  assign() { this._apply(this.state.assign(), 'assign'); }
  resolve() { this._apply(this.state.resolve(), 'resolve'); }
  close() { this._apply(this.state.close(), 'close'); }
  reopen() { this._apply(this.state.reopen(), 'reopen'); }
}

module.exports = { Ticket };
