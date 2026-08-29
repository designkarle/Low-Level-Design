'use strict';
// =============================================================================
// Interpreter in a real project — a discount / feature-flag rule engine. (Node.js)
//   node src/index.js
//
// Build the rule (isMember AND orders>=5) OR isVIP as an expression tree, then
// evaluate the SAME tree against different user contexts.
// =============================================================================
const { Flag, AtLeast, And, Or } = require('./expressions');

function demo() {
  // Rule: (isMember AND orders >= 5) OR isVIP
  const rule = new Or(new And(new Flag('isMember'), new AtLeast('orders', 5)), new Flag('isVIP'));

  const alice = { isMember: 1, orders: 7, isVIP: 0 };
  const bob = { isMember: 1, orders: 2, isVIP: 0 };
  const carol = { isMember: 0, orders: 0, isVIP: 1 };

  console.log('Rule: (isMember AND orders>=5) OR isVIP');
  console.log(`  Alice eligible? ${rule.eval(alice) ? 'yes' : 'no'}`);
  console.log(`  Bob   eligible? ${rule.eval(bob) ? 'yes' : 'no'}`);
  console.log(`  Carol eligible? ${rule.eval(carol) ? 'yes' : 'no'}`);
}

if (require.main === module) demo();

module.exports = { demo };
