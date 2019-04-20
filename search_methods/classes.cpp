#include "Header.h"


winTimer::winTimer()
{
	QueryPerformanceFrequency(&freq);
}
void winTimer::save_time()
{
	QueryPerformanceCounter(&start_time);
}
int winTimer::get_time()
{
	QueryPerformanceCounter(&read);
	return int((read.QuadPart - start_time.QuadPart)*1000000.) / freq.QuadPart;
}
void hash_table::push(Node* node)
{
	string key = convert_to_key(node);
	add_to_hash(key);
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
void hash_table::add_to_hash(string key)
{
	hashmap[key] = true;
}

bool hash_table::is_inside(Node* node)
{
	winTimer timer;

	string key = convert_to_key(node);
	//timer.save_time();
	if (hashmap.find(key) == hashmap.end())
		return false;
	//cout << "find time: " << timer.get_time() << endl;
	return true;
}
void hash_table::remove(Node* node)
{
	string key = convert_to_key(node);
	hashmap.erase(key);
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