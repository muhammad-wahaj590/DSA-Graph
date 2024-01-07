#include <iostream>
#include <unordered_map>
#include <list>                    // link list (diubly link list)
#include <set>                     // to store unique elements in a container in sorted order we use set library    
#include <vector>                  //dynamic array
#include <climits>                 //max or min define karta 
using namespace std;

class Graph {
public:
    vector<int> dijkstra(vector<vector<int>> &vec, int vertices, int edges, int source) {   // vector<vector<int>> &vec = 2d vector (& use kia taky directly modifucation ho)
        // Create an adjacency list
//                                  <node, distance>
        unordered_map<int, list<pair<int, int>>> adj;
        for (int i = 0; i < edges; i++) {
            int u = vec[i][0];          // 1st colum source
            int v = vec[i][1];          // 2nd column destination
            int w = vec[i][2];          // 3rd column weight

            adj[u].push_back(make_pair(v, w));     //connection u to v
            adj[v].push_back(make_pair(u, w));     //connecting v to u
        }

        // Create an array to store distances with initial values set to INT_MAX
        vector<int> dist(vertices, INT_MAX);

        // Create a set to track (distance, node) pairs
        set<pair<int, int>> st;

        // Initialize the distance and set with the source node
        dist[source] = 0;
        st.insert(make_pair(0, source));

        while (!st.empty()) {
            // Fetch the top record
            auto top = *(st.begin());   //st.begin() se pahle element ka iterator nikala jata hai, aur fir * se us element ki value(distance, node) ka pair ko top variable mein store kiya jata hai.

            int nodeDistance = top.first;   //top node k cuurent distance ko point kar rahy yahan 
            int topNode = top.second;       // or usi top k second ko bhi point kar rahy

            // Remove the top record
            st.erase(st.begin());         // first element erase kardena set se

            // Traverse the neighbors
            for (auto neighbor : adj[topNode]) {
                if (nodeDistance + neighbor.second < dist[neighbor.first]) {
                    auto record = st.find(make_pair(dist[neighbor.first], neighbor.first));

                    // If the record is found, erase it
                    if (record != st.end()) {
                        st.erase(record);
                    }

                    // Update the distance
                    dist[neighbor.first] = nodeDistance + neighbor.second;

                    // Record is pushed into the set
                    st.insert(make_pair(dist[neighbor.first], neighbor.first));
                }
            }
        }
        return dist;
    }
};

int main() {
    Graph g;
    int vertices, edges;
    cout << "Enter the number of vertices: ";
    cin >> vertices;
    cout << "Enter the number of edges: ";
    cin >> edges;

    vector<vector<int>> edgesList(edges, vector<int>(3));

    cout << "Enter the edges in the format (source destination weight):" << endl;
    for (int i = 0; i < edges; i++) {
        cin >> edgesList[i][0] >> edgesList[i][1] >> edgesList[i][2];
    }

    int source;
    cout << "Enter the source node: ";
    cin >> source;

    vector<int> distances = g.dijkstra(edgesList, vertices, edges, source);

    cout << "Shortest distances from node " << source << " to all other nodes:" << endl;
    for (int i = 0; i < vertices; i++) {
        cout << "Node " << i << ": " << distances[i] << endl;
    }

    return 0;
}

