'use strict';
// =============================================================================
// Visitor in a real project — operations over cart items. (Node.js)
//   node src/index.js
//
// Two visitors (invoice + tax) run over a mixed cart; each item dispatches to the
// right per-type method on the visitor.
// =============================================================================
const { Book, Electronics, Grocery } = require('./items');
const { TaxVisitor, InvoiceVisitor } = require('./visitors');

function demo() {
  const cart = [new Book('Clean Code', 500), new Electronics('Earbuds', 2000), new Grocery('Rice 5kg', 400)];

  console.log('Invoice:');
  const invoice = new InvoiceVisitor();
  for (const item of cart) item.accept(invoice);

  const tax = new TaxVisitor();
  for (const item of cart) item.accept(tax);
  console.log(`Total tax: Rs ${tax.tax}`);
}

if (require.main === module) demo();

module.exports = { demo };
