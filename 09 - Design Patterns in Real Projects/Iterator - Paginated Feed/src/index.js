'use strict';
// =============================================================================
// Iterator in a real project — a lazily-paginated API feed. (Node.js)
//   node src/index.js
//
// 7 items over 3 pages. The [api] fetch lines show pages arriving lazily as the
// for...of loop consumes items — not all up front.
// =============================================================================
const { FeedApi } = require('./feedApi');

function demo() {
  const api = new FeedApi(7, 3);     // 7 items over 3 pages (3+3+1)
  console.log('Scrolling the feed (pages fetched lazily as you go):');
  let n = 0;
  for (const item of api) { console.log(`  - ${item}`); n++; }
  console.log(`Read ${n} items total.`);
}

if (require.main === module) demo();

module.exports = { demo };
