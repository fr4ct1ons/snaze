#pragma once
#include"snaze.h"

namespace snz
{
    snaze::snaze(std::string filename)
    {
        std::ifstream inputFile(filename);

        inputFile >> levelH;
        inputFile >> levelW;

        level = new int*[levelH];
        for (size_t i = 0; i < levelH; i++)
        {
            level[i] = new int[levelW];
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
                        level[i][j] = 1;
                    else if(buffer[j] == ' ')
                        level[i][j] = 2;
                }
            }
        }

        for (size_t i = 0; i < levelH; i++)
        {
            for (size_t j = 0; j < levelW; j++)
            {
                if(level[i][j] == 1)
                    std::cout << '#';
                else if(level[i][j] == 2)
                    std::cout << ' ';
            }
            std::cout << "\n";
        }

        std::cout << std::endl;
    }

    snaze::~snaze(){}
}
