#pragma once
#include"snaze.h"
#include<cstdlib>
#include<ctime>

namespace snz
{
    snaze::snaze(std::string filename)
    {
        srand(time(NULL));
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

        size_t foodX = 0, foodY = 0;
        do
        {
            foodX = rand() % levelW;
            foodY = rand() % levelH;
        } while (level[foodY][foodX].gameObject != EMPTY);
        
        level[foodY][foodX].gameObject = FOOD;
        food.x = foodX;
        food.y = foodY;

        //std::cout << "Finished level read" << std::endl;
    }

    void snaze::render()
    {
        std::cout << "---------------  ======== SNAZE ========  --------------- \n";
        std::cout << "--------------------------------------------------------- \n";
        std::cout << "Score: " << score << "\n";
        std::cout << "--------------------------------------------------------- \n";
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
                else if(level[i][j].gameObject == FOOD)
                    std::cout << '$';
            }
            std::cout << "\n";
        }

        std::cout << "--------------------------------------------------------- \n";
        //std::cout << "Finished level output" << std::endl;

        std::cout << std::flush;
    }

    void snaze::move()
    {
        
        if(snakeDir == 'N')
        {
            if(level[snake[0]->y - 1][snake[0]->x].gameObject == FOOD)
            {
                eatFood();
            }
            for (size_t i = 0; i < snake.size(); i++)
            {
                snake[i]->y--;
                level[snake[i]->y + 1 ][snake[i]->x].gameObject = EMPTY;
                if(i == 0)
                    level[snake[i]->y][snake[i]->x].gameObject = SNAKEHEAD;
                else
                    level[snake[i]->y][snake[i]->x].gameObject = SNAKE;
            }
            if((level[snake[0]->y - 1 ][snake[0]->x].gameObject == EMPTY || level[snake[0]->y - 1 ][snake[0]->x].gameObject == FOOD) 
            && level[snake[0]->y][snake[0]->x + 1].gameObject == WALL 
            && level[snake[0]->y][snake[0]->x - 1].gameObject == WALL)
            {
                //Quickly cheks if the snake is in a straight corridor northwards.
                snakeDir = 'N';
                return;
            }
        }
        else if(snakeDir == 'S')
        {
            if(level[snake[0]->y + 1][snake[0]->x].gameObject == FOOD)
            {
                eatFood();
            }
            for (size_t i = 0; i < snake.size(); i++)
            {
                snake[i]->y++;
                level[snake[i]->y - 1 ][snake[i]->x].gameObject = EMPTY;
                if(i == 0)
                    level[snake[i]->y][snake[i]->x].gameObject = SNAKEHEAD;
                else
                    level[snake[i]->y][snake[i]->x].gameObject = SNAKE;
            }
            if((level[snake[0]->y + 1 ][snake[0]->x].gameObject == EMPTY || level[snake[0]->y + 1 ][snake[0]->x].gameObject == FOOD) 
            && level[snake[0]->y][snake[0]->x + 1].gameObject == WALL 
            && level[snake[0]->y][snake[0]->x - 1].gameObject == WALL)
            {
                //Quickly cheks if the snake is in a straight corridor southwards.
                snakeDir = 'S';
                return;
            }
        }
        else if(snakeDir == 'E')
        {
            if(level[snake[0]->y][snake[0]->x + 1].gameObject == FOOD)
            {
                eatFood();
            }
            for (size_t i = 0; i < snake.size(); i++)
            {
                snake[i]->x++;
                level[snake[i]->y][snake[i]->x - 1].gameObject = EMPTY;
                if(i == 0)
                    level[snake[i]->y][snake[i]->x].gameObject = SNAKEHEAD;
                else
                    level[snake[i]->y][snake[i]->x].gameObject = SNAKE;
            }
            if((level[snake[0]->y ][snake[0]->x + 1].gameObject == EMPTY || level[snake[0]->y ][snake[0]->x + 1].gameObject == FOOD)
            && level[snake[0]->y + 1][snake[0]->x].gameObject == WALL 
            && level[snake[0]->y - 1][snake[0]->x].gameObject == WALL)
            {
                //Quickly cheks if the snake is in a straight corridor eastwards.
                snakeDir = 'E';
                return;
            }
        }
        if(level[snake[0]->y][snake[0]->x - 1].gameObject == FOOD)
            {
                eatFood();
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
            if((level[snake[0]->y ][snake[0]->x - 1].gameObject == EMPTY || level[snake[0]->y ][snake[0]->x - 1].gameObject == FOOD) 
            && level[snake[0]->y + 1][snake[0]->x].gameObject == WALL 
            && level[snake[0]->y - 1][snake[0]->x].gameObject == WALL)
            {
                //Quickly cheks if the snake is in a straight corridor westwards.
                snakeDir = 'W';
                return;
            }
        }
        //If this part of the code was reached, then the snake may not be in a corridor.

        // T-Junction check
        if( snakeDir == 'S'
        && (level[snake[0]->y ][snake[0]->x + 1].gameObject == EMPTY || level[snake[0]->y ][snake[0]->x + 1].gameObject == FOOD) //Right of - East of snake head
        && (level[snake[0]->y ][snake[0]->x - 1].gameObject == EMPTY || level[snake[0]->y ][snake[0]->x - 1].gameObject == FOOD) //Left of - West of snake head
        && (level[snake[0]->y - 1 ][snake[0]->x].gameObject == EMPTY || level[snake[0]->y - 1 ][snake[0]->x].gameObject == FOOD)) //Above - North of snake head)
        {
            int newDir = rand() % 3;
            switch (newDir)
            {
            case 0:
                snakeDir = 'E';
                break;
            case 1:
                snakeDir = 'W';
                break;
            case 2:
                snakeDir = 'N';
                break;
            default:
                break;
            }
        }
        else if( snakeDir == 'N'
        && (level[snake[0]->y ][snake[0]->x + 1].gameObject == EMPTY || level[snake[0]->y ][snake[0]->x + 1].gameObject == FOOD) //Right of - East of snake head
        && (level[snake[0]->y ][snake[0]->x - 1].gameObject == EMPTY || level[snake[0]->y ][snake[0]->x - 1].gameObject == FOOD) //Left of - West of snake head
        && (level[snake[0]->y + 1 ][snake[0]->x].gameObject == EMPTY || level[snake[0]->y + 1 ][snake[0]->x].gameObject == FOOD))//Below - South of snake head)
        {
            int newDir = rand() % 3;
            switch (newDir)
            {
            case 0:
                snakeDir = 'E';
                break;
            case 1:
                snakeDir = 'W';
                break;
            case 2:
                snakeDir = 'S';
                break;
            default:
                break;
            }
        }
        else if( snakeDir == 'W'
        && (level[snake[0]->y ][snake[0]->x + 1].gameObject == EMPTY || level[snake[0]->y ][snake[0]->x + 1].gameObject == FOOD) //Right of - East of snake head
        && (level[snake[0]->y + 1][snake[0]->x].gameObject == EMPTY || level[snake[0]->y + 1][snake[0]->x].gameObject == FOOD) //Below - South of snake head
        && (level[snake[0]->y - 1 ][snake[0]->x].gameObject == EMPTY || level[snake[0]->y - 1 ][snake[0]->x].gameObject == FOOD))//Above - North of snake head)
        {
            int newDir = rand() % 3;
            switch (newDir)
            {
            case 0:
                snakeDir = 'E';
                break;
            case 1:
                snakeDir = 'S';
                break;
            case 2:
                snakeDir = 'N';
                break;
            default:
                break;
            }
        }
        else if( snakeDir == 'E'
        && (level[snake[0]->y ][snake[0]->x - 1].gameObject == EMPTY || level[snake[0]->y ][snake[0]->x - 1].gameObject == FOOD) //Left of - West of snake head
        && (level[snake[0]->y + 1][snake[0]->x].gameObject == EMPTY || level[snake[0]->y + 1][snake[0]->x].gameObject == FOOD) //Below - South of snake head
        && (level[snake[0]->y - 1 ][snake[0]->x].gameObject == EMPTY || level[snake[0]->y - 1 ][snake[0]->x].gameObject == FOOD))//Above - North of snake head)
        {
            int newDir = rand() % 3;
            switch (newDir)
            {
            case 0:
                snakeDir = 'W';
                break;
            case 1:
                snakeDir = 'S';
                break;
            case 2:
                snakeDir = 'N';
                break;
            default:
                break;
            }
        }
        //Two-Way junction check
        else if((level[snake[0]->y ][snake[0]->x + 1].gameObject == EMPTY || level[snake[0]->y ][snake[0]->x + 1].gameObject == FOOD) //Right of - East of snake head
        && (level[snake[0]->y ][snake[0]->x - 1].gameObject == EMPTY || level[snake[0]->y ][snake[0]->x - 1].gameObject == FOOD) //Left of - West of snake head
        && (level[snake[0]->y - 1 ][snake[0]->x].gameObject == WALL //Above - North of snake head
        || level[snake[0]->y + 1 ][snake[0]->x].gameObject == WALL)) //Below - South of snake head
        {
            int newDir = rand() % 2;
            switch (newDir)
            {
            case 0:
                snakeDir = 'E';
                break;
            case 1:
                snakeDir = 'W';
                break;
            default:
                break;
            }
        }
        else if((level[snake[0]->y ][snake[0]->x + 1].gameObject == WALL //Right of - East of snake head
        || level[snake[0]->y ][snake[0]->x - 1].gameObject == WALL) //Left of - West of snake head
        && (level[snake[0]->y - 1 ][snake[0]->x].gameObject == EMPTY || level[snake[0]->y - 1 ][snake[0]->x].gameObject == FOOD) //Above - North of snake head
        && (level[snake[0]->y + 1 ][snake[0]->x].gameObject == EMPTY || level[snake[0]->y + 1 ][snake[0]->x].gameObject == FOOD)) //Below - South of snake head
        {
            int newDir = rand() % 2;
            switch (newDir)
            {
            case 0:
                snakeDir = 'N';
                break;
            case 1:
                snakeDir = 'S';
                break;
            default:
                break;
            }
        }
        //90-Degree turn check
        else if(snakeDir != 'E' && (level[snake[0]->y ][snake[0]->x - 1].gameObject == EMPTY || level[snake[0]->y ][snake[0]->x - 1].gameObject == FOOD)) //Left of - West of snake head)
        {
            snakeDir = 'W';
        }
        else if(snakeDir != 'W' && (level[snake[0]->y ][snake[0]->x + 1].gameObject == EMPTY || level[snake[0]->y ][snake[0]->x + 1].gameObject == FOOD)) //Right of - East of snake head
        {
            snakeDir = 'E';
        }
        else if(snakeDir != 'S' && (level[snake[0]->y - 1 ][snake[0]->x].gameObject == EMPTY || level[snake[0]->y - 1 ][snake[0]->x].gameObject == FOOD))//Above - North of snake head)
        {
            snakeDir = 'N';
        }
        else if(snakeDir != 'N' && (level[snake[0]->y + 1][snake[0]->x].gameObject == EMPTY || level[snake[0]->y + 1][snake[0]->x].gameObject == FOOD)) //Below - South of snake head
        {
            snakeDir = 'S';
        }
        //Nowhere free to go? Then we have hit a dead end!
        else
        {
            canRun = true;
            render();
            std::cout << "WHOOPS! It seems like the snake has met its demise... \n";
            std::cout << "May it forever live on in our hearts. \n";
            std::cout << "Final score: " << score << std::endl;
            std::exit(0);
            return;
        }

    }
    /*
        QUICK REFERENCE
        level[snake[0]->y ][snake[0]->x - 1].gameObject //Left of - West of snake head
        level[snake[0]->y ][snake[0]->x + 1].gameObject //Right of - East of snake head
        level[snake[0]->y - 1 ][snake[0]->x].gameObject //Above - North of snake head
        level[snake[0]->y + 1 ][snake[0]->x].gameObject //Below - South of snake head
     */

    void snaze::eatFood()
    {
        score++;
        //std::cout << "\n \n WOOHOO! I HAVE MONEY!!!! \n \n \n" << score << std::endl;
        level[food.y][food.x].gameObject = EMPTY;
        if(score >=5)
        {
            canRun = true;
            return;
        }
        size_t foodX = 0, foodY = 0;
        do
        {
            foodX = rand() % levelW;
            foodY = rand() % levelH;
        } while (level[foodY][foodX].gameObject != EMPTY);
        
        level[foodY][foodX].gameObject = FOOD;
        food.x = foodX;
        food.y = foodY;
    }

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
