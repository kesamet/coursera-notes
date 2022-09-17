#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <random>
#include <algorithm>
using namespace std;

int myrandomfunc(int i) {return rand()%i;}

int main()
{
  srand(time(0));
  const int size=10;
  vector<int> best_moves_count(size);
  best_moves_count[2] = 5;
  best_moves_count[3] = 5;
  best_moves_count[4] = 5;

  // random_shuffle(best_moves_count.begin(), best_moves_count.end());
  for(int k=0; k<best_moves_count.size(); ++k){cout << best_moves_count[k] << " ";}
  cout << endl;

  vector<int> aa = best_moves_count;
  best_moves_count[3] = 1;

  // random_shuffle(best_moves_count.begin(), best_moves_count.end());
  for(int k=0; k<best_moves_count.size(); ++k){cout << best_moves_count[k] << " ";}
  cout << endl;
  for(int k=0; k<best_moves_count.size(); ++k){cout << aa[k] << " ";}
  cout << endl;

  // auto max_el = max_element(best_moves_count.begin(), best_moves_count.end());
  // int idx = distance(best_moves_count.begin(), max_el);
  // if(*max_el == 0)
  // {
  //   cout << "None found" << endl;
  // }
  // cout << idx << endl;
  const int max = *max_element(best_moves_count.begin(), best_moves_count.end());
  vector<int> indices;
  for(int i=0; i<best_moves_count.size(); ++i)
  {
    if(best_moves_count[i] == max)
      indices.push_back(i);
  }
  random_shuffle(indices.begin(), indices.end(), myrandomfunc);
  
  cout << indices[0] << endl;
}
