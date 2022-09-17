#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>
using namespace :: std;

const double INFTY=999999.0;

// Node
typedef struct Node Node;
struct Node
{
  int number;
  double weight;
};

// MST output
typedef struct mstOutput mstOutput;
struct mstOutput
{
  double cost;
  vector<int> edges;
  vector<double> distances;
};

// Graph class
class Graph
{
  public:
    Graph(int num_vertices = 0);
    Graph(const char* filename);
    int V();
    int E();
    double get_edge_value(int x, int y);
    void set_edge_value(int x, int y, double weight);
    mstOutput mst(int source);
    void show();

  private:
    int num_vertices;
    int num_edges;
    vector< vector<Node> > adj_list;
};

// Constructor of Graph class
Graph::Graph(int V)
{
  num_vertices = V;
  num_edges = 0;
  adj_list.resize(V);
}

// Constructor of Graph class by reading a file
Graph::Graph(const char* filename)
{
  // cout << __cplusplus << endl;
  ifstream fin;
  fin.open(filename);

  int V, v1, v2;
  double w;
  fin >> num_vertices;  // get number of nodes from file
  adj_list.resize(num_vertices);

  while(!fin.eof())
  {
    fin >> v1 >> v2 >> w;  // get edge (v1, v2) and weight w from file
    Node n_xy;
    n_xy.number = v2;
    n_xy.weight = w;
    adj_list[v1].push_back(n_xy);
    num_edges++;
  }
  fin.close();

  num_edges /= 2;  // edges are doubly counted
}

int Graph::V()
{
  return num_vertices;
}

int Graph::E()
{
  return num_edges;
}

// Get edge value between x and y, else return INFTY
double Graph::get_edge_value(int x, int y)
{
  
  for(vector<Node>::iterator p = adj_list[x].begin(); p != adj_list[x].end(); ++p)
  {
    if((*p).number == y)
      return (*p).weight;
  }
  return INFTY;
}

// Set edge value between x and y: x -> (y, weight)
void Graph::set_edge_value(int x, int y, double weight)
{
  // Store both directions for undirected graph
  Node n_xy;
  n_xy.number = y;
  n_xy.weight = weight;
  adj_list[x].push_back(n_xy);

  Node n_yx;
  n_yx.number = x;
  n_yx.weight = weight;
  adj_list[y].push_back(n_yx);

  num_edges += 1;
}

// Prim algorithm
mstOutput Graph::mst(int source)
{
  typedef pair<double, int> pair0;
  priority_queue< pair0, vector<pair0>, greater<pair0> > Q;
  vector<double> distances(num_vertices, INFTY);
  vector<int> edges(num_vertices, -1);
  vector<bool> inMST(num_vertices, false);
  int mstSize = 0;

  distances[source] = 0.0;
  Q.push(pair0(0.0, source));

  while((!Q.empty()) && (mstSize < num_vertices))
  {
    int v1 = Q.top().second;
    Q.pop();
    if(inMST[v1] == true)
      continue;
    inMST[v1] = true;
    mstSize += 1;

    for(vector<Node>::iterator p = adj_list[v1].begin(); p != adj_list[v1].end(); ++p)
    {
      int v2 = (*p).number;
      double d2 = (*p).weight;
      if(inMST[v2] == false && d2 < distances[v2])
      {
        distances[v2] = d2;
        edges[v2] = v1;
        Q.push(pair0(d2, v2));
      }
    }
  }

  double cost = 0.0;
  for(int i = 0; i < distances.size(); ++i)
    cost += distances[i];

  mstOutput result;
  result.cost = cost;
  result.edges = edges;
  result.distances = distances;
  return result;
}

void Graph::show()
{
  cout << "Graph: " << endl;
  for(int i = 0; i < adj_list.size(); ++i)
  {
    cout << "  Node" << i << endl;
    for(vector<Node>::iterator p = adj_list[i].begin(); p != adj_list[i].end(); ++p)
    {
      int v2 = (*p).number;
      double d2 = (*p).weight;
      cout << "  -> Node" << v2 << " (w=" << d2 << ")" << endl;
    }
    cout << endl;
  }
}

int main(int argc, char *argv[])
{
  if(argc != 2) {
      cout << "  Error: input filename is required" << endl;
      exit(1);
  }

  Graph g(argv[1]);
  // Graph g("SampleTestData_mst_data.txt");

  cout << "  Vertices: " << g.V() << endl;
  cout << "  Edges: " << g.E() << endl;
  // g.show();

  mstOutput result = g.mst(0);
  cout << "  MST cost: " << result.cost << endl;
  cout << "  MST:" << endl;  // Show MST tree
  for(int i = 0; i < g.V(); ++i)
    cout << "    " << i << " <- " << result.edges[i] << "  (w=" << result.distances[i] << ")" << endl;
}
