// Convert this program to C++
// change to C++ io
// change to one line comments
// change defines of constants to const
// change array to vector<>
// inline any short function

#include <iostream>
#include <vector>
using namespace :: std;

// change defines of constants to const
const int N = 40;

// inline sum function
template <typename T>
inline T sum(vector<T> data)
{
  T s = 0;
  for(int i = 0; i < data.size(); ++i)
    s += data[i];
  return s;
}

int main()
{
  // change array to vector<>
  vector<int> data(N);

  for(int i = 0; i < N; ++i)
    data[i] = i;

  cout << "sum is " << sum(data) << endl;
  return 0;
}
