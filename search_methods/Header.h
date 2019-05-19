#include <string>
#include <vector>
#include<unordered_map>
/#include<tr1/unordered_map>//c++98
#include <queue> 
#include <stack>
#include <stdlib.h>

using namespace std;

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
	int f;
	int g;
	bool out;

	Node();
};
class Comparator {
public:
	bool operator()(const Node* node1, const Node* node2);
};
class ComparatorIncrease {
public:
	bool operator()(const Node* node1, const Node* node2);

};
class hash_table
{
public:
	bool is_inside(Node* node);
	void push(Node* node);
	void remove(Node* node);
	Node* get_node(Node* node);
	void clear();
	int size();
private:

	//std::tr1::unordered_map< string, Node*> hashmap;//c++98
	unordered_map< string, Node*> hashmap;
	void add_to_hash(string key, Node* node);
	string convert_to_key(Node* node);
	
};


void pause_exit();
bool load_data(string input_file_name, string & algorithm_type, bool & time_flag, Node* start);
vector<Node*> BFS_algo(Node* start, Node* goal, int & count, bool & success);
vector<Node*> DFID_algo(Node* start, Node* goal, int & count, bool & success);
vector<Node*> A_star_algo(Node* start, Node* goal, int & count, bool & success);
vector<Node*> IDA_star_algo(Node* start, Node* goal, int & count, bool & success);
vector<Node*> DFBnB_algo(Node* start, Node* goal, int & count, bool & success);
Node* comp_goal(int N, int M);
void print_node(Node* node,string name);
string NumberToString(float Number);
string NumberToString(int Number);
string NumberToString(double Number);
float StringToFloat(const string &Text);
int StringToInt(const string &Text);
string create_path_string(vector<Node*> path, bool success);
vector<Node*> get_path(Node* node);
void save_data(string output_file, vector<string> answers);
bool check_goal(Node* node, Node* goal);
Node* get_node(Node* parent_node, Operation  operation);
vector<Operation> get_allowed_operators(Node* node);
int get_cost(Operation  operation);
void replace_node_in_priority_quene(priority_queue <Node*, vector<Node*>, Comparator > & pq, Node* exist_node, Node * node);
void remove_from_stack(stack<Node*> s, Node * node);
int comp_heuristic(Node * node, Node * goal);
vector<Node*> get_path(stack<Node*> & st);
Node* copy_node(Node* node);


