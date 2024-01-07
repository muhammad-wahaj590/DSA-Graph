#include <iostream>
#include <unordered_map>
#include <list>              // linked list k liye
#include <vector>            // dynamic arrays (vectors)
#include <climits>           // ek C++ header file hai jo integer types ke liye minimum aur maximum values provide karti hai.
using namespace std;

class Graph {
public:
    unordered_map<int, list<pair<int, int>>> adj;  //particular node k corresponding dosri node along its weight

    Graph() {} 

    void addEdge(int u, int v, int w) {            //u= source, v=destination, w=weight
        adj[u].push_back(make_pair(v, w));         //u(source) se v(destination) tak jati hai or v tak pohanchty hoye edge ka weight bhi hota to usy v or w ka pair banaya jata
        adj[v].push_back(make_pair(u, w));         //undirected graph k liye ese karty hain v se u
    }
    
    int calculateTotalCost(int n, vector<int> key) { //n=total nodes in graph
    int totalCost = 0;                               //initialy set the value 0 
    for (int i = 1; i <= n; i++) {
        if (key[i] != INT_MAX) {                     //nodes se key value select karty agar woh different hoti to mst main ajati
            totalCost += key[i];                     // or or us key ko add karty 
        }
    }
    return totalCost;                                
}
	
//	to initialzide key, mst, parent
    void primMST(int n) {
        vector<int> key(n + 1);                   //vector ki indexing 0 se start hoti to us k liye n+1 kia taky array main sari store ho saken
        vector<bool> mst(n + 1, false);           //mst se node ko visite karne ka process hota or initially sab false hoti kyon k koi bhi visited nhi hoti
        vector<int> parent(n + 1, -1);            //parent node create karty taky or start main usy -1 se initialze karty kyon k starting main koi bhi kisi ka parent nhi hota

        for (int i = 0; i <= n; i++) {            // n basically graph k number of nodes hotin 
            key[i] = INT_MAX;                     //INT_MAX = infinity (starting main ar node ko infinity oe set kia jata)
        }

        key[1] = 0;                               //strating node ko 0 pe rakhty hain 
        parent[1] = -1;                           //pr us ka koi parent nhi hota to -1 hoti value

        for (int i = 0; i < n; i++) {  
            int mini = INT_MAX;                   //set smallest value infinity
            int u;                                //creating MST starting node u


            for (int v = 1; v <= n; v++) {        //to find the smallest key value
                if (!mst[v] && key[v] < mini) {   //v(node) woh ati jo mst main nhi shamil hoi hotin pehlay or shamil hone wali v ki key value mini se choti hai ya nhi
                    u = v;                        //update u into v
                    mini = key[v];                //ab next mini v ban chuka hota 
                }
            }

            mst[u] = true;                        //ab new u ko bhi true mark karna hota 
//it = edge
            for (auto it : adj[u]) {             //select kia jany wala u ab us k adj main loop chalta hai
                int v = it.first;                //v ki destion main it(edge) se us ki pehli value store hoti v main
                int w = it.second;               //us it(edge) ka weight bhi store karta w main

                if (!mst[v] && w < key[v]) {     // checking 
                    parent[v] = u;               //setting parent node u of v (current node)
                    key[v] = w;                  //updating weight store in v(key value node)
                }
            }
        }

		int totalCost = calculateTotalCost(n, key);
        cout << "Total Cost of MST: " << totalCost << endl;    
        
        for (int i = 2; i <= n; i++) {         //starting node pehlay mst main include hoti to node1 alreay hoa wa hota tab hi node2 se start karty or loop ka i bhi 2 se start hota
            cout << "Edge: " << parent[i] << " - " << i << " Weight: " << key[i] << endl;
        }
    }
};

int main() {
    int n, m; // Number of nodes and edges in the graph
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> m;

    Graph g;

    cout << "Enter the edges and their weights (u, v, w):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    g.primMST(n);

    return 0;
}

