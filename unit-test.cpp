#include "cstringset.h"
#include "test.h"

#include <iostream>
#include <sstream>
#include <chrono>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::endl;
using std::stringstream;
using std::milli;
using std::chrono::time_point;
using std::chrono::steady_clock;
using std::chrono::duration;

int main(int argc, char* argv[]){
    CStringSet a;
    int testPassed = 0;
    const float TOTAL_TESTS = 86.0f;
    // Tests for Initial State
    if (Test(a.Size() == 0, "Initial: Size")){
        testPassed++;
    }
    if (Test(a.IsEmpty(), "Initial: Is Empty")){
        testPassed++;
    }
    if (Test(a.ToString() == "{}", "Initial: ToString")){
        testPassed++;
    }
    if (Test(!a.IsMember("null"), "Initial: IsMember")){
        testPassed++;
    }
    if (Test(!a.Remove("null"), "Initial: Remove")){
        testPassed++;
    }
    // Add elements
    if (Test(a.Add("Canterbury"), "Add Element - \"Canterbury\"")){
        testPassed++;
    }
    if (Test(!a.Add("Canterbury"), "Add Repeated Element - \"Canterbury\"")){
        testPassed++;
    }
    if (Test(a.ToString() == "{Canterbury}", "ToString Single Element")){
        testPassed++;
    }
    if (Test(a.Size() == 1, "Size after adding one element")){
        testPassed++;
    }
    if (Test(!a.IsEmpty(), "Is Empty false after adding")){
        testPassed++;
    }
    if (Test(a.Add("Geoffrey"), "Add another element - \"Geoffrey\"")){
        testPassed++;
    }
    if (Test(a.Add("Chaucer"), "Add another element - \"Chaucer\"")){
        testPassed++;
    }
    if (Test(a.Size() == 3, "Checking Size = 3")){
        testPassed++;
    }
    if (Test(a.ToString() == "{Canterbury, Chaucer, Geoffrey}", "Checking elements are sorted")){
        testPassed++;
    }
    if (Test(a.IsMember("Canterbury"), "Check IsMember(\"Canterbury\")")){
        testPassed++;
    }
    if (Test(a.IsMember("Chaucer"), "Check IsMember(\"Chaucer\")")){
        testPassed++;
    }
    if (Test(a.IsMember("Geoffrey"), "Check IsMember(\"Geoffrey\")")){
        testPassed++;
    }
    if (Test(!a.IsMember("Beowulf"), "Check !IsMember(\"Beowulf\")")){
        testPassed++;
    }
    if (Test(!a.IsMember("Cat"), "Check !IsMember(\"Cat\")")){
        testPassed++;
    }
    if (Test(!a.IsMember("Dog"), "Check !IsMember(\"Dog\")")){
        testPassed++;
    }
    if (Test(!a.IsMember("Tales"), "Check !IsMember(\"Tales\")")){
        testPassed++;
    }
    if (Test(!a.Remove("A"), "Check cannot remove \"A\"")){
        testPassed++;
    }
    if (Test(!a.Remove("Cat"), "Check cannot remove \"Cat\"")){
        testPassed++;
    }
    if (Test(!a.Remove("Dog"), "Check cannot remove \"Dog\"")){
        testPassed++;
    }
    if (Test(!a.Remove("Zzz"), "Check cannot remove \"Zzz\"")){
        testPassed++;
    }
    if (Test(a.Remove("Chaucer"), "Check Remove \"Chaucer\"")){
        testPassed++;
    }
    if (Test(a.ToString() == "{Canterbury, Geoffrey}", "Check ToString after Removing")){
        testPassed++;
    }
    a.Clear();
    if (Test(a.Size() == 0, "Check Size == 0 after Clear")){
        testPassed++;
    }
    if (Test(a.ToString() == "{}", "ToString after Clear")){
        testPassed++;
    }
    if (Test(!a.IsMember("Chaucer"), "IsMember(\"Chaucer\") after Clear")){
        testPassed++;
    }
    if (Test(!a.IsMember("Geoffrey"), "IsMember(\"Geoffrey\") after Clear")){
        testPassed++;
    }
    if (Test(!a.Remove("A"), "Remove after Clear")){
        testPassed++;
    }

    cout << "- - - - - - - - - - - - - - - - - - - - - - - -" << endl <<
            "B a s i c    O p e r a t i o n s    P a s s e d" << endl <<
            "- - - - - - - - - - - - - - - - - - - - - - - -" << endl << endl;

    stringstream data("45 44 93 31 68 36 58 87 45 31 72 93 40");
    if (Test(a.Read(data) == 10, "Reading from Stream 10 values")){
        testPassed++;
    }
    if (Test(a.ToString() == "{31, 36, 40, 44, 45, 58, 68, 72, 87, 93}", "ToString after Reading from Stream")){
        testPassed++;
    }
    stringstream outputTest;
    if (Test(a.Write(outputTest)==10,"Writing to Stream")){
        testPassed++;
    }
    if (Test(outputTest.str() == "31 36 40 44 45 58 68 72 87 93 ", "Stream output")){
        testPassed++;
    }
    data.clear();
    data.str("12 58 41");
    if (Test(a.Read(data) == 2, "Reading additional 3, 1 repeated ")){
        testPassed++;
    }
    if (Test(a.ToString() == "{12, 31, 36, 40, 41, 44, 45, 58, 68, 72, 87, 93}", "ToString after Reading from Stream")){
        testPassed++;
    }
    data.clear();
    data.str("61");
    if (Test(a.Read(data) == 1, "Reading additional 1")){
        testPassed++;
    }
    if (Test(a.ToString() == "{12, 31, 36, 40, 41, 44, 45, 58, 61, 68, 72, 87, 93}", "ToString after Reading from Stream")){
        testPassed++;
    }
    data.clear();
    data.str("");
    if (Test(a.Read(data) == 0, "Read on empty string")){
        testPassed++;
    }
    if (Test(a.ToString() == "{12, 31, 36, 40, 41, 44, 45, 58, 61, 68, 72, 87, 93}", "ToString after Reading from Stream")){
        testPassed++;
    }


    cout << "- - - - - - - - - - - - - - - - - - - - - - - -" << endl <<
         "  I / O     O p e r a t i o n s    P a s s e d" << endl <<
         "- - - - - - - - - - - - - - - - - - - - - - - -" << endl << endl;

    const char *setW[] = {"1", "4", "8", "13"}, *setX[] = {"1", "5", "8"}, *setY[] = {"3", "5", "13"}, *setZ[] = {"4", "8"};
    CStringSet w(setW, sizeof(setW) / sizeof(setW[0]));
    CStringSet x(setX, sizeof(setX) / sizeof(setX[0]));
    CStringSet y(setY, sizeof(setY) / sizeof(setY[0]));
    CStringSet z(setZ, sizeof(setZ) / sizeof(setZ[0]));

    if (Test(w.Size() == sizeof(setW) / sizeof(setW[0]), "Set from Array W Size")){
        testPassed++;
    }
    if (Test(x.Size() == sizeof(setX) / sizeof(setX[0]), "Set from Array X Size")){
        testPassed++;
    }
    if (Test(y.Size() == sizeof(setY) / sizeof(setY[0]), "Set from Array Y Size")){
        testPassed++;
    }
    if (Test(z.Size() == sizeof(setZ) / sizeof(setZ[0]), "Set from Array Z Size")){
        testPassed++;
    }

    if (Test(w.ToString() == "{1, 13, 4, 8}", "Set X ToString")){
        testPassed++;
    }
    if (Test(x.ToString() == "{1, 5, 8}", "Set X ToString")){
        testPassed++;
    }
    if (Test(y.ToString() == "{13, 3, 5}", "Set Y ToString")){
        testPassed++;
    }
    if (Test(z.ToString() == "{4, 8}", "Set Z ToString")){
        testPassed++;
    }
    cout << "- - - - - - - - - - - - - - - - - - - - - - - -" << endl <<
         "  A r r a y    O p e r a t i o n s    P a s s e d" << endl <<
         "- - - - - - - - - - - - - - - - - - - - - - - -" << endl << endl;

    CStringSet r;
    r = x & w;
    if (Test(r.Size() == 2, "Intersection Size = 2")){
        testPassed++;
    }
    if (Test(r.ToString() == "{1, 8}", "Intersection Result With 2 Elements")){
        testPassed++;
    }
    r = x & y;
    if (Test(r.Size() == 1, "Intersection Size = 1")){
        testPassed++;
    }
    if (Test(r.ToString() == "{5}", "Intersection Result With 1 Element")){
        testPassed++;
    }
    r = y & z;
    if (Test(r.Size() == 0, "Disjoint Intersection Size")){
        testPassed++;
    }
    if (Test(r.ToString() == "{}", "Disjoint Intersection Result")){
        testPassed++;
    }
    if (Test(y.IsDisjoint(z), "Disjoint sets")){
        testPassed++;
    }
    if (Test(!w.IsDisjoint(y), "Not Disjoint sets")){
        testPassed++;
    }
    r = x | w;
    if (Test(r.Size() == 5, "Union of x and w Size")){
        testPassed++;
    }
    if (Test(r.ToString() == "{1, 13, 4, 5, 8}", "Union of x and w Result")){
        testPassed++;
    }
    r = x | z;
    if (Test(r.Size() == 4, "Union of x and z Size")){
        testPassed++;
    }
    if (Test(r.ToString() == "{1, 4, 5, 8}", "Union of x and z Result")){
        testPassed++;
    }
    r = y | z;
    if (Test(r.Size() == 5, "Union of y and z Size")){
        testPassed++;
    }
    if (Test(r.ToString() == "{13, 3, 4, 5, 8}", "Union of y and z Result")){
        testPassed++;
    }
    r = w - x;
    if (Test(r.Size() == 2, "Difference of w and z Size")){
        testPassed++;
    }
    if (Test(r.ToString() == "{13, 4}", "Difference of w and w Result")){
        testPassed++;
    }
    r = x - z;
    if (Test(r.Size() == 2, "Difference of x annd z Size")){
        testPassed++;
    }
    if (Test(r.ToString() == "{1, 5}", "Difference of x and z Result")){
        testPassed++;
    }
    r = z - x;
    if (Test(r.Size() == 1, "Difference of z and x Size")){
        testPassed++;
    }
    if (Test(r.ToString() == "{4}", "Difference of z and x Result")){
        testPassed++;
    }
    r = w ^ x;
    if (Test(r.Size() == 3, "Symmetric Difference of w and x Size")){
        testPassed++;
    }
    if (Test(r.ToString() == "{13, 4, 5}", "Symmetric Difference of w and x Result")){
        testPassed++;
    }
    r = x ^ z;
    if (Test(r.Size() == 3, "Symmetric Difference of x and z Size")){
        testPassed++;
    }
    if (Test(r.ToString() == "{1, 4, 5}", "Symmetric Difference x and z Result")){
        testPassed++;
    }
    r = x ^ y;
    if (Test(r.Size() == 4, "Symmetric Difference of x and y Size")){
        testPassed++;
    }
    if (Test(r.ToString() == "{1, 13, 3, 8}", "Symmetric Difference of x and y Result")){
        testPassed++;
    }

    cout << "- - - - - - - - - - - - - - - - - - - - - - - -" << endl <<
         "  S e t     O p e r a t i o n s    P a s s e d" << endl <<
         "- - - - - - - - - - - - - - - - - - - - - - - -" << endl << endl;
    const char *setP[] = {"1", "4", "8", "13"}, *setN[] = {"1", "4", "8"}, *setO[] = {"1", "13", "4", "8"};
    CStringSet p(setP, sizeof(setP) / sizeof(setP[0]));
    CStringSet n(setN, sizeof(setN) / sizeof(setN[0]));
    CStringSet o(setO, sizeof(setO) / sizeof(setO[0]));

    if (Test(n < p, "Proper Subset")){
        testPassed++;
    }
    if (Test(!(p < n), "Not Proper Subset")){
        testPassed++;
    }
    if (Test(p <= o, "Subset")){
        testPassed++;
    }
    if (Test(!(p <= n), "Not Subset")){
        testPassed++;
    }
    if (Test(p > n, "Proper Superset")){
        testPassed++;
    }
    if (Test(!(n > o), "Not Proper Superset")){
        testPassed++;
    }
    if (Test(p >= o, "Superset")){
        testPassed++;
    }
    if (Test(!(n >= p), "Not Superset")){
        testPassed++;
    }
    if (Test(o == p, "Equal")){
        testPassed++;
    }
    if (Test(!(o != p), "Not Equal")){
        testPassed++;
    }


    cout << "- - - - - - - - - - - - - - - - - - - - - - - -" << endl <<
         "  R e l a t i o n a l     O p e r a t i o n s    P a s s e d" << endl <<
         "- - - - - - - - - - - - - - - - - - - - - - - -" << endl << endl;



    cout << "- - - - - - - - - - - - - - - - - - - - - - - -" << endl <<
         "  S t a r t i n g    T i m e d   T e s t s" << endl <<
         "- - - - - - - - - - - - - - - - - - - - - - - -" << endl << endl;

    time_point<steady_clock> start, end;
    srand(time(NULL));
    CStringSet k, l, m;
    start = steady_clock::now();
    for (int i = 0; i < 10000; ++i) {
        k.Add(std::to_string(rand() % 10000).c_str());
    }
    end = steady_clock::now();
    cout << "Inserting 10,000 random elements: " << duration<double, milli>(end - start).count() << " ms" << endl;
    cout << "Elements inserted: " << k.Size() << endl;

    start = steady_clock::now();
    for (int i = 0; i < 10000; ++i) {
        l.Add(std::to_string(rand() % 10000).c_str());
    }
    end = steady_clock::now();
    cout << "Inserting 10,000 random elements: " << duration<double, milli>(end - start).count() << " ms" << endl;
    cout << "Elements inserted: " << l.Size() << endl;

    start = steady_clock::now();
    m = k | l;
    end = steady_clock::now();
    cout << "Union of two sets:        " << duration<double, milli>(end - start).count() << " ms\t";
    cout << "Size of LHS: " << k.Size() << " Size of RHS: " << l.Size() << " Size of Result: " << m.Size() << endl;

    start = steady_clock::now();
    m = k & l;
    end = steady_clock::now();
    cout << "Intersection of two sets: " << duration<double, milli>(end - start).count() << " ms\t";
    cout << "Size of LHS: " << k.Size() << " Size of RHS: " << l.Size() << " Size of Result: " << m.Size() << endl;

    start = steady_clock::now();
    m = k - l;
    end = steady_clock::now();
    cout << "Difference of two sets:   " << duration<double, milli>(end - start).count() << " ms\t";
    cout << "Size of LHS: " << k.Size() << " Size of RHS: " << l.Size() << " Size of Result: " << m.Size() << endl;

    cout << endl << "Test Passed: " << testPassed << "\t\t"
         << testPassed / TOTAL_TESTS * 100 << "%" << endl << endl;
    cout << endl << "All Unit Tests Passed!!!" << endl << endl;

    cout
            << "    .     '     ,		" << endl
            << "      _________		    " << endl
            << "   _ /_|_____|_\\ _	    " << endl
            << "     '. \\   / .'		" << endl
            << "       '.\\ /.'		    " << endl
            << "         '.'			" << endl << endl << endl;


    return 0;
}
