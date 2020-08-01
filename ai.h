#include "Board.h"
#include <cstdlib> // rand
#include <iostream>
#include <ctime> // time

using namespace std;

const int RANDOM_PLAYOUTS = 100;

// Starting cell better be in availableMoves()
int randomPlayout(Board b, int starting_cell) {
    // Perform the starting action for the AI (Player 1)
    b.action(starting_cell, 1);

    auto gamestate = b.checkVictory();

    // Do while the board is not full
    while (gamestate == -1) {
        // Simulated Human turn

        auto moves = b.availableMoves();
        int randNum = rand() % moves.size();
        int randMove = moves[randNum];

        b.action(randMove, 0);

        gamestate = b.checkVictory();

        if (gamestate != -1) {
            return gamestate;
        }

        // Simulated AI turn
        moves = b.availableMoves();
        randNum = rand() % moves.size();
        randMove = moves[randNum];

        b.action(randMove, 1);

        gamestate = b.checkVictory();
    }

    return gamestate;
}

int AITurn(Board b) {

    // Generate a new seed for random
    srand(time(NULL));
    
    auto moves = b.availableMoves();
    vector<int> scores (moves.size(), 0) ;

    for (int i = 0; i < moves.size(); i++) {
        auto chosen_move = moves[i];

        for (int j = 0; j < RANDOM_PLAYOUTS; j++) {
            auto res = randomPlayout(b, chosen_move);
            if (res == 1) {
                scores[i] += 1;
            } else if (res == 0) {
                scores[i] -= 1;
            } 
            // Add zero for ties
        }
    }

    // Find the highest score
    int index = 0;
    int max = scores[0];

    for (int i = 1; i < scores.size(); i++) {
        if (scores[i] > max) {
            max = scores[i];
            index = i;
        }
    }  

    return moves[index];
}