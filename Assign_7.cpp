#include <iostream>
#include <climits>
#include <vector>

using namespace std;

#define INF INT_MAX  // Define Infinity
#define MAX 100      // Maximum number of offices

class Graph {
    int V;           // Number of offices (vertices)
    int graph[MAX][MAX]; // Adjacency matrix

public:
    Graph(int vertices);
    void createGraph();
    void primMST();
};

// Constructor to initialize graph
Graph::Graph(int vertices) {
    V = vertices;
    // Initialize all edges as Infinity
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = INF;
        }
    }
}

// Function to create graph using adjacency matrix
void Graph::createGraph() {
    int edges, src, dest, cost;
    cout << "Enter the number of edges: ";
    cin >> edges;

    cout << "Enter edges in the format: source destination cost\n";
    for (int i = 0; i < edges; i++) {
        cin >> src >> dest >> cost;
        // Since the graph is undirected
        graph[src][dest] = cost;
        graph[dest][src] = cost;
    }
}

// Function to find Minimum Spanning Tree using Prim’s Algorithm
void Graph::primMST() {
    vector<bool> selected(V, false);  // To track included nodes
    vector<int> minCost(V, INF);      // To store the minimum cost for each node
    vector<int> parent(V, -1);        // To store the parent of each node

    minCost[0] = 0;  // Start from the first node
    int min_cost = 0; // Total MST cost

    cout << "\nEdges in Minimum Spanning Tree:\n";

    for (int edgeCount = 0; edgeCount < V - 1; edgeCount++) {
        // Find the minimum cost edge connecting an unvisited node
        int u = -1;
        int minEdge = INF;

        // Find the node with the smallest edge weight that has not been included
        for (int i = 0; i < V; i++) {
            if (!selected[i] && minCost[i] < minEdge) {
                u = i;
                minEdge = minCost[i];
            }
        }

        // If no valid edge found, break (graph is disconnected)
        if (u == -1) {
            cout << "The graph is not connected.\n";
            return;
        }

        selected[u] = true;  // Include the node in the MST
        min_cost += minEdge;

        // Update the minCost and parent for adjacent nodes
        for (int v = 0; v < V; v++) {
            if (!selected[v] && graph[u][v] != INF && graph[u][v] < minCost[v]) {
                minCost[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Output the MST edges
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " -- " << i << "  Cost: " << graph[parent[i]][i] << endl;
    }

    cout << "\nTotal Minimum Cost: " << min_cost << endl;
}

int main() {
    int vertices;
    cout << "Enter the number of offices (vertices): ";
    cin >> vertices;

    Graph g(vertices);
    g.createGraph();
    g.primMST();

    return 0;
}
