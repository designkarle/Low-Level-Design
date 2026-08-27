// =============================================================================
// MEDIATOR — define an object that centralizes how a set of objects interact.
// Instead of every object referencing every other (an n-to-n mess), they all
// talk to ONE mediator. This loosens coupling and puts coordination in one place.
//
// Domain: air-traffic control. Aircraft never talk to each other directly — they
// request actions via the control tower (mediator), which coordinates the single
// runway so two planes don't land at once.
//
// Build & run:
//   g++ -std=c++14 example.cpp -o example
//   ./example
// =============================================================================
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Aircraft;   // forward declaration

// ---------- Mediator interface ----------
class ControlTower {
public:
    virtual void requestLanding(Aircraft* who) = 0;
    virtual void runwayCleared(Aircraft* who) = 0;
    virtual ~ControlTower() {}
};

// ---------- Colleague ----------
class Aircraft {
private:
    string id;
    ControlTower* tower;
public:
    Aircraft(string id, ControlTower* tower) {
        this->id = id;
        this->tower = tower;
    }
    string getId() { return this->id; }

    void requestLanding() {
        cout << this->id << ": requesting permission to land" << endl;
        this->tower->requestLanding(this);     // talk to the mediator, not other planes
    }
    void leaveRunway() {
        cout << this->id << ": taxied off the runway" << endl;
        this->tower->runwayCleared(this);
    }
    // Called by the mediator:
    void land() { cout << "  " << this->id << ": CLEARED -> landing" << endl; }
    void hold() { cout << "  " << this->id << ": HOLD (runway busy)" << endl; }
};

// ---------- Concrete mediator: owns the coordination logic ----------
class AirportControlTower : public ControlTower {
private:
    bool runwayBusy;
    vector<Aircraft*> queue;
public:
    AirportControlTower() { this->runwayBusy = false; }
    void requestLanding(Aircraft* who) {
        if (this->runwayBusy) {
            who->hold();
            this->queue.push_back(who);         // serialize access to the runway
        } else {
            this->runwayBusy = true;
            who->land();
        }
    }
    void runwayCleared(Aircraft* who) {
        this->runwayBusy = false;
        if (!this->queue.empty()) {             // let the next waiting plane land
            Aircraft* next = this->queue.front();
            this->queue.erase(this->queue.begin());
            this->runwayBusy = true;
            next->land();
        }
    }
};

int main() {
    AirportControlTower tower;
    Aircraft a("AI-101", &tower);
    Aircraft b("MH-202", &tower);
    Aircraft c("UK-303", &tower);

    a.requestLanding();    // runway free -> lands
    b.requestLanding();    // busy -> holds
    c.requestLanding();    // busy -> holds

    cout << "...time passes..." << endl;
    a.leaveRunway();       // frees runway -> next queued plane (b) lands
    b.leaveRunway();       // -> c lands
    return 0;
}
