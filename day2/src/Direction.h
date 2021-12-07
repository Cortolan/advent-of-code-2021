#include <string>
#include <sstream>
#include <StringSplitter.h>

class Direction {
    public:
        std::string direction;
        int magnitude;  
        Direction(std::string input);
    
        int string_to_int(std::string input_str){
                std::stringstream ss;
                int converted_int;
                ss << input_str;
                ss >> converted_int;
                return converted_int;
        }
};

Direction::Direction (std::string input) {        
        std::vector<std::string> split_input = split(input, ' ');
        direction = split_input[0];
        magnitude = string_to_int(split_input[1]);
}