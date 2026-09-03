// =============================================================================
// VISITOR (Java twin of example.cpp) — add operations (area, SVG export) over a
// shape hierarchy without modifying the shape classes. Overload resolution of
// visit(Circle)/visit(Rectangle) provides the "double dispatch".
//
// Build & run:
//   javac Main.java
//   java Main
// =============================================================================
import java.util.ArrayList;
import java.util.List;

// ---------- Visitor interface: one visit() per concrete element ----------
interface ShapeVisitor {
    void visit(Circle c);
    void visit(Rectangle r);
}

// ---------- Element interface ----------
interface Shape {
    void accept(ShapeVisitor v);
}

// ---------- Concrete elements ----------
class Circle implements Shape {
    double radius;
    Circle(double r) { this.radius = r; }
    public void accept(ShapeVisitor v) { v.visit(this); }
}
class Rectangle implements Shape {
    double width;
    double height;
    Rectangle(double w, double h) { this.width = w; this.height = h; }
    public void accept(ShapeVisitor v) { v.visit(this); }
}

// ---------- Concrete visitors ----------
class AreaVisitor implements ShapeVisitor {
    private double totalArea = 0;
    public void visit(Circle c) { this.totalArea += 3.14159 * c.radius * c.radius; }
    public void visit(Rectangle r) { this.totalArea += r.width * r.height; }
    double total() { return this.totalArea; }
}

class SvgExportVisitor implements ShapeVisitor {
    public void visit(Circle c) { System.out.println("  <circle r=\"" + c.radius + "\"/>"); }
    public void visit(Rectangle r) { System.out.println("  <rect w=\"" + r.width + "\" h=\"" + r.height + "\"/>"); }
}

public class Main {
    public static void main(String[] args) {
        List<Shape> doc = new ArrayList<Shape>();
        doc.add(new Circle(2.0));
        doc.add(new Rectangle(3.0, 4.0));
        doc.add(new Circle(1.0));

        AreaVisitor area = new AreaVisitor();
        for (Shape s : doc) s.accept(area);
        System.out.println("Total area: " + area.total());

        System.out.println("SVG export:");
        SvgExportVisitor svg = new SvgExportVisitor();
        for (Shape s : doc) s.accept(svg);

        // To add a "bounding box" operation, write ONE new visitor — no shape edits.
    }
}
