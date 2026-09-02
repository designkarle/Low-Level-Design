'use strict';
// PROXY — a stand-in with the SAME interface as the real service that adds
// access-control + caching, without the caller (or the real service) knowing.

// ---- Real subject (expensive: a network call) ----
class RemoteUserService {
  fetch(userId) {
    console.log(`    [remote] network call for ${userId} ...`);
    return `profile(${userId})`;
  }
}

// ---- Proxy: same fetch() signature; adds auth then a cache ----
class UserServiceProxy {
  constructor(real, authorized) {
    this.real = real;
    this.authorized = authorized;
    this.cache = {};
  }
  fetch(userId) {
    if (!this.authorized) { console.log('    [proxy] ACCESS DENIED'); return ''; }
    if (userId in this.cache) { console.log(`    [proxy] cache hit for ${userId}`); return this.cache[userId]; }
    const result = this.real.fetch(userId);
    this.cache[userId] = result;
    return result;
  }
}

module.exports = { RemoteUserService, UserServiceProxy };
