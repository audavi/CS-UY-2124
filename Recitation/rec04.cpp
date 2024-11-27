//  Emily Lopez (el4100)
//  rec04.cpp

#include <iostream>
using namespace std;

//Task 16:
struct Complex{
    double real;
    double img;
};

//Task 17
class PlainOldClass {
public:
   PlainOldClass() : x(-72) {}
   int getX() const { return x; }
    void setX( int x )  { this->x = x; }
private:
   int x;
};

//Task 28
class Colour {
public:
    Colour(const string& name, unsigned r, unsigned g, unsigned b)
        : name(name), r(r), g(g), b(b) {}
    void display() const {
        cout << name << " (RBG: " << r << "," << g<< "," << b << ")";
    }
private:
    string name;      // what we call this colour
    unsigned r, g, b; // red/green/blue values for displaying
};
//TASK 30
class Person {
public:
    Person(const string& name) : name(name) {}
    void movesInWith(Person& newRoomate) {
        roomie = &newRoomate;        // now I have a new roomie
        newRoomate.roomie = this;    // and now they do too
    }
    const string& getName() const { return name; }
    // Don't need to use getName() below, just there for you to use in debugging.
    const string& getRoomiesName() const { return roomie->getName(); }
private:
    Person* roomie;
    string name;
};

int main(){
    //Task 2
    int x; // &x = 0x16dff27c
    x = 10;
    cout << "x = " << x << endl;

    //Task 8
    int* p; // type "pointer to int" p
    p = &x; // this takes the address of x and copies that value into p.
    cout << "p = " << p << endl;

    //Task 9
    //p = 0x16dff27c; // we cannot convert int to int* (pointer to int)

    //Task 10
    //*p is the dereference operator applied to the variable p. This follows the addres stored and p and gets the value stored where p points.
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p contains " << *p <<endl;

    //Task 11
    *p = -2763;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "x now contains " << x << endl;

    //Task 12
    int y(13);
    cout << "y contains " << y << endl;
    p = &y;
    cout << "p now points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    *p = 980;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "y now contains " << y << endl;

    //Task 13
    int* q;
    q = p;
    cout << "q points to where " << *q << " is stored\n";
    cout << "*q contains " << *q << endl;

    //Task 14
    double d(33.4);
    double* pD(&d);
    *pD = *p; //points to 980
    *p = *pD; // also points to 980
    *q = *p; // also 980
    //pD = p; //Compilation error: cannot cast a int* to a double*.
    //p = pD; //Compilation error: cannot cast a double * to a int*

    //Task 15
    int joe = 24;
    const int sal = 19;
    int* pI;
    //REMOVE SOME COMMENTS BEFORE TURNING IN.

    //    pI = &joe;
    //    *pI = 234;
    //    pI = &sal;  NO We cannot assign a const int to an int.
    //    *pI = 7623;

    //    const int* pcI;
    //    pcI = &joe;
    //    *pcI = 234;  NO we cannot assign a new value since pcI is constant.
    //    pcI = &sal;
    //    *pcI = 7623; NO we cannot assign a new value since pcI is a const int.

    //    int* const cpI; NO. There is no default initialization of what must be constant.
    //    int* const cpI(&joe);
    //    int* const cpI(&sal); // NO. Cannot assign a variable of type int* const to a constant integer
    //    cpI = &joe; // NO. Cannot assign a new address to cpI since its const.
    //    *cpI = 234;
    //    cpI = &sal; // NO. We cant change the const address.
    //    *cpI = 7623;

    //const int* const cpcI; // NO. there is no default initialization to qualify our const
    //const int* const cpcI(&joe);
    //const int* const cpcI(&sal);
    //cpcI = &joe; // NO  we cannot assign to variable since it is const
    //cpcI = &sal; // NO cannot assign a variable since it is const
    //cpcI = 7623; //NO  cannot change a const int

    //Task 16
    Complex c = {11.23,45.67};
    Complex* pC(&c);
    cout << "real: " << (*pC).real << "\nimaginary: " << (*pC).img << endl;
    cout << "real: " << pC->real << "\nimaginary: " << pC->img << endl;

    //Task 17
    PlainOldClass poc;
    PlainOldClass* ppoc( &poc );
    cout << ppoc->getX() << endl;
    ppoc->setX( 2837 );
    cout << ppoc->getX() << endl;

    //Task 19
    int* pDyn = new int(3); //p points to an int initialized to 3 on the heap
    *pDyn = 17;
    cout << "The " << *pDyn
         << " is stored at address " << pDyn
    << " which is in the heap\n";

    //Task 20
    cout << pDyn << endl;
    delete pDyn;
    cout << pDyn << endl;

    cout << "The 17 might STILL be stored at address " << pDyn<< " even though we deleted pDyn\n";
    cout << "But can we dereference pDyn?  We can try.  This might crash... " << *pDyn << ".  Still here?\n";
    //Task 21
    pDyn = nullptr;
    double* pDouble = nullptr;
    //Task 22
    // cout << "Can we dereference nullptr?  " << *pDyn << endl;
    // cout << "Can we dereference nullptr?  " << *pDouble << endl;

    //Task 23
    // YES

    //Task 24
    double* pTest = new double(12);
    delete pTest;
    pTest = nullptr;
    delete pTest; // safe

    //Task 25
    short* pShrt = new short(5);
    delete pShrt;
    //delete pShrt; Crashed. Pointer being freed was not alocated.

    //Task 26
    long jumper = 12238743;
    //delete jumper;

    long* ptrTolong = &jumper;
    //delete ptrTolong;// cannot delete type long.
    // delete can only be used with the heap(dynamic memory/free storage)
    Complex cmplx;
    //delete cmplx; // cannot delete type complex.

    //Task 27
    vector<Complex*> complV; // can hold pointers to Complex objects
    Complex* tmpPCmplx;      // space for a Complex pointer
    for (size_t ndx = 0; ndx < 3; ++ndx) {
       tmpPCmplx = new Complex; // create a new Complex object on the heap
       tmpPCmplx->real = ndx;   // set real and img to be the
       tmpPCmplx->img  = ndx;   // value of the current ndx
       complV.push_back(tmpPCmplx); // store the ADDRESS of the object in a vector or pointer to Complex
    }
    // display the objects using the pointers stored in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        cout << complV[ ndx ]->real << endl;
        cout << complV[ ndx ]->img  << endl;
    }
    // release the heap space pointed at by the pointers in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        delete complV[ndx];
    }
    // clear the vector
    complV.clear(); // does not delete on the things inside the vector

    //Task 28
    vector<Colour*> colours;
    string inputName;
    unsigned inputR, inputG, inputB;

    // fill vector with Colours from the file
    // this could be from an actual file but here we are using the keyboard instead of a file
    // (so we don't have to create an actual file)
    // Do you remember the keystroke combination to indicate "end of file" at the keyboard?
    // somehow the while's test has to fail - from keyboard input
    while (cin >> inputName >> inputR >> inputG >> inputB) {
        colours.push_back(new Colour(inputName, inputR, inputG, inputB));
    }

    // display all the Colours in the vector:
    for (size_t ndx = 0; ndx < colours.size(); ++ndx) {
        colours[ndx]->display();
        cout << endl;
    }


    //Task 30


    // write code to model two people in this world
    Person joeBob("Joe Bob"), billyJane("Billy Jane");

    // now model these two becoming roommates
    joeBob.movesInWith(billyJane);

    // did this work out?
    cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
    cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;


}
