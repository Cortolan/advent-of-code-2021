#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

void readfile(string file_name, vector <int> &data)
{
    string line;
    ifstream input_file(file_name.c_str());
    if (input_file.is_open())
    {
        while (getline(input_file, line))
        {
            stringstream ss;
            int line_to_int;
            ss << line;
            ss >> line_to_int;
            data.push_back(line_to_int);
        }
        input_file.close();
    }
    else
        cout << "Unable to open file " << file_name;

    return;
}

int count_number_of_increases(vector <int> data)
{
    int number_of_increases = 0;
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i] > data[i-1])
            number_of_increases++;
    }
    return number_of_increases;
}

int summed_group_comparison(vector <int> data)
{
    int number_of_increases = 0;

    for (int i = 1; i < data.size() -2; i++)
    {
        int first_group = data[i-1] + data[i] + data[i+1];
        int second_group = data[i] + data[i+1] + data[i+2];
        if (first_group < second_group)
             number_of_increases++;
    }
    return number_of_increases;
}

int main()
{
    string input_file_location ("../data/input.txt");
    vector <int> data;
    
    readfile(input_file_location, data);
    cout << "Number of increases: " << count_number_of_increases(data) << endl;
    cout << "Number of summed grouped increases: " << summed_group_comparison(data);
    getchar();
}