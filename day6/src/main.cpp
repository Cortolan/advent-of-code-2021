#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
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

vector<double> parseData(string input)
{
    vector<double> parsed_input;
    vector<double> all_fish(9, 0);
    vector<string> split_input = split(input, ',');
    for (auto item : split_input)
    {
        int converted_int;
        stringstream ss;
        ss << item;
        ss >> converted_int;
        parsed_input.push_back(converted_int);
    }
    for (auto fish : parsed_input)
    {
        all_fish[fish]++;
    }

    return all_fish;
}

void incrementOneDay(vector<double> &all_fish)
{
    int new_fish = 0;
    vector<double> fish_next_day(9, 0);

    for (int i = 0; i < all_fish.size(); i++)
    {
        if (i == 0)
        {
            fish_next_day[6] += all_fish[0]; // Fish restart cycle at 6 days
            fish_next_day[8] += all_fish[0]; // New fish spawn at 8 days
        }
        else
        {
            fish_next_day[i - 1] += all_fish[i];
        }
    }
    all_fish = fish_next_day;
}

double getAllFishCount(vector<double> all_fish)
{
    double count = 0;
    for (double item : all_fish)
    {
        count += item;
    }
    return count;
}

int main()
{
    string input_file_location("../data/input.txt");
    string input_data = readFile(input_file_location);
    vector<double> all_fish = parseData(input_data);
    int toatal_days = 256;

    cout << "How many days total would you like to calculate?" << endl;
    cin >> toatal_days;

    for (int day = 0; day < toatal_days; day++)
    {
        incrementOneDay(all_fish);
    }
    
    cout.precision(15);
    cout << "After " << toatal_days << " days there are " << getAllFishCount(all_fish) << " fish." << endl;
    getchar();
}