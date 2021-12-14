#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <wire_solver.h>

using namespace std;

void readFile(string file_name, vector<wire_solver> &data)
{
    string line;
    ifstream input_file(file_name.c_str());
    if (input_file.is_open())
    {
        while (getline(input_file, line))
        {
            data.push_back(wire_solver(line));
        }
        input_file.close();
    }
    else
        cout << "Unable to open file " << file_name;
    return;
}

int main()
{
    string input_file_location("../data/input.txt");
    vector<wire_solver> wire_data;
    readFile(input_file_location, wire_data);
    int number_of_unique_segments = 0;
    int total_decoded_sum = 0;

    for (auto item : wire_data)
    {
        number_of_unique_segments += item.total_unique_segments;
        total_decoded_sum += item.decoded_value;
    }

    cout << "Number of times 1,4,7,or 8 appear: " << number_of_unique_segments << endl;
    cout << "Total decoded sum: " << total_decoded_sum << endl;
    getchar();
}