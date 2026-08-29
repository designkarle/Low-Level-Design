'use strict';
// ITERATOR — a lazily-paginated API feed. Exposing [Symbol.iterator] as a
// generator lets callers `for...of` the feed while pages are fetched on demand
// (you only pay for the pages you actually scroll to).
class FeedApi {
  constructor(total, pageSize) { this.total = total; this.pageSize = pageSize; }

  fetchPage(p) {
    const start = p * this.pageSize;
    if (start >= this.total) return [];
    console.log(`    [api] fetch page ${p}`);
    const out = [];
    for (let i = start; i < start + this.pageSize && i < this.total; i++) out.push(`post#${i + 1}`);
    return out;
  }

  // Make the feed iterable: for...of fetches pages lazily.
  *[Symbol.iterator]() {
    let page = 0, buffer = this.fetchPage(page++);
    while (buffer.length) {
      for (const item of buffer) yield item;
      buffer = this.fetchPage(page++);
    }
  }
}

module.exports = { FeedApi };
