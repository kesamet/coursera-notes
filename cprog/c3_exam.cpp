#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

#define foo1( a ) (a * a)
inline int foo2( int a ) { return (a * a); }
inline int goo1( int x ) { return foo1(foo2(x)); }
inline int goo2( int& x ) { return x = foo2(foo1(x)); }
inline int goo3( int& x, int y ) { return foo2(foo1(y + 1)); }
inline void goo4( int& x, int y ) { x = foo1(foo2(y + 1)); }

void qn0()
{
    int i = 2, j = 1;
    cout << "foo1 = " << foo1( 1 + 2 + 3) << "\n";
    cout << "foo2 = " << foo2( 2 + 1 ) << "\n";
    cout << "goo1 = " << goo1( i ) << "\n";
    cout << "goo2 = " << goo2( j ) << "\n";
    cout << "goo3 = " << goo3( i, j ) << "\n";
    goo4( i, j );
    cout << "i = " << i << "\nj = " << j << "\n";
}

void qn1()
{
    int a = 2, b = -3, c = 2; 
    bool tval1 = false, tval2 = true;
    char ch = 'b';

    cout << b + c * a << endl;
    cout << c % 5 /2 << endl;
    cout << -a*c++ << endl;
    auto x = tval1 && tval2;
    cout << x << endl;
    ch+=2;
    cout << ch << endl;
}

template <class T1, class T2>

int mystery(T1& a, T2 b, int c)
{
    T1 t = a;
    a = a + b;
    return ( a - t + c);
}

void qn2()
{
    int a = 3;
    double b = 2.5;
    int c = 1;
    cout << " answer 1 is  " << mystery(a, 2, c) << endl;
    cout << " answer 2 is  " << mystery(a, 1, c) << endl;
    a = 5;
    cout << " answer 3 is  " << mystery(a, b, c) << endl;
    a = 2; 
    b = 2.5;
    cout << " answer 4 is  " << mystery(a, b, b) << endl;
    cout << " answer 5 is  " << mystery(a,mystery(a, b, b),c)<< endl;
}

void qn4()
{
    vector<int> data(5,1);
    int sum {0};

    cout << sum << endl;

    for(auto element : data)
        sum += element;

    cout << sum << endl;

    for(auto p = ++data.begin(); p != --data.end(); ++p)
        sum += *p;

    cout << sum << endl;

    sum = 0;
    data.push_back(2);
    data.push_back(3);
    for(auto element : data)
        sum += element;

    cout << sum << endl;
    cout << accumulate(data.begin(), data.end(), data[0]) << endl;
}

int main()
{
    qn0();
    cout << endl;
    qn1();
    cout << endl;
    qn2();
    cout << endl;
    qn4();
    return 0;
}
