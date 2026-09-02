// =============================================================================
// PROXY (Java twin of example.cpp) — a virtual proxy defers the expensive load
// of a high-res image until it is first displayed.
//
// Build & run:
//   javac Main.java
//   java Main
// =============================================================================

// ---------- Subject: the shared interface ----------
interface Image {
    void display();
}

// ---------- Real subject: expensive to create ----------
class HighResImage implements Image {
    private String file;
    HighResImage(String file) {
        this.file = file;
        loadFromDisk();                       // the costly operation
    }
    private void loadFromDisk() {
        System.out.println("  [disk] loading large image " + this.file + " ... done");
    }
    public void display() { System.out.println("  showing " + this.file); }
}

// ---------- Virtual proxy: same interface, defers the real load ----------
class ImageProxy implements Image {
    private String file;
    private HighResImage real = null;         // null until first display()
    ImageProxy(String file) { this.file = file; }
    public void display() {
        if (this.real == null) {              // create on first use only
            this.real = new HighResImage(this.file);
        }
        this.real.display();
    }
}

public class Main {
    public static void main(String[] args) {
        System.out.println("Opening document with 3 images (note: no disk loads yet):");
        Image img1 = new ImageProxy("photo1.png");
        Image img2 = new ImageProxy("photo2.png");
        Image img3 = new ImageProxy("photo3.png");   // never viewed

        System.out.println();
        System.out.println("User scrolls to image 1:");
        img1.display();                          // loads now
        System.out.println("User scrolls back to image 1 again:");
        img1.display();                          // already loaded — no second disk hit

        System.out.println("User scrolls to image 2:");
        img2.display();                          // loads now
        System.out.println();
        System.out.println("(photo3 was never displayed, so it was never loaded.)");
    }
}
