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
        uint8_t score_ = (64 - score - (INVALID_POINTS * invalid_count));
        printf("points needed for bonus points: %d", score_);
    } else {
        printf("You got the bonus points: %d!", score);
    }
    printf("---\n");
    printf("7.  Three of a Kind: %d\n", three_kind);
    printf("8.  Four of a Kind: %d\n",  four_kind);
    printf("9.  Full House: %d\n",      full_house);
    printf("10. Small Straight: %d\n",  small_straight);
    printf("11. Large Straight: %d\n",  large_straight);
    printf("12. Yahtzee: %d\n",         yahtzee);
    printf("13. Chance: %d\n",          chance);
    printf("14. Bonus yahtzee: %d\n\n", bonus_yahtzee);
    printf("15. Cross off option\n");
    printf("-----------------------------------\n");
}

void Scorecard::set_score(const Dice dices[5]) {
    print_score();
    do {
        printf("Choose what to fill in: \n"
               "select 1-15 \n");
        scanf("%d", &select);
    } while (!is_selected_slot_empty());

    if (select == 15){
        do {
            printf("Which do you want too cross of your scorecard?\n"
                   "select 1-15 \n");
            scanf("%d", &select);
        } while (select > 13 && !is_selected_slot_empty());
        invalidate_select();
        print_score();
        return;
    }

    while (!selected_sum(dices) && select < 7){
        printf("Choose what to fill in: \n"
               "select 1-15 \n");
        scanf("%d", &select);
    }

    while (!check_duplicates(dices) && ((select == THREE_OF_A_KIND) || (select == FOUR_OF_A_KIND) || (select == FULL_HOUSE) || (select == YAHTZEE) || (select == BONUS_YAHTZEE))){
        printf("Choose what to fill in: \n"
               "select 1-15 \n");
        scanf("%d", &select);
    }

    while (!check_ascending(dices) && ((select == SMALL_STRAIGHT) || (select == LARGE_STRAIGHT))){
        printf("Choose what to fill in: \n"
               "select 1-15 \n");
        scanf("%d", &select);
    }

    if (select < 7){
        part1_scorecard[select - 1] = selected_sum(dices);
        print_score();
        return;
    }

    switch (select) {
        case THREE_OF_A_KIND:
            three_kind += cumulative_sum(dices);
            break;
        case FOUR_OF_A_KIND:
            four_kind += cumulative_sum(dices);
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
            chance += cumulative_sum(dices);
            break;
        case BONUS_YAHTZEE:
            bonus_yahtzee = BONUS_POINTS_YAHTZEE;
            break;
        default: break;
    }
    print_score();
}

bool Scorecard::is_selected_slot_empty(){
    if (select < 6 && part1_scorecard[select - 1]   != 0) return false;
    if (select == THREE_OF_A_KIND && three_kind     != 0) return false;
    if (select == FOUR_OF_A_KIND  && four_kind      != 0) return false;
    if (select == FULL_HOUSE      && full_house     != 0) return false;
    if (select == SMALL_STRAIGHT  && small_straight != 0) return false;
    if (select == LARGE_STRAIGHT  && large_straight != 0) return false;
    if (select == YAHTZEE         && yahtzee != 0) return false;
    if (select == CHANCE          && chance  != 0) return false;
    if (select == BONUS_YAHTZEE   && bonus_yahtzee  != 0) return false;
    if (select > 15) return false;
    return true;
}

bool Scorecard::check_duplicates(const Dice dices[MAX_DICE]) {
    uint8_t dice_values[MAX_DICE];
    for (int i = 0; i < MAX_DICE; ++i) { dice_values[i] = dices[i].get_value(); }

    uint8_t count[6];
    bool pair = false;
    bool three_dup = false;
    bool four_dup  = false;
    bool five_dup  = false;

    // Store the count of each element of the dice
    for (int i = 0; i < MAX_DICE; i++) { count[dice_values[i]]++; }
    for (int i = 0; i < 6; i++) {
        if (count[i] == 2){ pair      = true;}
        if (count[i] > 2) { three_dup = true;}
        if (count[i] > 3) { four_dup  = true;}
        if (count[i] > 4) { five_dup  = true;}
    }

    if ((select == THREE_OF_A_KIND) && three_dup) { return true; }
    if (select == FOUR_OF_A_KIND && four_dup)     { return true; }
    if (select == FULL_HOUSE && pair && three_dup){ return true; }
    if (select == YAHTZEE && five_dup)            { return true; }
    // Bonus yahtzee can only be used after the first yahtzee
    if (select == BONUS_YAHTZEE && yahtzee == 0)  { return false; }
    if (select == BONUS_YAHTZEE && five_dup)      { return true; }
    else return false;
}

bool Scorecard::check_ascending(const Dice dices[MAX_DICE]) {
    uint8_t dice_values[MAX_DICE];
    for (int i = 0; i < MAX_DICE; ++i) { dice_values[i] = dices[i].get_value(); }

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

uint8_t Scorecard::selected_sum(const Dice dices[MAX_DICE]) {
    uint8_t sum = 0;
    for (int i = 0; i < MAX_DICE; ++i) {
        if (dices[i].get_value() == select) {
            sum += dices[i].get_value();
        }
    }
    return sum;
}

uint8_t Scorecard::cumulative_sum(const Dice dices[MAX_DICE]) {
    uint8_t sum = 0;
    for (int i = 0; i < MAX_DICE; ++i) {
        sum += dices[i].get_value();
    }
    return sum;
}

void Scorecard::invalidate_select() {
    if (select < 7){
        part1_scorecard[select - 1] = INVALID_POINTS;
        invalid_count++;
        return;
    }

    switch (select) {
        case THREE_OF_A_KIND:
            three_kind = INVALID_POINTS;
            break;
        case FOUR_OF_A_KIND:
            four_kind = INVALID_POINTS;
            break;
        case FULL_HOUSE:
            full_house = INVALID_POINTS;
            break;
        case SMALL_STRAIGHT:
            small_straight = INVALID_POINTS;
            break;
        case LARGE_STRAIGHT:
            large_straight = INVALID_POINTS;
            break;
        case YAHTZEE:
            yahtzee = INVALID_POINTS;
            break;
        case CHANCE:
            chance = INVALID_POINTS;
            break;
        default: break;
    }
    invalid_count++;
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

    // Remove any invalidated option points (cross out)
    total_score -= (INVALID_POINTS * invalid_count);
    return  total_score;
}






