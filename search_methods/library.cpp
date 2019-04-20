#include<iostream>
#include<string>
#include <sstream> // stringstream
#include <iomanip> // setprecision
#include <ctime>
#include "Header.h"

string NumberToString(double Number)//becuase it use only c++98
{
	ostringstream ss;
	ss << Number;
	return ss.str();
}
string NumberToString(float Number)//becuase it use only c++98
{
	ostringstream ss;
	ss << Number;
	return ss.str();
}
string NumberToString(int Number)//becuase it use only c++98
{
	ostringstream ss;
	ss << Number;
	return ss.str();
}

float StringToFloat(const string &Text)//becuase it use only c++98
{
	istringstream ss(Text);
	float result;
	return ss >> result ? result : 0;
}
int StringToInt(const string &Text)//becuase it use only c++98
{
	istringstream ss(Text);
	int result;
	return ss >> result ? result : 0;
}

void pause_exit()
{
	cout << "press any key to exit the program" << endl;
	getchar();
	exit(1);
}


Node* comp_goal(int N, int M)
{
	Node* goal = new Node();
	goal->holes[0][0] = M - 2;
	goal->holes[1][0] = M - 1;
	goal->holes[0][1] = N - 1;
	goal->holes[1][1] = N - 1;
	goal->M = M;
	goal->N = N;
	int cnt = 1;
	for (int i = 0; i < N; i++)
	{
		vector<int> row;
		for (int j = 0; j < M; j++)
		{
			row.push_back(cnt);
			cnt++;
		}
		goal->state.push_back(row);
	}
	goal->state[goal->holes[0][1]][goal->holes[0][0]] = 0;
	goal->state[goal->holes[1][1]][goal->holes[1][0]] = 0;
	return goal;
}

void print_node(Node* node,string name)
{
	cout << "node "<<name<<endl;
	for (int i = 0; i < node->N; i++)//rows
	{
		for (int j = 0; j < node->M; j++)
		{
			cout << node->state[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;

}

string get_path(Node* node,int & cost)
{
	string path;
	vector<string>path_vec;
	cost = 0;
	while (1)
	{

		print_node(node,"path");
		
		
		if (node->root)
			break;
		path_vec.push_back(node->operation.create_string());
		if (node->operation.blockes_val.size() == 1)
			cost += 5;
		else if (node->operation.direction == 1 || node->operation.direction == 3)//vertical
			cost += 7;
		else
			cost += 6;

		node = node->parent;
	}
	reverse(path_vec.begin(), path_vec.end());
	for (int i = 0; i < path_vec.size(); i++)
	{
		path.append(path_vec[i]);
		path.append("-");
	}
	path = path.substr(0, path.size() - 1);
	return path;
}
Node* copy_node(Node* node)
{
	Node* c_node = new Node();//copy node 

							  //c_node->M = node->M;
							  //c_node->N = node->N;
							  //c_node->state = node->state;
							  //c_node->holes[0][0] = node->holes[0][0];
							  //c_node->holes[0][1] = node->holes[0][1];
							  //c_node->holes[1][0] = node->holes[1][0];
							  //c_node->holes[1][1] = node->holes[1][1];
	return c_node;
}

bool check_goal(Node* node, Node* goal)
{
	for (int i = 0; i< node->N; i++)//rows
		for (int j = 0; j < node->M; j++)
		{
			if (node->state[i][j] != goal->state[i][j])
				return false;
		}
	return true;
}

Node* get_node(Node* parent_node, Operation  operation)
{
	//Node* node = copy_node(parent_node);//copy node 
	Node* node = new Node();
	node->M = parent_node->M;
	node->N = parent_node->N;
	node->state = parent_node->state;
	node->parent = parent_node;
	node->operation.direction = operation.direction;

	for (int i = 0; i < operation.blockes_ind.size(); i++)//for all blockes (1 or 2)
	{
		vector<int> ind = { operation.blockes_ind[i][1],operation.blockes_ind[i][0] };

		node->operation.blockes_ind.push_back(ind);
		node->operation.blockes_val.push_back(node->state[operation.blockes_ind[i][1]][operation.blockes_ind[i][0]]);
		if (operation.direction == 0)//left
		{
			node->state[operation.blockes_ind[i][1]][operation.blockes_ind[i][0] - 1] = node->state[operation.blockes_ind[i][1]][operation.blockes_ind[i][0]];
			node->state[operation.blockes_ind[i][1]][operation.blockes_ind[i][0]] = 0;

		}

		if (operation.direction == 1)//up
		{
			node->state[operation.blockes_ind[i][1] - 1][operation.blockes_ind[i][0]] = node->state[operation.blockes_ind[i][1]][operation.blockes_ind[i][0]];
			node->state[operation.blockes_ind[i][1]][operation.blockes_ind[i][0]] = 0;

		}

		if (operation.direction == 2)//right
		{
			node->state[operation.blockes_ind[i][1]][operation.blockes_ind[i][0] + 1] = node->state[operation.blockes_ind[i][1]][operation.blockes_ind[i][0]];
			node->state[operation.blockes_ind[i][1]][operation.blockes_ind[i][0]] = 0;

		}

		if (operation.direction == 3)//down
		{
			node->state[operation.blockes_ind[i][1] + 1][operation.blockes_ind[i][0]] = node->state[operation.blockes_ind[i][1]][operation.blockes_ind[i][0]];
			node->state[operation.blockes_ind[i][1]][operation.blockes_ind[i][0]] = 0;
		}

	}
	if (operation.blockes_ind.size() == 2)
	{
		for (int i = 0; i < operation.blockes_ind.size(); i++)//for all blockes (1 or 2)
		{
			node->holes[i][0] = operation.blockes_ind[i][0];
			node->holes[i][1] = operation.blockes_ind[i][1];
		}
	}
	else//(operation.blockes_ind.size() == 1)
	{
		node->holes[operation.hole_ind][0] = operation.blockes_ind[0][0];
		node->holes[operation.hole_ind][1] = operation.blockes_ind[0][1];
		int index;
		if (operation.hole_ind == 0)
			index = 1;
		else
			index = 0;
		node->holes[index][0] = parent_node->holes[index][0];
		node->holes[index][1] = parent_node->holes[index][1];
	}

	return node;
}


vector<Operation> get_allowed_operators(Node* node)//return the allowed operators in the required order
{
	winTimer timer;
	//must to change it such that higher rows are before lowers
	//0-L
	//1-U
	//2-R
	//3-D

	vector<Operation> operations;


	//two holes one above the second and not on the left edge:
	if ((abs(node->holes[0][1] - node->holes[1][1]) == 1 && node->holes[0][0] == node->holes[1][0]) && node->holes[0][0] < node->M - 1)
	{
		Operation operation;
		for (int i = 0; i < 2; i++)
		{
			vector<int> block = { node->holes[i][0] + 1 ,node->holes[i][1] };

			operation.blockes_ind.push_back(block);
		}
		operation.direction = 0;//left
		operation.hole_ind = 2;
		operations.push_back(operation);
	}



	//two holes side by side and not on the upper edge:
	if ((abs(node->holes[0][0] - node->holes[1][0]) == 1 && node->holes[0][1] == node->holes[1][1]) && node->holes[0][1] < node->N - 1)
	{
		Operation operation;
		for (int i = 0; i < 2; i++)
		{
			vector<int> block = { node->holes[i][0],node->holes[i][1] + 1 };
			operation.blockes_ind.push_back(block);
		}
		operation.direction = 1;//up
		operation.hole_ind = 2;
		operations.push_back(operation);
	}
	//two holes one above the second and not on the right edge:
	if ((abs(node->holes[0][1] - node->holes[1][1]) == 1 && node->holes[0][0] == node->holes[1][0]) && node->holes[0][0] > 0)
	{
		Operation operation;
		for (int i = 0; i < 2; i++)
		{
			vector<int> block = { node->holes[i][0] - 1,node->holes[i][1] };
			operation.blockes_ind.push_back(block);
		}
		operation.direction = 2;//right
		operation.hole_ind = 2;
		operations.push_back(operation);
	}


	//two holes side by side and not  on the under edge:
	if ((abs(node->holes[0][0] - node->holes[1][0]) == 1 && node->holes[0][1] == node->holes[1][1]) && (node->holes[0][1] > 0))
	{
		Operation operation;
		for (int i = 0; i < 2; i++)
		{
			vector<int> block = { node->holes[i][0], node->holes[i][1] - 1 };
			operation.blockes_ind.push_back(block);
		}
		operation.direction = 3;//down
		operation.hole_ind = 2;
		operations.push_back(operation);
	}
	int first_hole;
	if (node->holes[0][1] < node->holes[0][1])//0 is above 1
		first_hole = 0;
	else if (node->holes[0][1] > node->holes[0][1])//1 is above 0
		first_hole = 1;
	else if (node->holes[0][0] < node->holes[0][0])//both in the same row and 0 is left to 1
		first_hole = 0;
	else//both in the same row and 1 is left to 0
		first_hole = 1;
	int hole = first_hole;
	for (int i = 0; i < 2; i++)//for each of the holes
	{

		if (node->holes[hole][0] < node->M - 1)
		{
			Operation operation;

			vector<int> block = { node->holes[hole][0] + 1 , node->holes[hole][1] };

			operation.blockes_ind.push_back(block);

			operation.direction = 0;//left
			operation.hole_ind = hole;

			operations.push_back(operation);

		}
		if (node->holes[hole][1] < node->N - 1)
		{
			Operation operation;
			timer.save_time();

			vector<int> block = { node->holes[hole][0],node->holes[hole][1] + 1 };

			operation.blockes_ind.push_back(block);
			operation.direction = 1;//up
			operation.hole_ind = hole;
			operations.push_back(operation);
		}
		if (node->holes[hole][0] > 0)
		{
			Operation operation;
			vector<int> block = { node->holes[hole][0] - 1,node->holes[hole][1] };
			operation.blockes_ind.push_back(block);
			operation.direction = 2;//right
			operation.hole_ind = hole;
			operations.push_back(operation);
		}
		if ((node->holes[hole][1] > 0))
		{
			Operation operation;
			vector<int> block = { node->holes[hole][0] , node->holes[hole][1] - 1 };
			operation.blockes_ind.push_back(block);
			operation.direction = 3;//down
			operation.hole_ind = hole;
			operations.push_back(operation);
		}
		if (hole == 0) hole = 1;
		else hole = 0;

	}


	return operations;

}