'use strict';
// MEMENTO — game save / checkpoints. The character produces a snapshot of its
// own state (the memento) and can restore from one; the SaveManager (caretaker)
// just stores snapshots without ever reading their fields.
//
// JS has no friend access, so we keep the memento opaque by CONVENTION: the
// character returns a FROZEN plain object that only it interprets.
class GameCharacter {
  constructor() { this.level = 1; this.hp = 100; this.pos = 'Village'; }
  gainLevel() { this.level += 1; this.hp = 100; }
  takeDamage(d) { this.hp = Math.max(0, this.hp - d); }
  moveTo(p) { this.pos = p; }
  status(label) { console.log(`  ${label}: level ${this.level}, hp ${this.hp}, at ${this.pos}`); }
  save() { return Object.freeze({ level: this.level, hp: this.hp, pos: this.pos }); }
  restore(m) { this.level = m.level; this.hp = m.hp; this.pos = m.pos; }
}

class SaveManager {
  constructor() { this.slots = {}; }
  save(slot, m) { this.slots[slot] = m; console.log(`  [save] slot '${slot}'`); }
  load(slot) { console.log(`  [load] slot '${slot}'`); return this.slots[slot]; }
}

module.exports = { GameCharacter, SaveManager };
