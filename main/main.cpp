#include<string>
#include<fstream>
#include<iostream>
#include<chrono>
#include<thread>

#include"snaze.h"

int main(int argc, char const *argv[])
{
    snz::snaze snaze(argv[1]);
    std::chrono::milliseconds fps(100);
    snaze.render();
    while(!snaze.gameOver())
    {
        std::this_thread::sleep_for(fps);
        snaze.move();
        snaze.render();
    }
    
    return 0;
}
