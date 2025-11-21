#pragma once // To call it only once
using namespace std;
#include<vector>
#include"block.hpp"

struct Obstacle {
    Vector2 position;
    Block blocks[299];
    static int grid[13][23];
    Obstacle() { position = {0, 0}; }
    Obstacle(Vector2 i_position)
    {
        static const int Max_blocks = 276; // To store the total number of blocks made by the grid matrix
        int block_count = 0; // To use the block_count as an iterator inside the loop to keep the count of total blocks so we can update it as it gets damaged
        position = i_position; // To set the position of the obstacle with respect to the grid using parameter i_position

         // This is the obstacle at the start as it gets damaged more of the 1s will turn into 0s to show that it is damaged

        for(unsigned int row = 0; row < 13; ++row)
        {
            for(unsigned int column = 0; column < 23; ++column)
            {
                if(grid[row][column] == 1)
                {
                    // each block is 3 pixels wide
                    float pos_x = position.x + column * 3;
                    float pos_y = position.y  + row * 3;
                    Block block = Block({pos_x, pos_y});
                    if(block_count < Max_blocks)
                    {
                        blocks[block_count] = block;
                        block_count++;
                    }
                }
            }
        }
    }

    void draw()
    {
        for(unsigned int i = 0; i<276; i++)
        {
            blocks[i].draw();
        }
    }

    void update()
    {
    
    }
};
