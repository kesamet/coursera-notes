#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <random>
#include <algorithm>
using namespace std;

const static int directions[6][2] =
{
  {-1, 0},  // top left
  {-1, 1},  // top right
  {0, -1},  // left
  {0, 1},  // right
  {1, -1},  // bottom left
  {1, 0}   // bottom right
};
enum class Player {BLUE, RED};
const static char Blank = '.';
const static char Blue = 'X';  // symbol for Player BLUE
const static char Red = 'O';  // symbol for Player RED
typedef pair<int, int> coords;
const static bool useAI = true;

int myrandomfunc(int i) {return rand()%i;}

// HexGraph class
class HexGraph
{
  public:
    HexGraph(int sz): size(sz), board(sz, vector<char>(size, '.')){};
    void show();
    bool valid_move(int row, int col);
    void make_move(int row, int col, Player p);
    bool endgame(int x, int y);
    bool player_input(Player p);
    bool computer_input(Player p);

  private:
    int size;
    vector< vector<char> > board;
    const int ntrials = 1000;
    bool within_board(int x, int y);
    void reach_borders(char symbol, int x, int y, vector<bool> &flags);
    void endgame_msg(Player p);
    coords AIguess(Player p);
};

// Check if (row, col) is within board
bool HexGraph::within_board(int row, int col)
{
  return row>=0 && row<size && col>=0 && col<size;
}

// Check if (row, col) is within board and not occupied
bool HexGraph::valid_move(int row, int col)
{
  return within_board(row, col) && board[row][col] == Blank;
}

// Update board at (row, col) with player's symbol
void HexGraph::make_move(int row, int col, Player p)
{
  if(p == Player::BLUE)
    board[row][col] = Blue;
  else
    board[row][col] = Red;
}

// Set true if player has a position on respective borders
void HexGraph::reach_borders(char symbol, int row, int col, vector<bool> &flags)
{
  if((symbol == Blue && col == 0) || (symbol == Red && row == 0))
    flags[0] = true;
  else if((symbol == Blue && col == size-1) || (symbol == Red && row == size-1))
    flags[1] = true;
}

coords HexGraph::AIguess(Player p)
{
  vector< vector<char> > original_board = board;  // copy of original board
  Player counterplayer = ((p == Player::BLUE) ? Player::RED : Player::BLUE);
  char symbol = ((p == Player::BLUE) ? Blue : Red);

  vector<coords> empty_pos;
  for(int i=0; i<size; ++i)
  {
    for(int j=0; j<size; ++j)
    {
      if(board[i][j] == Blank)
        empty_pos.push_back(coords(i, j));
    }
  }
  
  vector<int> best_moves_count(size*size, 0);  // store all winning moves using flattened board (row*size+col)
  for(int n=0; n<ntrials; ++n)
  {
    // Randomize empty positions
    random_shuffle(empty_pos.begin(), empty_pos.end(), myrandomfunc);

    // Populate remaining positions on board
    board = original_board;
    for(int i=0; i<empty_pos.size(); ++i)
    {
      if(i % 2 == 0)
        make_move(empty_pos[i].first, empty_pos[i].second, p);
      else
        make_move(empty_pos[i].first, empty_pos[i].second, counterplayer);
    }

    // Store all winning moves
    for(int i=0; i<empty_pos.size(); ++i)
    {
      if(board[empty_pos[i].first][empty_pos[i].second] == symbol && endgame(empty_pos[i].first, empty_pos[i].second))
        ++best_moves_count[empty_pos[i].first*size+empty_pos[i].second];
    }
  }

  // TODO: checking
  for(int k=0; k<best_moves_count.size(); ++k){cout << best_moves_count[k] << " ";}
  cout << endl;

  board = original_board;  // revert to original board

  const int max = *max_element(best_moves_count.begin(), best_moves_count.end());
  vector<int> indices;  // store all indices with same max
  for(int i=0; i<best_moves_count.size(); ++i)
  {
    if(best_moves_count[i] == max)
      indices.push_back(i);
  }
  random_shuffle(indices.begin(), indices.end(), myrandomfunc);  // tie breaker
  return coords(indices[0]/size, indices[0]%size);
}

// Check if there is a path between respective borders
bool HexGraph::endgame(int x, int y)
{
  char symbol = board[x][y];
  vector<bool> flags(2, false);
  queue<coords> Q;
  vector< vector<bool> > visited(size, vector<bool>(size));

  Q.push(coords(x, y));
  visited[x][y] = true;
  while(!Q.empty())
  {
    coords top = Q.front();
    Q.pop();
    reach_borders(symbol, top.first, top.second, flags);

    for(int i=0; i<6; ++i)
    {
      int row = top.first + directions[i][0];
      int col = top.second + directions[i][1];
      if(within_board(row, col) && board[row][col] == symbol && !visited[row][col])
      {
        visited[row][col] = true;
        Q.push(coords(row, col));
      }
    }
  }
  return flags[0] && flags[1];
}

// Winner message helper
void HexGraph::endgame_msg(Player p)
{
  cout << endl << "Player " << ((p == Player::BLUE) ? "Blue(X) (east-west)" : "Red(O) (north-south)");
  cout << " wins!" << endl;
}

// Player input. Return true if game ends.
bool HexGraph::player_input(Player p)
{
  int x, y;
  while(true)
  {
    cout << ((p == Player::BLUE) ? "Player Blue" : "Player Red");
    cout << " (you), input (row, col):" << endl;
    if(cin >> x >> y)
      break;
    else
    {
      cout << "Wrong input. Enter valid input." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }

  while(!valid_move(x, y))
  {
    cout << "Invalid move! ";
    cout << ((p == Player::BLUE) ? "Player Blue" : "Player Red");
    cout << " (you), input (row, col) again:" << endl;
    cin >> x >> y;
  }

  make_move(x, y, p);

  if(endgame(x, y))
  {
    endgame_msg(p);
    show();
    return true;
  }
  show();
  return false;
}

// Computer input. Return true if game ends.
bool HexGraph::computer_input(Player p)
{
  srand(time(0));
  int x, y;
  if(useAI)
  {
    coords pos = AIguess(p);
    x = pos.first;
    y = pos.second;
  }
  else
  {
    do
    {
      x = rand() % size;
      y = rand() % size;
    }
    while(!valid_move(x, y));
  }
  cout << ((p == Player::BLUE) ? "Player Blue" : "Player Red") ;
  cout << " (computer), input (row, col): (" << x << ", " << y << ")" << endl;

  make_move(x, y, p);

  if(endgame(x, y))
  {
    endgame_msg(p);
    show();
    return true;
  }
  show();
  return false;
}

// To show board
void HexGraph::show()
{
  string edges = "\\";
  for (int i=1; i<size; ++i)
    edges += " / \\";

  // first line
	cout << endl << board[0][0];
	for(int j=1; j<size; ++j)
		cout << " - " << board[0][j];
	cout << endl;

	string space = "";
	for(int i=1; i<size; ++i)
	{
		space += ' ';
		cout << space << edges << endl;
		space += ' ';
		cout << space << board[i][0];
		for(int j=1; j<size; ++j)
			cout << " - " << board[i][j];
		cout << endl;
	}

  cout << endl;
  for(int k=0; k<size*6; ++k)
    cout << "=";
  cout << endl;
}

int main()
{
  const int size = 7;  // set board size
  HexGraph boardgraph(size);

  cout << "Player Blue plays east-west. Player Red plays north-south." << endl;

  // Alternate between 2 computers
  int steps = 0;
  while(true)
  {
    if(steps % 2 == 0)
    {
      if(boardgraph.computer_input(Player::BLUE))
        break;
    }
    else{
      if(boardgraph.computer_input(Player::RED))
        break;
    }
    steps++;
  }

  return 0;
}

int main0()
{
  int size;  // set board size
  while(true)
  {
    cout << "Enter board size: " << endl;
    if(cin >> size)
      break;
    else
    {
      cout << "Wrong input. Enter valid input." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
  // const int size = 5;
  HexGraph boardgraph(size);

  int human, computer;
  cout << "Player Blue plays east-west. Player Red plays north-south." << endl;
  while(true)
  {
    cout << "Enter 0 for Blue(X) or 1 for Red(O) (Blue starts first): " << endl;
    if(cin >> human && (human == 0 || human == 1))
      break;
    else
    {
      cout << "Wrong input. Enter valid input (0 or 1)." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
  computer = !human;

  // Alternate between human and computer
  Player turn;
  int steps = 0;
  while(true)
  {
    turn = ((steps % 2 == 0) ? Player::BLUE : Player::RED);
    if(steps % 2 == human)
    {
      if(boardgraph.player_input(turn))
        break;
    }
    else{
      if(boardgraph.computer_input(turn))
        break;
    }
    steps++;
  }

  return 0;
}
