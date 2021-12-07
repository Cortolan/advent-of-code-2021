#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Direction.h>

using namespace std;

void readfile(string file_name, vector <Direction> &data)
{
    string line;
    ifstream input_file(file_name.c_str());
    if (input_file.is_open())
    {
        while (getline(input_file, line))
        {
            Direction input_direction(line);
            data.push_back(input_direction);
        }
        input_file.close();
    }
    else
        cout << "Unable to open file " << file_name;

    return;
}

void get_location(vector <Direction> directions)
{
    int horizontal_pos = 0;
    int depth = 0;

    for (int i = 0; i < directions.size(); i++)
    {
        if (directions[i].direction == "forward")
            horizontal_pos += directions[i].magnitude;
        else{
            if (directions[i].direction == "up")
                depth -= directions[i].magnitude;
            else{
                if (directions[i].direction == "down")
                depth += directions[i].magnitude;
            }
        }
    }
    
    cout << "Forward: " << horizontal_pos << endl;
    cout << "Depth: " << depth << endl;
    cout << "Multiplied they equal " << horizontal_pos*depth << endl;
}

void get_location_with_aim(vector <Direction> directions)
{
    int horizontal_pos = 0;
    int depth = 0;
    int aim = 0;

    for (int i = 0; i < directions.size(); i++)
    {
        if (directions[i].direction == "forward"){
            horizontal_pos += directions[i].magnitude;
            depth += aim * directions[i].magnitude;
            }        
        else{
            if (directions[i].direction == "up")
                aim -= directions[i].magnitude;
            else{
                if (directions[i].direction == "down")
                   aim += directions[i].magnitude;
            }
        }
    }
    
    cout << "Forward: " << horizontal_pos << endl;
    cout << "Depth: " << depth << endl;
    cout << "Multiplied they equal " << horizontal_pos*depth << endl;
}

int main()
{
    string input_file_location ("../data/input.txt");
    vector <Direction> directions;
    
    readfile(input_file_location, directions);
    cout << "Part 1:\n";
    get_location(directions);
    cout << "Part 2:\n";
    get_location_with_aim(directions);
    getchar();
}