#include "Board.h"
#include <iostream>

using namespace std;

const int RANDOM_PLAYOUTS = 1500;

// return the move
// Return -1 if passed instead
int simulateTurn(Board b, bool player) {
    auto moves = b.availableMoves(player);
    if (moves.size() == 0) { // If no available moves, increase the pass_counter
        return -1;
    }

    int randNum = rand() % moves.size();
    return moves[randNum];
}

// Starting cell better be in availableMoves()
int randomPlayout(Board b, int starting_cell) {

    // Perform the starting action for the AI (Player 1)
    b.action(starting_cell, 1);

    auto gamestate = b.checkVictory(0);
    int pass_counter = 0; // If there are 2 consecutive passes, the game is ended.

    // Do while the board is not full
    while (gamestate == -1) {
        // Simulated Human turn
        int player = 0;
        auto move = simulateTurn(b, player);
        if (move == -1) {
            pass_counter += 1;
        } else {
            b.action(move, player);
            pass_counter = 0;
        }

        gamestate = b.checkVictory(pass_counter);
        if (gamestate != -1) {
            return gamestate;
        }

        // Simulated AI turn
        player = 1;
        move = simulateTurn(b, player);
        if (move == -1) {
            pass_counter += 1;
        } else {
            b.action(move, player);
            pass_counter = 0;
        }

        gamestate = b.checkVictory(pass_counter);
    }

    return gamestate;
}

int AITurn(Board b, bool player) {

    b.printBoard(player);

    auto moves = b.availableMoves(player);
    if (moves.size() == 0) {
        cout << "AI " << player << " has no available moves. Passing to opponent.\n";
        return -1;
    }

    vector<int> scores (moves.size(), 0);

    for (int i = 0; i < moves.size(); i++) {
        auto chosen_move = moves[i];

        for (int j = 0; j < RANDOM_PLAYOUTS; j++) {
            auto res = randomPlayout(b, chosen_move);
            if (res == player) {
                scores[i] += 1;
            } else if (res == !player) {
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

    for (int i = 0; i < scores.size(); i++) {
        cout << b.numberToGrid(moves[i]) << ": " << scores[i] << " | ";
    }
    cout << "\n";

    string xo = "X";

    if (player == 0) {
        xo = "O";
    }
    cout << "The " << xo << " AI has chosen " << b.numberToGrid(moves[index]) << "\n";
    return moves[index];
}