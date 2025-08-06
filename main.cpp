#include <cstdint>
#include <string>

#include "game.hpp"

// Create instance of the class
Game game;

int main(){
    // Providing a seed value
    srand((unsigned) time(NULL));

    //start game
    game.start();
}