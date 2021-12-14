#include <vector>
#include <string>
#include <algorithm>
#include <string_splitter.h>

class wire_solver
{
public:
    std::vector<std::string> input_data_;
    std::vector<std::string> output_data_;
    int decoded_value = 0;
    int total_unique_segments = 0;
    wire_solver(std::string input_data);

private:
    std::string coded_one = "";
    std::string coded_four = "";
    void findUniqueNumbers();
    void decodeOutput();
    std::string decodeNumber(int number_length, int intersection_with_one, int intersection_with_four);
};

wire_solver::wire_solver(std::string input_data)
{
    std::vector<std::string> split_input = split(input_data, '|');
    input_data_ = split(split_input[0], ' ');
    output_data_ = split(split_input[1], ' ');
    findUniqueNumbers();
    decodeOutput();
}

void wire_solver::findUniqueNumbers()
{
    // we only need 1 and 4 for all calculations so we identify them
    for (auto scrambled_number : input_data_)
    {
        if (scrambled_number.length() == 2)
        {
            std::sort(scrambled_number.begin(), scrambled_number.end());
            coded_one = scrambled_number;
        }
        else if (scrambled_number.length() == 4)
        {
            std::sort(scrambled_number.begin(), scrambled_number.end());
            coded_four = scrambled_number;
        }
    }
}

void wire_solver::decodeOutput()
{
    std::string number_str = "";
    std::stringstream string_to_int;
    for (std::string number : output_data_)
    {
        std::string intersection_with_one, intersection_with_four;
        std::sort(number.begin(), number.end());
        std::set_intersection(coded_one.begin(), coded_one.end(), number.begin(), number.end(), std::back_inserter(intersection_with_one));
        std::set_intersection(coded_four.begin(), coded_four.end(), number.begin(), number.end(), std::back_inserter(intersection_with_four));
        number_str += decodeNumber(number.length(), intersection_with_one.length(), intersection_with_four.length());
    }
    decoded_value = std::stoi(number_str);
}

std::string wire_solver::decodeNumber(int number_length, int intersection_with_one, int intersection_with_four)
{
    // Based off there unique length we can identify 1, 4, 7, and 8
    // Using the intersection with numbers one and four we can find the rest
    switch (number_length)
    {
    case 2:
        total_unique_segments++;
        return "1";
    case 3:
        total_unique_segments++;
        return "7";
    case 4:
        total_unique_segments++;
        return "4";
    case 5:
        if (intersection_with_one == 2)
        {
            return "3";
        }
        else if (intersection_with_four == 2)
        {
            return "2";
        }
        else
        {
            return "5";
        }
        break;
    case 6:
        if (intersection_with_one == 1)
        {
            return "6";
        }
        else if (intersection_with_four == 4)
        {
            return "9";
        }
        else
        {
            return "0";
        }
        break;
    case 7:
        total_unique_segments++;
        return "8";
    }
}