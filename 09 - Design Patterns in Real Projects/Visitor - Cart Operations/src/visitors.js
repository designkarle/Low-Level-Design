'use strict';
// Two operations over the cart, each a VISITOR. Adding an operation = a new
// visitor class; the item types never change. (The trade-off: adding a new item
// type means touching every visitor — Visitor favours stable type sets.)

// ---- Tax visitor (rates vary per type) ----
class TaxVisitor {
  constructor() { this.tax = 0; }
  visitBook() {}                                  // 0% (exempt)
  visitElectronics(e) { this.tax += e.price * 0.18; }
  visitGrocery(g) { this.tax += g.price * 0.05; }
}

// ---- Invoice visitor ----
class InvoiceVisitor {
  visitBook(b) { this._line('Book', b.name, b.price); }
  visitElectronics(e) { this._line('Electronics', e.name, e.price); }
  visitGrocery(g) { this._line('Grocery', g.name, g.price); }
  _line(type, name, price) { console.log(`    ${type}: ${name} - Rs ${price}`); }
}

module.exports = { TaxVisitor, InvoiceVisitor };
