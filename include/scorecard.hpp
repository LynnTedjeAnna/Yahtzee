//
// Created by Lynn Tedje Anna Meindertsma on 08 Apr 2024.
//
#ifndef YAHTZEE_SCORECARD_HPP
#define YAHTZEE_SCORECARD_HPP

#include "dice.hpp"

enum scores{
    THREE_OF_A_KIND = 7,
    FOUR_OF_A_KIND = 8,
    FULL_HOUSE = 9,
    SMALL_STRAIGHT = 10,
    LARGE_STRAIGHT = 11,
    YAHTZEE = 12,
    CHANCE = 13,
    BONUS_YAHTZEE = 14
};


 #define BONUS_SCORE 63
 #define BONUS_POINTS 35
 #define POINTS_FULL_HOUSE 25
 #define POINTS_SMALL_STRAIGHT 30
 #define POINTS_LARGE_STRAIGHT 40
 #define POINTS_YAHTZEE 50
 #define BONUS_POINTS_YAHTZEE 100

class Scorecard {
public:
    //Constructor
    Scorecard();

    void print_score();
    void set_score(const Dice dices[5]);
    bool check_score();
    bool check_duplicates(const Dice dices[5]);
    bool check_ascending(const Dice dices[5]);
    uint16_t calc_total_score();

private:
    uint16_t total_score = 0;
    uint8_t part1_scorecard[6];
    uint8_t three_kind = 0;
    uint8_t four_kind = 0;
    uint8_t full_house = 0;
    uint8_t small_straight = 0;
    uint8_t large_straight = 0;
    uint8_t yahtzee = 0;
    uint8_t bonus_yahtzee = 0;
    uint8_t chance = 0;
    uint32_t select;
};
#endif //YAHTZEE_SCORECARD_HPP