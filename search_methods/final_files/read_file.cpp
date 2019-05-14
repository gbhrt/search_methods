
#include <string>
#include <fstream>
#include <vector>
#include <iostream>


#include "Header.h"

using namespace std;



string replace_substr(string str, string search, string replace)
{
	for (size_t pos = 0; ; pos += replace.length()) {
		// Locate the substring to replace
		pos = str.find(search, pos);
		if (pos == string::npos) break;
		// Replace by erasing and inserting
		str.erase(pos, search.length());
		str.insert(pos, replace);
	}
	return str;
}

string remove_equal_sign(string str)
{
	size_t pos = 0;
	pos = str.find("=");
	if (pos == 0)
		str.erase(0, 1);
	else
	{
		cout << "error in input file format - cannot remove_equal_sign" << endl;
		pause_exit();
	}
	return str;
}
vector<string> split_line(string str)//split a string to words (remove spaces and ",")
{
	vector<string> tokens;
	size_t comma_pos;
	size_t space_pos;
	size_t end_pos;
	size_t  min_pos = -1;
	size_t pos = 0;
	size_t var_name_lenght;
	do
	{
		min_pos = -1;
		comma_pos = str.find(",");
		space_pos = str.find(" ");
		end_pos = str.length();
		if (comma_pos < min_pos && comma_pos != string::npos)
			min_pos = comma_pos;
		if (space_pos < min_pos && space_pos != string::npos)
			min_pos = space_pos;
		if (end_pos < min_pos && end_pos != string::npos)
			min_pos = end_pos;

		if (min_pos != -1)
		{
			if (min_pos == 0)
			{
				str.erase(0, 1);
			}
			else
			{
				var_name_lenght = min_pos;
				tokens.push_back(str.substr(0, var_name_lenght));
				str.erase(0, var_name_lenght);
			}
		}
	} while (str.length() != 0);

	return tokens;

}

string run_to_line(vector<string> line_buffer, int & line_index, string search_word)
{
	bool find_flag = false;
	for (line_index; line_index<line_buffer.size(); line_index++)
	{
		if (line_buffer[line_index].find(search_word) != string::npos)
		{
			find_flag = true;
			break;
		}
	}
	if (find_flag)
		return line_buffer[line_index];
	else
		return string("error");
}


vector<string> read_data_from_file(string input_file_name)
{
	string line;
	vector<string> line_buffer;
	fstream in_file;
	in_file.open(input_file_name.c_str());
	if (in_file.is_open())
	{
		string line;
		while (getline(in_file, line))
		{
			line_buffer.push_back(line);
		}
		cout << "Input data was loaded\n";
		in_file.close();
	}
	else
	{
		cout << "cannot open file: " << input_file_name << endl;
		pause_exit();
	}

	return line_buffer;
}


bool load_data(string input_file_name, string & algorithm_type, bool & time_flag, Node* start)
{
	vector<string> line_buffer = read_data_from_file(input_file_name);
	int line_ind = 0;
	algorithm_type = line_buffer[line_ind];
	line_ind++;
	if (line_buffer[line_ind] == "with time")
		time_flag = true;
	else
		time_flag = false;
	line_ind++;

	string line = replace_substr(line_buffer[line_ind], "x", ",");
	vector<string> words = split_line(line);
	start->N = StringToInt(words[0]);
	start->M = StringToInt(words[1]);
	int holes_cnt = 0;
	line_ind++;

	for (int i = 0; i < start->N; i++)//rows
	{
		vector<string> words = split_line(line_buffer[line_ind]);
		line_ind++;
		vector<int> row;
		for (int j = 0; j < start->M; j++)
		{
			if (words[j] == "_")
			{
				start->holes[holes_cnt][0] = j;
				start->holes[holes_cnt][1] = i;
				holes_cnt++;
				row.push_back(0);		
			}
			else
				row.push_back(StringToInt(words[j]));
		}
		start->state.push_back(row);
	}
	return false;
}

void save_data(string output_file, vector<string> answers)
{
	ofstream out_file;
	out_file.open(output_file.c_str());
	for (int i = 0; i < answers.size(); i++)
	{
		out_file << answers[i] << endl;
	}
	cout << "Answers saved to " << output_file << endl;

}