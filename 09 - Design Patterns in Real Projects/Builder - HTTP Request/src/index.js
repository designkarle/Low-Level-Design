'use strict';
// =============================================================================
// Builder in a real project — a fluent HTTP request builder. (Node.js)
//   node src/index.js
//
// A chained, readable way to construct a complex request; invalid combinations
// (GET + body) are rejected at build() time.
// =============================================================================
const { HttpRequestBuilder } = require('./httpRequest');

function demo() {
  console.log('GET with query + headers:');
  new HttpRequestBuilder('https://api.shop.com/products')
    .query('category', 'books').query('page', '2')
    .header('Accept', 'application/json').timeout(5000)
    .build().describe();

  console.log('POST with a JSON body:');
  new HttpRequestBuilder('https://api.shop.com/orders')
    .method('POST')
    .header('Content-Type', 'application/json').header('Authorization', 'Bearer xyz')
    .body('{"sku":"BOOK-42","qty":1}')
    .build().describe();

  console.log('Invalid (GET with a body) is rejected at build():');
  try { new HttpRequestBuilder('https://x').body('oops').build(); }
  catch (e) { console.log(`  ${e.message}`); }
}

if (require.main === module) demo();

module.exports = { demo };
