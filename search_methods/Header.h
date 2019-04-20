#pragma once
#include <string>
#include <vector>
#include<unordered_map>
#include<Windows.h>
using namespace std;

class winTimer
{
public:
	winTimer();
	void save_time();
	int get_time();
private:
	LARGE_INTEGER  freq, start_time,read;
	
	
	
};
class Operation
{
public:
	vector< vector<int> > blockes_ind;//one or two
	int direction;
	int hole_ind;//0-first,1-second,2-both
	vector<int> blockes_val;//one or two
	string create_string();
};

class Node
{
public:
	bool root;
	int N;
	int M;
	vector< vector<int> > state;
	int holes[2][2];
	Node * parent;//the parent of this node
	Operation operation;//the operation that lead from parent to this node
	Node();

};

class hash_table
{
public:
	bool is_inside(Node* node);
	void push(Node* node);
	void remove(Node* node);
	//Node* get_node(Node & node);
private:
	unordered_map< string, bool> hashmap;
	void add_to_hash(string key);
	string convert_to_key(Node* node);
	
};


void pause_exit();
bool load_data(string input_file_name, string & algorithm_type, bool & time_flag, Node* start);
bool BFS_algo(Node* start, Node* goal, int & count);
bool DFID_algo(Node* start, Node* goal, int & count);
Node* comp_goal(int N, int M);
void print_node(Node* node,string name);
string NumberToString(float Number);
string NumberToString(int Number);
string NumberToString(double Number);
float StringToFloat(const string &Text);
int StringToInt(const string &Text);
string get_path(Node* node, int & cost);
void save_data(string output_file, vector<string> answers);
bool check_goal(Node* node, Node* goal);
Node* get_node(Node* parent_node, Operation  operation);
vector<Operation> get_allowed_operators(Node* node);

