/*
    Eric Cheung
    rec10.cpp
    lab 10
 */

#include <iostream>
#include <vector>
using namespace std;
class Instrument {
public:
    virtual void makeSound() const = 0;
    virtual void play() const = 0;
    friend ostream& operator<<(ostream& os, const Instrument& inst);
    virtual void display(ostream& os) const = 0;
};

ostream& operator<<(ostream& os, const Instrument& inst) {
    inst.display(os);
    return os;
}

void Instrument::makeSound() const {
    cout << "To make a sound... ";
}

class Brass : public Instrument {
public:
    Brass(int mouthpiece) : mouthpiece(mouthpiece) {}
    void makeSound() const override {
        Instrument::makeSound();
        cout << "blow on the mouthpiece of size " << mouthpiece << endl;
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
    void play() const override {
        cout << "Blat";
    }
    void display(ostream& os) const override {
        os << "Trombone";
        Brass::display(os);
    }
};

class Trumpet : public Brass {
public:
    Trumpet(int mouthpiece) : Brass(mouthpiece) {}
    void play() const override {
        cout << "Toot";
    }
    void display(ostream& os) const override {
        os << "Trumpet";
        Brass::display(os);
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
    void play() const override {
        cout << "Squawk";
    }
    void display(ostream& os) const override {
        os << "Cello";
        String::display(os);
    }
};

class Violin : public String {
public:
    Violin(int pitch) : String(pitch) {}
    void play() const override {
        cout << "Screech";
    }
    void display(ostream& os) const override {
        os << "Violin";
        String::display(os);
    }
};

class Percussion : public Instrument {
public:
    void makeSound() const override {
        Instrument::makeSound();
        cout << "hit me!" << endl;
    } 
};

class Drum : public Percussion {
public:
    void play() const override {
        cout << "Boom";
    }
    void display(ostream& os) const override {
        os << "Drum" << endl;
    }
};

class Cymbal : public Percussion {
public:
    void play() const override {
        cout << "Crash";
    }
    void display(ostream& os) const override {
        os << "Cymbal" << endl;
    }

};

class MILL {
public:
    void receiveInstr(Instrument& inst) {
        inst.makeSound();
        for (size_t i = 0; i < instrs.size(); ++i) {
            if (instrs[i] == nullptr) {
                instrs[i] = &inst;
                return;
            }  
        }
        instrs.push_back(&inst);
    }

    void dailyTestPlay() const {
        for (size_t i = 0; i < instrs.size(); ++i) {
            if (instrs[i] != nullptr) {
                instrs[i]->makeSound();
            }
        }
    }

    Instrument* loanOut() {
        for (size_t i = 0; i < instrs.size(); ++i) {
            if (instrs[i] != nullptr) {
                Instrument* result = instrs[i];
                instrs[i] = nullptr;
                return result;
            }
        }
        return nullptr;
    }

    friend ostream& operator<<(ostream& os, const MILL& mill);


private:
    vector<Instrument*> instrs;
};

ostream& operator<<(ostream& os, const MILL& mill) {
    os << "The MILL has the following instruments:\n";
    if (mill.instrs.empty()) {
        os << "None";
        return os;
    }

    bool found_non_null = false;
    for (size_t i = 0; i < mill.instrs.size(); ++i) {
        if (mill.instrs[i] != nullptr) {
            os << "    ";
            os << *(mill.instrs[i]);
            found_non_null = true;
        }
    }
    if (!found_non_null) {
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
        // Don't do anything if we don't have an instrument.
    }
private:
    Instrument* instr;
    string name;
};

class Orch {
public:
    void addPlayer(Musician& m) {
        musicians.push_back(&m);
    }

    void play() {
        for (size_t i = 0; i < musicians.size(); ++i) {
            musicians[i]->play();
        }
        cout << endl;
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

    //
    // PART TWO
    
    
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


