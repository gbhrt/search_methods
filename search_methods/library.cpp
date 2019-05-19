#include<iostream>
#include<string>
#include <sstream> // stringstream
#include <iomanip> // setprecision
#include <ctime>
#include <queue> 
#include <stack> 
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

vector<int> init_vec98(int a, int b)
{
	vector<int> vec;
	vec.push_back(a);
	vec.push_back(b);
	return vec;
}

void pause_exit()
{
	cout << "press any key to exit the program" << endl;
	//getchar();
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

int get_cost(Operation  operation)
{
	if (operation.blockes_ind.size() == 1)
		return 5;
	else if (operation.direction == 1 || operation.direction == 3)//vertical
		return 7;
	else
		return 6;
}
vector<Node*> get_path(Node* node)
{
	vector<Node*> path;
	while (1)
	{
		if (node->root)
			break;
		path.push_back(copy_node(node));
		node = node->parent;
	}
	return path;
}
string create_path_string(vector<Node*> path,bool success)
{
	if (!success)
	{
		cout << "cannot compute path"<< endl;
		return "no path";
	}

	vector<string>path_vec;
	//for (Node* node : path)
	for(int i = 0;i<path.size();i++)
	{
		path_vec.push_back(path[i]->operation.create_string());
	}
	string str_path;
	for (int i =path_vec.size()-1; i >= 0; i--)
	{
		str_path.append(path_vec[i]);
		str_path.append("-");
	}
	str_path = str_path.substr(0, str_path.size() - 1);
	return str_path;
}

Node* copy_node(Node* node)
{
	Node* c_node = new Node();//copy node 

	c_node->M = node->M;
	c_node->N = node->N;
	c_node->g = node->g;
	c_node->f = node->f;
	c_node->state = node->state;
	c_node->holes[0][0] = node->holes[0][0];
	c_node->holes[0][1] = node->holes[0][1];
	c_node->holes[1][0] = node->holes[1][0];
	c_node->holes[1][1] = node->holes[1][1];

	c_node->operation.blockes_ind = node->operation.blockes_ind;
	c_node->operation.blockes_val = node->operation.blockes_val;
	c_node->operation.direction = node->operation.direction;
	c_node->operation.hole_ind = node->operation.hole_ind;

	c_node->root = node->root;
	c_node->out = node->out;

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
	Node* node = new Node();
	node->M = parent_node->M;
	node->N = parent_node->N;
	node->state = parent_node->state;
	node->parent = parent_node;
	node->operation.direction = operation.direction;
	node->g = get_cost(operation) + parent_node->g;

	for (int i = 0; i < operation.blockes_ind.size(); i++)//for all blockes (1 or 2)
	{
		vector<int> ind = init_vec98( operation.blockes_ind[i][0],operation.blockes_ind[i][1] );

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

bool check_operation(Node* node, Operation operation)//check if the operation leads to parents node
{
	if (node->root)
		return true;
	if(operation.blockes_ind.size() != node->operation.blockes_ind.size()|| 
		operation.direction % 2 != node->operation.direction % 2 || operation.direction == node->operation.direction)//not the same number of blockes or not the opposide direction
		return true;
	
	vector<int>blockes_ind;//the index of the  position of the moved block from the parent node
	if (node->operation.direction == 0)
		blockes_ind = init_vec98(node->operation.blockes_ind[0][0] - 1, node->operation.blockes_ind[0][1]);
	else if (node->operation.direction == 1)
		blockes_ind = init_vec98(node->operation.blockes_ind[0][0], node->operation.blockes_ind[0][1] - 1);
	else if (node->operation.direction == 2)
		blockes_ind = init_vec98(node->operation.blockes_ind[0][0] + 1, node->operation.blockes_ind[0][1]);
	else// (node->operation.direction == 3)
		blockes_ind = init_vec98(node->operation.blockes_ind[0][0], node->operation.blockes_ind[0][1] + 1);

	if (operation.blockes_ind[0][0] != blockes_ind[0] || operation.blockes_ind[0][1] != blockes_ind[1])
		return true;
	if (operation.blockes_ind.size() == 2)
		if(operation.blockes_ind[1][0] != blockes_ind[0] || operation.blockes_ind[1][1] != blockes_ind[1])
				return true;

	return false;
}

vector<Operation> get_allowed_operators(Node* node)//return the allowed operators in the required order
{

	//winTimer timer;
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
			vector<int> block = init_vec98(node->holes[i][0] + 1 ,node->holes[i][1] );

			operation.blockes_ind.push_back(block);
		}
		//if ()
		operation.direction = 0;//left
		operation.hole_ind = 2;
		if (check_operation(node, operation))
			operations.push_back(operation);
	}



	//two holes side by side and not on the upper edge:
	if ((abs(node->holes[0][0] - node->holes[1][0]) == 1 && node->holes[0][1] == node->holes[1][1]) && node->holes[0][1] < node->N - 1)
	{
		Operation operation;
		for (int i = 0; i < 2; i++)
		{
			vector<int> block = init_vec98(node->holes[i][0],node->holes[i][1] + 1 );
			operation.blockes_ind.push_back(block);
		}
		operation.direction = 1;//up
		operation.hole_ind = 2;
		if (check_operation(node, operation))
			operations.push_back(operation);
	}
	//two holes one above the second and not on the right edge:
	if ((abs(node->holes[0][1] - node->holes[1][1]) == 1 && node->holes[0][0] == node->holes[1][0]) && node->holes[0][0] > 0)
	{
		Operation operation;
		for (int i = 0; i < 2; i++)
		{
			vector<int> block = init_vec98(node->holes[i][0] - 1,node->holes[i][1] );
			operation.blockes_ind.push_back(block);
		}
		operation.direction = 2;//right
		operation.hole_ind = 2;
		if (check_operation(node, operation))
			operations.push_back(operation);
	}


	//two holes side by side and not  on the under edge:
	if ((abs(node->holes[0][0] - node->holes[1][0]) == 1 && node->holes[0][1] == node->holes[1][1]) && (node->holes[0][1] > 0))
	{
		Operation operation;
		for (int i = 0; i < 2; i++)
		{
			vector<int> block = init_vec98(node->holes[i][0], node->holes[i][1] - 1 );
			operation.blockes_ind.push_back(block);
		}
		operation.direction = 3;//down
		operation.hole_ind = 2;
		if (check_operation(node, operation))
			operations.push_back(operation);
	}
	int first_hole;
	if (node->holes[0][1] < node->holes[1][1])//0 is above 1
		first_hole = 0;
	else if (node->holes[0][1] > node->holes[1][1])//1 is above 0
		first_hole = 1;
	else if (node->holes[0][0] < node->holes[1][0])//both in the same row and 0 is left to 1
		first_hole = 0;
	else//both in the same row and 1 is left to 0
		first_hole = 1;
	int hole = first_hole;
	int second_hole;
	if (first_hole == 0) second_hole = 1;
	else second_hole = 0;
	for (int i = 0; i < 2; i++)//for each of the holes
	{

		if (node->holes[hole][0] < node->M - 1)
		{
			
			vector<int> block = init_vec98(node->holes[hole][0] + 1 , node->holes[hole][1] );
			if (block[0] != node->holes[second_hole][0] || block[1] != node->holes[second_hole][1])
			{
				Operation operation;
				operation.blockes_ind.push_back(block);

				operation.direction = 0;//left
				operation.hole_ind = hole;
				if (check_operation(node, operation))
					operations.push_back(operation);
			}

		}
		if (node->holes[hole][1] < node->N - 1)
		{
			vector<int> block = init_vec98(node->holes[hole][0],node->holes[hole][1] + 1 );
			if (block[0] != node->holes[second_hole][0] || block[1] != node->holes[second_hole][1])
			{
				Operation operation;
				operation.blockes_ind.push_back(block);
				operation.direction = 1;//up
				operation.hole_ind = hole;
				if (check_operation(node, operation))
					operations.push_back(operation);
			}
		}
		if (node->holes[hole][0] > 0)
		{
			vector<int> block = init_vec98(node->holes[hole][0] - 1,node->holes[hole][1] );
			if (block[0] != node->holes[second_hole][0] || block[1] != node->holes[second_hole][1])
			{
				Operation operation;
				operation.blockes_ind.push_back(block);
				operation.direction = 2;//right
				operation.hole_ind = hole;
				if (check_operation(node, operation))
					operations.push_back(operation);
			}
		}
		if ((node->holes[hole][1] > 0))
		{
			vector<int> block = init_vec98(node->holes[hole][0] , node->holes[hole][1] - 1 );
			if (block[0] != node->holes[second_hole][0]  || block[1] != node->holes[second_hole][1])
			{
				Operation operation;
				operation.blockes_ind.push_back(block);
				operation.direction = 3;//down
				operation.hole_ind = hole;
				if (check_operation(node, operation))
					operations.push_back(operation);
			}

		}
		hole = second_hole;
		second_hole = first_hole;
	}
	return operations;

}

void replace_node_in_priority_quene(priority_queue <Node*, vector<Node*>, Comparator > & pq, Node* exist_node, Node * node)
{
	vector<Node*> tmp;
	int size = pq.size();
	do
	{
		tmp.push_back(pq.top());
		pq.pop();
	} while (tmp.back() != exist_node);

	exist_node->f = node->f;
	exist_node->g = node->g;
	exist_node->parent = node->parent;
	for (int i = 0; i < tmp.size(); i++)
		pq.push(tmp[i]);
	
}

void remove_from_stack(stack<Node*> s,Node * node)
{
	stack<Node*> tmp_s;
	do
	{
		tmp_s.push(s.top());
		s.pop();
	} while (tmp_s.top() != node);

	tmp_s.pop();
	while (!tmp_s.empty())
	{
		s.push(tmp_s.top());
		tmp_s.pop();
	}
}

vector<Node*> get_path(stack<Node*> & st)
{	
	vector<Node*> result;
	stack<Node*> tmp_s;

	while (!st.empty())
	{
		Node* n = st.top();
		if (n->out)
			result.push_back(copy_node(n));
		else
			tmp_s.push(n);
		st.pop();

	}
	while (!tmp_s.empty())
		st.push(tmp_s.top());
	
	return result;
}