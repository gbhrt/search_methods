#include <string>
#include <vector>
#include <iostream> 
#include <stack> 
#include <ctime>
#include <list>

#include "Header.h"


using namespace std;


vector<Node*> DFBnB_algo(Node* start, Node* goal, int & count,bool & error)
{
	int inf = 99999999;
	int upper_bound = 12;

	vector<Node*> result;//solution
	stack <Node*> L;//create open nodes stack 
	hash_table H;
	int t = upper_bound;



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
			if (!n->root)
				delete n;
		}
		else
		{
			n->out = true;
			count++;
			//cout << count << endl;
			L.push(n);
			vector <Operation> operations = get_allowed_operators(n);
			print_node(n, "_____n____");

			list<Node*> N;
			//for (Operation operation : operations)
			for(int i = 0; i< operations.size();i++)
			{
				Node* g = get_node(n, operations[i]);//create a new node
				
				int h = comp_heuristic(g, goal);
				g->f = g->g + h;
				
				g->out = false;
				N.push_back(g);
			}
			N.sort(ComparatorIncrease());
			list<Node*>::iterator it = N.begin();
			while (it != N.end())
			{
				Node* g = *it;
				
				print_node(g, "g");
				cout << "f: " << g->f << endl;// "h: " << h << endl;
				if (g->f > t)
				{
					while (it != N.end())
						it= N.erase(it);

					break;//avoids it++ at the end of the loop
				}
				else if (H.is_inside(g))
				{
					Node* exist_g = H.get_node(g);
					if (exist_g->out)
					{
						it = N.erase(it);
						continue;//avoids it++ at the end of the loop
						
					}
					else//(!exist_g->out)
					{
						if (exist_g->f <= g->f)
						{
							it = N.erase(it);
							continue;//avoids it++ at the end of the loop
						}
						else
						{
							remove_from_stack(L, exist_g);
							H.remove(exist_g);
						}
					}
				}
				else if (check_goal(g, goal))
				{
					t = g->f;
					cout << "found goal " << t << endl;

					//result = get_path(L);
					result = get_path(g);
					//result.push_back(copy_node(g));
					while (it != N.end())
						it = N.erase(it);
					break;
				}
				++it;
			}
			if (N.size() > 0)
			{
				it = N.end();
				it--;
				while (1)
				{
					L.push(*it);
					H.push(*it);
					
					if (it == N.begin())
						break;
					it--;
				}
			}
		}
	}
	return result;
}

				