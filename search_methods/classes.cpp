#include "Header.h"

void hash_table::push(Node* node)
{
	string key = convert_to_key(node);
	add_to_hash(key, node);
}

string hash_table::convert_to_key(Node* node)
{
	string key;
	//convert the state of the node to a string. dont include parents
	for (int i = 0; i < node->N; i++)//rows
	{
		for (int j = 0; j < node->M; j++)
		{
			key.append(NumberToString(node->state[i][j]));
			key.append(",");
		}
	}
	return key;
}
void hash_table::add_to_hash(string key, Node* node)
{
	hashmap[key] = node;
}

bool hash_table::is_inside(Node* node)
{
	string key = convert_to_key(node);
	if (hashmap.find(key) == hashmap.end())
		return false;
	return true;
}
Node* hash_table::get_node(Node* node)
{
	string key = convert_to_key(node);
	return hashmap[key];
}
void hash_table::remove(Node* node)
{
	string key = convert_to_key(node);
	hashmap.erase(key);
}
void hash_table::clear()
{
	hashmap.clear();
}
int hash_table::size()
{
	return hashmap.size();
}

Node::Node()
{
	root = false;
}
string Operation::create_string()
{
	string dir_code[] = { "L","U","R","D" };

	string str;
	if (blockes_val.size() == 2)
		str.append(NumberToString(blockes_val[0]) + "&" + NumberToString(blockes_val[1]));
	else
		str.append(NumberToString(blockes_val[0]));
	str.append(dir_code[direction]);
	return str;
}


bool Comparator:: operator()(const Node* node1, const Node* node2)
{
	return (node1->f > node2->f);
}

bool ComparatorIncrease:: operator()(const Node* node1, const Node* node2)
{
	return (node1->f < node2->f);
}