#include "Header.h"


bool DFS_algo(Node* start, Node* goal, int max_depth, int & count)
{
	//Node* node = new Node();
	if (check_goal(start, goal))
		return true;

	vector <Operation> operations = get_allowed_operators(start);
	for (int i = 0; i < operations.size(); i++)
	{
		Node* g = get_node(start, operations[i]);//create a new node
		count++;
		if (count == max_depth)
			return false;
		if (DFS_algo(g, goal, max_depth, count))
			return true;
	}
	return false;
}

bool DFID_algo(Node* start, Node* goal, int & count)
{
	int max_depth = 1;
	count = 0;
	while (1) 
	{
		if (DFS_algo(start, goal, max_depth, count))
			return true;
		count++;
	}
	return false;

}