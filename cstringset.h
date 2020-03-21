/*
 * Title:   Lab 8 - CStringSet.h
 *
 * Purpose: Declares the class CStringSet which is a Set of C-strings
 *          using a sorted linked list as the underlying data structure
 *
 * Class:   CSC 2430 Winter 2020
 * Author:  Max Benson and Carlos Arias
 */

#ifndef CSTRING_SET_H
#define CSTRING_SET_H

#include <string>
#include <iostream>
using std::string;
using std::istream;
using std::ostream;

class CStringSet{
public:
    // Default constructor
    CStringSet();

    // Copy Constructor
    CStringSet(const CStringSet& copyFromMe);

    // Constructor that takes an array
    CStringSet(const char *data[], size_t size);

    // Destructor
    ~CStringSet();

    // Copy Assignment operator
     CStringSet& operator=(const CStringSet& rhs);

    // Return count of elements
    size_t Size() const;

    // Add,  Remove
    bool Add(const char *sz);           // Adds an element to the set if not already present, the C string is copied when inserted, returns false if present
    bool Remove(const char *sz);        // Removes an element from the set, returns false if not present
    void Clear();                       // Remove all elements

    // Returns a string representation of the set
    string ToString()const;
    // Reads the elements from input and adds them to the set
    size_t Read(istream& input);
    // Sends the elements of the set to the output
    size_t Write(ostream& output)const;


    // Union Operator
    CStringSet& operator |=(const CStringSet&rhs);
    // Intersection Operator
    CStringSet& operator &=(const CStringSet&rhs);
    // Difference Operator
    CStringSet& operator -=(const CStringSet&rhs);
    // Symmetric Difference Operator
    CStringSet& operator ^=(const CStringSet&rhs);


    // Relational operators between sets
    bool operator==(const CStringSet& rhs) const;
    bool operator!=(const CStringSet& rhs) const;
    bool operator<(const CStringSet& rhs) const;
    bool operator<=(const CStringSet& rhs) const;
    bool operator>(const CStringSet& rhs) const;
    bool operator>=(const CStringSet& rhs) const;

    // Other relationship testing
    bool IsMember(const char* sz) const;
    bool IsDisjoint(const CStringSet& rhs) const;
    bool IsEmpty() const;


private:
    struct Node{
       char *sz;
       Node* next;
    };

    // Head of the list
    Node* _head;
};

// Binary operators
CStringSet operator|(const CStringSet& lhs, const CStringSet& rhs);
CStringSet operator&(const CStringSet& lhs, const CStringSet& rhs);
CStringSet operator-(const CStringSet& lhs, const CStringSet& rhs);
CStringSet operator^(const CStringSet& lhs, const CStringSet& rhs);


#endif