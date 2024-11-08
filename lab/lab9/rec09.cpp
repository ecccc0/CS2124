#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial( unsigned numPages )
        : numOfPages(numPages) {}
    virtual void displayNumPages() const = 0;
    private:
    unsigned numOfPages;
};

void PrintedMaterial::displayNumPages() const {
    cout << numOfPages << endl;
}

class Magazine : public PrintedMaterial {
public:
    Magazine( unsigned numPages )
        : PrintedMaterial(numPages) {}
    void displayNumPages() const {
        cout << "Pages: "; 
        PrintedMaterial::displayNumPages();
    }
private:
};

class Book : public PrintedMaterial {
public:
    Book( unsigned numPages )
        : PrintedMaterial(numPages) {}
private:
};

class TextBook : public Book {
public:
    TextBook( unsigned numPages, unsigned numIndexPages )
        : Book(numPages),
          numOfIndexPages(numIndexPages) {}
    void displayNumPages() const {
        cout << "Pages: "; 
        PrintedMaterial::displayNumPages();
        cout << "Index: " << numOfIndexPages << endl;
    }
private:
    unsigned numOfIndexPages;
};

class Novel : public Book {
public:
    Novel( unsigned numPages )
        : Book(numPages) {}
    void displayNumPages() const {
        cout << "Pages: "; 
        PrintedMaterial::displayNumPages();
    }
private:
};

void displayNumberOfPages( const PrintedMaterial& pm ) {
    pm.displayNumPages();
}

// tester/modeler code
int main() {
    vector<PrintedMaterial*> printed;
    TextBook t(5430, 23);
    Magazine m(6);
    printed.push_back(&t);
    printed.push_back(&m);
    Novel n(213);
    printed.push_back(&n);
    for (const PrintedMaterial* pm : printed) {
        pm->displayNumPages();
    }
}