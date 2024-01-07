
#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
using namespace std;
//steps: 1) sab se pehlay root node se start kia or usy queue k front function se 2) queue main push karwaya 3} or usy false se true mark karwaya k yeh  visited hai 4)then output main usy print karwaya 5) complete traverse karne k bad queue ko empty karwaya
class Graph{
	public:
		unordered_map<int, list<int>> adj;
		
		void addEdge(int u, int v){
			adj[u].push_back(v);
			adj[v].push_back(u);   //undirected graph
		}
		
		void BFS(int startVertex){                //jahan se node start ho rahi hai
			unordered_map<int, bool> visited;     //starting node ko push karna or false se true karna
			queue<int> q;
			
			q.push(startVertex);                 //node ko push kia queue main
			visited[startVertex] = true;         //us node ko false ko se tryue karwaya
			
			while(!q.empty()){
				int frontNode = q.front();      // front node ko display karo
				q.pop();
				cout<<frontNode<<" ";           //print the current node
				
				for(int neighbor : adj[frontNode]){   //ab neighbors ki iteration ki bari
					if(!visited[neighbor]){           // node k elements visited nhi hain to 
						q.push(neighbor);            // to usy queue main daldo
						visited[neighbor] = true;    // or usy bhi true mark karwa do
					}
				}
			}
		}
};

int main(){
	Graph g;
	
	int n;
	cout<<"Enter the number of nodes: "<<endl;
	cin >> n;
	
	int m;
	cout<<"Enter the number of edges: "<<endl;
	cin >> m;
	
	for(int i=0; i<m; i++){
		int u, v;
		cin >> u >> v;
		g.addEdge(u, v);
	}
	
	int startVertex;
	cout<<"Enter the starting vertex of BFS ";
	cin >> startVertex;
	
	g.BFS(startVertex);
	
	return 0;
}







