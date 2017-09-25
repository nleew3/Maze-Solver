#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <stdexcept>
#include <exception>
#include <string.h>
#include <queue>


using namespace std;

class Graph
{
private:
	struct node{
		int level;
		int row;
		int col;
		char dirc;
		node *next;
	};

	struct bfs_node{
		int level;
		int row;
		int col;
		char dirc;
	};

	struct list{
		struct node* head;
		struct node* tail;
		bool goal;
	};

	int levels, rows, cols, num_cells, queue_size, front, rear, stack_size, top, bottom;
	list ***array;
	bfs_node *bfs;
	bfs_node *queue;
	int start_l, start_r, start_c;
	int goal;
	char *path;

public:
	Graph(int l, int r, int c)
	{
		levels = l;
		rows = r;
		cols = c;
		num_cells = l * r * c;

		array = (list ***)malloc(levels*sizeof(list**));

        for (int a = 0; a < levels; a++) {

         array[a] = (list **) malloc(rows*sizeof(list *));

          for (int b = 0; b < rows; b++) {

              array[a][b] = (list *)malloc(cols*sizeof(list));
          }

        }

        bfs = new bfs_node [num_cells];
        queue = new bfs_node [num_cells];
        path = new char [num_cells];
        front = -1;
        rear = -1;
        queue_size = 0;
        stack_size = 0;
        top = 0;

		for(int i = 0; i < levels; i++){
			for(int j = 0; j < rows; j++){
				for(int k = 0; k < cols; k++){
					array[i][j][k].head = NULL;
					array[i][j][k].tail = NULL;
					array[i][j][k].goal = false;
				}
			}
		}
	}

	Graph()
	{

	}

	struct node* New_node(int l, int r, int c, char d)
	{
    	struct node* new_node =
        	    (struct node*) malloc(sizeof(struct node));
    	new_node->level = l;
    	new_node->row = r;
		new_node->col = c;
		new_node->dirc = d;
    	new_node->next = NULL;
    	return new_node;
	}

	void addStart(int l, int r, int c)
	{
		start_l = l;
		start_r = r;
		start_c = c;
		// cout << l << "\n";
		// cout << r << "\n";
		// cout << c << "\n";
	}

	void addGoal(int l, int r, int c)
	{
		array[l][r][c].goal = true;
	}

	void addEdge(int s_l, int s_r, int s_c, int d_l, int d_r, int d_c, char direction)
	{
		//cout << "Eveything good here \n";
		struct node* new_node = New_node(d_l, d_r, d_c, direction);
		//cout << "Eveything good here \n";

		if(array[s_l][s_r][s_c].head == NULL){
			array[s_l][s_r][s_c].head = new_node;
			array[s_l][s_r][s_c].tail = new_node;
			//cout << "Eveything good here \n";
		}
		else{
			array[s_l][s_r][s_c].tail->next = new_node;
			
			array[s_l][s_r][s_c].tail = new_node;
			//cout << "Eveything good here \n";
		}

		array[s_l][s_r][s_c].tail->next = NULL;
		//cout << "Eveything good here \n";

	}

	void Dimensions()
	{
		cout << levels << "\n";
		cout << rows << "\n";
		cout << cols << "\n";
	}

	bool Queue_isEmpty(){
		if(queue_size == 0){
			return true;
		}

		return false;
	}

	void enqueue(struct bfs_node new_node){
		//cout << "Everything good here\n";
		if(Queue_isEmpty()){
			front = rear = 0;
		}
		else{
			rear++;
		}

		//cout << "Everything good here\n";
		queue[rear] = new_node;
		queue_size++;
	}

	struct bfs_node dequeue(){
		struct bfs_node pop = queue[front];

		if(front == rear){
			rear = front = -1;
		}
		else{
			front++;
		}

		queue_size--;
		return pop;
	}

	bool Stack_isEmpty()
	{
		if(stack_size == -1){
			return true;
		}

		return false;
	}

	void push(char c)
	{
		path[top] = c;
		top++;
		stack_size++;
	}

	char pop()
	{
		char c;

		c = path[top];
		top--;
		stack_size--;

		return c;
	}

	void BFS()
	{
		int i = 0;
		struct bfs_node root;
		struct bfs_node new_node;
		struct  bfs_node s;
		struct node* current;
		root.level = start_l;
		root.row = start_r;
		root.col = start_c;

		//cout << "Everything good here\n";
		bool visited[levels][rows][cols];
		
		for(int a = 0; a < levels; a++){
			for(int b = 0; b < rows; b++){
				for(int c = 0; c < cols; c++){
					visited[a][b][c] = false;
				}
			}
		}

		//cout << "Everything good here\n";
		visited[start_l][start_r][start_c] = true;
		//cout << "Everything good here\n";
		enqueue(root);

		while(!Queue_isEmpty()){
			//cout << "Everything good here\n";
			s = dequeue();
			
			bfs[i] = s;
			
			// cout << bfs[i].level << " ";
			// cout << bfs[i].row << " ";
			// cout << bfs[i].col << "\n";


			current = array[s.level][s.row][s.col].head;

			if(array[s.level][s.row][s.col].goal == true){
				goal = i;
			}

			i++;


			//cout << "Everything good here\n";
			while(current != NULL){
				if(!visited[current->level][current->row][current->col]){
					// cout << current->level << " ";
					// cout << current->row << " ";
					// cout << current->col << "\n";

					visited[current->level][current->row][current->col] = true;

					new_node.level = current->level;
					new_node.row = current->row;
					new_node.col = current->col;
					new_node.dirc = current->dirc;

					enqueue(new_node);

					current = current->next;
				}
				else{
					current = current->next;
				}
			}
		}

		// cout << bfs[0].level << " ";
		// cout << bfs[0].row << " ";
		// cout << bfs[0].col << "\n";

		// for(int i = 1; i < num_cells; i++){
		// 	cout << bfs[i].level << " ";
		// 	cout << bfs[i].row << " ";
		// 	cout << bfs[i].col << " ";
		// 	cout << bfs[i].dirc << "\n";
		// }
	}

	bool isAdjacenct(int s_l, int s_r, int s_c, int d_l, int d_r, int d_c)
	{
		struct node* current;

		current = array[s_l][s_r][s_c].head;

		while(current != NULL){
			if(current->level == d_l && current->row == d_r && current->col == d_c){
				return true;
			}

			current = current->next;
		}

		return false;
	}

	void shortest_path()
	{
		ofstream output;

		struct bfs_node current;
		int i = goal;
		current = bfs[i];

		// cout << bfs[i].level << " ";
		// cout << bfs[i].row << " ";
		// cout << bfs[i].col << "\n";
		push(current.dirc);

		while(i != 0){
			if(isAdjacenct(current.level, current.row, current.col, bfs[i].level, bfs[i].row, bfs[i].col)){
				// cout << bfs[i].level << " ";
				// cout << bfs[i].row << " ";
				// cout << bfs[i].col << "\n";
				
				current = bfs[i];
				push(current.dirc);
			}

			i--;
		}

		output.open("output.txt", std::ofstream::app);
		while(!Stack_isEmpty()){
			output << pop() << " ";
		}
		output << "\n";
		output.close();
	}

	void printGraph()
	{
		node* current;

		for(int i = 0; i < levels; i++){
			for(int j = 0; j < rows; j++){
				for(int k = 0; k < cols; k++){
					cout << "Coordinatets (level, row, column): ";
					cout << "(" << i;
					cout << ", " << j;
					cout << ", " << k ;
					cout << ") ";
					
					current = array[i][j][k].head;

					cout << "Possible moves: ";

					while(current != NULL){
						cout << "(" << current->level;
						cout << ", " << current->row;
						cout << ", " << current->col << ") ";
						cout << "Direction: " << current->dirc;
						cout << "    ";

						current = current->next;
					}

					cout << "\n";
				}
			}
		}
					
	}
};