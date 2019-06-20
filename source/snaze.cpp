#pragma once
#include"snaze.h"

namespace snz
{
    snaze::snaze(std::string filename)
    {
        std::ifstream inputFile(filename);

        inputFile >> levelH;
        inputFile >> levelW;

        level = new object*[levelH];
        for (size_t i = 0; i < levelH; i++)
        {
            level[i] = new object[levelW];
        }
        
        std::string buffer;
        std::getline(inputFile, buffer);
        for (size_t i = 0; i < levelH; i++)
        {
            if(std::getline(inputFile, buffer))
            {
                for (size_t j = 0; j < buffer.size(); j++)
                {
                    if(buffer[j] == '#')
                        level[i][j] = WALL;
                    else if(buffer[j] == ' ')
                        level[i][j] = EMPTY;
                }
            }
        }

        for (size_t i = 0; i < levelH; i++)
        {
            for (size_t j = 0; j < levelW; j++)
            {
                if(level[i][j] == WALL)
                    std::cout << "\u2592";
                else if(level[i][j] == EMPTY)
                    std::cout << ' ';
            }
            std::cout << "\n";
        }

        std::cout << std::endl;
    }

    snaze::~snaze(){}
}
