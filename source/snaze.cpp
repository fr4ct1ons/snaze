#pragma once
#include"snaze.h"

namespace snz
{
    snaze::snaze(std::string filename)
    {
        std::ifstream inputFile(filename);

        inputFile >> levelH;
        inputFile >> levelW;

        level = new game_object*[levelH];
        for (size_t i = 0; i < levelH; i++)
        {
            level[i] = new game_object[levelW];
        }
        //std::cout << "Created array!" << std::endl;

        std::string buffer;
        std::getline(inputFile, buffer);
        //std::cout << "Entering level read" << std::endl;
        for (size_t i = 0; i < levelH; i++)
        {
            if(std::getline(inputFile, buffer))
            {
                for (size_t j = 0; j < buffer.size(); j++)
                {
                    if(buffer[j] == '#')
                        level[i][j].gameObject = WALL;
                    else if(buffer[j] == ' ')
                        level[i][j].gameObject = EMPTY;
                    else if(buffer[j] == '*')
                        level[i][j].gameObject = SPAWN;
                }
            }
        }

        //std::cout << "Finished level read" << std::endl;

        for (size_t i = 0; i < levelH; i++)
        {
            for (size_t j = 0; j < levelW; j++)
            {
                if(level[i][j].gameObject == WALL)
                    std::cout << "\u2592";
                else if(level[i][j].gameObject == EMPTY || level[i][j].gameObject == SPAWN)
                    std::cout << ' ';
            }
            std::cout << "\n";
        }

        //std::cout << "Finished level output" << std::endl;

        std::cout << std::flush;
    }

    snaze::~snaze()
    {
        for (size_t i = 0; i < levelH; i++)
        {
            delete[] level[i];
        }
        delete level;
    }
}
