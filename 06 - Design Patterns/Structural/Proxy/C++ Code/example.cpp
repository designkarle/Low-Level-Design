// =============================================================================
// PROXY — provide a surrogate/placeholder for another object to control access
// to it. The proxy implements the SAME interface as the real object, so clients
// can't tell the difference — but it can add lazy-loading, access control,
// caching, or logging around the real call.
//
// Domain: a document viewer shows many high-resolution images. Loading every
// image up front is wasteful. A VIRTUAL proxy defers the expensive load until
// the image is actually displayed for the first time.
//
// Build & run:
//   g++ -std=c++14 example.cpp -o example
//   ./example
// =============================================================================
#include <iostream>
#include <string>

using namespace std;

// ---------- Subject: the shared interface ----------
class Image {
public:
    virtual void display() = 0;
    virtual ~Image() {}
};

// ---------- Real subject: expensive to create ----------
class HighResImage : public Image {
private:
    string file;
    void loadFromDisk() {
        cout << "  [disk] loading large image " << this->file << " ... done" << endl;
    }
public:
    HighResImage(string file) {
        this->file = file;
        this->loadFromDisk();                 // the costly operation
    }
    void display() { cout << "  showing " << this->file << endl; }
};

// ---------- Virtual proxy: same interface, defers the real load ----------
class ImageProxy : public Image {
private:
    string file;
    HighResImage* real;                       // null until first display()
public:
    ImageProxy(string file) {
        this->file = file;
        this->real = nullptr;
    }
    void display() {
        if (this->real == nullptr) {          // create on first use only
            this->real = new HighResImage(this->file);
        }
        this->real->display();
    }
    ~ImageProxy() {
        if (this->real != nullptr) delete this->real;
    }
};

int main() {
    cout << "Opening document with 3 images (note: no disk loads yet):" << endl;
    Image* img1 = new ImageProxy("photo1.png");
    Image* img2 = new ImageProxy("photo2.png");
    Image* img3 = new ImageProxy("photo3.png");   // never viewed

    cout << endl << "User scrolls to image 1:" << endl;
    img1->display();                          // loads now
    cout << "User scrolls back to image 1 again:" << endl;
    img1->display();                          // already loaded — no second disk hit

    cout << "User scrolls to image 2:" << endl;
    img2->display();                          // loads now
    cout << endl << "(photo3 was never displayed, so it was never loaded.)" << endl;

    delete img1;
    delete img2;
    delete img3;
    return 0;
}
