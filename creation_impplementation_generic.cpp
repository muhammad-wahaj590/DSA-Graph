#include <iostream>
#include <unordered_map>
#include <list>
using namespace std;
template <typename T>      // generic code ban jaye ga koi bhi type chal sakti int char main se koi bhi 

class Graph {
public:
    unordered_map<T, list<T>> adj;

    void addEdge(T u, T v, bool direction) {
        if (direction == 0) {
            adj[v].push_back(u);
        }
        if (direction == 1) {
            adj[u].push_back(v);
        }
    }

    void print_adjList() {
        for (auto i : adj) {
            cout << i.first << "-> ";
            for (auto j : i.second) {
                cout << j << ", ";
            }
            cout << endl;
        }
    }
};

int main() {
    int n;
    cout << "Enter the number of nodes: ";
    cin >> n;

    int m;
    cout << "Enter the number of edges: ";
    cin >> m;

    Graph<int> g;
    Graph<char> g;
    
    for (int i = 0; i < m; i++) {
        char u, v;
        cin >> u >> v;
        g.addEdge(u, v, 0);
    }
    g.print_adjList();
    return 0;
}

