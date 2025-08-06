//
// Created by Lynn Tedje Anna Meindertsma on 08 Apr 2024.
//
#ifndef YAHTZEE_GAME_HPP
#define YAHTZEE_GAME_HPP

#include "dice.hpp"
#include "player.hpp"

class Game {
public:
    //Constructor
    Game() = default;

    //Methode to start the game
    void start();

    //Methode to choose game category
    uint8_t category();

    //Methode to proceed to the next player's turn
    void next_roll();

    //Methode to proceed to the next player's round
    void next_round();

    //Methode to determine the winner and end the game
    void end_game();

private:
    Dice dices[5];
    Player player;
    uint32_t num_players = 0;
    uint32_t cat;
    // Dynamically allocate an array of Player objects
    Player* players = nullptr;
};

#endif //YAHTZEE_GAME_HPP
