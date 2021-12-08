#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

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

char get_most_common_for_column (vector <string> data, int key)
{
        int total_zeros = 0;
        int total_ones = 0;
        for (string item : data)
        {
            if (item[key] == '1')
                total_ones++;
            else
                total_zeros++;
        }
        
        if (total_zeros < total_ones || total_ones == total_zeros)
            return '1';
        else
            return '0';
}

string get_epsilon(vector <string> data)
{
    string epsilon = "";
    for (int i = 0; i < data[0].length(); i++)
    {
        int column_comm = get_most_common_for_column(data, i);
        
        if (column_comm == '0')
            epsilon += '0';
        else
            epsilon += '1';
    }
    return epsilon;
}

string get_gamma_rate(string epsilon_rate)
{
    string gamma_rate;
    for (char i : epsilon_rate){
        if(i == '1')
            gamma_rate += '0';
        else
            gamma_rate += '1';
    }
    return gamma_rate;
}

string get_oxygen_rating(vector <string> data, bool inverse)
{
    //CO2 rating is inverse to oxygen pass false for oxy rating and true for co2
    vector <string> current = data;   
    vector <string> next;

    for (int i =0; i < data[0].length(); i++){
        char most_common = get_most_common_for_column(current, i);        
        if (inverse)
            if (most_common == '1')
                most_common = '0';
            else
                most_common = '1';

        for (string &item : current){
            if (item[i] == most_common)
                next.push_back(item);
        }
        
        if (next.size() == 1)
            return next[0];
        else{
            current = next;
            next.clear();
        }              
    }
    return current[0];
}

int main()
{
    string input_file_location ("../data/input.txt");
    vector <string> data;
    readfile(input_file_location, data);
    
    string epsilon_rate_str = get_epsilon(data);
    string gamma_rate_str = get_gamma_rate(epsilon_rate_str);
    string oxygen_rate_str = get_oxygen_rating(data, false);
    string co2_rate_str = get_oxygen_rating(data, true);

    int gamma_rate = stoull(gamma_rate_str, 0, 2);
    int epsilon_rate = stoull(epsilon_rate_str, 0, 2); 
    int oxygen_rate = stoull(oxygen_rate_str, 0, 2);
    int co2_rate = stoull(co2_rate_str, 0, 2);

    cout << "Gamma rate: "<< gamma_rate_str << " which converted to decimal is " << gamma_rate << endl;
    cout << "Epsilon rate: " << epsilon_rate_str << " which converted to decimal is " << epsilon_rate << endl;
    cout << "Multiplied they equal: " << epsilon_rate * gamma_rate << endl << endl;

    cout << "Oxygen rate: "<< oxygen_rate_str << " which converted to decimal is " << oxygen_rate << endl;
    cout << "C02 rate: " << co2_rate_str << " which converted to decimal is " << co2_rate << endl;
    cout << "Multiplied they equal: " << oxygen_rate * co2_rate << endl;

    getchar();
}