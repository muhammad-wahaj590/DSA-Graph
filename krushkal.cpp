#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph{
	public:
		
		bool cmp(vector<int> &a, vector<int> &b){    //kruskal graph waly ki edge ko sort karna a or b parameters hain har edge vector main yeh [source_node, destination_node, weight] hoty
			return a[2] < b[2];       //weight 3rd column means 2nd index
		}  // a or b dono edges k weight hain jo cmpare(cmp) karwa rahy taky edges ka weight ascending order k hisab se set ho jaye 
		
		void makeSet(vector<int> &parent, vector<int> &rank, int n){
			for(int i=0; i<n; i++){
				parent[i] = i;           // Initially, each node is its own parent.
				rank[i] = 0;            // Initial rank is 0 for all nodes.
			}
		}

		int findParent(vector<int> &parent, int node){
			//		base case
			if(parent[node] == node){    //agar node ka parent khud node hai
				return node;            //matlab jab parent k node ko check karty hoye jab root node pe chaly jayen jahan node ka parent khud node hi ho to wahan ruk jaoor return kardo
			}
// Recursively find the parent and perform path compression.
			return parent[node] = findParent(parent, parent[node]);
		}
		
//		union karne k liye u v ko set kia parent bana kar 
		void unionSet(int u, int v, vector<int> &parent, vector<int> &rank){
			u = findParent(parent, u);
			v = findParent(parent, v);      // u or v k parent nikal liye
			
			if(rank[u] < rank[v]){         //rank u v se less hai to
				parent[u] = v;             //v ko u ka parent bana do
			}
			else if(rank[v] < rank[u]){    //v less hai u se 
				parent[v] = u;             // u ko parent bana do v ka
			}
			else{
				parent[v] = u;            //agar dono same hain to dono ko mila do
				rank[u]++;                //or rank u ko jo parent ban raha ho usy increment karado
			}
		}
		
		int kruskalMST(vector<vector<int>>& edges, int n){  //kyon k smalleest key value se start karen ge 
			sort(edges.begin(), edges.end(), [this](vector<int>& a, vector<int>& b) {    //edge vector k element ko sort karna ascending order
            return a[2] < b[2];         //this keyword class k member func main curr obj ko point karne k liye use kia hai taky sorting ho saky 
        });
			 vector<int> parent(n);       //parent ka array
			 vector<int> rank(n);         //rank ka array
			 makeSet(parent, rank, n);       //dono ko mila do
			 
			 int minWeight = 0;
			 
			 for(int i=0; i<edges.size(); i++){
//			 	finding parents
				int u = findParent(parent, edges[i][0]);          // edges[i][0]  means source node jo u main store hai 0 represent source
				int v = findParent(parent, edges[i][1]);          // edges[i][1] means destination node hai jahan 1 represent destination
			 	int wt = edges[i][2];                             // edges[i][2] means weight node jahan edge ka weight store ho wt main 
			 	
			 	if(u!=v){             // Agar u aur v ke parents alag hai (matlab yeh edge MST mein shamil ho sakti hai) To fir is edge ko MST mein shamil karte hain
			 	minWeight += wt;      // Edge ka weight MST ke weight me add kiya jata hai.
			 	unionSet(u, v, parent, rank);      // u aur v ke parents ko union kar diya jata hai.
				 }
			 }
			 return minWeight;                     // jitna miWeight ho jata calculate usy return kardia 
		}
};

int main(){
	
	Graph g;
    int n;                                                   // Number of nodes
    cout << "Enter the number of nodes: ";
    cin >> n;
    
    vector<vector<int>> edges;                              // to store 3 edges(source, destination, weight) that's why we use vector of vector   
    int m;                                                  // Number of edges
    cout << "Enter the number of edges: ";
    cin >> m;
    
    cout << "Enter the edges in the format (source destination weight):" << endl;
    for (int i = 0; i < m; i++) {
        int source, destination, weight;
        cin >> source >> destination >> weight;
        edges.push_back({source, destination, weight});    //edge vector main yeh 3 formats add kar rahy
    }
    
    int minWeight = g.kruskalMST(edges, n);               //edges = 2d vector, n = total number of nodes
    cout << "Minimum Spanning Tree Weight: " << minWeight << endl;

    return 0;
}
