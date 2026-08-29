// =============================================================================
// ITERATOR (Java twin of example.cpp) — a Playlist exposes a GoF-style explicit
// iterator (hasNext/next) AND implements Iterable so for-each works too.
//
// Build & run:
//   javac Main.java
//   java Main
// =============================================================================
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

class Playlist implements Iterable<String> {
    private List<String> songs = new ArrayList<String>();   // hidden from clients
    void add(String song) { this.songs.add(song); }

    // Concrete GoF-style iterator: knows the internal layout; clients don't.
    static class SongIterator {
        private List<String> songs;
        private int pos = 0;
        SongIterator(List<String> s) { this.songs = s; }
        boolean hasNext() { return this.pos < this.songs.size(); }
        String next() { return this.songs.get(this.pos++); }
    }
    SongIterator songIterator() { return new SongIterator(this.songs); }

    // Bonus: support idiomatic for-each.
    public Iterator<String> iterator() { return this.songs.iterator(); }
}

public class Main {
    public static void main(String[] args) {
        Playlist pl = new Playlist();
        pl.add("Lose Yourself");
        pl.add("Numb");
        pl.add("Believer");

        System.out.println("Via explicit iterator (hasNext/next):");
        Playlist.SongIterator it = pl.songIterator();
        while (it.hasNext()) System.out.println("  - " + it.next());

        System.out.println("Via for-each (same collection):");
        for (String song : pl) System.out.println("  * " + song);
    }
}
