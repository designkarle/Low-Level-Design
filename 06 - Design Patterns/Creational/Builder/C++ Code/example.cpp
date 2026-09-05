// =============================================================================
// BUILDER — construct a complex object step by step. The product can stay
// consistent with many optional fields, with no "telescoping constructor" mess.
//
// Domain: assembling a custom Computer. A few required parts (CPU, RAM) and many
// optional ones (GPU, SSD, liquid cooling, Wi-Fi). A constructor with 8
// parameters would be unreadable; a fluent builder makes intent obvious.
//
// Build & run:
//   g++ -std=c++14 example.cpp -o example
//   ./example
// =============================================================================
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// ---------- Product ----------
class Computer {
public:
    void summary() {
        cout << "  Computer { CPU=" << this->cpu << ", RAM=" << this->ramGB << "GB"
             << ", GPU=" << (this->gpu.empty() ? "integrated" : this->gpu)
             << ", SSD=" << this->ssdGB << "GB"
             << ", liquidCooled=" << (this->liquidCooling ? "yes" : "no")
             << ", wifi=" << (this->wifi ? "yes" : "no") << " }" << endl;
    }
private:
    Computer() {                     // only the Builder may construct one
        this->ramGB = 0;
        this->ssdGB = 256;
        this->liquidCooling = false;
        this->wifi = false;
    }
    friend class ComputerBuilder;

    string cpu;
    int ramGB;
    string gpu;
    int ssdGB;
    bool liquidCooling;
    bool wifi;
};

// ---------- Builder: fluent, chainable, validates at build() ----------
class ComputerBuilder {
public:
    ComputerBuilder(string cpu, int ramGB) {
        this->c.cpu = cpu;
        this->c.ramGB = ramGB;
    }
    ComputerBuilder& withGpu(string gpu)   { this->c.gpu = gpu; return *this; }
    ComputerBuilder& withSsd(int gb)       { this->c.ssdGB = gb; return *this; }
    ComputerBuilder& withLiquidCooling()   { this->c.liquidCooling = true; return *this; }
    ComputerBuilder& withWifi()            { this->c.wifi = true; return *this; }

    Computer build() {
        if (this->c.cpu.empty() || this->c.ramGB <= 0)
            throw invalid_argument("CPU and RAM are required");
        return this->c;              // a finished, consistent product
    }
private:
    Computer c;
};

int main() {
    // Read it like a sentence — each option is named, order doesn't matter.
    Computer office = ComputerBuilder("Intel i5", 16)
                          .withSsd(512)
                          .withWifi()
                          .build();

    Computer gaming = ComputerBuilder("Ryzen 9", 64)
                          .withGpu("RTX 4090")
                          .withSsd(2000)
                          .withLiquidCooling()
                          .withWifi()
                          .build();

    cout << "Office build:" << endl; office.summary();
    cout << "Gaming build:" << endl; gaming.summary();
    return 0;
}
