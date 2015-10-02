//----------------------------------------------------------------------------------------------------------------------------------------------
/* //
Table of Contents
1. Check if an unweighted, acyclic directed/undirected graph is connected using BFS/DFS, T(n) = O(n), S(n) = O(1)

// TODO:
2. Check if graph is weakly connected component
0. Check
1. BFS
2. DFS
3. Topological Sort
4. Djikstra
5. Given directed graph, find out if there exist a route between 2 nodes
//--------------------------------------------
note: Complexity is measured in terms of |V| = number of nodes and |E| = number of edges!
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
    BFS => Must use a queue (append to back)
    DFS => Use recursion, or use a stack (Append to front)
            note: If you use recursion, you may end up visiting the first node in each list of edges of a node first
                  whereas in stack, you may end up visiting the last node in each list of edges of a node first
            note: Recursion => Call stack 
                  Stack => User Stack 
*/
//----------------------------------------------------------------------------------------------------------------------------------------------
// 1 Check if unweighted, acyclic directed/undirected graph is connected using BFS/DFS
// Time Complexity, T(V,E) = O(V+E)
// Space Complexity, S(V,E) = O(V)
// Algorithm: 
// 1. Mark all nodes as not seen, O(V)
// 2. Traverse using BFS/DFS from any node
//                  
//          BFS => Queue Implementation:
    //                 T(V,E) = O(V+E)
    //                 S(V,E) = O(V) // to maintain the queue of nodes to visit
//          DFS => Stack Implementation:
//                 T(V,E) = O(V+E)
//                 S(V,E) = O(V)  = O(bd) // to maintain the queue of nodes to visit, b = branching factor, d = depth of graph
//                          // note: More space as you push all current branch before recursing
//                 Recursive (call stack) Implementation:
//                 T(V,E) = O(V+E)
//                 S(V,E) = O(d) // d = Longest depth of graph (since program runs sequentially instead of in parallel,
//                              // it does not go through every node
//                             // note: use less space as you recursively first node of all branch and then next node later, so save more space
//                
// 3. Check that all nodes are marked as seen, if not , it is unconnected, O(n)
// Use Adjacency List as it is more efficient than Adjacency Matrix in looking at the next edge node
// 1 = [2,3]    
// 2 = [1]
// 3 = [1]
//--------------------------------------------
 //
#include <vector> // To hold all nodes that exist and index them quickly
#include <list> // To search through each adjacent node given a node
#include <queue> // For BFS traversal
#include <iostream> 
using namespace std; 

class Graph 
{
private:
    // Uses adjacency list representation
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
    void addEdgeUndirected(int v, int w)
    {
        adj[v].push_back(w);
        adj[w].push_back(v);
    }
    void addEdgeDirected(int v, int w)
    {
        adj[v].push_back(w);
    }
    bool isConnectedBFS(); // the main algorithm for this problem using BFS
    bool isConnectedDFS(); // the main algorithm for this problem using DFS
};
bool Graph::isConnectedDFS()
{
    // O(V)
    for(int i = 0; i < numNodes; i++)
    {
        // reset all visited nodes to false
        visited[i] = false;
    }
    // Start with the first node
    visited[0] = true;
    // O(V)
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

// O(E)
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
    for(int i = 0; i < numNodes; i++) // O(V)
    {
        // reset all visited nodes to false
        visited[i] = false;
    }
    // Traverse the nodes of the first node only
    queue<int> q; 
    visited[0] = true;
    q.push(0); 
    while(!q.empty()) // O(E)
    {
        // MISTAKE: For queue, it is q.front(), only stacks are s.top()
        int node = q.front();
        q.pop();
        // auto => A C++11 feature, run with: g++ -std=c++11 fileName.cpp
        for(auto i = adj[node].begin(); i != adj[node].end(); i++)
        {
            // MISTAKE: You only declare visited after popping from queue, should declare visited before popping to save space
                // note: You may end up inserting the same node twice if it has not been visited yet
                // therefore, you must check if(!visited[node]) above
                // This also means that the space complexity may be higher than just O(V) 
                // To prevent this, you have 3 states for each node instead of 2, 
                // Thus, whenever you push something into the queue, you change its state to the 2nd state and when you pop it, you change its state to 3rd state
                // OR just have 2 states but declare visited before pushing into queue so you dont push same node twice
            if (!visited[*i])
            {
                // Set node i to visited so you don't push it again in another node
                visited[*i] = true;
                q.push(*i); // S(V,E) = O(V), since you only push if it is not visited yet
            }
        }
        // Perform action on node here
    }
    // O(V)
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
    cout << "Undirected Graph" << endl;
    Graph* g = new Graph(5);
    g->addEdgeUndirected(0,1);
    g->addEdgeUndirected(0,2);
    g->addEdgeUndirected(1,3);
    // Nothing connects to node 4 
    bool answer = g->isConnectedBFS();
    if (answer) cout << "Connected!" << endl;
    else cout << "Not Connected!" << endl;
    answer = g->isConnectedDFS();
    if (answer) cout << "Connected!" << endl;
    else cout << "Not Connected!" << endl;
    g->addEdgeUndirected(2,4);
    answer = g->isConnectedBFS();
    if (answer) cout << "Connected!" << endl;
    else cout << "Not Connected!" << endl;
    answer = g->isConnectedDFS();
    if (answer) cout << "Connected!" << endl;
    else cout << "Not Connected!" << endl;
    delete g;
    cout << endl;
    cout << "Directed Graph" << endl;
    g = new Graph(5);
    g->addEdgeDirected(0,1);
    g->addEdgeDirected(0,2);
    g->addEdgeDirected(1,3);
    // Nothing connects to node 4 
    answer = g->isConnectedBFS();
    if (answer) cout << "Connected!" << endl;
    else cout << "Not Connected!" << endl;
    answer = g->isConnectedDFS();
    if (answer) cout << "Connected!" << endl;
    else cout << "Not Connected!" << endl;
    g->addEdgeDirected(2,4);
    answer = g->isConnectedBFS();
    if (answer) cout << "Connected!" << endl;
    else cout << "Not Connected!" << endl;
    answer = g->isConnectedDFS();
    if (answer) cout << "Connected!" << endl;
    else cout << "Not Connected!" << endl;
    return 0;
    // note: If this was a different problem and you need to traverse all nodes, you need to re-run the BFS/DFS algorithm on any nodes that are still unseen
    // as they were not connected to your starting node
}
// */
//----------------------------------------------------------------------------------------------------------------------------------------------
