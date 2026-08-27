// =============================================================================
// MEDIATOR (Java twin of example.cpp) — aircraft coordinate through a control
// tower (mediator) instead of talking to each other.
//
// Build & run:
//   javac Main.java
//   java Main
// =============================================================================
import java.util.ArrayList;
import java.util.List;

// ---------- Mediator interface ----------
interface ControlTower {
    void requestLanding(Aircraft who);
    void runwayCleared(Aircraft who);
}

// ---------- Colleague ----------
class Aircraft {
    private String id;
    private ControlTower tower;
    Aircraft(String id, ControlTower tower) { this.id = id; this.tower = tower; }
    String getId() { return this.id; }

    void requestLanding() {
        System.out.println(this.id + ": requesting permission to land");
        this.tower.requestLanding(this);       // talk to the mediator, not other planes
    }
    void leaveRunway() {
        System.out.println(this.id + ": taxied off the runway");
        this.tower.runwayCleared(this);
    }
    void land() { System.out.println("  " + this.id + ": CLEARED -> landing"); }
    void hold() { System.out.println("  " + this.id + ": HOLD (runway busy)"); }
}

// ---------- Concrete mediator ----------
class AirportControlTower implements ControlTower {
    private boolean runwayBusy = false;
    private List<Aircraft> queue = new ArrayList<Aircraft>();
    public void requestLanding(Aircraft who) {
        if (this.runwayBusy) {
            who.hold();
            this.queue.add(who);                // serialize access to the runway
        } else {
            this.runwayBusy = true;
            who.land();
        }
    }
    public void runwayCleared(Aircraft who) {
        this.runwayBusy = false;
        if (!this.queue.isEmpty()) {            // let the next waiting plane land
            Aircraft next = this.queue.remove(0);
            this.runwayBusy = true;
            next.land();
        }
    }
}

public class Main {
    public static void main(String[] args) {
        AirportControlTower tower = new AirportControlTower();
        Aircraft a = new Aircraft("AI-101", tower);
        Aircraft b = new Aircraft("6E-202", tower);
        Aircraft c = new Aircraft("UK-303", tower);

        a.requestLanding();    // runway free -> lands
        b.requestLanding();    // busy -> holds
        c.requestLanding();    // busy -> holds

        System.out.println("...time passes...");
        a.leaveRunway();       // frees runway -> next queued plane (b) lands
        b.leaveRunway();       // -> c lands
    }
}
