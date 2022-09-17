#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <random>
using namespace std;

const static int directions[6][2] =
{
  {-1, 0},  // top left
  {-1, 1},  // top right
  {0, -1},  // left
  {0, 1},  // right
  {1, -1},   // bottom left
  {1, 0}   // bottom right
};
enum class Player {BLUE, RED};
const static char Blank = '.';
const static char Blue = 'X';  // symbol for Player BLUE
const static char Red = 'O';  // symbol for Player RED

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
    bool within_board(int x, int y);
    void reach_borders(char symbol, int x, int y, vector<bool> &flags);
    void endgame_msg(Player p);
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

// Check if there is a path between respective borders
bool HexGraph::endgame(int x, int y)
{
  char symbol = board[x][y];
  vector<bool> flags(2, false);
  typedef pair<int, int> coords;
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
  cout << endl << "Player " << ((p == Player::BLUE) ? "Blue" : "Red");
  cout << "(" << ((p == Player::BLUE) ? Blue : Red) << ") ";
  cout << ((p == Player::BLUE) ? "(east-west)" : "(north-south)") << " wins!" << endl;
}

// Player input. Return true if game ends.
bool HexGraph::player_input(Player p)
{
  int x, y;
  cout << ((p == Player::BLUE) ? "Player Blue" : "Player Red") ;
  cout << ", input (row, col):" << endl;
  cin >> x >> y;

  while(!valid_move(x, y))
  {
    cout << "Invalid move! ";
    cout << ((p == Player::BLUE) ? "Player Blue" : "Player Red") ;
    cout << ", input (row, col) again:" << endl;
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
  do
  {
    x = rand() % size;
    y = rand() % size;
  }
  while(!valid_move(x, y));
  cout << ((p == Player::BLUE) ? "Player Blue" : "Player Red") ;
  cout << ", input (row, col): (" << x << ", " << y << ")" << endl;

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

int main0()
{
  const int size = 11;  // set board size
  HexGraph board(size);

  cout << "Player Blue plays east-west. Player Red plays north-south." << endl;

  int x, y;
  Player turn;
  int steps = 0;
  srand(time(0));
  while(true)
  {
    turn = ((steps % 2 == 0) ? Player::BLUE : Player::RED);
    do
    {
      x = rand() % size;
      y = rand() % size;
    }
    while(!board.valid_move(x, y));

    board.make_move(x, y, turn);

    cout << "Step " << steps << " - ";
    cout << "Player " << ((turn == Player::BLUE) ? "Blue" : "Red");
    cout << ": (" << x << ", " << y << ")" << endl;

    if((steps+1) % 10 == 0)
      board.show();

    if(board.endgame(x, y))
    {
      cout << endl << "Player " << ((turn == Player::BLUE) ? "Blue" : "Red");
      cout << "(" << ((turn == Player::BLUE) ? Blue : Red) << ") ";
      cout << ((turn == Player::BLUE) ? "(east-west)" : "(north-south)") << " wins!" << endl;
      board.show();
      break;
    }

    steps++;
  }

  return 0;
}

int main()
{
  int size;  // set board size
  cout << "Choose board size: ";
  cin >> size;
  HexGraph board(size);

  int human, computer;
  cout << "Player Blue plays east-west. Player Red plays north-south." << endl;
  cout << "Enter 0 for Blue(X) or 1 for Red(O) (Blue starts first): " << endl;
  cin >> human;
  computer = !human;

  Player turn;
  int steps = 0;
  while(true)
  {
    turn = ((steps % 2 == 0) ? Player::BLUE : Player::RED);
    if(steps % 2 == human)
    {
      if(board.player_input(turn))
        break;
    }
    else{
      if(board.computer_input(turn))
        break;
    }
    steps++;
  }

  return 0;
}
