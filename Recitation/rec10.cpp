/*
  Emily Lopez
  rec10.cpp
 */

#include <iostream>
#include <vector>
using namespace std;

//
// Musician class as provided to the students. Requires an Instrument class.
//
class Instrument {
    friend ostream& operator<<(ostream& os, const Instrument& instr);
public:
    virtual void makeSound() const = 0;
    virtual void play() = 0;
    virtual void display(ostream& os) const = 0;

};
ostream& operator<<(ostream& os, const Instrument& instr) {
    instr.display(os);
    return os;
}
void Instrument::makeSound() const { cout << "To make a sound... "; }


class Brass : public Instrument {
public:
    // constructor that takes in either a big, medium, or small mouthpiece
    Brass (unsigned mouthpiece) : mouthpiece(mouthpiece) {}
    void makeSound() const {
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size " << mouthpiece << endl;
    }
protected:
    unsigned getMouthpiece() const { return mouthpiece; }

private:
    unsigned mouthpiece;
};
class String : public Instrument {
public:
    String (unsigned pitch) : pitch(pitch) {}
    void makeSound() const {
        Instrument::makeSound();
        cout << "blow a string with pitch "<< pitch << endl;
    }
protected:
    unsigned getPitch() const { return pitch; }
private:
    unsigned pitch;
};
class Percussion : public Instrument {
public:
    void makeSound() const {
        Instrument::makeSound();
        cout << "hit me!" << endl;
    }
};

class Trumpet : public Brass {
public:
    Trumpet(unsigned mouthpiece) : Brass(mouthpiece) {}
    void play() {
        cout << "Toot";
    }
    void display(ostream& os) const {
        os << "Trumpet: " << getMouthpiece();
    }
};
class Trombone : public Brass {
public:
    Trombone(unsigned mouthpiece) : Brass(mouthpiece) {}
    void play() {
        cout << "Blat";
    }
    void display(ostream& os) const {
        os << "Trombone: " << getMouthpiece();
    }
};

class Violin : public String {
public:
    Violin(unsigned pitch) : String(pitch) {}
    void play() {
        cout << "Screech";
    }
    void display(ostream& os) const {
        os << "Violin: " << getPitch();
    }
};
class Cello : public String {
public:
    Cello(unsigned pitch) : String(pitch) {}
    void play() {
        cout << "Squawk";
    }
    void display(ostream& os) const {
        os << "Cello: " << getPitch();
    }
};

class Drum : public Percussion {
public:
    Drum() : Percussion() {}
    void play() {
        cout << "Boom";
    }
    void display(ostream& os) const {
        os << "Drum";
    }
};
class Cymbal : public Percussion {
public:
    Cymbal() : Percussion() {}
    void play() {
        cout << "Crash";
    }
    void display(ostream& os) const {
        os << "Cymbal";
    }
};

class MILL {
    friend ostream& operator<<(ostream& os, const MILL& mill);
public:
    void receiveInstr(Instrument& instr) {
        inventorySize += 1;
        // test the instrument by making a sound
        instr.makeSound();
        // add to the first available place in the inventory
        for (size_t i = 0; i < inventory.size(); i++) {
            // if the inventory doesn't have enough space,
            // add additional space at the end
            if (inventory[i] == nullptr) {
                inventory[i] = &instr;
                return;
            }
        }
        inventory.push_back(&instr);
    }
    Instrument* loanOut() {
        inventorySize -= 1;
        for (size_t i = 0; i < inventory.size(); i++) {
            if (inventory[i] != nullptr) {
                Instrument* instPtr = inventory[i];
                inventory[i] = nullptr;
                return instPtr;
            }
        }
        return nullptr;
    }
    void dailyTestPlay() const {
        for (const Instrument* instr : inventory) {
            if (instr != nullptr) {
                instr->makeSound();
            }
        }
    }

private:
    vector<Instrument*> inventory;
    int inventorySize;
};
ostream& operator<<(ostream& os, const MILL& mill) {
    if (mill.inventorySize == 0) {
        os << "The MILL has the following instruments: None" << endl;
    }
    else {
        os << "The MILL has the following instruments:" << endl;
        for (const Instrument* instr : mill.inventory) {
            if (instr != nullptr) {
                os << "\t" << *instr << endl;
            }
        }
    }
    return os;
}


class Musician {
public:
    Musician(const string& name) : instr(nullptr), name(name) {}

    // acceptInstr takes in an instrument for the Musician to later play.
    //  "loses" any instrument that it used to have.
    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    // giveBackInstr: gives the instrument that the Musicial was holding "back"
    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    // testPlay: testing out my instrument
    void testPlay() const {
        if (instr) instr->makeSound();
        else cerr << name << " has no instr\n";
    }

    // play: play the instrument

    //   Not making it const so that Instrument::play method does not
    //   need to be const. Allows the instrument to be modifed in the
    //   process of being played.
    void play() {
        if (instr) instr->play();
        // Don't do anything if we don't have an instrument.
    }
private:
    Instrument* instr;
    string name;
};

class Orch {
public:
    void addPlayer(Musician& musician) {
        orchestraMusicians.push_back(&musician);
    }
    void play() const {
        for (size_t i = 0; i < orchestraMusicians.size(); i++) {
            orchestraMusicians[i]->play();
        }
        cout << endl;
    }
private:
    vector<Musician*> orchestraMusicians;
};

int main() {

    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ---------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;

    cout << "Define the MILL -----------------------------------------------\n";
    MILL mill;
    cout << "The MILL before adding instruments:\n" << mill << "\n\n";

    cout << "Put the instruments into the MILL -----------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
    cout << "\nThe MILL after adding some instruments:\n" << mill << "\n\n";

    cout << "Daily test ----------------------------------------------------\n"
	 << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();
     cout << endl;

    cout << "Define some Musicians------------------------------------------\n";
    Musician harpo("Harpo");
    Musician groucho("Groucho");

    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();	 // Groucho doesn't have an instrument yet.

    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
    // wrong output here
    groucho.testPlay();
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();
    harpo.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL after giving out some instruments:\n";
    cout << mill << "\n\n";

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    mill.receiveInstr(*groucho.giveBackInstr());

    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    cout << endl;

    cout << "dailyTestPlay()" << endl;
        mill.dailyTestPlay();

    cout << "\nThe MILL at the end of Part One:\n";
     cout << mill << endl;

    //
    // PART TWO
    //
    cout << "\nP A R T  T W O\n";

    Musician bob("Bob");
    Musician sue("Sue");
    Musician mary("Mary");
    Musician ralph("Ralph");
    Musician jody("Judy");
    Musician morgan("Morgan");

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    cout << endl << mill << endl;

}

