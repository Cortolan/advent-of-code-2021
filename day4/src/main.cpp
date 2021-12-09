#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <BingoBoard.h>

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

vector <BingoBoard> bingo_boards_setup(vector <string> data)
{   
    vector <BingoBoard> all_boards;
    vector <string> current_board;
    for(int i = 0; i < data.size(); i++)
    {
        if (data[i] != ""){
            current_board.push_back(data[i]);

        }else{
            all_boards.push_back(BingoBoard(current_board));
            current_board.clear();
        }
    }
    all_boards.push_back(BingoBoard(current_board));
    return all_boards;
}

vector <int> get_bingo_numbers(vector <string> &data)
{
    string bingo_numbers_str = data[0];
    vector <string> split_bingo_numbers_str = split(bingo_numbers_str, ',');
    vector <int> bingo_numbers_int;
    
    for (auto item : split_bingo_numbers_str){
    stringstream ss;
    int converted_int;
    ss << item;
    ss >> converted_int;
    bingo_numbers_int.push_back(converted_int);
    }

    data.erase(data.begin(), data.begin()+2);
    return bingo_numbers_int;
}

int main()
{
    string input_file_location ("../data/input.txt");
    vector <string> data;    
    readfile(input_file_location, data);

    vector <int> bingo_numbers = get_bingo_numbers(data);
    vector <BingoBoard> all_bingo_boards = bingo_boards_setup(data);
    vector <BingoBoard> all_winners;

    for (auto called_number : bingo_numbers){
        for (auto &bingo_board : all_bingo_boards){
            if (!bingo_board.winner){
                bingo_board.check_for_number(called_number);
                if (bingo_board.winner){
                    all_winners.push_back(bingo_board);
                }
            }
        }
    }
    
    if (all_winners.size() > 0){
        cout << "First winner on number " << all_winners[0].last_bingo_number << " with a score of " << all_winners[0].score << endl;
        cout << "Last winner on number " << all_winners[all_winners.size()-1].last_bingo_number << " with a score of " << all_winners[all_winners.size()-1].score << endl;
    }else{
        cout << "No winners found";
    }
    getchar();
}