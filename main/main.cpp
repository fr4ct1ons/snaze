#include<string>
#include<fstream>
#include<iostream>
#include<chrono>
#include<thread>

#include"snaze.h"

int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        std::cout << "Invalid input file! Closing program." << std::endl;
        std::cout << "Make sure you're running the program as ./snaze <input-file>." << std::endl;
        return 0;
    }
    std::chrono::seconds waitTime(15);
    std::cout <<" .d8888. d8b   db  .d8b.  d88888D d88888b \n"
              <<" 88'  YP 888o  88 d8' `8b YP  d8' 88'     \n"
              <<" `8bo.   88V8o 88 88ooo88    d8'  88ooooo \n"
              <<"   `Y8b. 88 V8o88 88~~~88   d8'   88~~~~~ \n"
              <<" db   8D 88  V888 88   88  d8' db 88.     \n"
              <<" `8888Y' VP   V8P YP   YP d88888P Y88888P \n" << std::endl;
    std::cout << "Welcome to SNAZE! A copy of the fun snake game with a twist - YOU'RE TRAPPED ON A MAZE! \n" ;
    std::cout << "In Snaze, the snake will run around the maze aimlessly until it finds the money, where your score will go up! \n";
    std::cout << "The game stops when either the snakes hits itself or when it finds money 5 times. \n";
    std::cout << "Will the snake perish, or live a life of riches? Let's find out NOW!" << std::endl;

    std::this_thread::sleep_for(waitTime);

    snz::snaze snaze(argv[1]);
    std::chrono::milliseconds fps(150);
    snaze.render();
    while(!snaze.gameOver())
    {
        std::this_thread::sleep_for(fps);
        snaze.move();
        snaze.render();
    }
    std::cout << "It appears the snake lives, after adventuring the hardships of the maze! Hurray! \n";
    std::cout << "May it live a wonderful and prosperous life! And thank you for playing SNAZE!" << std::endl;
    
    return 0;
}
