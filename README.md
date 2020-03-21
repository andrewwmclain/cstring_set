# LAB 8 - C-String Set implemented with Linked List


## Goal

The goal of this lab is for you to practice:
- Multiple files compilation
- Command line compilation
- Apply pointers and dynamic memory by implementing a single linked list
- Apply dynamic memory allocation for the "data" of the nodes in the linked list
- Use Unit Tests to check the correct implementation of your program
- Testing your program for memory leaks (Using `valgrind`)

 
## Description
For this lab you will implement a class to represent a set of c-strings: `CStringSet`. This class will store the elements of the set using a single linked list.

The operations of the `CStringSet` are:

Operation | Description
--------- | -----------
Default Constructor | Creates an empty set
Copy Constructor | Creates a deep copy of the object
Constructor initializing with an array | Creates a set using the data given by an array taken as parameter. The array is not guaranteed to be sorted.
Destructor | Takes care of releasing the allocated memory, remember that for this class you will need to free the c-strings as well
Assignment Operator | Helps with the assignment of `CStringSet` objects
`Add` | To add an element to the set
`Remove` | Removes an element from the set
`Clear` | Removes all elements of the set
`Size` | Returns the number of elements in the set
`ToString` | returns a string representation of the set (i.e. `{Ann, Peter, Will}`)
`Read` | Reads the numbers of a set from an input stream
`Write` | Writes the elements of the set to an output stream
Union Operators | Overloads the `\|` and `\=` operators to operate the union of sets
Intersection Operators | Overloads the `&` and `&=` operators to operated the intersection of sets
Difference Operators |  Overloads the `-` and `-=` operators to operated the difference of sets
Symmetric Difference Operators |  Overloads the `^` and `^=` operators to operated the symmetric difference of sets
Equality Operator | Overloads the `==` operator to test if two sets are identical
Different Operator | Overloads the `!=` operator to test if two sets are different (not identical)
Proper Subset Operator | Overloads the `<` operator to test if the LHS is a proper subset of the RHS
Subset Operator | Overloads the `<=` operator to test if the LHS is a subset of the RHS
Proper Superset Operator | Overloads the `>` operator to test if the LHS is a proper superset of the RHS
Superset Operator | Overloads the `>=` operator to test if the LHS is a superset of the RHS
`IsMember` | Checks if the string is a member of the set
`IsDisjoint` | Checks wheter two sets are disjoint, that is their intersection is the empty set
`IsEmpty` | Checks whether a set has no elements or not.



### Linked List Implementation Details

For this lab you will use a single linked list. For this purpose you will need a `struct` to represent a _Node_ of the list. This `struct` is private to the class `CStringSet` since no other client needs to know about the specific implementation of the set.
The `struct` declaration is:
```cpp
struct Node{
    char* sz;
    Node* next;
};
```
Each node will contain a pointer to a dynamically allocated c-string, this represents a single element in the set, and a pointer to the next node.

The `CStringSet` class has one data member:
```cpp
    Node* _head;
```

The `_head` represents the first element in the list. By default, in the beginning this member is set to `nullptr`. 

The following image shows the internal representation of a set with elements Ann, John and Peter.
![SetExample](images/set-example.png)

The following images will show the progression of adding elements to the set. Please note that the set is always sorted!

When the set is just declared:
![Step1](images/set-step1.png)

After adding Pat.
![Step1](images/set-step2.png)

After adding Rae.
![Step1](images/set-step3.png)

After adding Qin.
![Step1](images/set-step4.png)

After adding Anne.
![Step1](images/set-step5.png)

Although is not shown in the pictures, the set never has repeated elements.

### More detailed description of methods

- **Default Constructor**, initializes `_head` to `nullptr`.Simple method: one liner!.
- **Copy Constructor**, creates a deep copy, traverses the original set adding each of its element to the new set. 
- **Constructor initializing with an array**, takes in an array and its size as parameter. Then it attempts to add each of the elements of the array to the set. The elements are not guaranteed to be sorted and there might be duplicates.
- **Destructor**, this method will take care of _cleaning up_ when an `CStringSet` object needs to be de-allocated. The method will traverse the list releasing the allocated memory for each of the nodes and each of the allocated c-strings. Be careful not to lose the reference of the next node before deleting the current one.
- **Assignment Operator**, very much like the Copy Constructor, but at the end it returns `*this`. 
- **`Add`** adds an element to the set. Issues to remember:
  - The set needs to be always sorted, so every time you add an element the first thing you need to do is find what is the appropriate place to insert the new element.
  - The set does not store repeated values, so if the value is already on the set, do not add it and return `false`.
  - Once you have successfully added the element to the set, you can return `true`.
  When adding an element to the list, remember to consider the different cases: the element should go before `_head`, the element goes after the `_head`, the element goes last, the list is empty.
- **`Remove`** removes an element from the set. The method removes the node containing the number from the list, remember to release the memory used by the removed node and the c-string the node points to. The method returns `true` if it successfully removes the element, `false` if it does not, for example, if the element was not on the set.
- **`Size`** returns the number of elements of the set. 
- **`ToString`** returns a string representation of the `CStringSet`. The string representation is just the strings on the set separated by commas and between curly braces: `{Albert, Betty, Dennis, Felix, Ion, Zeek}`. Notice there is a space after the comma.
- **`Read`** reads the the elements of a set from an input stream (it can be an `istringstream` or an `ifstream`, as a matter of fact any `istream`). There are no guarantees that the strings are going to be sorted or that there will be no duplicates. The method returns the number of elements that were actually added to the set. For instance if the input stream has the following data: `Jeff George Albert Jeff` then when calling the `Read` method on that input stream, the resulting set would be `{Albert, George, Jeff}` and the `Read` method would return `3`. 
- **`Write`** writes the elements of the set the the given output stream (it can be an `ostringstream` or an `ofstream`, as a matter of fact any `ostream`). The method just sends the elements separated by spaces to the output stream, no further formatting is required.
- **Union Operators** there are two union operators, one of them is `|=` and the other `|`.
  - `operator|=`, this overload will add the elements to `this`, thus modifying `this`. For example if `A={A, V, Z}` and `B={B, V, X}` then the operation `A |= B` would result in `A` changing into `{A, B, V, X, Z}`.
  - `operator|`, this is a non-member function, it will execute the union between the two sets sent as parameters: `lhs` and `rhs`. For example `A={X, Z}`, `B={R, X}`, the operation `C = A | B` would result in `C` becoming `{R, X, Z}` without changing `A` or `B`.
- **Intersection Operators** there are two intersection operators, one of them is `&=` and the other `&`.
  - `operator&=`, this overload will add the elements common to `this` and `rhs` (the parameter), thus modifying `this`. For example if `A={A, V, Z}` and `B={B, V, X}` then the operation `A &= B` would result in `A` changing into `{V}`.
  - `operator&`, this is a non-member function, it will execute the intersection between the two sets sent as parameters: `lhs` and `rhs`. For example `A={X, Z}`, `B={R, X}`, the operation `C = A & B` would result in `C` becoming `{X}` without changing `A` or `B`.
- **Difference Operators** there are two difference operators, one of them is `-=` and the other `-`.
  - `operator-=`, this overload will add the elements in `this` that are not in `rhs` (the parameter), thus modifying `this`. For example if `A={A, V, Z}` and `B={B, V, X}` then the operation `A -= B` would result in `A` changing into `{A, Z}`.
  - `operator-`, this is a non-member function, it will execute the difference between the two sets sent as parameters: `lhs` and `rhs`. For example `A={X, Z}`, `B={R, X}`, the operation `C = A - B` would result in `C` becoming `{Z}` without changing `A` or `B`.
- **Symmetric Difference Operators** there are two symmetric difference operators, one of them is `^=` and the other `^`.
  - `operator^=`, this overload will add the elements in `this` and in `rhs` (the parameter) without the common elements, thus modifying `this`. For example if `A={A, V, Z}` and `B={B, V, X}` then the operation `A ^= B` would result in `A` changing into `{A, B, X, Z}`.
  - `operator^`, this is a non-member function, it will execute the symmetric difference between the two sets sent as parameters: `lhs` and `rhs`. For example `A={X, Z}`, `B={R, X}`, the operation `C = A - B` would result in `C` becoming `{R, Z}` without changing `A` or `B`.
- **Relational Operators** these are operators to compare sets:
  - **Equality operator**: `operator==`, checks if `this` and the `rhs` are identical, returns `true` when they are, `false` otherwise
  - **Different operator**: `operator!=`, checks if `this` and `rhs` are not identical, returns `false` when they are identical, `false` otherwise
  - **Proper Subset**: `operator<`, checks if `this` elements are in `rhs`, but without being identical. Returns `true` if `this` is contained in `rhs`, `false` otherwise
  - **Subset**: `operator<=`, checks if `this` elements are in `rhs` it allows the two sets to be identical. Returns `true` if `this` is contained or is identical to `rhs`
  - **Proper Superset**: `operator>`, checks if `rhs` elements are in `this`, but without being identical. Returns `true` if `rhs` is contained in `this`, `false` otherwise
  - **Subset**: `operator>=`, checks if `rhs` elements are in `this` it allows the two sets to be identical. Returns `true` if `rhs` is contained or is identical to `this`
- **`IsMemeber`** takes in a c-string as parameter, the method returns `true` if the c-string is on the set, `false` otherwise.
- **`IsDisjoint`** takes in a `CStringSet`, returns `true` if the intersection of `this` and `rhs` is empty, `false` otherwise.
- **`IsEmpty`** returns `true` if the set is empty, that is if it has zero elements, it returns `false` otherwise.


## Sample Run (main)
We are providing the `main` program for this lab, you will not need to write this code!

To compile the program you will need to open your command line and move to the directory where your source code resides. You will find there the following files: `cstringset.h`, `cstringset.cpp`, `main.cpp`, `unit-test.cpp`, `test.h`, `test.cpp` and `makefile`. These are the files you are going to need to compile your program.


To compile run the following command: `make`. The `make` utility is a program that executes the `makefile`. In the `makefile` we have written instructions on how and what to compile to create the executable file. By running `make` the executable that will be created is `set`, given that your program compiles succesfully. This is the newly created executable. Your code should compile without errors and without warnings.

To run the program just type: `./set` and that will execute your program. The following text shows an instance of the program running. You are expected to write your own main program that has the exact same output as the one shown here.
```
root@fa746f285819:/tmp/tmp.ILoveSPU/# make
g++ -c main.cpp -std=c++14 -Wall -g
g++ cstringset.o main.o -o set -std=c++14 -Wall -g
root@fa746f285819:/tmp/tmp.ILoveSPU/# ./set
1. Set Union
2. Set Intersection
3. Set Difference
4. Set Symmetric Difference
5. Exit
1
Set A:
Input words to be included in the set all, enter a period to stop
Beta Alpha Gamma Pi Alpha .
Beta successfully added
Alpha successfully added
Gamma successfully added
Pi successfully added
Alpha already in the set
A = {Alpha, Beta, Gamma, Pi}
Set B:
Input words to be included in the set all, enter a period to stop
Gamma Zetta Pi Omega Pi .
Gamma successfully added
Zetta successfully added
Pi successfully added
Omega successfully added
Pi already in the set
B = {Gamma, Omega, Pi, Zetta}
A U B = C = {Alpha, Beta, Gamma, Omega, Pi, Zetta}
1. Set Union
2. Set Intersection
3. Set Difference
4. Set Symmetric Difference
5. Exit
2
Set A:
Input words to be included in the set all, enter a period to stop
A V Z .
A successfully added
V successfully added
Z successfully added
A = {A, V, Z}
Set B:
Input words to be included in the set all, enter a period to stop
X V B .
X successfully added
V successfully added
B successfully added
B = {B, V, X}
A n B = C = {V}
1. Set Union
2. Set Intersection
3. Set Difference
4. Set Symmetric Difference
5. Exit
3
Set A:
Input words to be included in the set all, enter a period to stop
A Z V .
A successfully added
Z successfully added
V successfully added
A = {A, V, Z}
Set B:
Input words to be included in the set all, enter a period to stop
X B V .
X successfully added
B successfully added
V successfully added
B = {B, V, X}
A - B = C = {A, Z}
1. Set Union
2. Set Intersection
3. Set Difference
4. Set Symmetric Difference
5. Exit
4
Set A:
Input words to be included in the set all, enter a period to stop
Z A V .
Z successfully added
A successfully added
V successfully added
A = {A, V, Z}
Set B:
Input words to be included in the set all, enter a period to stop
X V B .
X successfully added
V successfully added
B successfully added
B = {B, V, X}
A ^ B = C = {A, B, X, Z}
1. Set Union
2. Set Intersection
3. Set Difference
4. Set Symmetric Difference
5. Exit
5
Goodbye

```

### Error validation

Your program should be robust and not crash on wrong input. See the following sample run:
```
root@fa746f285819:/tmp/tmp.CodingIsFun/# ./set
1. Set Union
2. Set Intersection
3. Set Difference
4. Set Symmetric Difference
5. Exit
A
Incorrect input!
1. Set Union
2. Set Intersection
3. Set Difference
4. Set Symmetric Difference
5. Exit
7
Incorrect menu option!
1. Set Union
2. Set Intersection
3. Set Difference
4. Set Symmetric Difference
5. Exit
5
Goodbye
```


## Sample Run (unit test)

We are providing you with an additional file that has a `main` function. The source code is on the file `unit-test.cpp`. To run this you will need to compile it first. To compile you will need to run the command: `make test`. This command will create a new executable called `test`. To test your program you need only to run test: `./test`. 

When you run your test program the output should be:

```
ML-ARIAS:Lab8-Solution arias$ ./test
Initial: Size                            Passed   1 tests passed
Initial: Is Empty                        Passed   2 tests passed
Initial: ToString                        Passed   3 tests passed
Initial: IsMember                        Passed   4 tests passed
Initial: Remove                          Passed   5 tests passed
Add Element - "Canterbury"               Passed   6 tests passed
Add Repeated Element - "Canterbury"      Passed   7 tests passed
ToString Single Element                  Passed   8 tests passed
Size after adding one element            Passed   9 tests passed
Is Empty false after adding              Passed  10 tests passed
Add another element - "Geoffrey"         Passed  11 tests passed
Add another element - "Chaucer"          Passed  12 tests passed
Checking Size = 3                        Passed  13 tests passed
Checking elements are sorted             Passed  14 tests passed
Check IsMember("Canterbury")             Passed  15 tests passed
Check IsMember("Chaucer")                Passed  16 tests passed
Check IsMember("Geoffrey")               Passed  17 tests passed
Check !IsMember("Beowulf")               Passed  18 tests passed
Check !IsMember("Cat")                   Passed  19 tests passed
Check !IsMember("Dog")                   Passed  20 tests passed
Check !IsMember("Tales")                 Passed  21 tests passed
Check cannot remove "A"                  Passed  22 tests passed
Check cannot remove "Cat"                Passed  23 tests passed
Check cannot remove "Dog"                Passed  24 tests passed
Check cannot remove "Zzz"                Passed  25 tests passed
Check Remove "Chaucer"                   Passed  26 tests passed
Check ToString after Removing            Passed  27 tests passed
Check Size == 0 after Clear              Passed  28 tests passed
ToString after Clear                     Passed  29 tests passed
IsMember("Chaucer") after Clear          Passed  30 tests passed
IsMember("Geoffrey") after Clear         Passed  31 tests passed
Remove after Clear                       Passed  32 tests passed
- - - - - - - - - - - - - - - - - - - - - - - -
B a s i c    O p e r a t i o n s    P a s s e d
- - - - - - - - - - - - - - - - - - - - - - - -

Reading from Stream 10 values            Passed  33 tests passed
ToString after Reading from Stream       Passed  34 tests passed
Writing to Stream                        Passed  35 tests passed
Stream output                            Passed  36 tests passed
Reading additional 3, 1 repeated         Passed  37 tests passed
ToString after Reading from Stream       Passed  38 tests passed
Reading additional 1                     Passed  39 tests passed
ToString after Reading from Stream       Passed  40 tests passed
Read on empty string                     Passed  41 tests passed
ToString after Reading from Stream       Passed  42 tests passed
- - - - - - - - - - - - - - - - - - - - - - - -
  I / O     O p e r a t i o n s    P a s s e d
- - - - - - - - - - - - - - - - - - - - - - - -

Set from Array W Size                    Passed  43 tests passed
Set from Array X Size                    Passed  44 tests passed
Set from Array Y Size                    Passed  45 tests passed
Set from Array Z Size                    Passed  46 tests passed
Set X ToString                           Passed  47 tests passed
Set X ToString                           Passed  48 tests passed
Set Y ToString                           Passed  49 tests passed
Set Z ToString                           Passed  50 tests passed
- - - - - - - - - - - - - - - - - - - - - - - -
  A r r a y    O p e r a t i o n s    P a s s e d
- - - - - - - - - - - - - - - - - - - - - - - -

Intersection Size = 2                    Passed  51 tests passed
Intersection Result With 2 Elements      Passed  52 tests passed
Intersection Size = 1                    Passed  53 tests passed
Intersection Result With 1 Element       Passed  54 tests passed
Disjoint Intersection Size               Passed  55 tests passed
Disjoint Intersection Result             Passed  56 tests passed
Disjoint sets                            Passed  57 tests passed
Not Disjoint sets                        Passed  58 tests passed
Union of x and w Size                    Passed  59 tests passed
Union of x and w Result                  Passed  60 tests passed
Union of x and z Size                    Passed  61 tests passed
Union of x and z Result                  Passed  62 tests passed
Union of y and z Size                    Passed  63 tests passed
Union of y and z Result                  Passed  64 tests passed
Difference of w and z Size               Passed  65 tests passed
Difference of w and w Result             Passed  66 tests passed
Difference of x annd z Size              Passed  67 tests passed
Difference of x and z Result             Passed  68 tests passed
Difference of z and x Size               Passed  69 tests passed
Difference of z and x Result             Passed  70 tests passed
Symmetric Difference of w and x Size     Passed  71 tests passed
Symmetric Difference of w and x Result   Passed  72 tests passed
Symmetric Difference of x and z Size     Passed  73 tests passed
Symmetric Difference x and z Result      Passed  74 tests passed
Symmetric Difference of x and y Size     Passed  75 tests passed
Symmetric Difference of x and y Result   Passed  76 tests passed
- - - - - - - - - - - - - - - - - - - - - - - -
  S e t     O p e r a t i o n s    P a s s e d
- - - - - - - - - - - - - - - - - - - - - - - -

Proper Subset                            Passed  77 tests passed
Not Proper Subset                        Passed  78 tests passed
Subset                                   Passed  79 tests passed
Not Subset                               Passed  80 tests passed
Proper Superset                          Passed  81 tests passed
Not Proper Superset                      Passed  82 tests passed
Superset                                 Passed  83 tests passed
Not Superset                             Passed  84 tests passed
Equal                                    Passed  85 tests passed
Not Equal                                Passed  86 tests passed
- - - - - - - - - - - - - - - - - - - - - - - -
  R e l a t i o n a l     O p e r a t i o n s    P a s s e d
- - - - - - - - - - - - - - - - - - - - - - - -

- - - - - - - - - - - - - - - - - - - - - - - -
  S t a r t i n g    T i m e d   T e s t s
- - - - - - - - - - - - - - - - - - - - - - - -

Inserting 10,000 random elements: 91.2708 ms
Elements inserted: 6325
Inserting 10,000 random elements: 101.609 ms
Elements inserted: 6325
Union of two sets:        4.86197 ms	Size of LHS: 6325 Size of RHS: 6325 Size of Result: 8662
Intersection of two sets: 4.01065 ms	Size of LHS: 6325 Size of RHS: 6325 Size of Result: 3988
Difference of two sets:   3.47707 ms	Size of LHS: 6325 Size of RHS: 6325 Size of Result: 2337

Test Passed: 86		100%


All Unit Tests Passed!!!

    .     '     ,
      _________
   _ /_|_____|_\ _
     '. \   / .'
       '.\ /.'
         '.'



```

You are expected to run `valgrind` too, this way you will check if your code has any memory issues (i.e. memory leaks), the expected output should look like as follows:

```
root@f10904b8e654:Lab8-Solution # valgrind --leak-chek=full ./test
valgrind: Unknown option: --leak-chek=full
valgrind: Use --help for more information or consult the user manual.
root@f10904b8e654:Lab8-Solution # valgrind --leak-check=full ./test
==1819== Memcheck, a memory error detector
==1819== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==1819== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==1819== Command: ./test
==1819==
Initial: Size                            Passed   1 tests passed
Initial: Is Empty                        Passed   2 tests passed
Initial: ToString                        Passed   3 tests passed
Initial: IsMember                        Passed   4 tests passed
Initial: Remove                          Passed   5 tests passed
Add Element - "Canterbury"               Passed   6 tests passed
Add Repeated Element - "Canterbury"      Passed   7 tests passed
ToString Single Element                  Passed   8 tests passed
Size after adding one element            Passed   9 tests passed
Is Empty false after adding              Passed  10 tests passed
Add another element - "Geoffrey"         Passed  11 tests passed
Add another element - "Chaucer"          Passed  12 tests passed
Checking Size = 3                        Passed  13 tests passed
Checking elements are sorted             Passed  14 tests passed
Check IsMember("Canterbury")             Passed  15 tests passed
Check IsMember("Chaucer")                Passed  16 tests passed
Check IsMember("Geoffrey")               Passed  17 tests passed
Check !IsMember("Beowulf")               Passed  18 tests passed
Check !IsMember("Cat")                   Passed  19 tests passed
Check !IsMember("Dog")                   Passed  20 tests passed
Check !IsMember("Tales")                 Passed  21 tests passed
Check cannot remove "A"                  Passed  22 tests passed
Check cannot remove "Cat"                Passed  23 tests passed
Check cannot remove "Dog"                Passed  24 tests passed
Check cannot remove "Zzz"                Passed  25 tests passed
Check Remove "Chaucer"                   Passed  26 tests passed
Check ToString after Removing            Passed  27 tests passed
Check Size == 0 after Clear              Passed  28 tests passed
ToString after Clear                     Passed  29 tests passed
IsMember("Chaucer") after Clear          Passed  30 tests passed
IsMember("Geoffrey") after Clear         Passed  31 tests passed
Remove after Clear                       Passed  32 tests passed
- - - - - - - - - - - - - - - - - - - - - - - -
B a s i c    O p e r a t i o n s    P a s s e d
- - - - - - - - - - - - - - - - - - - - - - - -

Reading from Stream 10 values            Passed  33 tests passed
ToString after Reading from Stream       Passed  34 tests passed
Writing to Stream                        Passed  35 tests passed
Stream output                            Passed  36 tests passed
Reading additional 3, 1 repeated         Passed  37 tests passed
ToString after Reading from Stream       Passed  38 tests passed
Reading additional 1                     Passed  39 tests passed
ToString after Reading from Stream       Passed  40 tests passed
Read on empty string                     Passed  41 tests passed
ToString after Reading from Stream       Passed  42 tests passed
- - - - - - - - - - - - - - - - - - - - - - - -
  I / O     O p e r a t i o n s    P a s s e d
- - - - - - - - - - - - - - - - - - - - - - - -

Set from Array W Size                    Passed  43 tests passed
Set from Array X Size                    Passed  44 tests passed
Set from Array Y Size                    Passed  45 tests passed
Set from Array Z Size                    Passed  46 tests passed
Set X ToString                           Passed  47 tests passed
Set X ToString                           Passed  48 tests passed
Set Y ToString                           Passed  49 tests passed
Set Z ToString                           Passed  50 tests passed
- - - - - - - - - - - - - - - - - - - - - - - -
  A r r a y    O p e r a t i o n s    P a s s e d
- - - - - - - - - - - - - - - - - - - - - - - -

Intersection Size = 2                    Passed  51 tests passed
Intersection Result With 2 Elements      Passed  52 tests passed
Intersection Size = 1                    Passed  53 tests passed
Intersection Result With 1 Element       Passed  54 tests passed
Disjoint Intersection Size               Passed  55 tests passed
Disjoint Intersection Result             Passed  56 tests passed
Disjoint sets                            Passed  57 tests passed
Not Disjoint sets                        Passed  58 tests passed
Union of x and w Size                    Passed  59 tests passed
Union of x and w Result                  Passed  60 tests passed
Union of x and z Size                    Passed  61 tests passed
Union of x and z Result                  Passed  62 tests passed
Union of y and z Size                    Passed  63 tests passed
Union of y and z Result                  Passed  64 tests passed
Difference of w and z Size               Passed  65 tests passed
Difference of w and w Result             Passed  66 tests passed
Difference of x annd z Size              Passed  67 tests passed
Difference of x and z Result             Passed  68 tests passed
Difference of z and x Size               Passed  69 tests passed
Difference of z and x Result             Passed  70 tests passed
Symmetric Difference of w and x Size     Passed  71 tests passed
Symmetric Difference of w and x Result   Passed  72 tests passed
Symmetric Difference of x and z Size     Passed  73 tests passed
Symmetric Difference x and z Result      Passed  74 tests passed
Symmetric Difference of x and y Size     Passed  75 tests passed
Symmetric Difference of x and y Result   Passed  76 tests passed
- - - - - - - - - - - - - - - - - - - - - - - -
  S e t     O p e r a t i o n s    P a s s e d
- - - - - - - - - - - - - - - - - - - - - - - -

Proper Subset                            Passed  77 tests passed
Not Proper Subset                        Passed  78 tests passed
Subset                                   Passed  79 tests passed
Not Subset                               Passed  80 tests passed
Proper Superset                          Passed  81 tests passed
Not Proper Superset                      Passed  82 tests passed
Superset                                 Passed  83 tests passed
Not Superset                             Passed  84 tests passed
Equal                                    Passed  85 tests passed
Not Equal                                Passed  86 tests passed
- - - - - - - - - - - - - - - - - - - - - - - -
  R e l a t i o n a l     O p e r a t i o n s    P a s s e d
- - - - - - - - - - - - - - - - - - - - - - - -

- - - - - - - - - - - - - - - - - - - - - - - -
  S t a r t i n g    T i m e d   T e s t s
- - - - - - - - - - - - - - - - - - - - - - - -

Inserting 10,000 random elements: 5398.25 ms
Elements inserted: 6403
Inserting 10,000 random elements: 5218.09 ms
Elements inserted: 6316
Union of two sets:        120.345 ms	Size of LHS: 6403 Size of RHS: 6316 Size of Result: 8734
Intersection of two sets: 82.5498 ms	Size of LHS: 6403 Size of RHS: 6316 Size of Result: 3985
Difference of two sets:   66.3697 ms	Size of LHS: 6403 Size of RHS: 6316 Size of Result: 2418

Test Passed: 86		100%


All Unit Tests Passed!!!

    .     '     ,
      _________
   _ /_|_____|_\ _
     '. \   / .'
       '.\ /.'
         '.'


==1819==
==1819== HEAP SUMMARY:
==1819==     in use at exit: 0 bytes in 0 blocks
==1819==   total heap usage: 129,386 allocs, 129,386 frees, 1,429,589 bytes allocated
==1819==
==1819== All heap blocks were freed -- no leaks are possible
==1819==
==1819== For counts of detected and suppressed errors, rerun with: -v
==1819== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

```
Once you have passed all the unit tests your code is ready to be submitted.

## Description of Lab Files

- `cstringset.h` contains the `CStringSet` class declaration. This file should not be modified.
- `cstringset.cpp` contains the `CStringSet` class methods definition. This is where you will do most of your work.
- `main.cpp` contains the program that holds the menu shown in the previous section. It is provided to you.
- `unit-test.cpp` contains the unit tests for the `CStringSet` class. This file should not be modified.
- `test.cpp` and `test.h` contain helper functions for the unit tests. These files should not be modified.
- `makefile` contains the instructions on how to compile your code to produce the `set` program and the `test` program


## Style

Your program needs to be orderly and readable.  If you are working a development team and don’t write clean looking code, you will be unpopular among your colleagues and may not work on that team very long.  Because of this your program will be graded on style as well as correctness.  Please refer to the style guidelines discussed in class and in reading assignments concerning

  *	Indention of code
  *	Consistent use of {}, preferably Stroustrup style
  *	Meaningful names of identifiers
  *	Naming conventions for identifiers (camelCase for variables, CamelCase for function names. First word of a function name typically should be a verb. Data members with the _ prefix)
  *	No use of global variables. Global variables sometimes are appropriate, but not in the assignments we will be giving this quarter.
  *	Making sure `struct` and object parameters are passed by reference (and declared const if appropriate)
  
## Documentation
    
At the start of your file you should have a header comment that gives the title of the assignment, the purpose, and your name.  Here is an example (from Lab 1) of what that could look like:

```cpp
/*
    Title:      Lab 8 – CStringSet.cpp
    Purpose:    implement the CStringSet class methods
    Author:     John Wick
    Date:       January 6, 2020
*/
```
Each subordinate function should also start with a header that describes what it does, it’s parameters, what it returns, and how errors are handled.  Here is an example (again from Lab 1):

```cpp
// Produce a string of evaluation steps for simplifying an expression
// For example:
//      if “2+3*4-5”  is passed to this function, the string “2+3*4-5 = 2+12-5\n        = 14-5\n        = 9”
//      would be returned
// Parameters:
//      expression - an arithmetic expression
// Returns:
//      a string consisting of the evaluation steps needed to simplify the expression
// Possible Error Conditions: 
//      If evaluating the expression causes division by zero, this function crash.
//      If evaluating the expression causes an oveflow, the results may not be reliable.
```

You should include additional comments in your code to describe what you are doing.   If it is hard to understand what a variable is for, add a comment after it.   It possible, though, to put in too many comments, so be judicious and make sure you have time left to do well in your other classes when it comes to commenting.

## Submitting your code
Your solution should be contained within files that were provided.  You MUST NOT modify `unit-test.cpp`, `test.h`, `test.cpp`, `cstringset.h`, `makefile` or `CMakeFiles.txt`.

Make sure you test your code thoroughly.  We will try your code with our own test files, and we will programmatically test your database ADT with our own test program.  

Your code needs to be submitted through GitHub.  You will need to push your last version of your program before the lab deadline. As a good programming practice remember to commit frequently and to push every time you have a functioning version of your code.

## Grading
Correctness is essential.  Make sure your solution builds as described above and correctly handles the test cases displayed in the screen shot.  We will test on other input values as well. Your code must compile and should not have runtime errors (crash).

Even if your solution operates correctly, points will be taken off for:
- Not following the design described above
- Not adhering to style guidelines described above
- Using techniques not presented in class
- Programming error not caught by other testing
- Not following good programming practices

## Academic Integrity
This programming assignment is to be done on an individual basis. At the same time, it is understood that learning from your peers is valid and you are encouraged to talk among yourselves about programming in general and current assignments in particular.  Keep in mind, however, that each individual student must do the work in order to learn.  Hence, the following guidelines are established:
- Feel free to discuss any and all programming assignments but do not allow other students to look at or copy your code. Do not give any student an electronic or printed copy of any program you write for this class.
- Gaining the ability to properly analyze common programming errors is an important experience. Do not deprive a fellow student of his/her opportunity to practice problem solving: control the urge to show them what to do by writing the code for them.
- If you’ve given the assignment a fair effort and still need help, see the instructor or a lab assistant.
- **If there is any evidence that a program or other written assignment was copied from another student, neither student will receive any credit for it. This rule will be enforced.**
- Protect yourself: Handle throw-away program listings carefully, keep your repository private.

Refer to the ECS Department Policy on Academic Integrity that is included in the class syllabus.

## Grading Rubric Summary
The following aspects are going to be consider during grading. Make sure you comply with all of them.
- The program compiles (there will be no partial credit for programs that do not compile)
- Provides the correct output for the test cases
- Catches errors gracefully, the program does not crash on incorrect input
- The program outputs the information in the specified format
- The assignment follows all the instructions
- In general the program does not crash 

Refer to the Rubrics PPT on Canvas to refresh how Lab Assignments are graded.

**NOTE**: The runtime test of this lab will be the Unit Test.

