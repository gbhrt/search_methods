#include <string>
#include <vector>
#include <iostream> 
#include <queue> 
#include <ctime>

#include "Header.h"

using namespace std;

vector<Node*> A_star_algo(Node* start, Node* goal, int & count, bool & success)
{
	priority_queue <Node*,vector<Node*>, Comparator > pq;//create open nodes quene 

	start->f = 5;//start->g;
	pq.push(start);//initialize with start node
	hash_table hash_pq;
	hash_pq.push(start);
	hash_table hash_C;
	count = -1;//because also count the given start node.
	while (!pq.empty())
	{
		Node* n = pq.top();
		pq.pop();
		hash_pq.remove(n);
		count++;
		if (check_goal(n, goal))
		{
			success = true;
			return get_path(n);
		}
		hash_C.push(n);
		
		vector <Operation> operations = get_allowed_operators(n);
		for (int i = operations.size() - 1; i >= 0; i--)//if f values are the same for two nodes, pop first nodes from quene according to operator preference
		{
			Node* g = get_node(n, operations[i]);//create a new node
			g->f = g->g + comp_heuristic(g, goal);//A*
			
			if (!hash_C.is_inside(g) && !hash_pq.is_inside(g))//check if the new node is in the open or closed list
			{
				pq.push(g);
				hash_pq.push(g);
			}
			else if(hash_pq.is_inside(g))
			{
				Node* exist_g = hash_pq.get_node(g);
				if (exist_g->f > g->f)
				{
					replace_node_in_priority_quene(pq, exist_g, g);
				}
			}

		}
	}
	
	success = false;
	vector<Node*> path;
	return path;
}