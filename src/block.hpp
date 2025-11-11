#pragma once // To only call it once
#include <raylib.h>
#include "laser.hpp"

struct Block 
{   
    Vector2 position;

    Block(Vector2 i_position)
    {
        position = i_position;
    }
    
    void draw()
    {
        DrawRectangle(position.x,position.y,3,3,{243,216,63,255});
    }
};
