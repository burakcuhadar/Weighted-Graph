#ifndef PROJECT3_WEIGHTEDGRAPH_H
#define PROJECT3_WEIGHTEDGRAPH_H

#include <list>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

# define INF 0x3f3f3f3f

struct Edge{
	int endNode = 0;
	int weight = 0;
	set<int> thieves;

	Edge(int e, int w, set<int> & t) {
		endNode = e;
		weight = w;
		thieves = t;
	}
};

typedef pair<int, int> iPair;
typedef pair<set<int>, list<Edge>> townPair;
typedef pair<set<int>, vector<int>> coinPath;
typedef pair<iPair, coinPath> functionPair;


struct Comp{
	bool operator()(const iPair& lhs, const iPair& rhs) {
		return lhs.first > rhs.first;
	}
};

struct Comp2{
	bool operator()(const functionPair& lhs, const functionPair& rhs) {
		return lhs.first.first > rhs.first.first;
	}
};

class WeightedGraph {
    int V = 0;          // number of vertices
    townPair *adj; // adjacency list
    priority_queue< functionPair, vector<functionPair>, Comp2 > functionQueue;
    vector<bool> calledDijkstra;	//stores whether dijkstra algorithm is called from a node
    //concatenates two paths and stores it in newPath
	void concatenatePaths(vector<int> & newPath, int start_node, const vector<int> & firstPath, const vector<iPair> & dist);

public:
	int min_distance = INF;
	vector<int> min_path;
    WeightedGraph(int V);   // constructor
    void addJeweler(int u, int j);	// add coin types to a town
    void addUndirectedEdge(int u, int v, int w, set<int> & thieves);     // add an undirected edge to graph
    void shortestPath(int start_node, int start_dist);	//helpe function for dijkstra function
    void dijkstra( int start_node, int start_dist, set<int> coins, vector<int> path); 
    bool canPass(set<int> & coins, set<int> & thieves);
    ~WeightedGraph();	//destructor
};

#endif 
