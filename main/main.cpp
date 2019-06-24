#include<string>
#include<fstream>
#include<iostream>

#include"snaze.h"

int main(int argc, char const *argv[])
{
    snz::snaze snaze(argv[1]);
    snaze.render();
    while(!snaze.gameOver())
    {
        snaze.move();
        snaze.render();
    }
    
    return 0;
}
