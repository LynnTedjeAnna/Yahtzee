//
// Created by Lynn Tedje Anna Meindertsma on 07 Apr 2024.
//
#include<iostream>
#include<cstdlib>

#include "dice.hpp"

Dice::Dice() {}

void Dice::roll() {
    // Retrieve a random number between 1 and 6
    dice_value = (rand() % 6) + 1;
}

uint8_t Dice::get_value() const {
    return dice_value;
}