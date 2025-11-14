#pragma once // To call it only once
using namespace std;
#include<vector>
#include"block.hpp"

struct Obstacle {
    Vector2 position;
    std::vector<Block> blocks;
    static std::vector<std::vector<int>> grid;
    Obstacle(Vector2 i_position)
    {
        position = i_position; // To set the position of the obstacle with respect to the grid using parameter i_position

         // This is the obstacle at the start as it gets damaged more of the 1s will turn into 0s to show that it is damaged

        for(unsigned int row = 0; row < grid.size(); ++row)
        {
            for(unsigned int column = 0; column < grid[0].size(); ++column)
            {
                if(grid[row][column] == 1)
                {
                    // each block is 3 pixels wide
                    float pos_x = position.x + column * 3;
                    float pos_y = position.y  + row * 3;
                    Block block = Block({pos_x, pos_y});
                    blocks.push_back(block);
                }
            }
        }
    }

    void draw()
    {
        for(auto& block: blocks)
        {
            block.draw();
        }
    }
};
