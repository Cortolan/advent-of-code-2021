#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

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

tuple<int, double> getScore(vector<string> data)
{
    vector<char> valid_openers = {'{', '[', '(', '<'};
    map<char, char> closing_pairs = {{'}', '{'}, {']', '['}, {')', '('}, {'>', '<'}};
    map<char, int> points = {{'}', 1197}, {']', 57}, {')', 3}, {'>', 25137}, {'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}};
    vector<char> found;
    int score_for_mistakes = 0;
    double score_for_incompleate = 0;
    vector<double> incomplete_scores;

    for (string line : data)
    {
        for (int i = 0; i < line.length(); i++)
        {
            if (find(valid_openers.begin(), valid_openers.end(), line[i]) != valid_openers.end())
            {
                found.push_back(line[i]);
            }
            else
            {
                // Check if closer matches last opener, else found the error and score apropriatly
                if (found.back() == closing_pairs[line[i]])
                {
                    found.pop_back();
                }
                else
                {
                    score_for_mistakes += points[line[i]];
                    found.clear();
                    break;
                }
            }
            if (i == line.length() - 1)
            {
                // If line has no syntax errors its incomplete, reverse order to score apropriatly for how to place brackets to complete
                reverse(found.begin(), found.end());
                double line_incomplete_score = 0;
                for (char item : found)
                {
                    line_incomplete_score = (line_incomplete_score * 5) + points[item];
                }
                incomplete_scores.push_back(line_incomplete_score);
                found.clear();
            }
        }
    }

    // Get middle score for mistakes, promp stated there will always be an odd number of entries so not accounting for even number of entries 
    sort(incomplete_scores.begin(), incomplete_scores.end());
    score_for_incompleate = incomplete_scores[(incomplete_scores.size() / 2)];
    return make_tuple(score_for_mistakes, score_for_incompleate);
}

int main()
{
    string input_file_location("../data/input.txt");
    vector<string> data;
    readFile(input_file_location, data);
    tuple<int, double> scores = getScore(data);
    cout.precision(17);

    cout << "Mistakes score is: " << get<0>(scores) << endl;
    cout << "Incompleate score is: " << get<1>(scores) << endl;
    getchar();
}