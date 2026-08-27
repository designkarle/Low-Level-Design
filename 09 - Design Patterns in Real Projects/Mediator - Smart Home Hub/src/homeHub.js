'use strict';
// HomeHub — the concrete MEDIATOR. It owns the automation rules: when a sensor
// fires, the hub decides which actuators react. Devices stay decoupled — adding
// a rule changes only the hub, not the devices.
class HomeHub {
  constructor(light, thermostat, alarm) {
    this.light = light;
    this.thermostat = thermostat;
    this.alarm = alarm;
    this.armed = false;
  }
  setArmed(armed) { this.armed = armed; console.log(`  [hub] armed=${armed ? 'yes' : 'no'}`); }
  notify(sender, event) {
    if (sender === 'motion' && event === 'night') { this.light.on(); this.thermostat.setTemp(22); }
    else if (sender === 'door' && event === 'open') {
      if (this.armed) this.alarm.trigger();
      else console.log('      (disarmed: welcome home)');
    }
  }
}

module.exports = { HomeHub };
