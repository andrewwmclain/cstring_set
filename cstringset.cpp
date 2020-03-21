/*
 * Title:   Lab 8 - CStringSet.cpp
 *
 * Purpose: Implement the class CStringSet which is a set of C-strings
 *          using a sorted linked list as the underlying data structure
 *
 * Class:   CSC 2430 Winter 2020
 * Author:  Max Benson and Carlos Arias
 */

#include "cstringset.h"
#include <sstream>
#include <cstring>
using std::stringstream;

/**
 * Default Constructor.
 * Sets the _head to nullptr
 */
CStringSet::CStringSet(){
    //initialize _head to nullptr
    _head = nullptr;
}


/**
 * Copy Constructor.
 * Creates a deep copy of the copyFromMe String Set
 * @param copyFromMe
 */
CStringSet::CStringSet(const CStringSet& copyFromMe){
    //Write from set being copied, read to destination set
    stringstream ss;
    copyFromMe.Write(ss);
    Read(ss);
}


/**
 * Destructor.
 * Deallocates the memory used by the String Set. Remember to free the memory
 * that is used to dynamically store the string. So, you must delete the c-string
 * and the node.
 */
CStringSet::~CStringSet() {
    //Deallocates each node in set when object runs out of scope
    Clear();
}

/**
 * Copy Assignment Operator.
 * Makes a deep copy of rhs into this. Remember to check if there are no
 * self assignments.
 * @param rhs String Set to be assigned to this
 * @return *this
 */
CStringSet& CStringSet::operator=(const CStringSet& rhs){
    //if rhs is the same place in the heap, return this set
    if(this == &rhs){
        return *this;
    }
    //clear contents of this set
    Clear();
    //write from rhs and read to this set
    stringstream ss;
    rhs.Write(ss);
    Read(ss);
    return *this;
}


/**
 * Constructor that takes an array of c-strings.
 * This constructor takes an array of c-strings called data. The size of the array is store
 * in the parameter size. You will need to add each of the elements of the array into the
 * String Set, remember there are no guarantees that the array is sorted or that there are
 * no duplicates.
 * @param data the name of the array of strings, data[0] represents the 0th element of the array.
 * @param size the number of elements in the array
 */
CStringSet::CStringSet(const char *data[], size_t size){
    //if array is empty, just set _head to nullptr without adding anything
    if(size == 0){
        _head = nullptr;
    }
    //otherwise, add each index from the array to this set
    else{
        _head = nullptr;
        for(size_t i = 0; i < size; i++){
            Add(data[i]);
        }
    }
}

/**
 * Union Operator.
 * This operator executes the Union between rhs and this placing the result in this.
 * For example:
 * CStringSet a, b;
 * a.Add("Love");
 * a.Add("Peace");
 * a.Add("Harmony");
 * b.Add("Peace");
 * b.Add("Strength");
 * cout << a.ToString() << endl; // outputs: {Harmony, Love, Peace}
 * cout << b.ToString() << endl; // outputs: {Peace, Strength}
 * a |= b;
 * cout << a.ToString() << endl; // outputs: {Harmony, Love, Peace, Strength}
 * cout << b.ToString() << endl; // outputs: {Peace, Strength}
 * @param rhs the right hand side operand of the union operation
 * @return *this with the elements of rhs (Union)
 */
CStringSet& CStringSet::operator|=(const CStringSet& rhs){
    //write from rhs and read to this set
    stringstream ss;
    rhs.Write(ss);
    Read(ss);
    return *this;
}

/**
 * Intersection Operator.
 * This operator executes the Intersection between rhs and this placing the result in this.
 * For example:
 * CStringSet a, b;
 * a.Add("Love");
 * a.Add("Peace");
 * a.Add("Harmony");
 * b.Add("Peace");
 * b.Add("Strength");
 * cout << a.ToString() << endl; // outputs: {Harmony, Love, Peace}
 * cout << b.ToString() << endl; // outputs: {Peace, Strength}
 * a &= b;
 * cout << a.ToString() << endl; // outputs: {Peace}
 * cout << b.ToString() << endl; // outputs: {Peace, Strength}
 * @param rhs the right hand side operand of the intersection operation
 * @return *this only with the common elements of rhs and this (Intersection)
 */
CStringSet& CStringSet::operator&=(const CStringSet& rhs){
    stringstream thisSS;
    string rhsStr;
    string thisStr;

    //write from this set to thisSS and put elements of rhs into a string
    Write(thisSS);
    rhsStr = rhs.ToString();

    //read a word from thisSS
    while(thisSS >> thisStr){
        //if that word is not found in rhs, then remove it from this set
        if(rhsStr.find(thisStr) == string::npos){
            Remove(thisStr.c_str());
        }
    }
    return *this;
}

/**
 * Difference Operator.
 * This operator executes the Difference between rhs and this placing the result in this.
  * You may want to consider the case that the two sets are equal...
* For example:
 * CStringSet a, b;
 * a.Add("Love");
 * a.Add("Peace");
 * a.Add("Harmony");
 * b.Add("Peace");
 * b.Add("Strength");
 * cout << a.ToString() << endl; // outputs: {Harmony, Love, Peace}
 * cout << b.ToString() << endl; // outputs: {Peace, Strength}
 * a -= b;
 * cout << a.ToString() << endl; // outputs: {Harmony, Love}
 * cout << b.ToString() << endl; // outputs: {Peace, Strength}
 * @param rhs the right hand side operand of the difference operation
 * @return *this without the elements of rhs (Difference)
 */
CStringSet& CStringSet::operator-=(const CStringSet& rhs){
    stringstream rhsSS;
    string rhsStr;
    string thisStr;

    //write elements of rhs into rhsSS and store elements of this set in string thisStr
    rhs.Write(rhsSS);
    thisStr = ToString();

    //read a word from rhs
    while(rhsSS >> rhsStr){
        //if that word from rhs is found in this set, remove it from this set
        if(thisStr.find(rhsStr) != string::npos){
            Remove(thisStr.c_str());
        }
    }
    return *this;
}
/**
 * Symmetric Difference Operator.
 * This operator executes the Symmetric Difference between rhs and this placing the result in this. The symmetric
 * difference is defined as the set of elements in both sets except the elements they have in common. You can
 * check: https://en.wikipedia.org/wiki/Symmetric_difference for further reference.
 * You may want to consider the case that the two sets are equal...
 * For example:
 * CStringSet a, b;
 * a.Add("Love");
 * a.Add("Peace");
 * a.Add("Harmony");
 * b.Add("Peace");
 * b.Add("Strength");
 * cout << a.ToString() << endl; // outputs: {Harmony, Love, Peace}
 * cout << b.ToString() << endl; // outputs: {Peace, Strength}
 * a ^= b;
 * cout << a.ToString() << endl; // outputs: {Harmony, Love, Strength}
 * cout << b.ToString() << endl; // outputs: {Peace, Strength}
 * @param rhs the right hand side operand of the symmetric difference operation
 * @return *this with the elements of rhs and this but without the common elements (Symmetric Difference)
 */
CStringSet& CStringSet::operator^=(const CStringSet& rhs){
    stringstream rhsSS;
    string rhsStr;
    string thisStr;

    //write elements of rhs into stream rhsSS, store elements of this set in string thisStr
    rhs.Write(rhsSS);
    thisStr = ToString();

    //read a word from rhs
    while(rhsSS >> rhsStr){
        //if that word is not found in this set, add it to this set
        if(thisStr.find(rhsStr) == string::npos){
            Add(rhsStr.c_str());
        }
        //otherwise, if that word is found, remove it from this set
        else{
            Remove(rhsStr.c_str());
        }
    }
    return *this;
}

/**
 * Equality.
 * This operator checks if two sets have the exact same elements.
 * @param rhs the right hand side operand of the expression
 * @return true if the two sets have the exact same elements, false otherwise
 */

bool CStringSet::operator==(const CStringSet& rhs)const{
    string lhsStr;
    string rhsStr;

    //if sizes are different, they cannot be equal
    if(Size() != rhs.Size()){
        return false;
    }
    //store this set as a string, store rhs as a string
    lhsStr = ToString();
    rhsStr = rhs.ToString();
    //if the strings are equal, the sets are equal
    if(lhsStr != rhsStr){
        return false;
    }
    return true;
}

/**
 * Inequality.
 * This operator checks if two sets have different elements.
 * @param rhs the right hand side operand of the expression
 * @return false if the two sets have the exact same elements, true otherwise
 */
bool CStringSet::operator!=(const CStringSet& rhs)const{
    //use == overloaded operator
    return !(*this == rhs);
}

/**
 * Proper Subset (Contains)
 * This operator executes the contains set operation. This operation is defined as follows:
 * A is said to be a proper subset of B if A is contained in B. If all elements of A are in B then
 * A is a subset of B, but the two sets are not equal.
 * Example:
 * A = {1, 2, 6}
 * B = {1, 2, 3, 6, 9}
 * C = {1, 2, 6}
 * A is a proper subset of B
 * A is not a proper subset of C
 * @param rhs the right hand side operand of the expression
 * @return true if this is a proper subset of rhs, false otherwise
 */
bool CStringSet::operator<(const CStringSet& rhs) const{
    //if sets are equal, this is not a proper subset of rhs
    if(*this == rhs){
        return false;
    }
    //store this set into stringstream thisSS, store rhs into a string rhsStr
    stringstream thisSS;
    Write(thisSS);
    string thisStr;
    string rhsStr = rhs.ToString();

    //read a word from this set
    while(thisSS >> thisStr){
        //if this set has a word that is not found in rhs, this set is not a proper subset of rhs
        if(rhsStr.find(thisStr) == string::npos){
            return false;
        }
    }
    return true;
}

/**
 * Subset (Contains)
 * This operator executes the contains set operation. This operation is defined as follows:
 * A is said to be a subset of B if A is contained in B. If all elements of A are in B then
 * A is a subset of B, the two sets can be equal.
 * Example:
 * A = {1, 2, 6}
 * B = {1, 2, 3, 6, 9}
 * C = {1, 2, 6}
 * A is a subset of B
 * A is a subset of C
 * @param rhs the right hand side operand of the expression
 * @return true if this is a subset of rhs, false otherwise
 */
 bool CStringSet::operator<=(const CStringSet& rhs)const{
     //if this set is equal to rhs, it is a subset of rhs
    if(*this == rhs){
        return true;
    }
    //write this set into stringstream thisSS, store rhs as a string
    stringstream thisSS;
    Write(thisSS);
    string thisStr;
    string rhsStr = rhs.ToString();

    //read a word from this set
    while(thisSS >> thisStr){
        //if this set has a word that is not found in rhs, it is not a subset of rhs
        if(rhsStr.find(thisStr) == string::npos){
            return false;
        }
    }
    return true;
 }

/**
 * Proper Superset (Is Contained)
 * This operator executes the is contained set operation. This operation is defined as follows:
 * A is said to be a proper superset of B if B is a proper subset of A.
 * Example:
 * A = {1, 2, 6}
 * B = {1, 2, 3, 6, 9}
 * C = {1, 2, 6}
 * B is a proper superset of A
 * C is not a proper super
 * A is not a proper subset of C
 * @param rhs the right hand side operand of the expression
 * @return true if this is a proper superset of rhs, false otherwise
 */
bool CStringSet::operator>(const CStringSet& rhs)const{
    //if this set is the same as rhs, this set is not a proper superset of rhs
    if(*this == rhs){
        return false;
    }
    //write rhs into a stringstream rhsSS, store this set into a string
    stringstream rhsSS;
    rhs.Write(rhsSS);
    string rhsStr;
    string thisStr = ToString();

    //read a word from rhs
    while(rhsSS >> rhsStr){
        //if rhs has a word that is not found in this set, this set is not a proper superset of rhs
        if(thisStr.find(rhsStr) == string::npos){
            return false;
        }
    }
    return true;
}

/**
 * Superset (Is Contained)
 * This operator executes the is contained set operation. This operation is defined as follows:
 * A is said to be a superset of B if B is a subset of A.
 * Example:
 * A = {1, 2, 6}
 * B = {1, 2, 3, 6, 9}
 * C = {1, 2, 6}
 * B is a superset of A
 * C is a superset of A
 * @param rhs the right hand side operand of the expression
 * @return true if this is a superset of rhs, false otherwise
 */
bool CStringSet::operator>=(const CStringSet& rhs)const{
    //if this set is equal to rhs, this set is a superset of rhs
    if(*this == rhs){
        return true;
    }
    //write rhs into stringstream rhsSS, store this set as string thisStr
    stringstream rhsSS;
    rhs.Write(rhsSS);
    string rhsStr;
    string thisStr = ToString();

    //read a wore from rhs
    while(rhsSS >> rhsStr){
        //if rhs has a word that is not found in this set, this set is not a superset of rhs
        if(thisStr.find(rhsStr) == string::npos){
            return false;
        }
    }
    return true;
}
/**
 * Belongs Operation
 * Tests whether a string belongs to the set or not, in other words if the word is found in the set or not.
 * @param sz the string that we are testing for.
 * @return true if sz is found in the set, false otherwise
 */
bool CStringSet::IsMember(const char* sz)const{
    //store this set as a string thisStr
    string thisStr = ToString();
    //if the word is not in this set, it does not belong in this set
    if(thisStr.find(sz) == string::npos){
        return false;
    }
    return true;
}
/**
 * Disjoint
 * Test whether this and rhs are disjoint or not. Two sets are said to be disjoint if the intersection of them
 * results in an empty set
 * @param rhs the set that we are using to test this with
 * @return true if the this and rhs are disjoint
 */
 bool CStringSet::IsDisjoint(const CStringSet& rhs)const{
     //Make a set C that is the intersection of this set and rhs
     CStringSet C = *this & rhs;
     //If C is empty, that means this set and rhs have no common elements
     if(C.IsEmpty()){
         return true;
     }
     else{
         return false;
     }
 }

/**
 * Is Empty
 * Checks whether the set is empty or not
 * @return true if there are no elements in the set, false otherwise
 */
bool CStringSet::IsEmpty() const{
    if(Size() == 0){
        return true;
    }
    return false;
}

/**
 * Size
 * Counts how many elements are in the set.
 * @return the number of elements in the set
 */
size_t CStringSet::Size()const{
    size_t size = 0;
    Node* tmp = _head;
    //iterate through this set until the end is hit, incrementing size at each counted node
    while(tmp != nullptr){
        size++;
        tmp = tmp->next;
    }
    return size;
}

/**
 * Add
 * Adds a string to the set. Note that you should not add strings that are already in the set, also, make
 * sure that the underlying list is always sorted. Remember to allocate space for the node AND for the string!
 * @param sz the string that is going to be added to the set
 * @return true if the string was added to the set, false otherwise (the string was already in the set)
 */

bool CStringSet::Add(const char *sz){
    //if list is empty, add to _head
    if(IsEmpty()){
        _head = new Node;
        _head->sz = new char[strlen(sz) + 1];
        _head->next = nullptr;
        strcpy(_head->sz, sz);
        return true;
    }
    //if first element sz is equal to sz, can't add
    if(strcmp(_head->sz, sz) == 0){
        return false;
    }
    //tmp node to traverse w/o changing list
    Node* tmp = _head;
    //if first element is greater than sz, change _head
    if(strcmp(_head->sz, sz) > 0){
        Node* neo = new Node;
        neo->sz = new char[strlen(sz) + 1];
        strcpy(neo->sz, sz);
        neo->next = _head;
        _head = neo;
        return true;
    }
    //try to add in middle of list
    while(tmp->next != nullptr){
        if(strcmp(tmp->next->sz, sz) == 0){
            return false;
        }
        //if next node greater than current node, insert after current node
        if(strcmp(tmp->next->sz, sz) > 0){
            Node* neo = new Node;
            neo->sz = new char[strlen(sz) + 1];
            strcpy(neo->sz, sz);
            neo->next = tmp->next;
            tmp->next = neo;
            return true;
        }
        tmp = tmp->next;
    }
    //if end of list reached, add to end of list
    Node* neo = new Node;
    neo->sz = new char[strlen(sz) + 1];
    strcpy(neo->sz, sz);
    neo->next = nullptr;
    tmp->next = neo;
    return true;
}

/**
 * Remove
 * Removes a string from the set if possible, the string might not be in the set. Remember to free
 * the memory from the node and from the c-string.
 * @param sz the string to be removed
 * @return true if the string was removed, false otherwise (the string was not found)
 */

bool CStringSet::Remove(const char *sz){
    //if list is empty, return false
    if(IsEmpty()){
        return false;
    }
    Node* prev = _head;
    Node* curr = _head->next;
    //if first element is to be removed
    if(strcmp(_head->sz, sz) == 0){
        delete[] prev->sz;
        delete prev;
        _head = curr;
        return true;
    }
    while(curr != nullptr){
        if(strcmp(curr->sz, sz) == 0){
            prev->next = curr->next;
            delete[] curr->sz;
            delete curr;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    //element not found
    return false;
}

/**
 * Clear
 * Removes all element from the list.
 */
void CStringSet::Clear(){
    //if this set is already empty, do nothing
    if(IsEmpty()){
        return;
    }
    else{
        //make two temporary traversal nodes
        Node* curr = _head;
        Node* nxt = curr->next;
        //iterate until end of list is hit, deleting each node and cstring inside
        while(curr != nullptr) {
            nxt = curr->next;
            delete[] curr->sz;
            delete curr;
            curr = nxt;
        }
        _head = nullptr;
    }
}

/**
 * ToString
 * Creates a C++ string representation of the set. Example: {Albert, Peter, Zach}
 * @return a string containing the elements of the set with a { preceeding the first element and } after
 * the last element. Elements are separated by commas.
 */

string CStringSet::ToString()const{
    //if the set is empty, return empty brackets
    if(IsEmpty()){
        return "{}";
    }
    string setStr;
    setStr.append("{");
    Node* tmp = _head;
    //traverse list, adding node cstrings to the string until second to last node (fencepost)
    while(tmp->next != nullptr){
        setStr.append(tmp->sz);
        setStr.append(", ");
        tmp = tmp->next;
    }
    //add last plank on the fencepost (no comma)
    setStr.append(tmp->sz);
    setStr.append("}");
    return setStr;
}

/**
 * Read
 * Reads from an input stream a sequence of strings, and then it adds the strings. There are no guarantees that
 * the strings on the stream are sorted or that there are no duplicates
 * @param input the input stream to read from
 * @return the number of elements added to the set
 */

size_t CStringSet::Read(istream& input){
    //keep track of numAdded, starting at 0 and incrementing for each word added
    size_t numAdded = 0;
    string word;
    //add word by word until input stream runs out
    while(input >> word){
        if(Add(word.c_str())){
            numAdded++;
        }
    }
    return numAdded;
}

/**
 * Write
 * Writes to an output stream the elements of the set.
 * @param output the output stream to write to
 * @return the number of strings output to the stream, it should be the same number of elements in the set
 */

size_t CStringSet::Write(ostream& output)const{
    //initialize size and temporary traversal node
    size_t numWritten = 0;
    Node* tmp = _head;
    //traverse set, adding cstring to output stream at each node
    while(tmp != nullptr){
        output << tmp->sz;
        output << " ";
        numWritten++;
        tmp = tmp->next;
    }
    return numWritten;
}

// * * * * * * *  H I N T  * * * * * * *
// The following four functions for the operator overload of |, &, - and ^
// Remember that they are not members of the class, therefore they don't have access to the
// private variables or methods of the class. You may want to consider using
// public methods or operators that are publicly overloaded.

/**
 * Union Operator (without modifying this!)
 * Notice that this is not a member function, it's a plain function!
 * @param lhs left hand side operand of the expression
 * @param rhs right hand side operand of the expression
 * @return a new set with the elements of lhs and rhs, notice that neither operand is modified.
 */
CStringSet operator|(const CStringSet& lhs, const CStringSet& rhs){
    //create a third set C
    stringstream rhsSS;
    stringstream lhsSS;
    CStringSet C;

    //write rhs and lhs to stringstreams
    rhs.Write(rhsSS);
    lhs.Write(lhsSS);

    //read from rhs and lhs into C
    C.Read(lhsSS);
    C.Read(rhsSS);
    return C;
}
/**
 * Intersection Operator (without modifying this!)
 * Notice that this is not a member function, it's a plain function!
 * @param lhs left hand side operand of the expression
 * @param rhs right hand side operand of the expression
 * @return a new set with the common elements of lhs and rhs, notice that neither operand is modified.
 */
 CStringSet operator&(const CStringSet& lhs, const CStringSet& rhs){
     //create new set C
    CStringSet C;
    stringstream rhsSS;
    string lhsStr;
    string rhsStr;

    //write from rhs into a stringstream, store lhs as a string
    rhs.Write(rhsSS);
    lhsStr = lhs.ToString();

    //read a word from rhs
    while(rhsSS >> rhsStr){
        //if the word from rhs is also found in lhs, add it to C
        if(lhsStr.find(rhsStr) != string::npos){
            C.Add(rhsStr.c_str());
        }
    }
    return C;
 }

/**
 * Difference Operator (without modifying this!)
 * Notice that this is not a member function, it's a plain function!
 * @param lhs left hand side operand of the expression
 * @param rhs right hand side operand of the expression
 * @return a new set with the elements of lhs and without the elements of rhs, notice that neither operand is modified.
 */
CStringSet operator-(const CStringSet& lhs, const CStringSet& rhs){
    //create a third set C
    CStringSet C;
    stringstream lhsSS;
    string lhsStr;
    string rhsStr;

    //write lhs into stringstream lhsSS, store rhs as a string rhsStr
    lhs.Write(lhsSS);
    rhsStr = rhs.ToString();

    //read a word from lhs
    while(lhsSS >> lhsStr){
        //if the word from lhs is not found in rhs, add it to C
        if(rhsStr.find(lhsStr) == string::npos){
            C.Add(lhsStr.c_str());
        }
    }
    return C;
}
/**
 * Symmetric Difference Operator (without modifying this!)
 * Notice that this is not a member function, it's a plain function!
 * @param lhs left hand side operand of the expression
 * @param rhs right hand side operand of the expression
 * @return a new set with the of lhs and rhs but without the common elements, notice that neither operand is modified.
 */
CStringSet operator^(const CStringSet& lhs, const CStringSet& rhs){
    //Create a new set C which has all of the elements from lhs and rhs
    CStringSet C = lhs | rhs;
    stringstream rhsSS;
    string rhsStr;
    string lhsStr;

    //store rhs into a stringstream rhsSS
    rhs.Write(rhsSS);
    lhsStr = lhs.ToString();

    //read a word from rhs
    while(rhsSS >> rhsStr){
        //if the word from rhs is found in lhs, remove it from C
        if(lhsStr.find(rhsStr) != string::npos){
            C.Remove(rhsStr.c_str());
        }
    }
    return C;
}




