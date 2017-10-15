#ifndef Adjacency_List_h
#define Adjacency_List_h
#include <iostream>
#include <stdexcept>
#include <vector>
#include <math.h>
#include <stack>
#include <list>

using namespace std;

struct Vertex{
	int id;                                          //Records as the n'th node created.
	Vertex* n;                                       //Holds ptrs to the accessible vertices
	Vertex* e;
	Vertex* s;
	Vertex* w;
	Vertex(int id): id(id), n(NULL), e(NULL), s(NULL), w(NULL) {};
};
struct adj_node{
	int id;                                          //Holds the node's ID
	adj_node* next;                                  //Points to the location of the next node in the adj_list
	adj_node(int id): id(id), next(NULL) {};
};
struct adj_list{
	adj_node* head;                                  //Simply holds the beginning of the adj_list
	adj_list(int id){
		head = new adj_node(id);
	}
	void addAdj(adj_node* temp){
		adj_node* curr = head;
		while(curr->next != NULL){
			curr = curr->next;
		}
		curr->next = temp;
	}
};

class  Graph{
	int V, E;                                        //Holds the number of edges and vertices.
	vector<vector<Vertex*> > matrix;                 //Holds the vertices in a pretty format.
	vector<adj_list*>        adj;                    //Holds the adjacency list.
	void printBFS(int end, vector<int> parent);      //Prints out the BFS
		
public:
	Graph(int size);                                 //Constructor
	~Graph();                                        //Destructor
	void addVertex(int row, int col);                //Updates the matrix with a new vertex
	void addEdge(int row, int col, vector<int> dir); //Updates the matrix with a new edge
	void removeEdge();                               //Removes an edge from the matrix
	void removeVertex();                             //Removes a vertex from the matrix
	void DFS();                                      //Performs a Depth-First Search on the graph
	void BFS(int s);                                 //Performs a Breadth-First Search on the graph
	int  num_vertices(){return E;};                  //Gets the number of vertices
	int  num_edges(){return V;};                     //Gets the number of edges
	void vertices();                                 //Outputs all vertices of the graph
	void testRun();                                  //Does a lazy walk-through to see if the graph works.
	void printGraph();                               //Prints out the orientation and identity of graph nodes
	void printAdj();                                 //Prints the adjacency list.
};
Graph::Graph(int size){                              //Either janky or a clever fix, you decide.
	V = E = 0;                                       //Sets vertices and edges to 0
	for(int i = 0; i < sqrt(size); i++){
		vector<Vertex*>* part = new vector<Vertex*>(sqrt(size));
		matrix.push_back(*part);
	}
	cout << "The number of vectors held: " << matrix.size() << " number of members in the vector: " << matrix[0].size() << endl;
}
Graph::~Graph(){
	//do work here
}
void Graph::addEdge(int row, int col, vector<int> dir){
	int id = matrix[row].at(col)->id;                //Used to hold the ID of the vertex
	adj_node* temp;                                  //Will be used to create new nodes if a connection exists.
	adj_node* curr;                                  //Will be used to iterate through the existing adj_list
	cout << "Adding an edge at row: " << row << " col: " << col << endl;
	cout << "Checking north" << endl;
	if(dir.at(0) == 1){
		matrix[row].at(col)->n = matrix[row - 1][col];
		temp = new adj_node(matrix[row - 1][col]->id);
		adj.at(id)->addAdj(temp);
		E++;
	}
	cout << "Checking east" << endl;
	if(dir.at(1) == 1){
		matrix[row].at(col)->e = matrix[row].at(col+1);
		temp = new adj_node(matrix[row][col + 1]->id);
		adj.at(id)->addAdj(temp);
		E++;
	}
	cout << "Checking south" << endl;
	if(dir.at(2) == 1){
		matrix[row].at(col)->s = matrix[row + 1].at(col);
		temp = new adj_node(matrix[row + 1][col]->id);
		adj.at(id)->addAdj(temp);
		E++;
	}
	cout << "Checking west" << endl;
	if(dir.at(3) == 1){
		matrix[row].at(col)->w = matrix[row].at(col-1);
		temp = new adj_node(matrix[row][col-1]->id);
		adj.at(id)->addAdj(temp);
		E++;
	}
	return;
}
void Graph::addVertex(int row, int col){
	cout << "Adding a vertex at row: " << row << " col: " << col << endl;
	Vertex* temp = new Vertex(V);                    //Creates a new vertex object for the 2d matrix.
	matrix[row].at(col) = temp;                      //Places the vertex object in the correct grid-space.  
	adj_list* temp_a = new adj_list(V);              //Creates the adjacency list of the object.
	adj.push_back(temp_a);                           //Pushes the adjacency list of the object back to the vector of lists.
	V++;                                             //Increases the known value of vertices.
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
	char middle[matrix.size()];
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
				middle[j] = '|';
			}else{
				middle[j] = 'X';
			}
		}
		cout << endl << " ";
		for(int i = 0; i < matrix.size(); i++){
			cout << " " << middle[i] << "   ";
		}
		cout << endl;
	}
	return;
}
void Graph::printAdj(){
	adj_node* curr;
	for(int i = 0; i < adj.size(); i++){
		curr = adj.at(i)->head;
		cout << "Start: [";
		if(curr->id < 10){
			cout << "0";
		}
		cout << curr->id << "]";
		while(curr->next != NULL){
			curr = curr->next;
			cout << "->";
			cout << "[";
			if(curr->id < 10){
				cout << "0";
			} 
			cout << curr->id << "]";
		}
		cout << endl;	
	}
}
void Graph::BFS(int s){
	bool *seen = new bool[V];                 //Holds the value of whether the vertex has been seen yet.
	vector<int> parent(adj.size(), -1);       //Holds the parent values of the vertex
	list<adj_node*> buffer;                   //Holds the vertices as the graph is searched.  
	adj_node* curr;
	
	for(int i = 0; i < V; i++){               //Initializes all values of seen
		seen[i] = false;                      //As false
	}              
	seen[s] = true;                           //Marks the start node as seen.
	buffer.push_back(adj[s]->head);           //Enqueues the start node.
	cout << "Start BFS: ";
	while(!buffer.empty()){                   //While the buffer holding nodes has SOMETHING there:
		curr = buffer.front();                //Dequeues the next node in the list to have its adjacency queued. 
		buffer.pop_front();
		int temp = curr->id;
		while(curr->next != NULL){
			curr = curr->next;
			if(seen[curr->id] == false){
				seen[curr->id] = true;
				buffer.push_back(adj[curr->id]->head);
				parent[curr->id] = temp;
			}
		}
	}
	if(parent.at(V-1) == -1){
		cout << "No path found to the exit starting at 0. Terminating BFS." << endl;
		system("PAUSE");
		return;
	}
	printBFS(V - 1, parent);
}
void Graph::printBFS(int end, vector<int> parent){
	cout << endl;
	for(int i = 0; i < parent.size(); i++){
		cout << "Parent of: " << i << " is: " << parent.at(i) << endl;
	}
	stack<int> output;
	int count = 0;
	
	while(end >= 0){
		output.push(end);
		end = parent[end];
		count++;
	}
	while(!output.empty()){
		cout << output.top() << "->";
		output.pop();
	}
	cout << "END" << endl;
	cout << "This took the opening of: " << count << " doors using BFS." << endl;
}
#endif
