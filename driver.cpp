#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <limits>
#include <fstream>
#include <string>
#include <vector>
#include "Graph.h"

using namespace std;

void buildGraph()
{
	ifstream input;
	input.open("sample-input.txt");

	ofstream output;
	output.open("output.txt", std::ofstream::trunc);//delete everything in the output file if it already exists
	output.close();

	int num_levels, num_rows, num_cols, num_mazes;
	int start_level, start_row, start_col;
	int goal_level, goal_row, goal_col;
	char direction[6];
	string junk;
		

    if (input.is_open())
    {
        // while (input.good())
        // {
        input >> num_mazes;
        getline(input, junk);

        for(int a = 0; a < num_mazes; a++){
        	input >> num_levels >> num_rows >> num_cols;
           	getline(input, junk);
           	Graph g(num_levels, num_rows, num_cols);
           	//cout << "Everything good here\n";
           	//g.Dimensions();
           	//g.printGraph();
           	//input.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //advance one line

           	input >> start_level >> start_row >> start_col;
           	getline(input, junk);
           	g.addStart(start_level, start_row, start_col);
           	//cout << "Everything good here\n";
           	//input.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //advance one line

           	input >> goal_level >> goal_row >> goal_col;
           	getline(input, junk);
           	g.addGoal(goal_level, goal_row, goal_col);
           	//cout << "Everything good here\n";
           	//input.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //advance one line

           	for(int i = 0; i < num_levels; i++){
           		for(int j = 0; j < num_rows; j++){
           			for(int k = 0; k < num_cols; k++){
           				input >> direction;
           				//cout << direction;
           				
           				if(direction[0] == '1'){
           					//add edge between north
           					g.addEdge(i, j, k, i, j-1, k, 'N');
           				}
           				
           				if(direction[1] == '1'){
           					//add edge between east
           					g.addEdge(i, j, k, i, j, k+1, 'E');
           				}
           				
           				if(direction[2] == '1'){
           					//add edge between south
           					g.addEdge(i, j, k, i, j+1, k, 'S');
           				}
           				
           				if(direction[3] == '1'){
           					//add edge between west
           					g.addEdge(i, j, k, i, j, k-1, 'W');
           				}
           				
           				if(direction[4] == '1'){
           					//add edge between up
           					g.addEdge(i, j, k, i+1, j, k, 'U');
           				}
           				
           				if(direction[5] == '1'){
           					//add edge between down
           					g.addEdge(i, j, k, i-1, j, k, 'D');
           				}
           				//cout << "Everything good here\n";
           				//cout << i << " " << j << " " << k << "\n";

           			}

           			input.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //advance one line
           		}

           		//input.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //advance one line
           	}

            //input.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //advance one line
            //g.printGraph();
            g.BFS();
            g.shortest_path();
        }  	
        input.close();
        
    }
        
    else cout << "Unable to open file";
}

int main()
{
	// Graph g(2, 1, 2);
	// g.printGraph();
	// g.Dimensions();

	// g.addEdge(0, 0, 0, 1, 0, 0, 'U');
	// g.addEdge(0, 0, 1, 0, 0, 0, 'E');
	// g.addEdge(1, 0, 0, 0, 0, 0, 'D');
	// g.addEdge(0, 0, 0, 0, 0, 1, 'W');
	// g.addEdge(0, 0, 1, 1, 0, 1, 'U');
	// g.addEdge(1, 0, 1, 0, 0, 1, 'D');

	// g.addStart(0, 0, 0);

	// g.printGraph();
	// g.BFS();

	buildGraph();

	return 0;
}