//----------------------------------------------------------------------------------------
/*
1. Kruskal's Algorithm, T(V,E) = O(ElgV), S(V,E) = O(V)
TODO: 
2. 
*/
//
//----------------------------------------------------------------------------------------
// 1 Kruskal's Algorithm
// Time Complexity, T(V,E) = O(ElgV)
// Space Complexity, S(V,E) = O(V) 
//      V is for all the sets made
//      Assume if modify same graph, will only be deleting edges, so won't create any space for new edges

// note: qsort() is for arrays 
// sort() is for vectors
#include <iostream> 
#include <vector> 
#include <cstdlib> // qsort()
#include <algorithm> // sort()
using namespace std;

// Each subset in the entire Disjoint Sets
class Subset 
{
private:
    int rank; // to know rank of current subset if this subset is the head
    int parent; // to know which subset this subset belongs to
public: 
    Subset(int _rank, int _parent) : rank(_rank), parent(_parent) {}
    void setRank(int _rank)
    {
        rank = _rank;
    }
    void setParent(int _parent)
    {
        parent = _parent;
    }
    int getParent()
    {
        return parent;
    }
    int getRank()
    {
        return rank;
    }
};

class DisjointSet
{
private:
    Subset* s; // array of all the subsets
    int numSets;
public:
    DisjointSet(int _numSets)
    {
        numSets = _numSets;
        s = (Subset *) malloc(sizeof(Subset) * numSets);
        for(int i = 0; i < numSets; i++)
        {
            Subset newSubSet = Subset(0, i);
            s[i] = newSubSet;
        }
    }
    // Identify which set this node belongs to 
    int find(int node)
    {
        // Base Case
        if(s[node].getParent() == node)
            return node;
        // path compression
        s[node].setParent(find(s[node].getParent()));
        return s[node].getParent();
    }
    // This merge 2 sets together
    void mergeSets(int node1, int node2) 
    {
        int parent1 = find(node1);
        int parent2 = find(node2);
        // update the ranks
        if(s[parent1].getRank() == s[parent2].getRank())
        {
            s[parent2].setParent(parent1);
            s[parent1].setRank(s[parent1].getRank() + 1); // increase the rank
        }
        else if(s[parent1].getRank() > s[parent2].getRank())
        {
            s[parent2].setParent(parent1);
        }
        else
        {
            s[parent1].setParent(parent2);
        }
    }
};

// Using Object and Pointers Representation for Graph
class Edge 
{
private: 
    unsigned int node1, node2; 
    int weight; 
public:
    Edge(unsigned int nodeA, unsigned int nodeB, int w) : node1(nodeA), node2(nodeB), weight(w) {}
    int getWeight() 
    {
        return weight;
    }
    void setWeight(int w) 
    {
        weight = w; 
    }
    int getSrcNode()
    {
        return node1;
    }
    int getDestNode()
    {
        return node2;
    }
    void print()
    {
        cout << node1 << " : " << node2 << " = " << weight << endl;
    }
};

// Note: Must pass in const void* and re-cast it to be able to use qsort()
//       Must also not be inside any class but declared outside of class
int compareEdges(const void* e1,const void* e2)
{
    Edge* eA = (Edge *) e1;
    Edge* eB = (Edge *) e2;
    // return a > b if want to sort ascending order
    return eA->getWeight() > eB->getWeight();
}

class Graph 
{
private:
    unsigned int numNodes; 
    unsigned int numEdges; 
    unsigned int maxEdges; 
    Edge * Edges; // use pointers to be able to use qsort() 
    
    // Compare function for Edges for use in qsort()
public:
    Graph(unsigned int _numNodes, int maxEdges) 
    {
        numNodes = _numNodes; 
        numEdges = 0;
        Edges = (Edge *) malloc(sizeof(Edge) * maxEdges);
    }
    void addEdge(unsigned int v1, unsigned int v2, int weight)
    {
        Edge newEdge = Edge(v1, v2, weight);
        Edges[numEdges] = newEdge;
        numEdges++;
    }
    void print()
    {
        cout << "Number of nodes are: " << numNodes << endl;
        cout << "Number of edges are: " << numEdges << endl;
        for(int i = 0; i < numEdges; i++)
        {
            Edges[i].print();
            // Note: If using vectors:
            // vector<Edge> Edges
            // Edge e1 = Edge()
            // Edges.push_back(e1)
            // i->print()
            // --------------------
            // OR 
            // --------------------
            // vector<Edge *> Edges
            // Edge* e1 = new Edge()
            // Edges.push_back(e1)
            // i[0]->print()
        } 
    }
    Graph* Kruskal()
    {
        // Sort the edges O(ElgE) = O(ElgV) since E <= V^2
        qsort(Edges, numEdges, sizeof(Edge), compareEdges);
        // Make a set for all nodes O(V)
        DisjointSet ds = DisjointSet(numNodes);
        Graph* graph = new Graph(numNodes,numEdges);
        int numEdgesAdded = 0;
        // Should only add at most V-1 edges, after that no point traversing anymore
        // O(ElogV)
        for(int i = 0; i < numEdges; i++) // O(min(E, V-1)) 
        {
            // Group into same set if not the same set already O(1) amortized analysis for disjoint set with rank and path compression implementation
            // Worst case would be O(logV) 
            int node1 = Edges[i].getSrcNode();
            int node2 = Edges[i].getDestNode();
            int parent1 = ds.find(node1);
            int parent2 = ds.find(node2);
            if(parent1 != parent2)
            {
                ds.mergeSets(node1, node2);
                graph->addEdge(node1,node2,Edges[i].getWeight());
                numEdgesAdded++;
                if (numEdgesAdded == numNodes - 1)
                {
                    break;
                }
            }
        }
        // Return the created graph  with the latest edges
        return graph;
    }
};

int main(void)
{

    int V = 4;  // Number of nodes in graph
    Graph* graph = new Graph(V,10);
    graph->addEdge(0,1,10);
    graph->addEdge(0,2,6);
    graph->addEdge(0,3,5);
    graph->addEdge(1,3,15);
    graph->addEdge(2,3,4);
    graph->print();
    // Should end up with  edges
    // (0,1), (0,3), (2,3)
    Graph* MST = graph->Kruskal();
    MST->print();
    
    return 0;
}
// */
//----------------------------------------------------------------------------------------
