#include <string>
#include <vector>
#include <sstream>
#include <StringSplitter.h>

class BingoBoard
{
private:
    std::vector<std::vector <bool>> board_state;
    bool check_for_winner();
    void get_score();
public:
    std::vector<std::vector <int>> board_numbers;
    int last_bingo_number = -1;
    bool winner = false;
    int score = 0;
    BingoBoard();
    BingoBoard(std::vector<std::string> board_rows);
    void check_for_number(int bingo_board_number);
};

BingoBoard::BingoBoard()
{
    //empty board
}
BingoBoard::BingoBoard(std::vector<std::string> board_rows)
{
    for (int i =0;i < board_rows.size(); i++){
        std::vector<std::string> split_row = split(board_rows[i], ' ');
        std::vector<bool> state_row(split_row.size(), false);
        std::vector<int> number_row;
        
        for (auto item : split_row){
            std::stringstream ss;
            int converted_int;
            ss << item;
            ss >> converted_int;
            number_row.push_back(converted_int);
        }
        board_state.push_back(state_row);
        board_numbers.push_back(number_row);
    }
}

void BingoBoard::check_for_number(int bingo_board_number)
{
    if (winner != true){
        for (int row = 0; row < board_numbers.size(); row++){
            for (int columb = 0; columb < board_numbers[0].size(); columb++){
                if (board_numbers[row][columb] == bingo_board_number){
                    board_state[row][columb] = true;
                    last_bingo_number = bingo_board_number;
                    winner = check_for_winner();
                    if (winner){
                        get_score();
                        return;
                    }
                    return;
                }
            }       
        }    
    }
}

bool BingoBoard::check_for_winner()
{
    int columb_BingoBoard_count = 0;
    int row_BingoBoard_count = 0;
    
    for (auto row : board_state){ //check for row winner
        row_BingoBoard_count = 0;
         for (auto square : row){
             if(square)
                row_BingoBoard_count++;
         }
         if (row_BingoBoard_count == row.size())
            return true;       
    }

    for (int columb =0; columb < board_state[0].size(); columb++){ //check for columb winner
        columb_BingoBoard_count =0;
        for (auto row : board_state){
            if(row[columb])
                columb_BingoBoard_count++;
        }
        if (columb_BingoBoard_count == board_state.size())
            return true;
    }

    return false;
}
void BingoBoard::get_score()
{
    int summed_values = 0;
    for (int row = 0; row < board_state.size(); row++){
        for(int columb = 0; columb < board_state[row].size(); columb++){
            if (!board_state[row][columb])
                summed_values += board_numbers[row][columb];
        }
    }
    score = summed_values * last_bingo_number;
    return;
}