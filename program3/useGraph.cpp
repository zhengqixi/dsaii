#include "graph.h"
using namespace std;
int main(){
	graph* shortest = new graph();
	cout << "Please enter the name of the input file: ";
	string name;
	cin >> name;
	shortest->read(name);
	string vertex;
	while(1){
		cout << "Please enter a starting node: " ;
		cin >> vertex;
		if (shortest->contains(vertex)){
			break;
		}
	}
	shortest->dijkstra(vertex);
	return 0;
}
