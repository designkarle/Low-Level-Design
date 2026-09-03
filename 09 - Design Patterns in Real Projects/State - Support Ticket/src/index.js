'use strict';
// =============================================================================
// State in a real project — support-ticket lifecycle. (Node.js)
//   node src/index.js
//
// Open -> InProgress -> Resolved -> Closed, with reopen, and illegal actions
// (resolve from Open, assign from Closed) cleanly rejected.
// =============================================================================
const { Ticket } = require('./ticket');

function demo() {
  const t = new Ticket('TICK-1');
  t.resolve();   // illegal from Open
  t.assign();    // -> InProgress
  t.resolve();   // -> Resolved
  t.reopen();    // -> InProgress
  t.resolve();   // -> Resolved
  t.close();     // -> Closed
  t.assign();    // illegal from Closed
  t.reopen();    // -> InProgress
}

if (require.main === module) demo();

module.exports = { demo };
