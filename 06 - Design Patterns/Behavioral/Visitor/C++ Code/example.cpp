// =============================================================================
// VISITOR — represent an operation to perform on the elements of an object
// structure. Visitor lets you add NEW operations to a class hierarchy WITHOUT
// modifying the element classes — the new operation lives in a visitor class.
//
// Domain: a vector-graphics document of Shapes (Circle, Rectangle). We want to
// add operations — total area, export to SVG — without editing the shape classes
// each time. Each operation is a Visitor.
//
// Build & run:
//   g++ -std=c++14 example.cpp -o example
//   ./example
// =============================================================================
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Circle;       // forward decls so the visitor can name concrete elements
class Rectangle;

// ---------- Visitor interface: one visit() per concrete element ----------
class ShapeVisitor {
public:
    virtual void visit(Circle* c) = 0;
    virtual void visit(Rectangle* r) = 0;
    virtual ~ShapeVisitor() {}
};

// ---------- Element interface ----------
class Shape {
public:
    virtual void accept(ShapeVisitor* v) = 0;   // "double dispatch" entry point
    virtual ~Shape() {}
};

// ---------- Concrete elements: each just dispatches to the right visit() ----------
class Circle : public Shape {
public:
    double radius;
    Circle(double r) { this->radius = r; }
    void accept(ShapeVisitor* v) { v->visit(this); }
};
class Rectangle : public Shape {
public:
    double width;
    double height;
    Rectangle(double w, double h) { this->width = w; this->height = h; }
    void accept(ShapeVisitor* v) { v->visit(this); }
};

// ---------- Concrete visitors: add operations without touching the shapes ----------
class AreaVisitor : public ShapeVisitor {
private:
    double totalArea;
public:
    AreaVisitor() { this->totalArea = 0; }
    void visit(Circle* c) { this->totalArea += 3.14159 * c->radius * c->radius; }
    void visit(Rectangle* r) { this->totalArea += r->width * r->height; }
    double total() { return this->totalArea; }
};

class SvgExportVisitor : public ShapeVisitor {
public:
    void visit(Circle* c) { cout << "  <circle r=\"" << c->radius << "\"/>" << endl; }
    void visit(Rectangle* r) { cout << "  <rect w=\"" << r->width << "\" h=\"" << r->height << "\"/>" << endl; }
};

int main() {
    vector<Shape*> doc;
    doc.push_back(new Circle(2.0));
    doc.push_back(new Rectangle(3.0, 4.0));
    doc.push_back(new Circle(1.0));

    AreaVisitor area;
    for (int i = 0; i < (int)doc.size(); i++) doc[i]->accept(&area);
    cout << "Total area: " << area.total() << endl;

    cout << "SVG export:" << endl;
    SvgExportVisitor svg;
    for (int i = 0; i < (int)doc.size(); i++) doc[i]->accept(&svg);

    // To add a "bounding box" operation, write ONE new visitor — no shape edits.
    for (int i = 0; i < (int)doc.size(); i++) delete doc[i];
    return 0;
}
