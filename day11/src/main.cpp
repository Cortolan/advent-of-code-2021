#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <octopus.h>

using namespace std;

void readFile(string file_name, vector<string> &data)
{
    string line;
    ifstream input_file(file_name.c_str());
    if (input_file.is_open())
    {
        while (getline(input_file, line))
        {
            data.push_back(line);
        }
        input_file.close();
    }
    else
        cout << "Unable to open file " << file_name;
    return;
}

vector<vector<octopus>> createOctopusVector(vector<string> data)
{
    vector<vector<octopus>> all_octopuses;
    int max_x = data[0].size() - 1;
    int max_y = data.size() - 1;

    for (int row = 0; row <= max_x; row++)
    {
        vector<octopus> row_of_octopuses;
        for (int columb = 0; columb <= max_y; columb++)
        {
            int octopus_value = (int)data[row][columb] - 48; //-48 because ASCII numbers start at 48
            row_of_octopuses.push_back(octopus(columb, row, octopus_value, max_x, max_y));
        }
        all_octopuses.push_back(row_of_octopuses);
        row_of_octopuses.clear();
    }
    return all_octopuses;
}

void incrementAllOctopuses(vector<vector<octopus>> &all_octopuses)
{
    vector<tuple<int, int>> adjacent_charged;
    vector<tuple<int, int>> next_charge_list;
    vector<tuple<int, int>> current_next_charge_list;

    // Increment all octopuses by 1 charge and get intial list of adjacent bursts
    for (auto &row : all_octopuses)
    {
        for (octopus &selected_octopus : row)
        {
            adjacent_charged = selected_octopus.increaseCharge();
            for (auto item : adjacent_charged)
            {
                next_charge_list.push_back(item);
            }
            adjacent_charged.clear();
        }
    }

    // Loop until all charge bursts have been resolved
    while (next_charge_list.size() != 0)
    {
        current_next_charge_list = next_charge_list;
        for (tuple<int, int> item : current_next_charge_list)
        {
            adjacent_charged = all_octopuses[get<1>(item)][get<0>(item)].increaseCharge();
            for (auto item : adjacent_charged)
            {
                next_charge_list.push_back(item);
            }
            adjacent_charged.clear();
            next_charge_list.erase(next_charge_list.begin());
        };
    }
    // Reset all octopuses so that next increment can begin
    for (auto &row : all_octopuses)
    {
        for (octopus &selected_octopus : row)
        {
            selected_octopus.reset();
        }
    }
}

void printOctopusState(vector<vector<octopus>> all_octopuses)
{
    for (auto row : all_octopuses)
    {
        for (auto octo : row)
        {
            if (octo.charge_ > 9)
            {
                cout << 0;
            }
            else
            {
                cout << octo.charge_;
            }
        }
        cout << endl;
    }
}

double getFlashTotal(vector<vector<octopus>> all_octopuses)
{
    int flash_total = 0;
    for (auto row : all_octopuses)
    {
        for (auto octo : row)
        {
            flash_total += octo.flashed_count_;
        }
    }
    return flash_total;
}

bool allFlashing(vector<vector<octopus>> all_octopuses)
{
    bool flashing = true;
    for (auto row : all_octopuses)
    {
        for (auto octo : row)
        {
            if (octo.charge_ != 0)
            {
                flashing = false;
            }
        }
    }
    return flashing;
}

int main()
{
    string input_file_location("../data/input.txt");
    vector<string> data;
    readFile(input_file_location, data);
    vector<vector<octopus>> all_octopuses = createOctopusVector(data);
    int interation_count = 0;

    while (allFlashing(all_octopuses) == false)
    {
        interation_count++;
        incrementAllOctopuses(all_octopuses);
        if (interation_count == 100)
        {
            //Part 1 Answer
            cout << "\n\nIteration " << interation_count << endl;
            printOctopusState(all_octopuses);
            cout << "Flash total at 100 iterations: " << getFlashTotal(all_octopuses);
        }
    }
    // Part 2 Answer 
    cout << "\n\nAll flashing on Iteration " << interation_count << endl;
    printOctopusState(all_octopuses);
    getchar();
}