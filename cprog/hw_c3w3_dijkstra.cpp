#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>
using namespace :: std;

const double INFTY = 999999.0;

// Node
typedef struct Node Node;
struct Node
{
  int number;
  double weight;
};

// Graph class
class Graph
{
  public:
    Graph(int num_vertices = 0);
    int V();
    int E();
    double get_edge_value(int x, int y);
    void set_edge_value(int x, int y, double weight);
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
  
  for(int i = 0; i < adj_list[x].size(); ++i)
  {
    if(adj_list[x][i].number == y)
      return adj_list[x][i].weight;
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

void Graph::show()
{
  cout << "Graph: " << endl;
  for(int i = 0; i < adj_list.size(); ++i)
  {
    cout << "  Node" << i << endl;
    for(int j = 0; j < adj_list[i].size(); ++j)
    {
      int v2 = adj_list[i][j].number;
      double d2 = adj_list[i][j].weight;
      cout << "  -> Node" << v2 << " (w=" << d2 << ")" << endl;
    }
    cout << endl;
  }
}

// ShortestPath class
class ShortestPath
{
  public:
    ShortestPath(Graph g);
    vector<double> dijkstra(int source);
    double avg_distance(vector<double> distances);

  private:
    Graph graph;
};

// Constructor of ShortestPath class
ShortestPath::ShortestPath(Graph g)
{
  graph = g;
}

// Dijkstra algorithm
vector<double> ShortestPath::dijkstra(int source)
{
  int num_vertices = graph.V();

  typedef pair<double, int> pair0;
  priority_queue< pair0, vector<pair0>, greater<pair0> > Q;
  vector<double> distances(num_vertices, INFTY);  // store the shortest distance from source to the vertices indexed by number

  distances[source] = 0.0;

  // source pushed to stack
  Q.push(pair0(0.0, source));
  // Iterate until queue is empty
  while(!Q.empty())
  {
    // Pop the vertex with min distance from the source
    pair0 top = Q.top();
    Q.pop();
    int v = top.second;
    double d = top.first;

    if(d <= distances[v])
    {
      for(int v2 = 0; v2 < num_vertices; ++v2)
      {
        double d2 = graph.get_edge_value(v, v2);

        // if the earlier distance is more, update the distances array
        // and push the vertex into the queue
        if(distances[v2] > distances[v] + d2)
        {
          distances[v2] = distances[v] + d2;
          Q.push(pair0(distances[v2], v2));
        }
      }
    }
  }
  return distances;
}

// Compute average distance
double ShortestPath::avg_distance(vector<double> distances)
{
  double sum = 0.0;
  int num_neighbours = 0;
  for(int i = 0; i < distances.size(); ++i)
  {
    if((distances[i] != INFTY) && (distances[i] != 0.0))
    {
      sum += distances[i];
      num_neighbours += 1;
    }
  }
  return sum / num_neighbours;
}

// Monte Carlo class 
// To generate random graphs and run simulations
class MonteCarlo
{
  public:
    MonteCarlo();
    Graph randomGraph(int num_vertices, double density, double min_dist_edge, double max_dist_edge);
    void run(Graph g);

  private:
};

// Constructor of MonteCarlo Class
// Initializes the seed of random number generator
MonteCarlo::MonteCarlo()
{
  srand(time(NULL));
  // srand(10);
}

Graph MonteCarlo::randomGraph(int num_vertices, double density, double min_dist_edge, double max_dist_edge)
{
  double weight;
  
  Graph g(num_vertices);

  for(int i = 0; i < num_vertices; ++i)
  {
    for(int j = i + 1; j < num_vertices; ++j)
    {
      // double p = static_cast<double>(rand()) / RAND_MAX;	// Generate random probability
      double p = (1.0 * rand()) / RAND_MAX;	// Generate random probability
      if(p < density)	// If probability < density, set edge (i,j)
      {
        weight = (1.0 * rand()) / RAND_MAX * (max_dist_edge - min_dist_edge) + min_dist_edge; // Generate random weight 
        g.set_edge_value(i, j, weight);
      }
    }
  }
  return g;
}

void MonteCarlo::run(Graph g)
{
  // Print out graph information
  double d = (1.0 * g.E()) / (1.0 * (g.V() * (g.V() - 1)) / 2) * 100;	// actual density
  cout << "  Vertices: " << g.V() << endl;
  cout << "  Edges: " << g.E() << endl;
  cout << "  Density: " << d << "%" << endl;
  // g.show();

  ShortestPath shortestpath(g);
  vector<double> costs = shortestpath.dijkstra(0);
  cout << "  Avg path length: " << shortestpath.avg_distance(costs) << endl << endl;
}

int main()
{
  MonteCarlo simulation;

  // Create a graph with 50 nodes, density 20%
  Graph g = simulation.randomGraph(50, 0.2, 1.0, 10.0);
  simulation.run(g);

  // Create a graph with 50 nodes, density 40%
  g = simulation.randomGraph(50, 0.4, 1, 10);
  simulation.run(g);
  
  return 0;  
}
