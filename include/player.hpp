#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "dice.hpp"
#include "scorecard.hpp"

class Player {
public:
    Player();
    void initialize();
    void set_score(const Dice dices[5]);
    void print_score();
    std::string get_name();
    uint16_t get_total_score();
    uint8_t rounds();
    void set_ranking(uint8_t rank);
    uint8_t get_ranking();

private:
    std::string name;
    uint16_t total_score;
    Scorecard scorecard;
    uint16_t ranking_place = 0;
};

#endif // PLAYER_HPP
