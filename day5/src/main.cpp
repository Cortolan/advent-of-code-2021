#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <StringSplitter.h>
#include <VentMap.h>

using namespace std;

void readfile(string file_name, vector <string> &data)
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

vector <vector<vector <int>>> parse_data(vector <string> data)
{   vector <vector<vector<int>>> directions;
    vector <vector <int>> cordinates;
    for (auto line : data){
        vector <string> split_line = split(line, ' ');
        split_line.erase(split_line.begin()+1);
        for (auto item : split_line){
            vector <string> str_codinates = split(item, ',');
            vector <int> int_cordinates;
            for (auto string_cor : str_codinates){
                int converted_int;
                stringstream ss;
                ss << string_cor;
                ss >> converted_int;
                int_cordinates.push_back(converted_int);
            }
            cordinates.push_back(int_cordinates);
        }
        directions.push_back(cordinates);
        cordinates.clear();
    }
    return directions;
}

int main()
{
    string input_file_location ("../data/input.txt");
    vector <string> data;
    vector <vector<vector <int>>> directions;

    readfile(input_file_location, data);
    directions = parse_data(data);
    
    VentMap part1(1000); //both set to 1000 given the size of the map in data is 1000^2
    VentMap part2(1000);

    for(auto vent : directions){
        part1.plotVent(vent[0], vent[1]);
        part2.plotVent(vent[0], vent[1], true);
    }
    cout << "Number of intersections on map Part 1: " << part1.countIntersections() << endl;
    cout << "Number of intersections on map Part 2: " << part2.countIntersections() << endl;
    getchar();
}