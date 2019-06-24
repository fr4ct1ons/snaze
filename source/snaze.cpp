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
                    level[i][j].x = j;
                    level[i][j].y = i;
                    if(buffer[j] == '#')
                        level[i][j].gameObject = WALL;
                    else if(buffer[j] == ' ')
                        level[i][j].gameObject = EMPTY;
                    else if(buffer[j] == '*')
                    {
                        level[i][j].gameObject = SNAKEHEAD;
                        spawn = level[i][j];
                        snake.push_back(&level[i][j]);
                    }
                    level[i][j].x = j;
                    level[i][j].y = i;
                }
            }
        }

        //std::cout << "Finished level read" << std::endl;
    }

    void snaze::render()
    {
        for (size_t i = 0; i < levelH; i++)
        {
            for (size_t j = 0; j < levelW; j++)
            {
                if(level[i][j].gameObject == WALL)
                    std::cout << "\u2592";
                else if(level[i][j].gameObject == SNAKEHEAD)
                    std::cout << "G";
                else if(level[i][j].gameObject == SNAKE)
                    std::cout << "O";
                else if(level[i][j].gameObject == EMPTY || level[i][j].gameObject == SPAWN)
                    std::cout << ' ';
            }
            std::cout << "\n";
        }

        //std::cout << "Finished level output" << std::endl;

        std::cout << std::flush;
    }

    void snaze::move()
    {
        if(snakeDir == 'N')
        {
            for (size_t i = 0; i < snake.size(); i++)
            {
                snake[i]->y--;
                level[snake[i]->y + 1 ][snake[i]->x].gameObject = EMPTY;
                if(i == 0)
                    level[snake[i]->y][snake[i]->x].gameObject = SNAKEHEAD;
                else
                    level[snake[i]->y][snake[i]->x].gameObject = SNAKE;
            }
            if(level[snake[0]->y - 1 ][snake[0]->x].gameObject == EMPTY 
            && level[snake[0]->y][snake[0]->x + 1].gameObject == WALL 
            && level[snake[0]->y][snake[0]->x - 1].gameObject == WALL)
            {
                //Quickly cheks if the snake is in a straight corridor northwards.
                snakeDir = 'N';
            }
        }
        else if(snakeDir == 'S')
        {
            for (size_t i = 0; i < snake.size(); i++)
            {
                snake[i]->y++;
                level[snake[i]->y - 1 ][snake[i]->x].gameObject = EMPTY;
                if(i == 0)
                    level[snake[i]->y][snake[i]->x].gameObject = SNAKEHEAD;
                else
                    level[snake[i]->y][snake[i]->x].gameObject = SNAKE;
            }
            if(level[snake[0]->y + 1 ][snake[0]->x].gameObject == EMPTY 
            && level[snake[0]->y][snake[0]->x + 1].gameObject == WALL 
            && level[snake[0]->y][snake[0]->x - 1].gameObject == WALL)
            {
                //Quickly cheks if the snake is in a straight corridor southwards.
                snakeDir = 'S';
            }
        }
        else if(snakeDir == 'E')
        {
            for (size_t i = 0; i < snake.size(); i++)
            {
                snake[i]->x++;
                level[snake[i]->y][snake[i]->x - 1].gameObject = EMPTY;
                if(i == 0)
                    level[snake[i]->y][snake[i]->x].gameObject = SNAKEHEAD;
                else
                    level[snake[i]->y][snake[i]->x].gameObject = SNAKE;
            }
            if(level[snake[0]->y ][snake[0]->x + 1].gameObject == EMPTY 
            && level[snake[0]->y + 1][snake[0]->x].gameObject == WALL 
            && level[snake[0]->y - 1][snake[0]->x].gameObject == WALL)
            {
                //Quickly cheks if the snake is in a straight corridor eastwards.
                snakeDir = 'E';
            }
        }
        else if(snakeDir == 'W')
        {
            for (size_t i = 0; i < snake.size(); i++)
            {
                snake[i]->x--;
                level[snake[i]->y][snake[i]->x + 1].gameObject = EMPTY;
                if(i == 0)
                    level[snake[i]->y][snake[i]->x].gameObject = SNAKEHEAD;
                else
                    level[snake[i]->y][snake[i]->x].gameObject = SNAKE;
            }
            if(level[snake[0]->y ][snake[0]->x - 1].gameObject == EMPTY 
            && level[snake[0]->y + 1][snake[0]->x].gameObject == WALL 
            && level[snake[0]->y - 1][snake[0]->x].gameObject == WALL)
            {
                //Quickly cheks if the snake is in a straight corridor westwards.
                snakeDir = 'W';
            }
        }

    }
    /*
        QUICK REFERENCE
        level[snake[0]->y ][snake[0]->x - 1] //Left of - West of snake head
        level[snake[0]->y ][snake[0]->x + 1] //Right of - East of snake head
        level[snake[0]->y - 1 ][snake[0]->x] //Above - North of snake head
        level[snake[0]->y + 1 ][snake[0]->x] //Below - South of snake head
     */

    snaze::~snaze()
    {
        /*for (size_t i = 0; i < levelH; i++)
        {
            delete[] level[i];
        }
        delete[] level;
        */
    }

    bool snaze::gameOver(){return canRun;}
}
