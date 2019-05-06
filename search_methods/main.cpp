#include "Header.h"
#include <iostream>
//#include<time.h>
#include <ctime>
using namespace std;

int main()
{
	string input_file_name = "files/input_3x3.txt";//_orginal input_hard_A_star input_hard_BFS
	string output_file_name = "files/output_3x3";
	Node* start = new Node();
	string algorithm_type;
	bool time_flag = false;
	bool error = load_data(input_file_name, algorithm_type, time_flag, start);
	start->root = true;
	start->g = 0;

	vector<string> algorithms = { "DFID","BFS","A*" };// ,
	//algorithm_type = "BFS";
	for (int i = 0; i < algorithms.size(); i++)
	{
		algorithm_type = algorithms[i];
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
		int count = 0, cost = 0;
		clock_t begin = clock();

		if (algorithm_type == "BFS")
			success = BFS_algo(start, goal, count);
		if (algorithm_type == "DFID")
			success = DFID_algo(start, goal, count);
		if (algorithm_type == "A*")
		{
			algorithm_type = "A_star";
			success = A_star_algo(start, goal, count);

		}


		run_time = clock() - begin;
		string path;
		if (success)
			path = get_path(goal, cost);
		else
			path = "no path";
		vector<string> answers;
		answers.push_back(path);
		answers.push_back("Num: " + NumberToString(count));
		answers.push_back("Cost: " + NumberToString(cost));
		cout << "real cost: " << cost << endl;
		if (time_flag)
			answers.push_back(NumberToString(run_time));

		save_data(output_file_name+" "+algorithm_type+"_.txt", answers);
	}

//catch (int e)
//{
//	cout << "An exception occurred. Exception Nr. " << e << '\n';
//}
	getchar();
	return 0;
}