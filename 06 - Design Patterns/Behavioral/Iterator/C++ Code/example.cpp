// =============================================================================
// ITERATOR — provide a way to access the elements of a collection sequentially
// WITHOUT exposing its underlying representation. The collection can change its
// internal storage and clients that use the iterator don't care.
//
// Domain: a Playlist. We expose an iterator so clients traverse songs
// (hasNext / next) without knowing it's backed by a vector — and we also wire up
// C++ range-for via begin()/end().
//
// Build & run:
//   g++ -std=c++14 example.cpp -o example
//   ./example
// =============================================================================
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------- Iterator interface (the GoF-style explicit iterator) ----------
template <typename T>
class Iterator {
public:
    virtual bool hasNext() = 0;
    virtual T next() = 0;
    virtual ~Iterator() {}
};

// ---------- Aggregate + its concrete iterator ----------
class Playlist {
private:
    vector<string> songs;   // could be a list/tree/file — hidden from clients
public:
    void add(string song) { this->songs.push_back(song); }

    // Concrete iterator: knows the internal layout; clients don't.
    class SongIterator : public Iterator<string> {
    private:
        const vector<string>& songs;
        int pos;
    public:
        SongIterator(const vector<string>& s) : songs(s) { this->pos = 0; }
        bool hasNext() { return this->pos < (int)this->songs.size(); }
        string next() { return this->songs[this->pos++]; }
    };

    Iterator<string>* iterator() { return new SongIterator(this->songs); }

    // Bonus: support idiomatic C++ range-for by exposing begin()/end().
    vector<string>::const_iterator begin() const { return this->songs.begin(); }
    vector<string>::const_iterator end() const { return this->songs.end(); }
};

int main() {
    Playlist pl;
    pl.add("Lose Yourself");
    pl.add("Numb");
    pl.add("Believer");

    cout << "Via explicit iterator (hasNext/next):" << endl;
    Iterator<string>* it = pl.iterator();
    while (it->hasNext()) cout << "  - " << it->next() << endl;
    delete it;

    cout << "Via C++ range-for (same collection):" << endl;
    for (string song : pl) cout << "  * " << song << endl;
    return 0;
}
