//----------------------------------------------------------------------------------------------------------------------------------------------
/* // 
Table of Contents
1. Check if an unweighted, acyclic directed/undirected graph is connected using BFS/DFS, T(n) = O(n), S(n) = O(1)
2. Djikstra Algorithm Using Binary Heap: Find single-source shortest path for Directed, Weighted Graphs, weight >= 0, T(V,E) = O(ElogV), S(V,E) = O(V + E)
3. Prim's Algorithm using Binary Heap: Find Minimum Spanning Tree of Undirected Weighted Graph, T(V,E) = O(ElogV), S(V,E) = O(V + E)

Graph Algorithms in other folders:
    - Kruskal (Disjoint Set)
//-------------------------
TODO:
// Time Complexity, T(V,E) = O(V + ElogV), S(V,E) = O
22. Check if graph is weakly connected component
11. BFS
12. DFS
13. Topological Sort
14. Given directed graph, find out if there exist a route between 2 nodes
15. Djikstra using Fibonacci Heap
//-------------------------
note: Complexity is measured in terms of |V| = number of nodes and |E| = number of edges!
//-------------------------
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

note: Implementation for Djikstra Algorithm and Prim's Algorithm is very similar. The difference is that:
    - Djikstra Algorithm updates the minimum value to the shortest path from source to current node whereas
          if(curr.val + edge.weight < adj.val) adj.val = curr.val + edge.weight;
    - Djikstra is >= 0 weight, directed

    - Prim's Algorithm updates the minimum value based on the edges connecting the vertex to a current vertex already included in the MST.
          if(edge.weight < adj.val) adj.val = edge.weight;
    - Must be undirected for greedy approach of picking vertex with current minimum surrounding edges to make sense
*/
//----------------------------------------------------------------------------------------------------------------------------------------------
// 1 Check if unweighted, acyclic directed/undirected graph is connected using BFS/DFS
// Time Complexity, T(V,E) = O(V+E)
// Space Complexity, S(V,E) = O(V)
//-------------------------
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
//-------------------------
/* //
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
    this->DFS(0);
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
// 2 Djikstra Algorithm Using Binary Heap: Find single-source shortest path for Directed, Weighted Graphs, weight >= 0
// Time Complexity, T(V,E) = O(ElogV)
// Space Complexity, S(V,E) = O(V + E)
//-------------------------
/*
Note: Best implementation is using Fibonacci Heap which is
T(V,E) = O(E + VlogV) as E >> V => O(E + VlogV) < O(ElogV)
*/
//-------------------------
/* //
#include <climits> // for INT_MAX
#include <vector> // to store distance for each node in minHeap
#include <list>  // to store the adjacency list
#include <iostream> 
using namespace std; 

// the minHeap class that stores the vertex
class MinHeap
{
private:
    vector<int> verToPos; // a map of the vertex[i] with its actual position for distance in the heap distance 
    vector<int> distance; // minHeap
    vector<int> posToVer; // a map of the actual position in the heap distance to vertex number in graph
    int numNodes; // current number of nodes in minHeap
    void swap(int posI, int posJ)
    {
        // Swap the distance value
        int temp = this->distance[posI]; 
        this->distance[posI] = this->distance[posJ];
        this->distance[posJ] = temp;

        // Swap the vertex positions as indicated
        this->verToPos[this->posToVer[posI]] = posJ; 
        this->verToPos[this->posToVer[posJ]] = posI; 

        // Swap the positionToVertex 
        temp = this->posToVer[posI]; 
        this->posToVer[posI] = this->posToVer[posJ];
        this->posToVer[posJ] = temp;
        return;
    }
public:
    MinHeap(int _numNodes)
    {
        this->numNodes = _numNodes; 
        for(int i = 0; i < numNodes; i++)
        {
            this->distance.push_back(INT_MAX);
            this->posToVer.push_back(i); 
            this->verToPos.push_back(i);
        }
    }
    // Extracts the current minimum Vertex
    int extractMinVertex(void)
    {
        // int minValue = this->distance[this->numNodes-1]; // need return the minimumVertex, not the minimum distance value
        int minVertex = this->posToVer[0]; // MISTAKE: accidentally got minVertex after swapping which wouldn't be minimum anymore
        // swap the first element with last
        this->swap(0, this->numNodes-1);
        // Decrement number of nodes
        this->numNodes--;
        // Bubble down till found proper placement
        int i = 0;
        while (i < this->numNodes)
        {
            int smallest = i;
            if (((2*i + 1) < numNodes) && (this->distance[smallest] > this->distance[2*i + 1]))
            {
                smallest = 2*i + 1;
            }
            if (((2*i + 2) < numNodes) && (this->distance[smallest] > this->distance[2*i + 2]))
            {
                smallest = 2*i + 2;
            }
            if(smallest != i)
            {
                swap(i, smallest);
                i = smallest;
            }
            // Already in proper position
            else 
            {
                break;
            }
        }
        return minVertex;
    }
    int getDistance(int vertex)
    {
        return this->distance[this->verToPos[vertex]];
    }
    void updateMinDistance(int vertex, int dist)
    {
        // no changes if already out of heap  or already having an equal or lower distance value
        if((this->verToPos[vertex] >= numNodes) || (this->distance[this->verToPos[vertex]] <= dist)) return; 
        // Update it
        this->distance[this->verToPos[vertex]] = dist;
        // Update MinHeap
        // get Parent position of this vertex
        int parentPos = (this->verToPos[vertex]-1)/2; // Mistake: Used (pos/2) - 1 instead of (pos-1)/2
        while(parentPos >= 0)
        {
            if(this->distance[this->verToPos[vertex]] < this->distance[parentPos]) // Mistake: Accidentally used '>' instead of '<'
            {
                this->swap(verToPos[vertex], parentPos);
                parentPos = (this->verToPos[vertex]-1)/2;
            }
            // Break if already at right position
            else
            {
                break;
            }
        }
        return;
    }
};

class Edge 
{
private:
    int node;
    int weight; 
public:
    Edge(int _node, int _weight) : node(_node), weight(_weight) {};
    int getNode() { return this->node; }
    int getWeight() { return this->weight; }
};

// Adjacency List Representation
class Graph 
{
private:
    int numNodes;
    list<Edge *>* adj; // a pointer to lists of weighted Edges
public:
    Graph(int num)
    {
        this->numNodes = num; 
        this->adj = new list<Edge *>[numNodes];
    } 
    // Directed Acyclic Graph, weighted
    void addEdgeDirected(int src, int dest, int weight)
    {
        Edge * newEdge = new Edge(dest, weight); 
        this->adj[src].push_back(newEdge);
    }
    // Execute Djikstra Algorithm using Binary Heap
    void DjikstraBinaryHeap(int src)
    {
        // First, create a MinHeap
        MinHeap mH(this->numNodes);
        mH.updateMinDistance(src, 0); // initialize source node to have a distance of 0
        // Extract the minimum for all |V| nodes and update adjacent distances
        for(int i = 0; i < this->numNodes; i++)
        {
            int currVertex = mH.extractMinVertex();
            // Do a BFS to update all adjacent
            for(auto i = this->adj[currVertex].begin(); i != this->adj[currVertex].end(); i++) // C++ 11 feature
            {
                Edge * currEdge = *i; 
                // update the distance to currVertex with its weight
                mH.updateMinDistance(currEdge->getNode(), mH.getDistance(currVertex) + currEdge->getWeight());
            } 
            cout << "Vertex: " << currVertex << " has Distance: " << mH.getDistance(currVertex) << endl;
        }
        return;
    }
};

 // initialize all position to point to its original position
int main(void)
{
    int V = 5;
    Graph g(V);
    g.addEdgeDirected(0,1,2);
    g.addEdgeDirected(0,2,4);
    g.addEdgeDirected(1,2,1);
    g.DjikstraBinaryHeap(0);
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------------------
// 3 Prim's Algorithm using Binary Heap: Find Minimum Spanning Tree of Undirected Weighted Graph
// Time Complexity, T(V,E) = O(ElogV)
// Space Complexity, S(V,E) = O(V + E)
//-------------------------
/* 
Finds minimum spanning tree of weighted undirected graph. Note: Must be undirected if not greedy approach won't make sense
Note: Best implementation is using Fibonacci Heap which is
T(V,E) = O(E + VlogV) as E >> V => O(E + VlogV) < O(ElogV)
*/
//-------------------------
/* //
#include <climits> // for INT_MAX
#include <vector> // For MinHeap
#include <list> // Adjacency list representation of graph
#include <iostream> 
using namespace std;

// MinHeap class for Prim's Algorithm
class MinHeap
{
private:
    int numNodes;
    vector<int> verToPos;
    vector<int> posToVer;
    vector<int> minWeight; // minimum weight edges connecting currNode to node already in Minimum Spanning Tree
    // Swap nodes in posI and posJ
    void swap(int posI, int posJ)
    {
        // Swap the weight values 
        int temp = this->minWeight[posI]; 
        this->minWeight[posI] = this->minWeight[posJ];
        this->minWeight[posJ] = temp;
        // swap the verToPos
        this->verToPos[posToVer[posI]] = posJ;
        this->verToPos[posToVer[posJ]] = posI;
        // Swap the posToVer
        temp = this->posToVer[posI]; 
        this->posToVer[posI] = this->posToVer[posJ];
        this->posToVer[posJ] = temp;
        return;
    }
public:
    MinHeap(int _numNodes) // Constructor
    {
        this->numNodes = _numNodes;
        for(int i = 0; i < numNodes; i++)
        {
            this->minWeight.push_back(INT_MAX);
            this->posToVer.push_back(i);
            this->verToPos.push_back(i);
        }
    }
    int getMinWeight(int vertex) { return this->minWeight[verToPos[vertex]]; }
    // Returns current minimum Vertex in MinHeap and pops it out from MinHeap
    int popMinimumVertex() 
    {
        int minVertex = this->posToVer[0]; 
        // Swap to final element
        this->swap(0, this->numNodes-1);
        this->numNodes--;
        // Bubble down first element
        int currIndex = 0;
        while(currIndex < this->numNodes)
        {
            int minPos = currIndex; 
            if(((currIndex*2 + 1) < this->numNodes) && (this->minWeight[currIndex] > this->minWeight[currIndex*2 + 1]))
            {
                minPos = currIndex*2 + 1;
            }
            else if(((currIndex*2 + 2) < this->numNodes) && (this->minWeight[currIndex] > this->minWeight[currIndex*2 + 2]))
            {
                minPos = currIndex*2 + 2;
            }
            // Update if needed
            if(minPos != currIndex)
            {
                this->swap(minPos, currIndex);
                currIndex = minPos; 
            }
            else // break if already at right position
            {
                break;
            }
        }
        return minVertex;
    }
    void setWeight(int numVertex, int weight)
    {
        // Return if no longer in heap or already minimum
        if((this->verToPos[numVertex] >= this->numNodes) || (this->minWeight[this->verToPos[numVertex]] <= weight)) return; // no changes
        // Set to new value 
        this->minWeight[this->verToPos[numVertex]] = weight;
        // Push it upwards the heap only if able
        int parentPos = (this->verToPos[numVertex]-1)/2;
        while(parentPos >= 0)
        {
            if(this->minWeight[verToPos[numVertex]] < this->minWeight[parentPos])
            {
                this->swap(this->verToPos[numVertex], parentPos);
                parentPos = (this->verToPos[numVertex]-1)/2;
            }
            else break; // break if no changes
        }
    }
};

class Edge {
private:
    int dest; // destination node
    int weight; // weight of this edge
public:
    Edge(int _dest, int _weight) : dest(_dest), weight(_weight) {};
    int getWeight() { return this->weight; }
    int getNode() { return this->dest; }
};

class Graph {
private:
    list<Edge *> * adj; // a pointer to lists of Edges
    int numNodes; // number of nodes in this graph
public:
    Graph(int _numNodes) 
    {
        this->numNodes = _numNodes; 
        this->adj = new list<Edge *>[numNodes];
    }
    void addUndirectedEdge(int vertexA, int vertexB, int weight)
    {
        Edge * edgeAB = new Edge(vertexB, weight);
        adj[vertexA].push_back(edgeAB);
        Edge * edgeBA = new Edge(vertexA, weight);
        adj[vertexB].push_back(edgeBA);
        return;
    }
    // Executes prim algorithm by creating MinHeaps
    void Prim(int srcVertex)
    {
        int totalWeight = 0; 
        // Create a minHeap
        MinHeap mh(this->numNodes);
        mh.setWeight(srcVertex,0); // initialize sourceVertex to have weight of 0
        for(int i = 0; i < numNodes; i++)
        {
            int currMinNode = mh.popMinimumVertex(); 
            totalWeight += mh.getMinWeight(currMinNode); cout << "CurrWeight picked is: " << mh.getMinWeight(currMinNode) << endl;
            for(auto i = this->adj[currMinNode].begin(); i != this->adj[currMinNode].end(); i++) // C++ 11 feature
            {
                Edge * currEdge = *i;
                // Update the weight on that node in minHeap if it is in minHeap
                mh.setWeight(currEdge->getNode(), currEdge->getWeight());
            }
        }
        cout << "Total weight of edges for Minimum Spanning Tree is: " << totalWeight << endl;
        return; 
    }
};
int main(void)
{
    int V = 4;  // Number of nodes in graph
    Graph* graph = new Graph(V);
    graph->addUndirectedEdge(0,1,10);
    graph->addUndirectedEdge(0,2,6);
    graph->addUndirectedEdge(0,3,5);
    graph->addUndirectedEdge(1,3,15);
    graph->addUndirectedEdge(2,3,4);
    graph->Prim(0); // 19 = 10 + 5 + 4 (note: First weight of 0 doesn't mean anything as the source node has no edges connected to it at first)
    return 0;
}
// */
//----------------------------------------------------------------------------------------------------------------------------------------------
