//
// Created by Lynn Tedje Anna Meindertsma on 07 Apr 2024.
//
#ifndef YAHTZEE_DICE_HPP
#define YAHTZEE_DICE_HPP

#include <cstdint>

class Dice {
public:
    // Constructor
    Dice();

    // Method to roll the dice and set a new random value
    void roll();

    // Method to get the current value of the dice
    uint8_t get_value() const;

private:
    uint8_t dice_value; // Current value of the dice
};

#endif //YAHTZEE_DICE_HPP