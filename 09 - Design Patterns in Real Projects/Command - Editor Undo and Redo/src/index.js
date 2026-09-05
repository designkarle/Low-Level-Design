'use strict';
// =============================================================================
// Command in a real project — editor undo / redo / macros. (Node.js)
//   node src/index.js
//
// Type, undo, redo, delete, and run a macro that the invoker can undo as a unit.
// =============================================================================
const { Document, InsertCommand, DeleteLastCommand, MacroCommand } = require('./commands');
const { Editor } = require('./editor');

function demo() {
  const doc = new Document();
  const editor = new Editor(doc);

  editor.run(new InsertCommand(doc, 'Hello'), "type 'Hello'");
  editor.run(new InsertCommand(doc, ' World'), "type ' World'");
  editor.undo();                                  // -> "Hello"
  editor.redo();                                  // -> "Hello World"
  editor.run(new DeleteLastCommand(doc, 6), 'delete 6');   // -> "Hello"
  editor.undo();                                  // -> "Hello World"

  const macro = new MacroCommand();
  macro.add(new InsertCommand(doc, '!!!'));
  macro.add(new InsertCommand(doc, '??'));
  editor.run(macro, "macro(+'!!!' +'??')");        // -> "Hello World!!!??"
  editor.undo();                                  // undoes the whole macro
}

if (require.main === module) demo();

module.exports = { demo };
