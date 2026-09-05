'use strict';
// BUILDER — a fluent HTTP request builder. The builder accumulates optional
// parts step by step and validates invariants once, in build().

class HttpRequest {
  constructor() {
    this.methodVal = 'GET';
    this.url = '';
    this.headers = {};
    this.queryParams = {};
    this.bodyVal = '';
    this.timeoutMs = 30000;
  }
  _query() {
    const keys = Object.keys(this.queryParams);
    if (!keys.length) return '';
    return '?' + keys.map((k) => `${k}=${this.queryParams[k]}`).join('&');
  }
  describe() {
    console.log(`  ${this.methodVal} ${this.url}${this._query()}`);
    for (const k of Object.keys(this.headers)) console.log(`    ${k}: ${this.headers[k]}`);
    if (this.bodyVal) console.log(`    body: ${this.bodyVal}`);
    console.log(`    timeout: ${this.timeoutMs}ms`);
  }
}

class HttpRequestBuilder {
  constructor(url) { this.req = new HttpRequest(); this.req.url = url; }
  method(m) { this.req.methodVal = m; return this; }      // each setter returns `this`
  header(k, v) { this.req.headers[k] = v; return this; }
  query(k, v) { this.req.queryParams[k] = v; return this; }
  body(b) { this.req.bodyVal = b; return this; }
  timeout(ms) { this.req.timeoutMs = ms; return this; }
  build() {
    if (!this.req.url) throw new Error('url is required');
    if (this.req.bodyVal && this.req.methodVal === 'GET') throw new Error('GET requests cannot have a body');
    return this.req;
  }
}

module.exports = { HttpRequest, HttpRequestBuilder };
