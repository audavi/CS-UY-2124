// Doubly linked list
// Emily Lopez
// rec12.cpp

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
private:
    // output operator
    friend ostream& operator<<(ostream& os, const List& rhs) {
        for (const Node* ptr = rhs.header->next; ptr != rhs.trailer; ptr = ptr->next) {
            os << ptr->data << ' ';
        }
        return os;
    }
    // node struct (task 1)
    struct Node {
        int data =0;
        Node* next;
        Node* prev;
    };
    Node* header;
    Node* trailer;
    size_t theSize;
public:
    // TASK 5
    class iterator {
        friend List;
        friend bool operator==(const iterator& lhs, const iterator& rhs) {
            return lhs.where == rhs.where;
        }
        friend bool operator!=(const iterator& lhs, const iterator& rhs) {
            return lhs.where != rhs.where;
        }
    public:
        // constructor
        iterator (Node* where) : where(where) {}
        // ++
        iterator& operator++() {
            where = where->next;
            return *this;
        }
        // --
        iterator& operator--() {
            where = where->prev;
            return *this;
        }
        // ==
        // bool operator==(const iterator& rhs) { return where == rhs.where; }
        // // !=
        // bool operator!=(const iterator& rhs) { return where != rhs.where; }
        // dereference
        int& operator*() const { return where->data; }

    private:
        Node* where;
    };
    // default constructor
    List() : header(new Node()), trailer(new Node()), theSize(0) {
        header->next =trailer;
        trailer->prev = header;
    }
    // push back
    void push_back(int data) {
        Node* newNode = new Node(data);
        trailer->prev->next = newNode;
        newNode->prev = trailer->prev;
        // header->next = newNode;
        // newNode->prev = header;
        trailer->prev = newNode;
        newNode->next = trailer;
        ++theSize;
    }
    // pop_back: remove last element
    void pop_back() {
    // check if list is empty
        if (theSize != 0) {
            Node* removedNode = trailer->prev;
            Node* secondToLast = trailer->prev->prev;
            trailer->prev = secondToLast;
            secondToLast->next = trailer;
            delete removedNode;
            --theSize;
        }
    }
    // front: returns the first data item
    int& front() {
        if (theSize != 0) {
            cout << "";
        }
        return header->next->data;
    }
    // back: accesses the last item
    int& back() {
        if (theSize != 0) {
            cout << "";
        }
        return trailer->prev->data;
    }
    // const version of front
    int front() const {
        if (theSize != 0) {
            cout << "";
        }
        return header->next->data;
    }
    // const version of back
    int back() const {
        if (theSize != 0) {
            cout << "";
        }
        return trailer->prev->data;
    }
    // size of the doubly linked list
    size_t size() const { return theSize; }

    // TASK 2
    void push_front(int data) {
        Node* newFirstNode = new Node(data);
        Node* oldFirstNode = header->next;
        header->next = newFirstNode;
        newFirstNode->prev = header;
        newFirstNode->next = oldFirstNode;
        oldFirstNode->prev = newFirstNode;
        ++theSize;
    }
    void pop_front() {
        if (theSize != 0) {
            Node* removedNode = header->next;
            Node* newFirstNode = header->next->next;
            header->next = newFirstNode;
            newFirstNode->prev = header;
            delete removedNode;
            --theSize;
        }
    }
    // TASK 3
    void clear() {
        // remember not to delete the header and trailer
        while (header->next != trailer) {
            header = header->next;
            delete header->prev;
        }
        header->next = trailer;
        trailer->prev = header;
        theSize = 0;
    }
    // TASK 4
    //index operator
    int operator[] (size_t index) const {
       Node* node = header->next;
        if (index < theSize) {
            while( index != 0) {
                node = node->next;
                --index;
            }
        }
        return node->data;
    }
    //index operator that can modify contents
    int& operator[] (size_t index) {
        Node* node = header->next;
        if (index < theSize) {
            while( index != 0) {
                node = node->next;
                --index;
            }
        }
        return node->data;
    }

    // TASK 5
    iterator begin() { return iterator(header->next); }
    iterator end() { return iterator(trailer);}

    //TASK 6
    iterator insert (const iterator& iter, int data) {
        Node* before = iter.where->prev;
        Node* after = iter.where;

        Node* newNode = new Node(data);
        newNode->prev = before;
        before->next = newNode;
        newNode->next = after;
        after->prev = newNode;
        ++theSize;
        return iterator(newNode);
    }
    //TASK 7
    iterator erase(const iterator& iter) {
        Node* before = iter.where->prev;
        Node* after = iter.where->next;

        before->next = after;
        after->prev = before;
        delete iter.where;
        --theSize;
        return iterator(after);
    }
};

// Task 1
void printListInfo(const List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

// // The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List& theList) {
//     theList.front() = 17;
//     theList.back() = 42;
// }
//
void changeFrontAndBack(List& theList) {
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// // Task 8
// void doNothing(List aList) {
//     cout << "In doNothing\n";
//     printListInfo(aList);
//     cout << "Leaving doNothing\n";
// }

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";

    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    printListInfo(myList);
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);


    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

    // // Task 8
    // cout << "\n------Task Eight------\n";
    // cout << "Copy control\n";
    // cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    // myList.clear();
    // for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    // printListInfo(myList);
    // cout << "Calling doNothing(myList)\n";
    // doNothing(myList);
    // cout << "Back from doNothing(myList)\n";
    // printListInfo(myList);
    //
    // cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    // List listTwo;
    // for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    // printListInfo(listTwo);
    // cout << "listTwo = myList\n";
    // listTwo = myList;
    // cout << "myList: ";
    // printListInfo(myList);
    // cout << "listTwo: ";
    // printListInfo(listTwo);
    // cout << "===================\n";
}
