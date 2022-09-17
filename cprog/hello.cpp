#include <iostream>
using namespace :: std;

int main()
{
    int a = 3, b = 4;
    cout << "++a = " << ++a << endl;  // 4
    cout << "b++ = " << b++ << endl;  // 4
    cout << "++a + b++ = " << ++a + b++ << endl;  // 5 + 5
    cout << "a = " << a << endl;  // 5
    cout << "b = " << b << endl;  // 6
    return 0;
}
