// =============================================================================
// COMMAND (Java twin of example.cpp) — each remote action is an object that can
// execute() and undo(); the invoker keeps an undo history.
//
// Build & run:
//   javac Main.java
//   java Main
// =============================================================================
import java.util.ArrayDeque;
import java.util.Deque;

// ---------- Receivers ----------
class Light {
    private boolean on = false;
    void turnOn()  { this.on = true;  System.out.println("  light ON"); }
    void turnOff() { this.on = false; System.out.println("  light OFF"); }
    boolean isOn() { return this.on; }
}

class Fan {
    private int speedValue = 0;
    void setSpeed(int s) { this.speedValue = s; System.out.println("  fan speed = " + s); }
    int speed() { return this.speedValue; }
}

// ---------- Command interface ----------
interface Command {
    void execute();
    void undo();
}

// ---------- Concrete commands ----------
class LightOnCommand implements Command {
    private Light light;
    private boolean prev;
    LightOnCommand(Light l) { this.light = l; }
    public void execute() { this.prev = this.light.isOn(); this.light.turnOn(); }
    public void undo() { if (this.prev) this.light.turnOn(); else this.light.turnOff(); }
}

class FanSpeedCommand implements Command {
    private Fan fan;
    private int speed;
    private int prev;
    FanSpeedCommand(Fan f, int speed) { this.fan = f; this.speed = speed; }
    public void execute() { this.prev = this.fan.speed(); this.fan.setSpeed(this.speed); }
    public void undo() { this.fan.setSpeed(this.prev); }
}

// ---------- Invoker ----------
class RemoteControl {
    private Deque<Command> history = new ArrayDeque<Command>();
    void press(Command cmd) {
        cmd.execute();
        this.history.push(cmd);          // remember for undo
    }
    void undoLast() {
        if (this.history.isEmpty()) { System.out.println("  nothing to undo"); return; }
        System.out.println("  [undo]");
        this.history.pop().undo();
    }
}

public class Main {
    public static void main(String[] args) {
        Light light = new Light();
        Fan fan = new Fan();
        RemoteControl remote = new RemoteControl();

        remote.press(new LightOnCommand(light));
        remote.press(new FanSpeedCommand(fan, 3));
        remote.press(new FanSpeedCommand(fan, 5));

        System.out.println("Undo twice:");
        remote.undoLast();      // fan 5 -> 3
        remote.undoLast();      // fan 3 -> 0
    }
}
