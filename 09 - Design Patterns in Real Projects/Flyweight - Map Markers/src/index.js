'use strict';
// =============================================================================
// Flyweight in a real project — map markers. (Node.js)
//   node src/index.js
//
// Five markers on a map share just two icon objects (restaurant, fuel) — the
// position is the only per-marker data.
// =============================================================================
const { IconFactory } = require('./icons');

function demo() {
  const factory = new IconFactory();
  const resto = factory.get('restaurant', 'red', 'fork.png');
  const fuel = factory.get('fuel', 'green', 'pump.png');

  const markers = [
    { lat: 12.97, lng: 77.59, icon: resto },
    { lat: 12.98, lng: 77.60, icon: resto },
    { lat: 12.96, lng: 77.58, icon: fuel },
    { lat: 12.99, lng: 77.61, icon: fuel },
    { lat: 12.95, lng: 77.57, icon: factory.get('restaurant', 'red', 'fork.png') }, // reuse
  ];

  for (const m of markers) m.icon.draw(m.lat, m.lng);
  console.log(`${markers.length} markers share only ${factory.distinctIcons()} icon objects.`);
}

if (require.main === module) demo();

module.exports = { demo };
