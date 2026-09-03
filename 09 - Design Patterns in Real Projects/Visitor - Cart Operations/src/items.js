'use strict';
// The cart item types. Each accept(visitor) calls the visitor's per-type method
// (visitBook / visitElectronics / visitGrocery). JS has no overloading, so this
// per-type method name IS the double dispatch the Visitor pattern relies on.
class Book {
  constructor(name, price) { this.name = name; this.price = price; }
  accept(v) { return v.visitBook(this); }
}
class Electronics {
  constructor(name, price) { this.name = name; this.price = price; }
  accept(v) { return v.visitElectronics(this); }
}
class Grocery {
  constructor(name, price) { this.name = name; this.price = price; }
  accept(v) { return v.visitGrocery(this); }
}

module.exports = { Book, Electronics, Grocery };
