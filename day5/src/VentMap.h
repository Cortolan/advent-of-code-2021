#include <vector>
#include <iostream>
#include <cmath>

class VentMap
{
public:
    std::vector<std::vector<int>> map;
    VentMap(int size);
    void plotVent(std::vector<int> start, std::vector<int> end, bool plotVertical);
    void plotHorizontalAndVertical(int delta_x, int delta_y, std::vector<int> start, std::vector<int> end);
    void plotDiagnal(int delta_x, int delta_y, std::vector<int> start, std::vector<int> end);
    void viewMap();
    int countIntersections();
};

VentMap::VentMap(int size)
{
    for (int i =0; i < size; i++){
        std::vector <int> row (size, 0);
        map.push_back(row);
    }
}

void VentMap::plotVent(std::vector<int> start, std::vector<int> end, bool plot_diagnal = false)
{
    int delta_x = end[0] - start[0];
    int delta_y = end[1] - start[1];

    if (plot_diagnal){
        if (delta_x == 0 || delta_y == 0){
            plotHorizontalAndVertical(delta_x, delta_y, start, end);
        }else{
            plotDiagnal(delta_x, delta_y, start, end);
        }
    }else{
        if (delta_x == 0 || delta_y == 0){
            plotHorizontalAndVertical(delta_x, delta_y, start, end);
        }
    }
}

void VentMap::plotHorizontalAndVertical(int delta_x, int delta_y, std::vector<int> start, std::vector<int> end)
{
    if (delta_x == 0){
            
            if(delta_y > 0){
                for(int i = 0; i < delta_y+1; i++){
                    map[start[1]+i][start[0]]++;
                }
            }else{
                for(int i = 0; i < abs(delta_y)+1; i++){
                    map[end[1]+i][end[0]]++;
            }
        }
    }
    if (delta_y == 0){
            
        if(delta_x > 0){
            for(int i = 0; i < delta_x+1; i++){
                map[start[1]][start[0]+i]++;
            }
        }else{
            for(int i = 0; i < abs(delta_x)+1; i++){
                map[end[1]][end[0]+i]++;
            }
        }
    }
}
void VentMap::plotDiagnal(int delta_x, int delta_y, std::vector<int> start, std::vector<int> end)
{
    if (delta_x > 0 && delta_y > 0)
    {
        for (int i = 0; i < delta_x+1; i++){
            map[start[1]+i][start[0]+i]++;
        }
    }
    else{
        if (delta_x < 0 && delta_y < 0){
            for (int i = 0; i < abs(delta_x)+1; i++){
                map[end[1]+i][end[0]+i]++;
            }
        }else{
            if (delta_x > 0 && delta_y < 0){
                for (int i = 0; i < abs(delta_x)+1; i++){
                    map[start[1]-i][start[0]+i]++;
                }   
            }else{
                    for (int i = 0; i < abs(delta_x)+1; i++){
                        map[start[1]+i][start[0]-i]++;
                } 
            }
        }
    }
}

void VentMap::viewMap()
{
    for (auto row : map){
        for (auto item : row){
            if (item == 0){
                std::cout << ".";
            }else{
                std::cout << item;
            }
        }
        std::cout << "\n";
    }
}
int VentMap::countIntersections()
{
    int count = 0;
    for (auto row : map){
        for (auto item : row){
            if (item > 1){
                count++;
            }
        }
    }
    return count;
}