#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

vector<vector<int>> readFile(string file_name)
{
    string line;
    vector<int> this_line;
    vector<vector<int>> map;
    ifstream input_file(file_name.c_str());
    if (input_file.is_open())
    {
        while (getline(input_file, line))
        {
            for (char item : line)
            {
                // Convert char to int and subtract 48 cus ASCII numbers start at 48
                this_line.push_back((int)item - 48);
            }
            map.push_back(this_line);
            this_line.clear();
        }
        input_file.close();
    }
    else
    {
        cout << "Unable to open file " << file_name;
        return map;
    }
    return map;
}

bool checkIfLowPoint(vector<vector<int>> map, int x, int y)
{
    bool lower_than_left, lower_than_right, lower_than_top, lower_than_bottom = false;

    if (x != 0)
    {
        if (map[y][x] < map[y][x - 1])
        {
            lower_than_left = true;
        }
    }
    else
    {
        lower_than_left = true;
    }

    if (x != map[y].size() - 1)
    {
        if (map[y][x] < map[y][x + 1])
        {
            lower_than_right = true;
        }
    }
    else
    {
        lower_than_right = true;
    }

    if (y != 0)
    {
        if (map[y][x] < map[y - 1][x])
        {
            lower_than_bottom = true;
        }
    }
    else
    {
        lower_than_bottom = true;
    }

    if (y != map.size() - 1)
    {
        if (map[y][x] < map[y + 1][x])
        {
            lower_than_top = true;
        }
    }
    else
    {
        lower_than_top = true;
    }

    if (lower_than_left && lower_than_right && lower_than_top && lower_than_bottom)
    {
        return true;
    }
    else
    {
        return false;
    }
}
vector<tuple<int, int>> getDifference(vector<tuple<int, int>> &vector1, vector<tuple<int, int>> &vector2)
{
    vector<tuple<int, int>> difference;

    sort(vector1.begin(), vector1.end());
    sort(vector2.begin(), vector2.end());

    set_difference(vector1.begin(), vector1.end(), vector2.begin(), vector2.end(), back_inserter(difference));
    return difference;
}

void checkForMove(tuple<int, int> location, vector<vector<int>> map, vector<tuple<int, int>> &vistied_locations)
{
    vector<tuple<int, int>> new_locations;
    int x = get<0>(location);
    int y = get<1>(location);

    if (x != 0)
    {
        if (map[y][x - 1] != 9)
        {
            new_locations.push_back(make_tuple(x - 1, y));
        }
    }

    if (x != map[y].size() - 1)
    {
        if (map[y][x + 1] != 9)
        {
            new_locations.push_back(make_tuple(x + 1, y));
        }
    }

    if (y != 0)
    {
        if (map[y - 1][x] != 9)
        {
            new_locations.push_back(make_tuple(x, y - 1));
        }
    }

    if (y != map.size() - 1)
    {
        if (map[y + 1][x] != 9)
        {
            new_locations.push_back(make_tuple(x, y + 1));
        }
    }

    vector<tuple<int, int>> new_moves = getDifference(new_locations, vistied_locations);

    for (auto location : new_moves)
    {
        // Recursive call to find all locations
        vistied_locations.push_back(location);
        checkForMove(location, map, vistied_locations);
    }
    // Remove Duplicates
    sort(vistied_locations.begin(), vistied_locations.end());
    vistied_locations.erase(unique(vistied_locations.begin(), vistied_locations.end()), vistied_locations.end());

    return;
}

int getBasinSize(vector<vector<int>> map, int x, int y)
{
    vector<tuple<int, int>> vistied_locations;
    vistied_locations.push_back(make_tuple(x, y));
    checkForMove(vistied_locations[0], map, vistied_locations);
    return vistied_locations.size();
}

int main()
{
    string input_file_location("../data/input.txt");
    vector<vector<int>> map = readFile(input_file_location);
    vector<int> basin_sizes;
    int risk_level = 0;
    for (int row = 0; row < map.size(); row++)
    {
        for (int columb = 0; columb < map[row].size(); columb++)
        {
            if (checkIfLowPoint(map, columb, row))
            {
                risk_level += map[row][columb] + 1;
                basin_sizes.push_back(getBasinSize(map, columb, row));
            }
        }
    }
    sort(basin_sizes.begin(), basin_sizes.end(), greater<int>());
    double largest_basin_multiple = accumulate(basin_sizes.begin(), basin_sizes.begin() + 3, 1, multiplies<int>());

    cout << "Sum of all risk levels: " << risk_level << endl;
    cout << "Largest 3 basins multiplied together: " << largest_basin_multiple << endl;
    getchar();
}