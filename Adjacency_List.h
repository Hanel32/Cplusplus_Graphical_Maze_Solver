#ifndef Adjacency_List_h
#define Adjacency_List_h
#include <iostream>
#include <stdexcept>
#include <vector>
#include <math.h>
#include <stack>

using namespace std;

struct Vertex{
	int id;                        //Records as the n'th node created.
	Vertex* n;                     //Holds ptrs to the accessibly vertices
	Vertex* e;
	Vertex* s;
	Vertex* w;
	Vertex(int id): id(id), n(NULL), e(NULL), s(NULL), w(NULL) {};
};

class  Graph{
	int V, E;                         //Holds the number of edges and vertices.
	vector<vector<Vertex*> > matrix;  //Holds the adjacency list for the graph	
public:
	Graph(int size);               //Constructor
	~Graph();                      //Destructor
	void addVertex(int row, int col);                //Updates the matrix with a new vertex
	void addEdge(int row, int col, vector<int> dir); //Updates the matrix with a new edge
	void removeEdge();             //Removes an edge from the matrix
	void removeVertex();           //Removes a vertex from the matrix
	void DFS();                    //Performs a Depth-First Search on the graph
	void BFS();                    //Performs a Breadth-First Search on the graph
	int  num_vertices(){return E;};//Gets the number of vertices
	int  num_edges(){return V;};   //Gets the number of edges
	void vertices();               //Outputs all vertices of the graph
	void edges();                  //Outputs all edges of the graph
	void testRun();                //Does a lazy walk-through to see if the graph works.
	void printGraph();             //Prints out the orientation and identity of graph nodes
};
Graph::Graph(int size){            //Either janky or a clever fix, you decide.
	V = E = 0;                     //Sets vertices and edges to 0
	for(int i = 0; i < sqrt(size); i++){
		vector<Vertex*>* part = new vector<Vertex*>(sqrt(size));
		matrix.push_back(*part);
	}
	cout << "The number of vectors held: " << matrix.size() << " number of members in the vector: " << matrix[0].size() << endl;
}
void Graph::addEdge(int row, int col, vector<int> dir){
	cout << "Adding an edge at row: " << row << " col: " << col << endl;
	cout << "Checking north" << endl;
	if(dir.at(0) == 1){matrix[row].at(col)->n = matrix[row - 1][col];}
	cout << "Checking east" << endl;
	if(dir.at(1) == 1){matrix[row].at(col)->e = matrix[row].at(col+1);}
	cout << "Checking south" << endl;
	if(dir.at(2) == 1){matrix[row].at(col)->s = matrix[row + 1].at(col);}
	cout << "Checking west" << endl;
	if(dir.at(3) == 1){matrix[row].at(col)->w = matrix[row].at(col-1);}
	E += 4;
	return;
}
void Graph::addVertex(int row, int col){
	cout << "Adding a vertex at row: " << row << " col: " << col << endl;
	V++;
	Vertex* temp = new Vertex(V);
	matrix[row].at(col) = temp;
	cout << "We've just added: " << matrix[row].at(col) << endl;
	cout << "It should have an ID: " << matrix[row].at(col)->id << endl;
	cout << "Size is now: " << V << endl;
	return;
}
void Graph::testRun(){
	Vertex* start = matrix[0].at(0);
	cout << "Alright, we're at 1, attempting to walk east to 2" << endl;
	start = start->e;
	cout << "We've walked east, we're at: " << start->id << endl;
	cout << "Now that we've gone east, we're gonna go south to 6" << endl;
	start = start->s;
	cout << "We've walked south, we're at: " << start->id << endl;
	cout << "5 can't walk east, so we're gonna." << endl;
	start = start->e;
	cout << "So, now the current should be null(0): " << start << endl;
}
void Graph::printGraph(){
	stack<char> middle;
	for(int i = 0; i < matrix.size(); i++){
		cout << "X";
		for(int j = 0; j < matrix[0].size(); j++){
			cout << "[";
			if(matrix[i][j]->id < 10){
				cout << "0";
			}
			cout << matrix[i][j]->id;
			cout << "]";
			if(matrix[i][j]->e != NULL){
				cout << "-";
			}else{
				cout << "X";
			}
			if(matrix[i][j]->s != NULL){
				middle.push('|');
			}else{
				middle.push('X');
			}
		}
		cout << endl << " ";
		while(!middle.empty()){
			char temp = middle.top();
			middle.pop();
			cout << " " << temp << "   ";
		}
		cout << endl;
	}
	return;
}

#endif
