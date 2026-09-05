// =============================================================================
// BUILDER (Java twin of example.cpp) — a fluent, chainable builder constructs a
// Computer with many optional fields; the product is built only at build().
//
// Build & run:
//   javac Main.java
//   java Main
// =============================================================================

// ---------- Product ----------
class Computer {
    private String cpu;
    private int ramGB;
    private String gpu = "";
    private int ssdGB = 256;
    private boolean liquidCooling = false;
    private boolean wifi = false;

    private Computer() {}            // only the Builder may construct one

    void summary() {
        System.out.println("  Computer { CPU=" + cpu + ", RAM=" + ramGB + "GB"
            + ", GPU=" + (gpu.isEmpty() ? "integrated" : gpu)
            + ", SSD=" + ssdGB + "GB"
            + ", liquidCooled=" + (liquidCooling ? "yes" : "no")
            + ", wifi=" + (wifi ? "yes" : "no") + " }");
    }

    // ---------- Builder: fluent, chainable, validates at build() ----------
    static class Builder {
        private Computer c = new Computer();
        Builder(String cpu, int ramGB) { c.cpu = cpu; c.ramGB = ramGB; }
        Builder withGpu(String gpu)  { c.gpu = gpu; return this; }
        Builder withSsd(int gb)      { c.ssdGB = gb; return this; }
        Builder withLiquidCooling()  { c.liquidCooling = true; return this; }
        Builder withWifi()           { c.wifi = true; return this; }
        Computer build() {
            if (c.cpu == null || c.cpu.isEmpty() || c.ramGB <= 0)
                throw new IllegalArgumentException("CPU and RAM are required");
            return c;
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Computer office = new Computer.Builder("Intel i5", 16)
                              .withSsd(512)
                              .withWifi()
                              .build();

        Computer gaming = new Computer.Builder("Ryzen 9", 64)
                              .withGpu("RTX 4090")
                              .withSsd(2000)
                              .withLiquidCooling()
                              .withWifi()
                              .build();

        System.out.println("Office build:"); office.summary();
        System.out.println("Gaming build:"); gaming.summary();
    }
}
