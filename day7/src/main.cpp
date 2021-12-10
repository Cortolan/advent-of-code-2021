#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <bits/stdc++.h>
#include <string_splitter.h>

using namespace std;

string readFile(string file_name)
{
    string line;
    ifstream input_file(file_name.c_str());
    if (input_file.is_open())
    {
        getline(input_file, line);
        input_file.close();
    }
    else
        cout << "Unable to open file " << file_name;
    return line;
}

vector<int> parseData(string input)
{
    vector<int> parsed_input;
    vector<string> split_input = split(input, ',');
    for (auto item : split_input)
    {
        int converted_int;
        stringstream ss;
        ss << item;
        ss >> converted_int;
        parsed_input.push_back(converted_int);
    }
    return parsed_input;
}

int getTravelCost(int travel_distance)
{
    // Finding the nth triangle number
    int cost = (travel_distance * (travel_distance + 1)) / 2;
    return cost;
}

tuple<int, int> findOptimalLocation(vector<int> crabs, bool use_scaling_cost = false)
{
    int farthest_crab = *max_element(crabs.begin(), crabs.end());
    vector<tuple<int, int>> possiblities;
    for (int i = 0; i < farthest_crab; i++)
    {
        int total_gas = 0;
        for (auto crab : crabs)
        {
            if (use_scaling_cost)
            {
                total_gas += getTravelCost(abs(crab - i));
            }
            else
            {
                total_gas += abs(crab - i);
            }
        }
        possiblities.push_back(make_tuple(total_gas, i));
    }

    sort(possiblities.begin(), possiblities.end());
    return possiblities[0];
}

int main()
{
    string input_file_location("../data/input.txt");
    string input_data = readFile(input_file_location);
    vector<int> all_crabs = parseData(input_data);
    tuple<int, int> optimal_position = findOptimalLocation(all_crabs);
    tuple<int, int> optimal_position_with_cost = findOptimalLocation(all_crabs, true);
    
    cout << "Part 1: Ideal location is " << get<1>(optimal_position) << " with a gas fee of " << get<0>(optimal_position) << endl;
    cout << "Part 2: Ideal location is " << get<1>(optimal_position_with_cost) << " with a gas fee of " << get<0>(optimal_position_with_cost) << endl;
    getchar();
}