#include "Adjacency_List.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

int main(){
	ifstream input;                                      //Opens the file stream for the maze input file.
	char fileName[20] = {};                              //Holds a character filename up to 20 characters.
	int  size;                                           //Holds the size of the maze.
	
	cout << "Maze Filename (less than 20 characters): "; //Requests the filename
	cin  >> fileName;                                    //Gets the filename
	input.open(fileName);                                //Opens the input stream
	if(!input.is_open()){                                //Checks if the input stream was sucessfully opened
		cout << "Warning: File not found!" << endl;      //Lets the user know that there was an issue opening the file
		system("PAUSE");                                 //Pauses so you can see the error
		return 0;                                        //Terminates the program
	}
	cout << "Maze File " << fileName << " was successfully opened!" << endl;
	cout << "Beginning solution. . ." << endl;           //Signals a successful file opening.
	input >> size;                                       //Gets the size as the first input from the fle
	if(sqrt(size) == abs(sqrt(size))){                   //Checks if the size is a perfect square.
		cout << "Correct maze size processed!" << endl;  //If it's a perfect square, things are all good.
	}else{                                               //Otherwise, the program terminates before any errors occur.
		cout << "Invalid size in the file, please input a perfect square." << endl;
		system("PAUSE");
		return 0;
	}
	/*
	  Graph building operations begin beyond this point.
	*/
	Graph* matrix = new Graph(size);                      //Constructs a graph of sqrt(size), since it is a perfect square, holds dimensionality.
	vector<int> dir(4, 0);
	for(int i = 0; i < sqrt(size); i++){		          //Adds vertices to the matrix at the correct locations.
		for(int j = 0; j < sqrt(size); j++){
			matrix->addVertex(i, j);                     
		}
	}
	for(int i = 0; i < sqrt(size); i++){                  //Adds edges to the matrix at the correct locations.
		for(int j = 0; j < sqrt(size); j++){
			for(int k = 0; k < 4; k++){
				input >> dir.at(k); 
				cout << "Added the direction: " << dir.at(k) << " to edges to be added" << endl;
			}
			matrix->addEdge(i, j, dir);
		}
	}
	cout << endl << "Test run: " << endl;
	matrix->testRun();
	cout << endl << "Graph: " << endl;
	matrix->printGraph();
}
