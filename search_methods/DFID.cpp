#include "Header.h"
#include<iostream>
using namespace std;

bool DFS_algo(Node* start, Node* goal, hash_table & working_path, int max_depth, int & count,bool & reach_max)
{
	count++;
	if (max_depth == 0)
	{
		if (!start->root)
			delete start;
		reach_max = true;
		return false;
	}
	max_depth--;
	working_path.push(start);
	vector <Operation> operations = get_allowed_operators(start);
	//for (Operation operation: operations)
	for(int i=0;i<operations.size();i++)
	{
		Node* g = get_node(start, operations[i]);//create a new node

		if (working_path.is_inside(g))
		{
			delete g;
			continue;
		}
		if (check_goal(g, goal))
		{
			goal->operation = g->operation; 
			goal->parent = g->parent;
			goal->g = g->g;
			return true;
		}
		
		
		if (DFS_algo(g, goal, working_path, max_depth, count, reach_max))
			return true;
	}
	working_path.remove(start);
	if(!start->root)
		delete start;
	return false;
}

vector<Node*> DFID_algo(Node* start, Node* goal, int & count, bool & success)
{
	int max_depth = 1;
	hash_table  working_path;
	working_path.push(start);
	count = 0;
	
	while (1) 
	{
		bool reach_max = false;
		if (DFS_algo(start, goal, working_path, max_depth, count, reach_max))
		{
			success =  true;
			return get_path(goal);
		}
		if (reach_max)
			max_depth++;
		else
		{
			success = false;
			vector<Node*> path;
			return path;
		}
	}
	success = false;
	vector<Node*> path;
	return path;
}