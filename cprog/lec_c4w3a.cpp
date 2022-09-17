// Illustrate move semantics
#include <iostream>
using namespace std;

int main()
{
   int i {9};
   int* ptr_i ;
   int &&j = move(i);
   ptr_i = &j;
   cout << " Semantics of various declarations\n";
   cout << "i = "  << i << endl;
   cout << "j = "  << j << endl;
   cout << "&i = "  << &i << endl;
   cout << "ptr_i = "  << ptr_i << endl;
   ++i;
   cout << "i = "  << i << endl;
   cout << "j = "  << j << endl;
}

//  Semantics of various declarations
// i = 9
// j = 9
// &i = 0x16b08327c
// ptr_i = 0x16b08327c
// i = 10
// j = 10
