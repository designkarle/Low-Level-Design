'use strict';
// STATE — the support-ticket lifecycle. Each state returns the next state for a
// legal action, or null to reject it. No giant switch on a status field — the
// legal transitions live in the state classes themselves.
class TicketState {
  name() { throw new Error('abstract'); }
  assign() { return null; }
  resolve() { return null; }
  close() { return null; }
  reopen() { return null; }
}

class OpenState extends TicketState {
  name() { return 'Open'; }
  assign() { return new InProgressState(); }
}
class InProgressState extends TicketState {
  name() { return 'InProgress'; }
  resolve() { return new ResolvedState(); }
}
class ResolvedState extends TicketState {
  name() { return 'Resolved'; }
  close() { return new ClosedState(); }
  reopen() { return new InProgressState(); }
}
class ClosedState extends TicketState {
  name() { return 'Closed'; }
  reopen() { return new InProgressState(); }
}

module.exports = { TicketState, OpenState, InProgressState, ResolvedState, ClosedState };
