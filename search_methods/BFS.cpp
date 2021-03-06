#include <string>
#include <vector>
#include <iostream> 
#include <queue> 
#include <ctime>

#include "Header.h"

using namespace std;

vector<Node*> BFS_algo(Node* start, Node* goal, int & count, bool & success)
{
	queue <Node*> L;//create open nodes quene 
	L.push(start);//initialize with start node
	hash_table hash_L;
	hash_L.push(start);
	hash_table hash_C;
	count = 0;	
	while (!L.empty())
	{
		Node* n = L.front();
		L.pop();
		hash_L.remove(n);
		hash_C.push(n);
		count++;

		vector <Operation> operations = get_allowed_operators(n);
		for (int i = 0; i < operations.size(); i++)
		{
			Node* g = get_node(n, operations[i]);//create a new node

			if (!hash_C.is_inside(g) && !hash_L.is_inside(g))//check if the new node is in the open or closed list
			{
				if (check_goal(g, goal))
				{
					success = true;
					return get_path(g);
				}
				L.push(g);
				hash_L.push(g);
			}
		}
	}
	success = false;
	vector<Node*> path;
	return path;
}