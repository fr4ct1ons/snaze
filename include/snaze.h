#pragma once
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

        game_object **level; //!< 2D Array for the level objects.
        //std::stack<game_object * > path;
        std::vector<game_object * > snake; //!< Vector for storing the snake and its body positions. snake[0] corresponds to the head.
        size_t levelW = 0; //!< Width of the level.
        size_t levelH = 0; //!< Height of the level.
        game_object spawn; //!< Spawn place of the snake.
        char snakeDir = 'N'; //!< Value of the direction the snake is facing.
        bool canRun = false; //!< Variable that returns if the game is over or not.
        int score = 0; //!< Score of the snaze game.
        game_object food; //!< Reference of the food object.
    public:
        //! Default constructor
        /*! \param filename - Input file containing the level to be opened.
         */
        snaze(std::string filename);
        //! Default destructor
        ~snaze();
        //! Renders the current game state.
        void render();
        //! Advances the game state, i.e, moves the snake and spawns food.
        void move();
        //! Get if the game is over or not.
        bool gameOver();
        //! Process the event of the snake eating food
        /*! In extent, it adds a point to the score and respawns the food.
         */
        void eatFood();
    };
}