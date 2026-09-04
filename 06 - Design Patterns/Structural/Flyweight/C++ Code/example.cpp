// =============================================================================
// FLYWEIGHT — share common ("intrinsic") state across many objects so you can
// support huge numbers of them with little memory. The per-object ("extrinsic")
// state is passed in from outside instead of stored on every instance.
//
// Domain: a map renders a forest of trees. Each tree's mesh/texture/color is
// shared by thousands of trees (intrinsic, stored once) while only x/y position
// is unique per tree (extrinsic). We store the shared part ONCE in a factory.
//
// Build & run:
//   g++ -std=c++14 example.cpp -o example
//   ./example
// =============================================================================
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// ---------- Flyweight: the heavy, SHARED, intrinsic state ----------
class TreeType {                       // imagine this holds a big mesh + textures
private:
    string name;
    string texture;
    string color;
public:
    TreeType(string name, string texture, string color) {
        this->name = name;
        this->texture = texture;
        this->color = color;
    }
    void render(int x, int y) {        // extrinsic x/y supplied by the caller
        cout << "  draw " << this->color << " " << this->name
             << " [tex:" << this->texture << "] at (" << x << "," << y << ")" << endl;
    }
};

// ---------- Flyweight factory: returns shared instances, creating on demand ----
class TreeTypeFactory {
private:
    map<string, TreeType*> pool;
public:
    TreeType* get(string name, string texture, string color) {
        string key = name + "|" + texture + "|" + color;
        if (this->pool.find(key) != this->pool.end()) return this->pool[key];   // reuse
        TreeType* tt = new TreeType(name, texture, color);
        this->pool[key] = tt;                                                   // store once
        return tt;
    }
    int distinctTypes() { return (int)this->pool.size(); }
    ~TreeTypeFactory() {
        map<string, TreeType*>::iterator it;
        for (it = this->pool.begin(); it != this->pool.end(); ++it) delete it->second;
    }
};

// ---------- Context: the lightweight per-object part ----------
struct Tree {
    int x;
    int y;
    TreeType* type;   // pointer to a shared flyweight (NOT owned here)
    void render() { this->type->render(this->x, this->y); }
};

int main() {
    TreeTypeFactory factory;
    vector<Tree> forest;

    // Plant 5 trees but only 2 *kinds* — so only 2 heavy TreeType objects exist.
    TreeType* oak = factory.get("Oak", "oak.png", "green");
    TreeType* pine = factory.get("Pine", "pine.png", "dark-green");

    Tree t1 = {10, 20, oak};  forest.push_back(t1);
    Tree t2 = {15, 25, oak};  forest.push_back(t2);   // reuses the SAME TreeType
    Tree t3 = {30, 12, pine}; forest.push_back(t3);
    Tree t4 = {33, 18, pine}; forest.push_back(t4);
    Tree t5 = {40, 40, factory.get("Oak", "oak.png", "green")};  // reuse again
    forest.push_back(t5);

    for (int i = 0; i < (int)forest.size(); i++) forest[i].render();
    cout << forest.size() << " trees rendered using only "
         << factory.distinctTypes() << " shared TreeType objects." << endl;
    return 0;
}
