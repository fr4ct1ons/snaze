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
        int **level;
        size_t levelW = 0, levelH = 0;
    public:
        snaze(std::string);
        ~snaze();
    };
}