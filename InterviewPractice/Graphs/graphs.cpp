//----------------------------------------------------------------------------------------------------------------------------------------------
/* //
Table of Contents
1. Check if Undirected Graph is Connected, BFS and DFS, T(n) = O(n), S(n) = O(1)

// TODO:
0. Check
1. BFS
2. DFS
3. Topological Sort
4. Djikstra
5. Given directed graph, find out if there exist ar oute between 2 nodes
//--------------------------------------------
Adjacency Matrix Representation and Adjacency List Representation
Incidence Matrix Representation and Incidence List Representation
note: Adjacency Matrix is much easier to implement in an interview
note: Adjacency List is easier to implement if you use the <list> STL and it is undirected 
note: Undirected is much easier than directed, since you don't need to store weight information 
    Otherwise, you need to clear an Edge class/struct to be able to store the edges
    information such as weight
    Adjacency Matrix > Adjacency List 
    for: 
    - accessing arbitrary node
    - checking if 2 nodes are connected by an edge 
    Bad for:
    - traversing through nodes connected to current node O(V) always
    Adjacency List > Adjancency Matrix 
    for:
    - space requirements (less space if no edge)
    - Traversing through the nodes connected to the current node  O(V) only in worst case where a node is connected to all other nodes

Note: Both incidence Matrix and Incidence list are terrible and should never be used
    Incidence Matrix is basically Adjacency Matrix nodes at rows and edges at columns, 
    each column only has 2 1's connected by the vertices and everything else 0
    Incidence List is basically a single linked list of the pair of vertex that are connected by an edge.
    BFS => Must use a queue
    DFS => Use recursion
*/
//----------------------------------------------------------------------------------------------------------------------------------------------
// 1 Check if undirected graph is connected
// Time Complexity, T(n) = O(n)
// Space Complexity, S(n) = O(1)
// Algorithm: 
// 1. Mark all nodes as not seen, O(n)
// 2. Traverse using BFS/DFS from any node O(n)
// 3. Check that all nodes are marked as seen, if not , it is unconnected, O(n)
// Use Adjacency List as it is more efficient than Adjacency Matrix in looking at the next edge node
// 1 = [2,3]    
// 2 = [1]
// 3 = [1]
//--------------------------------------------
#include <vector> // To hold all nodes that exist and index them quickly
#include <list> // To search through each adjacent node given a node
#include <queue> // For BFS traversal
#include <iostream> 
using namespace std; 

class Graph 
{
private:
    list<int> * adj;
    int numNodes; 
    vector<bool> visited;
    void DFS(int currNode);
public:
    Graph(int N)
    {
        this->numNodes = N;
        adj = new list<int>[N];
        for(int i = 0; i < N;i++)
            visited.push_back(false);
    }
    ~Graph()
    {
        delete [] adj;
    }
    void addEdge(int v, int w)
    {
        adj[v].push_back(w);
        adj[w].push_back(v);
    }
    bool isConnectedBFS(); // the main algorithm for this problem using BFS
    bool isConnectedDFS(); // the main algorithm for this problem using DFS
};
bool Graph::isConnectedDFS()
{
    for(int i = 0; i < numNodes; i++)
    {
        // reset all visited nodes to false
        visited[i] = false;
    }
    // Start with the first node
    visited[0] = true;
    for(auto i = adj[0].begin(); i != adj[0].end(); i++)
    {
        if(!visited[*i])
        {
            visited[*i] = true;
            this->DFS(*i);
        }
    }
    // Check all are true
    for(int i = 0; i < numNodes; i++)
    {
        // Graph is not connected fully if any nodes remain unvisited
        if(!visited[i]) return false;
    }
    return true;
}

void  Graph::DFS(int currNode)
{
    for(auto i = adj[currNode].begin(); i != adj[currNode].end(); i++)
    {
        if(!visited[*i])
        {
            visited[*i] = true;
            this->DFS(*i);
        }
    }
}

bool Graph::isConnectedBFS()
{
    for(int i = 0; i < numNodes; i++)
    {
        // reset all visited nodes to false
        visited[i] = false;
    }
    // Traverse the nodes of the first node
    queue<int> q; 
    q.push(0);
    while(!q.empty())
    {
        // MISTAKE: For queue, it is q.front(), only stacks are s.top()
        int node = q.front();
        q.pop();
        // set visited to true
        visited[node] = true;
        // auto => A C++11 feature, run with: g++ -std=c++11 fileName.cpp
        for(auto i = adj[node].begin(); i != adj[node].end(); i++)
        {
            if (!visited[*i])
                q.push(*i);
        }
    }
    for(int i = 0; i < numNodes; i++)
    {
        // Graph is not connected fully if any nodes remain unvisited
        if(!visited[i]) return false;
    }
    // All nodes were seen, graph is fully connected
    return true;
}

int main(void)
{
    Graph* g = new Graph(5);
    g->addEdge(0,1);
    g->addEdge(0,2);
    g->addEdge(1,3);
    // Nothing connects to node 4 
    bool answer = g->isConnectedBFS();
    if (answer) cout << "Connected!" << endl;
    else cout << "Not Connected!" << endl;
    answer = g->isConnectedDFS();
    if (answer) cout << "Connected!" << endl;
    else cout << "Not Connected!" << endl;
    g->addEdge(2,4);
    answer = g->isConnectedBFS();
    if (answer) cout << "Connected!" << endl;
    else cout << "Not Connected!" << endl;
    answer = g->isConnectedDFS();
    if (answer) cout << "Connected!" << endl;
    else cout << "Not Connected!" << endl;
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------------------
