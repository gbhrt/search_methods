#include <string>
#include <vector>
#include <iostream> 
#include <queue> 
#include <ctime>

#include "Header.h"

using namespace std;

bool A_star_algo(Node* start, Node* goal, int & count)
{
	winTimer timer;

	priority_queue <Node*,vector<Node*>, Comparator > pq;//create open nodes quene 

	start->f = 5;//start->g;
	pq.push(start);//initialize with start node
	
	//goal->f = 0;
	//pq.push(goal);//initialize with start node
	//Node* n = pq.top();
	//pq.pop();
	//print_node(n, "n");


	hash_table hash_pq;
	hash_pq.push(start);
	hash_table hash_C;
	count = -1;//because also count the given start node.
	while (!pq.empty())
	{
		Node* n = pq.top();
		//if (count ==1)
		//{
		//	for (int i = 0; i < pq.size(); i++)
		//	{
		//		n = pq.top();
		//		pq.pop();
		//		cout << "f: " << n->f << endl;
		//	}
		//}

		
		pq.pop();
		hash_pq.remove(n);
		count++;
		if (check_goal(n, goal))
		{
			goal->parent = n->parent;
			goal->operation = n->operation;
			return true;
		}
		hash_C.push(n);
		
		/*cout << "_____________________\n";
		print_node(n,"n");*/

		vector <Operation> operations = get_allowed_operators(n);

		//cout << "operations size: " << operations.size() << endl;
		for (int i = 0; i < operations.size(); i++)
		{

			Node* g = get_node(n, operations[i]);//create a new node
			//g->f = g->g;//uniform cost search
			g->f = g->g + comp_heuristic(g, goal);//A*
			
												 //print_node(g,"new node");


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
	return false;
}