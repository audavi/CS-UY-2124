/*
  Emily Lopez (el4100)
  rec06.cpp
  CS2124
  Focus: Dynamic arrays and copy control
 */

#include <string>
#include <iostream>
using namespace std;

//
// Position class
//
class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs)
    {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    } // Position op<<
public:
    Position(const string& aTitle, double aSalary)
        : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
}; // class Position


//
// Directory class
//
class Directory {
    //
    // nested Entry class
    //
    class Entry {
	friend ostream& operator<<(ostream& os, const Entry& rhs)
        {
	    os << rhs.name << ' ' << rhs.room
	       << ' ' << rhs.phone << ", " << *rhs.pos;
	    return os;
	} // Entry op<<
    public:
	Entry(const string& name, unsigned room, unsigned phone, Position& position)
	    : name(name), room(room), phone(phone), pos(&position) {
	}
	const string& getName() const { return name; }
	unsigned getPhone() const { return phone; }
    private:
	string name;
	unsigned room;
	unsigned phone;
	Position* pos;
    }; // class Entry


    // Overload Directory's output operator
    friend ostream& operator<<(ostream& os, const Directory& rhs) {
        os << "Directory: " << rhs.company << endl;
        for (size_t i = 0; i < rhs.size; i++) {
            os << *(rhs.entries[i]) << endl;
        }
        return os;
    }

public:
    // Of course the first function you need to write for this (or
    // any) class is...
    Directory(const string& company)
    : company(company), size(0), capacity(0), entries(nullptr) {}

    // We'll get you started with the add method, but obviously you
    // have a lot of work to do here.
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity)	{
            // something is missing!!!  Add it!
            //check if capacity is 0 before resizing
            if (capacity == 0) {
                capacity = 1;
                entries = new Entry*[capacity];
            } else {
                // copy our old data
                Entry** old = entries;
                entries = new Entry*[capacity * 2];
                // copy the old data into the new directory
                for (size_t i =0; i < size; i++) {
                    entries[i] = old[i];
                }
                // free up the old array
                delete[] old;
                capacity *= 2;
            }

        } // if size < capacity
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add
    unsigned operator[](const string& name) const {
        for (size_t i = 0; i < size; i++) {
            if (entries[i]->getName() == name) {
                return entries[i]->getPhone();
            }
        }
        return 9999;
    }
    //
    // === Copy Control ===
    //
    // (get checked out on everything else before starting this)
    ~Directory() { // destructor
        for (size_t i = 0; i < size; i++) {
            delete entries[i];
        }
        delete[] entries;
    }
    Directory(const Directory& rhs) : company(rhs.company) { // copy constructor
        size = rhs.size;
        capacity = rhs.capacity;
        entries = new Entry*[capacity];
        // copy in the data
        for (size_t i = 0; i < size; i++) {

            entries[i] = new Entry(*rhs.entries[i]);
        }
    }
    Directory& operator=(const Directory& rhs) { // assignment operator
        // self assignment check
        if (this !=&rhs) {
            // free up the lhs but do not use the destructor itself
            for (size_t i = 0; i < size; i++) {
                delete entries[i];
            }
            delete []entries;
            // allocate and copy
            company = rhs.company;
            size = rhs.size;
            capacity = rhs.capacity;
            entries = new Entry*[capacity];
            for (size_t i = 0; i < size; i++) {
                entries[i] = new Entry(*rhs.entries[i]);
            }
        }
        return *this;
    }

private:
    Entry** entries; // Notice the type!!! Pointer to Entry pointers.
    size_t size;
    size_t capacity;
    string company;
}; // class Directory

void doNothing(Directory dir)
{
    // You need to overload the Directory output operator before
    // uncommenting the next line.
     cout << dir << endl;
} // doNothing

int main()
{
    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);

    Directory d("HAL");
    // Add someone
    d.add("Marilyn", 123, 4567, boss);
    // print the directory
    cout << d << endl;

    // Use the square bracket operator, aka the Index operator,
    // to access someone's phone extension.
    cout << "d[\"Marilyn\"]: " << d["Marilyn"] << endl;
    cout << "======\n\n";

    Directory d2 = d;
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << "Directory d:\n" << d << endl;
    cout << "Directory d2:\n" << d2 << endl;

    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    cout << d2["Carmack"] << endl;

    Directory d3("IBM");
    d3.add("Torvalds", 628, 3185, techie);
    d3.add("Ritchie", 123, 5813, techie);

    d2 = d3;
    // Should display 5813
    cout << d2["Ritchie"] << endl;

    cout << d2 << endl;
} // main
