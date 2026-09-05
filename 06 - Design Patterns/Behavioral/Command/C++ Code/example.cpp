// =============================================================================
// COMMAND — encapsulate a request as an object. This lets you parameterize an
// invoker with different requests, queue or log them, and support UNDO.
//
// Domain: a smart-home remote. Pressing a button executes a Command (turn the
// light on, set the fan speed). Because each action is an object that knows how
// to execute() AND undo() itself, the remote gets undo for free.
//
// Build & run:
//   g++ -std=c++14 example.cpp -o example
//   ./example
// =============================================================================
#include <iostream>
#include <stack>

using namespace std;

// ---------- Receivers: the objects that do the real work ----------
class Light {
private:
    bool on;
public:
    Light() { this->on = false; }
    void turnOn()  { this->on = true;  cout << "  light ON" << endl; }
    void turnOff() { this->on = false; cout << "  light OFF" << endl; }
    bool isOn() { return this->on; }
};

class Fan {
private:
    int speedValue;
public:
    Fan() { this->speedValue = 0; }
    void setSpeed(int s) { this->speedValue = s; cout << "  fan speed = " << s << endl; }
    int speed() { return this->speedValue; }
};

// ---------- Command interface ----------
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() {}
};

// ---------- Concrete commands: bind a receiver + remember how to reverse ----------
class LightOnCommand : public Command {
private:
    Light* light;
    bool prev;
public:
    LightOnCommand(Light* l) { this->light = l; this->prev = false; }
    void execute() { this->prev = this->light->isOn(); this->light->turnOn(); }
    void undo() { if (this->prev) this->light->turnOn(); else this->light->turnOff(); }
};

class FanSpeedCommand : public Command {
private:
    Fan* fan;
    int speed;
    int prev;
public:
    FanSpeedCommand(Fan* f, int speed) { this->fan = f; this->speed = speed; this->prev = 0; }
    void execute() { this->prev = this->fan->speed(); this->fan->setSpeed(this->speed); }
    void undo() { this->fan->setSpeed(this->prev); }
};

// ---------- Invoker: triggers commands and keeps an undo history ----------
class RemoteControl {
private:
    stack<Command*> history;
public:
    void press(Command* cmd) {
        cmd->execute();
        this->history.push(cmd);          // remember for undo
    }
    void undoLast() {
        if (this->history.empty()) { cout << "  nothing to undo" << endl; return; }
        cout << "  [undo]" << endl;
        Command* cmd = this->history.top();
        this->history.pop();
        cmd->undo();
        delete cmd;
    }
    ~RemoteControl() {
        while (!this->history.empty()) { delete this->history.top(); this->history.pop(); }
    }
};

int main() {
    Light light;
    Fan fan;
    RemoteControl remote;

    remote.press(new LightOnCommand(&light));
    remote.press(new FanSpeedCommand(&fan, 3));
    remote.press(new FanSpeedCommand(&fan, 5));

    cout << "Undo twice:" << endl;
    remote.undoLast();      // fan 5 -> 3
    remote.undoLast();      // fan 3 -> 0
    return 0;
}
