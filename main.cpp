#include "cstringset.h"

#include <iostream>
#include <iomanip>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

int Menu();
CStringSet CreateSet();

int main() {
    int option;
    while ((option = Menu())){
        if (option == 1){
            cout << "Set A:" << endl;
            CStringSet a = CreateSet();
            cout << "A = " << a.ToString() << endl;
            cout << "Set B:" << endl;
            CStringSet b = CreateSet();
            cout << "B = " << b.ToString() << endl;
            CStringSet c = a | b;
            cout << "A U B = C = " << c.ToString() << endl;
        }
        else if (option == 2){
            cout << "Set A:" << endl;
            CStringSet a = CreateSet();
            cout << "A = " << a.ToString() << endl;
            cout << "Set B:" << endl;
            CStringSet b = CreateSet();
            cout << "B = " << b.ToString() << endl;
            CStringSet c = a & b;
            cout << "A n B = C = " << c.ToString() << endl;

        }
        else if (option == 3) {
            cout << "Set A:" << endl;
            CStringSet a = CreateSet();
            cout << "A = " << a.ToString() << endl;
            cout << "Set B:" << endl;
            CStringSet b = CreateSet();
            cout << "B = " << b.ToString() << endl;
            CStringSet c = a - b;
            cout << "A - B = C = " << c.ToString() << endl;
        }
        else if (option == 4){
            cout << "Set A:" << endl;
            CStringSet a = CreateSet();
            cout << "A = " << a.ToString() << endl;
            cout << "Set B:" << endl;
            CStringSet b = CreateSet();
            cout << "B = " << b.ToString() << endl;
            CStringSet c = a ^ b;
            cout << "A ^ B = C = " << c.ToString() << endl;
        }
        else{
            cout << "Goodbye" << endl << endl;
            break;
        }
    }
    return 0;
}


int Menu(){
    int option = 0;
    while(true){
        cout << "1. Set Union" << endl;
        cout << "2. Set Intersection" << endl;
        cout << "3. Set Difference" << endl;
        cout << "4. Set Symmetric Difference" << endl;
        cout << "5. Exit" << endl;
        cin >> option;
        if (cin.fail()){
            cin.clear();
            cin.ignore(255, '\n');
            cerr << "Incorrect input!" << endl;
            continue;
        }
        if (option < 1 || option > 5){
            cerr << "Incorrect menu option!" << endl;
            continue;
        }
        break;
    }
    return option;
}

CStringSet CreateSet(){
    cout << "Input words to be included in the set all, enter a period to stop" << endl;
    string word;
    CStringSet retVal;
    while (cin >> word) {
        if (word == ".") {
            break;
        }
        if (retVal.Add(word.c_str())){
            cout << word.c_str() << " successfully added" << endl;
        }
        else{
            cout << word.c_str() << " already in the set" << endl;
        }
    }
    return retVal;
}