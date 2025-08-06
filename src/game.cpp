//
// Created by Lynn Tedje Anna Meindertsma on 08 Apr 2024.
//
#include<iostream>
#include <string>

#include "game.hpp"

using namespace std;

uint8_t Game::category() {
    // Standard game
    if (cat == 1){
        return  13;
    }
    // Short game
    if (cat == 2){
        return 5;
    } else {return 0;}
}

void Game::start() {
    printf("Do you want to play a game? \n"
           "0: NO\n"
           "1: STANDARD\n"
           "2: SHORT (5 rounds)\n");
    scanf("%d", &cat);
    category();
    printf("Enter the number of players:");
    scanf("%d", &num_players);

    players = new Player[num_players];
    // Initialize each player
    for (int i = 0; i < num_players; ++i) {
        players[i].initialize();
        printf("\n");
    }

    //game has max number of rounds
    for (int i = 0; i < category(); ++i) {
        next_round();
    }
    end_game();
}
void Game::next_roll() {
    std::string reroll;
    //You can re-roll only two times per round
    for (int i = 0; i < 2; ++i) {
        printf("Do you want to re-roll any of the dice? \n"
               "(Enter the index of the dice(s) you want to re-roll\n"
               "and press enter)\n");
        scanf("%s", &reroll);

        for (uint32_t j = 0; j < strlen(reroll.c_str()); j++) {
            switch (reroll[j]) {
                case '1': dices[0].roll(); break;
                case '2': dices[1].roll(); break;
                case '3': dices[2].roll(); break;
                case '4': dices[3].roll(); break;
                case '5': dices[4].roll(); break;
                default: break;
            }
        }

        printf("Your throw is: ");
        //print dice value
        for (int j = 0; j < 5; ++j) {
            printf("%d ", dices[j].get_value());
        }
        printf("\n");
    }
    //todo:bonus yahtzee bug
}

void Game::next_round() {
    for (int i = 0; i < num_players; ++i) {
        printf("...............................Player:%s...............................\n", players[i].get_name().c_str());
        players[i].print_score();
        printf("%s", "Your throw is: ");
        //dice roll
        for (int j = 0; j < 5; ++j) {
            dices[j].roll();
        }
        //print dice value
        for (int j = 0; j < 5; ++j) {
            printf("%d ", dices[j].get_value());
        }
        printf("\n");
        next_roll();
        players[i].set_score(dices);
    }
}

void Game::end_game() {
    // Sort players based on their total score (from highest to lowest)
    for (int i = 0; i < num_players - 1; ++i) {
        for (int j = i + 1; j < num_players; ++j) {
            if (players[i].get_total_score() < players[j].get_total_score()) {
                std::swap(players[i], players[j]);
            }
        }
    }
    // Assign rankings based on the sorted order
    for (int i = 0; i < num_players; ++i) {
        players[i].set_ranking(i + 1);
    }

    // Print each player's ranking and score
    for (int i = 0; i < num_players; ++i) {
        printf("\n%s ranking is: %d\n", players[i].get_name().c_str(), players[i].get_ranking());
        printf("Your total score is: %d\n", players[i].get_total_score());
    }
}