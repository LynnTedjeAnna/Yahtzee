//
// Created by Lynn Tedje Anna Meindertsma on 08 Apr 2024.
//
#include <cstdio>
#include <algorithm>

#include "scorecard.hpp"

Scorecard::Scorecard() {
    for (int i = 0; i < 6; ++i) {
        part1_scorecard[i] = 0;
    }
}
//todo: bonus yahtzee u dont lose a turn, u gain a turn

void Scorecard::print_score() {
    uint8_t score = 0;
    for (uint8_t i = 0; i < 6; ++i) { score += part1_scorecard[i]; }


    printf("\nScores:\n");
    printf("1. Ones: %d\n",     part1_scorecard[0]);
    printf("2. Twos: %d\n",     part1_scorecard[1]);
    printf("3. Threes: %d\n",   part1_scorecard[2]);
    printf("4. Fours: %d\n",    part1_scorecard[3]);
    printf("5. Fives: %d\n",    part1_scorecard[4]);
    printf("6. Sixes: %d\n",    part1_scorecard[5]);
    printf("---");
    if (score < BONUS_SCORE){
        uint8_t score_ = 64 - score;
        printf("points needed for bonus points: %d", score_);
    } else {
        printf("You got the bonus points: %d!", score);
    }
    printf("---\n");
    printf("7. Three of a Kind: %d\n",  three_kind);
    printf("8. Four of a Kind: %d\n",   four_kind);
    printf("9. Full House: %d\n",       full_house);
    printf("10. Small Straight: %d\n",  small_straight);
    printf("11. Large Straight: %d\n",  large_straight);
    printf("12. Yahtzee: %d\n",         yahtzee);
    printf("13. Chance: %d\n\n",        chance);
    printf("14. Bonus yahtzee: %d\n\n", bonus_yahtzee);
}

bool Scorecard::check_score(){
    if (select < 6 && part1_scorecard[select - 1]   != 0) return false;
    if (select == THREE_OF_A_KIND   && three_kind   != 0) return false;
    if (select == FOUR_OF_A_KIND    && four_kind    != 0) return false;
    if (select == FULL_HOUSE        && full_house   != 0) return false;
    if (select == SMALL_STRAIGHT    && small_straight != 0) return false;
    if (select == LARGE_STRAIGHT    && large_straight != 0) return false;
    if (select == YAHTZEE           && yahtzee  != 0) return false;
    if (select == CHANCE            && chance   != 0) return false;
    if (select == BONUS_YAHTZEE     && bonus_yahtzee  != 0) return false;
    if (select > BONUS_YAHTZEE) return false;
    return true;
}

bool Scorecard::check_duplicates(const Dice dices[5]) {
    uint8_t dice_values[5];
    for (int i = 0; i < 5; ++i) {
        dice_values[i] = dices[i].get_value();
    }

    std::sort(dice_values, dice_values + 5);
    uint8_t count = 1;

    for (int i = 0; i < 4; ++i) {
        //todo: when count is 4 rn PROBLEM for full house
        //  checkt alleen voor three of a kind niet full house
        if (dice_values[i] == dice_values[i + 1]) { count++; }
    }
    // If no or one duplicate(s) return false
    if (count == 1 || count == 2){ return false;}

    if ((select == THREE_OF_A_KIND) && (count > 2)) { return true; }
    if (select == FOUR_OF_A_KIND    && count > 3)   { return true; }
    // todo fix full house check
    if (select == FULL_HOUSE        && count == 4)  { return true; }
    if (select == YAHTZEE           && count == 5)  { return true; }
    //bonus yahtzee can only be used after the first yahtzee
    if (select == BONUS_YAHTZEE && yahtzee == 0)    { return false; }
    if (select == BONUS_YAHTZEE && count == 5)      { return true; }
    else return false;
}

bool Scorecard::check_ascending(const Dice dices[5]) {
    uint8_t dice_values[5];
    for (int i = 0; i < 5; ++i) { dice_values[i] = dices[i].get_value(); }

    std::sort(dice_values, dice_values + 5);
    uint8_t count = 1;

    for (int i = 0; i < 4; ++i) {
        if (dice_values[i] == (dice_values[i + 1] - 1)) { count++; }
        if (i == 2) {
            if (dice_values[i] != (dice_values[i - 1] + 1)) { count--; }
        }
    }
    if (select < 3 ){ return false;}
    if (select == SMALL_STRAIGHT && count > 3) { return true; }
    if (select == LARGE_STRAIGHT && count > 4) { return true; }
    return false;
}

// todo if no score is possible, cross off
void Scorecard::set_score(const Dice dices[5]) {
    print_score();
    do {
        printf("Choose what to fill in: \nselect 1-14 \n");
        scanf("%d", &select);
    } while (!check_score());

    while (!check_duplicates(dices) && ((select == THREE_OF_A_KIND) || (select == FOUR_OF_A_KIND) || (select == FULL_HOUSE) || (select == YAHTZEE) || (select == BONUS_YAHTZEE))){
        printf("Choose what to fill in: \nselect 1-14 \n");
        scanf("%d", &select);
    }

    while (!check_ascending(dices) && ((select == SMALL_STRAIGHT) || (select == LARGE_STRAIGHT))){
        printf("Choose what to fill in: \nselect 1-14 \n");
        scanf("%d", &select);
    }

    if (select <= 6){
        uint8_t add_up_dices = 0;
        for (int i = 0; i < 5; ++i) {
            if (dices[i].get_value() == select) {
                add_up_dices += dices[i].get_value();
            }
        }
        part1_scorecard[select - 1] = add_up_dices;
    }

    switch (select) {
        case THREE_OF_A_KIND:
            for (int i = 0; i < 5; ++i) {
                three_kind += dices[i].get_value();
            }
            break;
        case FOUR_OF_A_KIND:
            for (int i = 0; i < 5; ++i) {
                four_kind += dices[i].get_value();
            }
            break;
        case FULL_HOUSE:
            full_house = POINTS_FULL_HOUSE;
            break;
        case SMALL_STRAIGHT:
            small_straight = POINTS_SMALL_STRAIGHT;
            break;
        case LARGE_STRAIGHT:
            large_straight = POINTS_LARGE_STRAIGHT;
            break;
        case YAHTZEE:
            yahtzee = POINTS_YAHTZEE;
            break;
        case CHANCE:
            for (int i = 0; i < 5; ++i) {
                chance += dices[i].get_value();
            }
            break;
        case BONUS_YAHTZEE:
            bonus_yahtzee = BONUS_POINTS_YAHTZEE;
            break;
        default: break;
    }
    print_score();
}

uint16_t Scorecard::calc_total_score() {
    for (uint8_t i = 0; i < 6; ++i) { total_score += part1_scorecard[i]; }
    if (total_score >= BONUS_SCORE){ total_score += BONUS_POINTS; }

    total_score += three_kind;
    total_score += four_kind;
    total_score += full_house;
    total_score += small_straight;
    total_score += large_straight;
    total_score += yahtzee;
    total_score += bonus_yahtzee;
    total_score += chance;

    return  total_score;
}