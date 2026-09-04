'use strict';
// FLYWEIGHT — map markers. The heavy, SHARED part of a marker (its icon: sprite +
// colour + category) is the flyweight; the per-marker part (lat/lng) stays
// outside. A factory hands out one shared icon object per category.

// ---- Flyweight: heavy shared intrinsic state ----
class MarkerIcon {
  constructor(category, color, sprite) {
    this.category = category;
    this.color = color;
    this.sprite = sprite;
  }
  // Extrinsic state (position) is passed in, not stored.
  draw(lat, lng) {
    console.log(`    draw ${this.color} ${this.category} [${this.sprite}] at (${lat}, ${lng})`);
  }
}

// ---- Flyweight factory: one icon per category ----
class IconFactory {
  constructor() { this.pool = new Map(); }
  get(category, color, sprite) {
    if (this.pool.has(category)) return this.pool.get(category);
    const icon = new MarkerIcon(category, color, sprite);
    this.pool.set(category, icon);
    return icon;
  }
  distinctIcons() { return this.pool.size; }
}

module.exports = { MarkerIcon, IconFactory };
