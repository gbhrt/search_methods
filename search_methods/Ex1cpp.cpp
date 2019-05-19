#include "Header.h"
#include <iostream>
#include <ctime>
using namespace std;

int main()
{ 
	string input_file_name = "input.txt";
	string output_file_name = "output.txt";

	Node* start = new Node();
	string algorithm_type;
	bool time_flag = false;
	bool error = load_data(input_file_name, algorithm_type, time_flag, start);
	start->root = true;
	start->g = 0;

	if (error)
	{
		cout << "cannot load data\n";
		pause_exit();
	}

	Node* goal = comp_goal(start->N, start->M);

	cout << "heuristic gues: " << comp_heuristic(start, goal) << endl;
	print_node(start, "start");
	print_node(goal, "goal");
	bool success;
	double run_time;
	string str_path;
	vector<Node*> path;
	int count = 0, cost = 0;
	clock_t begin = clock();

	if (algorithm_type == "BFS")
		path = BFS_algo(start, goal, count, success);
	if (algorithm_type == "DFID")
		path = DFID_algo(start, goal, count, success);
	if (algorithm_type == "A*")
	{
		algorithm_type = "A_star";
		path = A_star_algo(start, goal, count, success);
	}
	if (algorithm_type == "IDA*")
	{
		algorithm_type = "IDA_star";
		path = IDA_star_algo(start, goal, count, success);
	}
	if (algorithm_type == "DFBnB")
		path = DFBnB_algo(start, goal, count,success);
		


	run_time = (float)(clock() - begin) / CLOCKS_PER_SEC;
	if (success)
	{
		Node* node = path.front();
		cost = node->g;
	}
	str_path = create_path_string(path, success);

	vector<string> answers;
	answers.push_back(str_path);
	answers.push_back("Num: " + NumberToString(count));
	answers.push_back("Cost: " + NumberToString(cost));
	if (time_flag)
		answers.push_back(NumberToString(run_time));

	save_data(output_file_name, answers);//+" "+algorithm_type+"_.txt"
	
	system("pause");
	return 0;
}