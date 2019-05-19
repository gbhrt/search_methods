#include <string>
#include <vector>
#include <iostream> 
#include <stack> 
#include <ctime>

#include "Header.h"

using namespace std;

vector<Node*> IDA_star_algo(Node* start, Node* goal, int & count, bool & success)
{
	int inf = 99999999;

	stack <Node*> L;//create open nodes stack 
	hash_table H;
	int t = comp_heuristic(start, goal);
	
	while (t < inf)
	{
		int minF = inf;
		start->out = false;
		L.push(start);//initialize with start node
		H.push(start);

		while (!L.empty())
		{
			Node* n = L.top();
			L.pop();
			if (n->out)
			{
				H.remove(n);
				if(!n->root)
					delete n;
			}
			else
			{
				n->out = true;
				count++;
				L.push(n);
				vector <Operation> operations = get_allowed_operators(n);
				for (int i = operations.size()-1; i>=0 ; i--)
				{
					Node* g = get_node(n, operations[i]);//create a new node
				
					int h = comp_heuristic(g, goal);
					g->f = g->g + h;
					g->out = false;
					if (g->f > t)
					{
						minF = min(minF, g->f);
						delete g;
						continue;
					}
					if (H.is_inside(g))
					{
						Node* exist_g = H.get_node(g);
						if (exist_g->out)
						{
							delete g;
							continue;
						}
						else//if (!exist_g->out)
						{
							if (exist_g->f > g->f)
							{
								remove_from_stack(L, exist_g);
								H.remove(exist_g);
							}
							else
							{
								delete g;
								continue;
							}
						}
					}
					if (check_goal(g, goal))
					{
						success = true;
						return get_path(g);
					}
					L.push(g);
					H.push(g);
				}
			}
		}
		t = minF;
		cout << "t: " << t << endl;
	}
	success = false;
	vector<Node*> path;
	return path;
}

