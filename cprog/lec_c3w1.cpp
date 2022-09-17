#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
const int sides = 6;

inline int r_sides(){ return(rand() % sides + 1); }

int main()
{
  const int n_dice = 2;
  int d1, d2;
  srand(clock());
  cout << "\nEnter number of trials: ";
  int trials;
  cin >> trials;
  int* outcomes = new int[n_dice * sides + 1];

  for(int j = 0; j < trials;  ++j) {
    d1 = r_sides();
    d2 = r_sides();
    outcomes[d1 + d2]++;
  }

  cout << "\nProbability:" << endl;
  for(int j = 2; j < n_dice * sides + 1; ++j) {
    cout << "j = " << j << " p = "
      << static_cast<double>(outcomes[j]) / trials
      << endl;
  }
}
