'use strict';
// =============================================================================
// Proxy in a real project — caching + access-control proxy. (Node.js)
//   node src/index.js
//
// The proxy short-circuits a repeat fetch from its cache, and denies an
// unauthorized client — the real service is only hit when it must be.
// =============================================================================
const { RemoteUserService, UserServiceProxy } = require('./userService');

function demo() {
  const remote = new RemoteUserService();
  const proxy = new UserServiceProxy(remote, true);

  console.log('First fetch u1 (miss -> remote):');  console.log(`  => ${proxy.fetch('u1')}`);
  console.log('Second fetch u1 (cache hit):');       console.log(`  => ${proxy.fetch('u1')}`);
  console.log('Fetch u2 (miss -> remote):');         console.log(`  => ${proxy.fetch('u2')}`);

  console.log('Unauthorized client:');
  const denied = new UserServiceProxy(remote, false);
  console.log(`  => '${denied.fetch('u1')}'`);
}

if (require.main === module) demo();

module.exports = { demo };
