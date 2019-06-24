#pragma once
#include"snake.h"
#include<fstream>
#include<iostream>
#include<string>
#include<stack>
#include<vector>

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
        game_object **level;
        std::stack<game_object * > path;
        std::vector<game_object * > snake;
        size_t levelW = 0, levelH = 0;
    public:
        snaze(std::string);
        ~snaze();
    };
}