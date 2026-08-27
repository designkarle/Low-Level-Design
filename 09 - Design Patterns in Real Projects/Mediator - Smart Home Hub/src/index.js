'use strict';
// =============================================================================
// Mediator in a real project — a smart-home automation hub. (Node.js)
//   node src/index.js
//
// Sensors report to the hub; the hub runs the rules and drives the actuators.
// Same door-open event does nothing (disarmed) or trips the alarm (armed).
// =============================================================================
const { Light, Thermostat, Alarm, MotionSensor, DoorSensor } = require('./devices');
const { HomeHub } = require('./homeHub');

function demo() {
  const light = new Light(), thermostat = new Thermostat(), alarm = new Alarm();
  const hub = new HomeHub(light, thermostat, alarm);
  const motion = new MotionSensor(hub);
  const door = new DoorSensor(hub);

  console.log('Evening, disarmed:');
  hub.setArmed(false);
  motion.detect(true);
  door.open();

  console.log('\nNight, armed (away):');
  hub.setArmed(true);
  door.open();
}

if (require.main === module) demo();

module.exports = { demo };
