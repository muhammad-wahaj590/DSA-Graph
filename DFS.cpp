#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>

using namespace std;

class Graph {
public:
    unordered_map<int, vector<int>> adj;

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void DFS(int startVertex) {
        unordered_map<int, bool> visited;
        stack<int> st;

        st.push(startVertex);
        visited[startVertex] = true;

        while (!st.empty()) {
            int currentNode = st.top();
            st.pop();
            cout << currentNode << " ";

            for (int neighbor : adj[currentNode]) {
                if (!visited[neighbor]) {
                    st.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
    }
};

int main() {
    Graph g;

    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    int m;
    cout << "Enter number of edges: ";
    cin >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    int currentNode;
    cout << "Enter the start vertex of DFS: ";
    cin >> currentNode;

    cout << "DFS Traversal: ";
    g.DFS(currentNode);

    return 0;
}
