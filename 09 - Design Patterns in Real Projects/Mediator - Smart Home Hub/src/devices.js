'use strict';
// The devices. Actuators (Light, Thermostat, Alarm) just do as they're told.
// Sensors (MotionSensor, DoorSensor) report events to the hub (mediator) — they
// never talk to actuators directly.
class Light { on() { console.log('      light ON'); } off() { console.log('      light OFF'); } }
class Thermostat { setTemp(t) { console.log(`      thermostat -> ${t}C`); } }
class Alarm { trigger() { console.log('      ALARM! intruder'); } }

class MotionSensor {
  constructor(hub) { this.hub = hub; }
  detect(night) {
    console.log(`  motion detected (${night ? 'night' : 'day'})`);
    this.hub.notify('motion', night ? 'night' : 'day');
  }
}

class DoorSensor {
  constructor(hub) { this.hub = hub; }
  open() { console.log('  door opened'); this.hub.notify('door', 'open'); }
}

module.exports = { Light, Thermostat, Alarm, MotionSensor, DoorSensor };
