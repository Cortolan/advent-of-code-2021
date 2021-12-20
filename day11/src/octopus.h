#include <vector>
#include <tuple>

class octopus
{
private:
    int max_x_;
    int max_y_;
    bool isValidNeighber(int x, int y);

public:
    int pos_x_;
    int pos_y_;
    int charge_;
    int flashed_count_ = 0;
    bool triggered_ = false;
    std::vector<std::tuple<int, int>> neighbers_;

    octopus(int pos_x, int pos_y, int charge, int max_x, int max_y);
    std::vector<std::tuple<int, int>> increaseCharge();
    void reset();
};

octopus::octopus(int pos_x, int pos_y, int charge, int max_x, int max_y)
{
    pos_x_ = pos_x;
    pos_y_ = pos_y;
    charge_ = charge;
    max_x_ = max_x;
    max_y_ = max_y;

    // make neighber list by verifying acceptible positions
    const int y[] = {-1, -1, -1, 1, 1, 1, 0, 0};
    const int x[] = {-1, 0, 1, -1, 0, 1, -1, 1};
    for (int i = 0; i < 8; ++i)
    {
        if (isValidNeighber(pos_x_ + x[i], pos_y_ + y[i]) == true)
        {
            neighbers_.push_back(std::make_tuple(pos_x_ + x[i], pos_y_ + y[i]));
        }
    }
}

std::vector<std::tuple<int, int>> octopus::increaseCharge()
{
    std::vector<std::tuple<int, int>> empty_list;
    charge_ += 1;
    if (charge_ > 9 && triggered_ == false)
    {
        triggered_ = true;
        return neighbers_;
    }
    else
    {
        return empty_list;
    }
}

void octopus::reset()
{
    if (triggered_ == true)
    {
        triggered_ = false;
        charge_ = 0;
        flashed_count_ += 1;
    }
}

bool octopus::isValidNeighber(int x, int y)
{
    if (x < 0 || x > max_x_)
    {
        return false;
    }
    if (y < 0 || y > max_y_)
    {
        return false;
    }
    return true;
}