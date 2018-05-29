#include "WeightedGraph.h"
#include <iostream>

WeightedGraph::WeightedGraph(int V)
{
    this->V = V;
    adj = new townPair[V];
    calledDijkstra=vector<bool>(V,false);
}

void WeightedGraph::addJeweler(int u, int j) {
    adj[u].first.insert(j);
}

void WeightedGraph::addUndirectedEdge(int u, int v, int w, set<int> & t)
{
    Edge tmp(v, w, t);
    Edge tmp2(u, w, t);
    adj[u].second.push_back(tmp);
    adj[v].second.push_back(tmp2);
}

void WeightedGraph::shortestPath(int start_node, int start_dist) {
	set<int> start_coins = adj[start_node].first;
	vector<int> start_path; //path is empty at the start
	functionQueue.push( make_pair(make_pair( start_dist, start_node), make_pair(start_coins, start_path)) );
	while( !functionQueue.empty() ){
		functionPair curr_func = functionQueue.top();
		functionQueue.pop();
		if(!calledDijkstra[curr_func.first.second]){
			dijkstra(curr_func.first.second, curr_func.first.first, curr_func.second.first, curr_func.second.second);
			calledDijkstra[curr_func.first.second]=true;
		} 
	}
}

void WeightedGraph::dijkstra(int start_node, int start_dist, set<int>  coins, vector<int>  path)
{
    priority_queue< iPair, vector<iPair>, Comp > pq;
    vector<iPair> dist(V, make_pair(INF, -1));
   	vector<bool> visited(V, false);

    // initialize start_node
    pq.push(make_pair(start_dist, start_node));
    dist[start_node].first = start_dist;

    while (!pq.empty())
    {
        int curr_node = pq.top().second;
        pq.pop();
        visited[curr_node] = true;

        //if the current node is Tehran, we have arrived to destination with the shortest path
        if(curr_node == V-1) {
            break;
        }

	    //add new coins from curr_node if there exist any
        set<int> tmp(coins);
        set<int>::iterator it;
        for( it = adj[curr_node].first.begin(); it != adj[curr_node].first.end(); ++it)
        {
            tmp.insert(*it);
        }
        //if there is a new coin type in curr_node that we do not have, run dijkstra from this node
        if(tmp.size() > coins.size()){
        	vector<int> tmpPath;
            concatenatePaths(tmpPath, dist[curr_node].second, path, dist);
            functionQueue.push(make_pair(make_pair( dist[curr_node].first, curr_node), make_pair(tmp, tmpPath) ));
        }
        //else add neighbors to priority queue
        else{	
            list< Edge >::iterator itr;
            for (itr = adj[curr_node].second.begin(); itr != adj[curr_node].second.end(); ++itr)
            {
                //if the neighbor is not visited and we have the required coins, pass
                if( !visited[itr->endNode] && canPass(coins, itr->thieves) ){

                    int curr_neighbor = itr->endNode;
                    int curr_weight = itr->weight;

                    //  if there is a shorter path to curr_neighbor through curr_node
                    if (dist[curr_neighbor].first > dist[curr_node].first + curr_weight)
                    {
                        // update distance and uplink of curr_neighbor
                        dist[curr_neighbor].first = dist[curr_node].first + curr_weight;
                        dist[curr_neighbor].second = curr_node;
                        pq.push(make_pair(dist[curr_neighbor].first, curr_neighbor));
                    }
                }
            }
        }
    }
    if(dist[V-1].first < min_distance ){
        min_distance = dist[V-1].first;
    	vector<int> tmpPath;
        concatenatePaths(tmpPath, V-1, path, dist);
        min_path = tmpPath;
    }
}

void WeightedGraph::concatenatePaths(vector<int> & newPath, int start_node, const vector<int> & firstPath, const vector<iPair> & dist ) {
	vector<int> tmpPath;
    int tmplink = start_node;
    while(tmplink != -1) {
            tmpPath.push_back(tmplink);
            tmplink = dist[tmplink].second;
    }
    reverse(tmpPath.begin(), tmpPath.end());
    newPath.reserve( firstPath.size() + tmpPath.size() ); // preallocate memory
    newPath.insert( newPath.end(), firstPath.begin(), firstPath.end() );
    newPath.insert( newPath.end(), tmpPath.begin(), tmpPath.end() );
}

bool WeightedGraph::canPass(set<int> & coins, set<int> & thieves) {

    set<int>::iterator itr;
    for(itr = thieves.begin(); itr != thieves.end(); ++itr) {
        if( coins.find(*itr) == coins.end()) {
            return false;
        }
    }
    return true;
}

WeightedGraph::~WeightedGraph(){
    delete [] adj;
}