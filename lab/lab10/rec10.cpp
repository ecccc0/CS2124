/*
  rec10.cpp
  Eric Cheung
  Lab 10
 */

#include <iostream>
#include <vector>
using namespace std;

class Instrument { 
public:
    virtual void makeSound() const = 0;
    friend ostream& operator<<(ostream& os, const Instrument& instr);
    virtual void display(ostream& os) const = 0;
    virtual void play() const = 0;
};

ostream& operator<<(ostream& os, const Instrument& instr) {
    instr.display(os);
    return os;
}

void Instrument::makeSound() const {
    cout << "To make a sound... ";
}

class Percussion : public Instrument {
public:
    void makeSound() const override {
        Instrument::makeSound();
        cout << "hit me!" << endl;
    }
};

class Drum : public Percussion {
public:
    void display(ostream& os) const override {
        os << "Drum" << endl;
    }
    void play() const override{
        cout << "Boom\n";
    }
};

class Cymbal : public Percussion {
public:
    void display(ostream& os) const override {
        os << "Cymbal" << endl;
    }
    void play() const override{
        cout << "Crash\n";
    }
};

class Brass : public Instrument {
public:
    Brass(int mouthpiece) : mouthpiece(mouthpiece) {}
    void makeSound() const override {
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size " << mouthpiece << endl;
    }
    void display(ostream& os) const override {
        os << ": " << mouthpiece << endl;
    }
private:
    int mouthpiece;
};

class Trombone : public Brass {
public:
    Trombone(int mouthpiece) : Brass(mouthpiece) {}
    void display(ostream& os) const override{
        os << "Trombone";
        Brass::display(os);
    }
    void play() const override{
        cout << "Blat\n";
    }
};

class Trumpet : public Brass {
public:
    Trumpet(int mouthpiece) : Brass(mouthpiece) {}
    void display(ostream& os) const override {
        os << "Trumpet";
        Brass::display(os);
    }
    void play() const override{
        cout << "Toot\n";
    }
};

class String : public Instrument {
public:
    String(int pitch) : pitch(pitch) {}
    void makeSound() const override {
        Instrument::makeSound();
        cout << "bow a string with pitch " << pitch << endl;
    }
    
    void display(ostream& os) const override {
        os << ": " << pitch << endl;
    }

private:
    int pitch;
};

class Cello : public String {
public:
    Cello(int pitch) : String(pitch) {}

    void display(ostream& os) const override {
        os << "Cello";
        String::display(os);
    }

    void play() const override {
        cout << "Squawk\n";
    }

};

class Violin : public String {
public:
    Violin(int pitch) : String(pitch) {}

    void display(ostream& os) const override {
        os << "Violin";
        String::display(os);
    }

    void play() const override{
        cout << "Screech\n";
    }
};

class MILL {
public:
    void receiveInstr(Instrument& instr) {
        instr.makeSound();
        for (size_t i = 0; i < inventory.size(); ++i) {
            if (inventory[i] == nullptr) {
                inventory[i] = &instr;
                return;
            }
        }
        inventory.push_back(&instr);
    }

    void dailyTestPlay() const {
        for (size_t i = 0; i < inventory.size(); ++i) {
            if (inventory[i] != nullptr) {
                inventory[i]->makeSound();
            }
        }
    }

    Instrument* loanOut() {
        for (size_t i = 0; i < inventory.size(); ++i) {
            if (inventory[i] != nullptr) {
                Instrument* instr = inventory[i];
                inventory[i] = nullptr;
                return instr;
            }
        }
        return nullptr;
    }

    friend ostream& operator<<(ostream& os, const MILL& mill);

private:
    vector<Instrument*> inventory;
};

ostream& operator<<(ostream& os, const MILL& mill) {
    os << "The MILL has the following instruments:\n";
    if (mill.inventory.empty()) {
        os << "None";
        return os;
    }
    bool found_non_null = false;
    for (size_t i = 0; i < mill.inventory.size(); ++i) {
        if (mill.inventory[i] != nullptr) {
            os << "    ";
            os << *(mill.inventory[i]);
            found_non_null = true;
        }
    }
    if (!found_non_null){
        os << "None";
    }
    return os;
}
// 
// Musician class as provided to the students. Requires an Instrument class.
// 

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
    //     // Don't do anything if we don't have an instrument.
    }
private:
    Instrument* instr;
    string name;
};


class Orch {
public:
    void play() {
        for (size_t i = 0; i < musicians.size() ;++i) {
            musicians[i]->play();
        }
    }
    
    void addPlayer(Musician &musician) {
        musicians.push_back(&musician);
    }


private:
    vector<Musician*> musicians;


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

    
    // PART TWO
    
    cout << "\nP A R T  T W O\n";
    
    Musician bob("Bob");
    Musician sue("Sue");
    Musician mary("Mary");
    Musician ralph("Ralph");
    Musician jody("Judy");
    Musician morgan("Morgan");

    Orch orch;

    // // THE SCENARIO

    // //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    // //The orchestra performs
    cout << "orch performs\n";
    orch.play();
    // ...

    // //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    // //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    // //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    // //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    // //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
    // ScreechBlatToot

    // //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    // //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
	// ScreechBlatToot
    // // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    // //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
    // SquawkScreechBlatTootCrash
    // //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    // //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
    // SquawkScreechBlatTootCrashBoom


    cout << endl << mill << endl;

}

