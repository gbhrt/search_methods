#include "Header.h"
#include<iostream>
using namespace std;
winTimer timer;
bool DFS_algo(Node* start, Node* goal, hash_table & working_path, int max_depth, int & count)
{
	
	if (max_depth == 0)
		return false;
	max_depth--;
	working_path.push(start);
	//cout << "working_path: " << working_path.size() << endl;
	vector <Operation> operations = get_allowed_operators(start);
	for (int i = 0; i < operations.size(); i++)
	{
		Node* g = get_node(start, operations[i]);//create a new node
		//print_node(g,"g"+NumberToString(i));
		count++;
		
		if (working_path.is_inside(g))
		{
			
			//cout << "loop avoided" << endl;
			delete g;
			continue;

		}
		
		

		if (check_goal(g, goal))
		{
			goal->parent = g->parent;
			goal->operation = g->operation;
			/*working_path.remove(start);
			delete start;*/
			return true;
		}
		
		if (DFS_algo(g, goal, working_path, max_depth, count))
		{
			//timer.save_time();
			//working_path.remove(start);
			//delete start;
			//cout << "time is_inside: " << timer.get_time() << endl;
			return true;
		}
	}
	working_path.remove(start);
	//if(!start->root)
	//	delete start;
	//cout << "end path ____________________\n";
	return false;
}

bool DFID_algo(Node* start, Node* goal, int & count)
{
	int max_depth = 0;
	hash_table  working_path;
	working_path.push(start);
	count = 0;
	while (1) 
	{
		if (DFS_algo(start, goal, working_path, max_depth, count))
			return true;
		//working_path.clear();
		max_depth++;
		cout << "max_depth: " << max_depth << "_____________________\n";
	}
	return false;

}