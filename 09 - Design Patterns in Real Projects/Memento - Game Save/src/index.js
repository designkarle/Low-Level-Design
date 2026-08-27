'use strict';
// =============================================================================
// Memento in a real project — game save / checkpoints. (Node.js)
//   node src/index.js
//
// Save a checkpoint, take a near-fatal hit, then reload to undo the damage.
// =============================================================================
const { GameCharacter, SaveManager } = require('./game');

function demo() {
  const hero = new GameCharacter();
  const saves = new SaveManager();

  hero.gainLevel(); hero.gainLevel(); hero.moveTo('Forest');
  hero.status('after grinding');
  saves.save('checkpoint', hero.save());

  hero.moveTo("Dragon's Lair");
  hero.takeDamage(95);
  hero.status('after the dragon fight');

  hero.restore(saves.load('checkpoint'));
  hero.status('after reload');
}

if (require.main === module) demo();

module.exports = { demo };
