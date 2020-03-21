//
// Created by Arias Arevalo, Carlos on 2/12/20.
//

#include "test.h"

#include <iostream>
#include <iomanip>
using std::ostream;
using std::endl;
using std::setw;
using std::left;
using std::right;


bool Test(bool condition, const char *message, ostream& output) {
    static int count = 0;
    if (condition){
        output << left << setw(40) << message  << right << " Passed"
               << setw(4) << ++count << " tests passed" << endl;
        return true;
    }else{
        output << setw(30) << message << " Failed" << endl;
        output << setw(4) << count << " tests passed in total" << endl;
        exit(1);
    }
}

