#include "Header.h"

vector<int> get_indexes(Node * goal,int num)//general method, if the goal is constant(as in this exersise) a more efficient algorithm exist
{
	for (int i = 0; i < goal->N; i++)//rows

		for (int j = 0; j < goal->M; j++)
			if (num == goal->state[i][j])
			{
				vector<int> indexes; indexes.push_back(i); indexes.push_back(j);
				return indexes;

			}
}
int comp_heuristic(Node * node, Node * goal)
{
	//manhattan distance:
	int manhattan_distance = 0;
	for (int i = 0; i < node->N; i++)//rows
	{
		for (int j = 0; j < node->M; j++)
		{
			if (node->state[i][j] == 0)
				continue;
			vector<int> indexes = get_indexes(goal, node->state[i][j]);
			manhattan_distance += abs(i - indexes[0]) + abs(j - indexes[1]);
		}
	}
	int odd = manhattan_distance % 2;

	return   (manhattan_distance - odd) * 3 + odd * 5;
}