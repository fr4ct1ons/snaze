#pragma once
#include"snake.h"
#include<fstream>
#include<iostream>
#include<string>

namespace snz
{
    class snaze
    {
    private:
        enum object
        {
            EMPTY,
            WALL,
            INVISWALL,
            SNAKE,
            SNAKEHEAD,
            FOOD,
            SPAWN
        };

        typedef struct game_object
        {
            object gameObject;
            size_t x, y; 
        } game_object;
        object **level;
        size_t levelW = 0, levelH = 0;
    public:
        snaze(std::string);
        ~snaze();
    };
}