'use strict';
// INTERPRETER — a tiny boolean rule language over a context object. Terminal
// expressions read the context; non-terminal expressions combine sub-expressions.
// eval(ctx) walks the tree. This is how discount/feature-flag rule engines work.

// ---- Terminal expressions ----
class Flag {
  constructor(key) { this.key = key; }
  eval(ctx) { return !!ctx[this.key]; }
}
class AtLeast {
  constructor(key, n) { this.key = key; this.n = n; }
  eval(ctx) { return (ctx[this.key] || 0) >= this.n; }
}

// ---- Non-terminal expressions ----
class And {
  constructor(a, b) { this.a = a; this.b = b; }
  eval(ctx) { return this.a.eval(ctx) && this.b.eval(ctx); }
}
class Or {
  constructor(a, b) { this.a = a; this.b = b; }
  eval(ctx) { return this.a.eval(ctx) || this.b.eval(ctx); }
}

module.exports = { Flag, AtLeast, And, Or };
