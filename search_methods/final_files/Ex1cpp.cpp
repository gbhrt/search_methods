#include "Header.h"
#include <iostream>
//#include<time.h>
#include <ctime>
using namespace std;

int main()
{ 
	
	//string folder = "files1/idastar/complex/";//no path easy input
	//string folder = "files1/dfid/easy input/";//no path easy input
	////string folder = "files1/bfs/easy input/";//no path easy input
	////string folder = "files1/a star/easy input/";//no path easy input
	string input_file_name = "input.txt";//_orginal input_hard_A_star input_hard_BFS
	string output_file_name = "output.txt";

	//string folder = "files/";//no path easy input
	//string input_file_name = folder + "input_orginal.txt";//_orginal input_hard_A_star input_hard_BFS
	//string output_file_name = folder + "output_orginal";

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

	//list<Node*> N;
	//N.push_back(start);
	//N.push_back(goal);
	//N.push_back(goal);
	//list<Node*>::iterator it = N.begin();

	//it = N.erase(it);
	//it = N.erase(it);

	////vector<string> algorithms = { "DFID","BFS","A*" ,"IDA*"};// ,
	//vector<string> algorithms = {"IDA*" };
	//vector<string> algorithms = { "DFBnB" };
	/*vector<string> algorithms = { "BFS" };*/
//	vector<string> algorithms;
	//algorithms.push_back("DFBnB");
	//for (string algorithm_type: algorithms)
	//for(int i =0;i<algorithms.size();i++)
	{
		//algorithm_type = algorithms[i];
		//algorithm_type = "DFID";

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
		cout << "time: " << run_time << endl;

		Node* node = path.front();
		cost = 10;// node->g;
		str_path = create_path_string(path, success);
		/*if (success)
			path = get_path(goal, cost);*/

		vector<string> answers;
		answers.push_back(str_path);
		answers.push_back("Num: " + NumberToString(count));
		answers.push_back("Cost: " + NumberToString(cost));
		cout << "real cost: " << cost << endl;
		if (time_flag)
			answers.push_back(NumberToString(run_time));

		save_data(output_file_name, answers);//+" "+algorithm_type+"_.txt"
	}

//catch (int e)
//{
//	cout << "An exception occurred. Exception Nr. " << e << '\n';
//}
	//getchar();
	system("pause");
	return 0;
}