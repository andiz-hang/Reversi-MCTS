#include "Board.h"
#include <iostream>

using namespace std;

const int PLAYOUTS_SIMPLE = 2400;
const int PLAYOUTS_ADVANCED = 1400;

const int WEIGHT_MAP[64] = {
    10, 2, 5, 5, 5, 5, 2, 10,
     2, 1, 4, 4, 4, 4, 1, 2,
     5, 4, 5, 5, 5, 5, 4, 5,
     5, 4, 5, 8, 8, 5, 4, 5, 
     5, 4, 5, 8, 8, 5, 4, 5,
     5, 4, 5, 5, 5, 5, 4, 5,
     2, 1, 4, 4, 4, 4, 1, 2,
    10, 2, 5, 5, 5, 5, 2, 10,
};

// return the move
// Return -1 if passed instead
int chooseRandomMoveAlg(Board b, bool player) {
    auto moves = b.availableMoves(player);
    if (moves.size() == 0) { // If no available moves, increase the pass_counter
        return -1;
    }

    int randNum = rand() % moves.size();
    return moves[randNum];
}

int weightedRand(vector<int> moves, vector<int> weights) {
    // https://stackoverflow.com/questions/1761626/weighted-random-numbers/1761646
    int sum_of_weight = 0;
    for (int i = 0; i < weights.size(); i++) {
        sum_of_weight += weights[i];
    }

    int rnd = rand() % sum_of_weight;
    for (int i = 0; i < moves.size(); i++) {
        if (rnd < weights[i]) {
            return moves[i];
        }
        rnd -= weights[i];
    }

    return -1; // Should not run
}

// return the move
// Return -1 if passed instead
int chooseCornersEdgesAlg(Board b, bool player) {
    auto moves = b.availableMoves(player);

    if (moves.size() == 0) { // If no available moves, increase the pass_counter
        return -1;
    }

    vector<int> weights (moves.size(), 0);

    for (int i = 0; i < moves.size(); i++) {
        weights[i] = WEIGHT_MAP[moves[i]];
    }

    return weightedRand(moves, weights);
}

// Starting cell better be in availableMoves()
int randomPlayout(Board b, int starting_cell, bool player, int (*move_alg)(Board, bool)) {

    // Perform the starting action for the AI (Player 1)
    b.action(starting_cell, player);

    auto gamestate = b.checkVictory(0);
    int pass_counter = 0; // If there are 2 consecutive passes, the game is ended.

    // Do while the board is not full
    while (gamestate == -1) {
        // Simulated Human turn
        auto move = move_alg(b, !player);
        if (move == -1) {
            pass_counter += 1;
        } else {
            b.action(move, !player);
            pass_counter = 0;
        }

        gamestate = b.checkVictory(pass_counter);
        if (gamestate != -1) {
            break;
        }

        // Simulated AI turn
        player = 1;
        move = move_alg(b, player);
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

// For each available space, calculate that space's score
vector<int> addScores(Board b, vector<int> moves, bool player, int (*alg)(Board, bool)) {
    vector<int> scores (moves.size(), 0);

    int playouts = -50 * moves.size();

    if (alg == chooseRandomMoveAlg) {
        playouts += PLAYOUTS_SIMPLE;
    } else if (alg == chooseCornersEdgesAlg) {
        playouts += PLAYOUTS_ADVANCED;
    }

    for (int i = 0; i < moves.size(); i++) {
        auto chosen_move = moves[i];

        for (int j = 0; j < playouts; j++) {
            auto res = randomPlayout(b, chosen_move, player, alg);
            if (res == player) {
                scores[i] += 1;
            } else if (res == !player) {
                scores[i] -= 1;
            } 
            // Add zero for ties
        }
    }

    return scores;
}

// Returns the index of the max score. Also prints each of the scores
int maxScore(vector<int> moves, vector<int> scores) {

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
        cout << numberToGrid(moves[i]) << ": " << scores[i] << " | ";
    }
    cout << "\n";

    return index;
}

int AITurn(Board b, bool player, int (*alg)(Board, bool)) {

    b.printBoard(player);

    auto moves = b.availableMoves(player);
    if (moves.size() == 0) {
        cout << "AI " << player << " has no available moves. Passing to opponent.\n";
        return -1;
    }

    auto scores = addScores(b, moves, player, alg);
    int index = maxScore(moves, scores);

    string xo = "X";

    if (player == 0) {
        xo = "O";
    }
    cout << "The " << xo << " AI has chosen " << numberToGrid(moves[index]) << "\n";
    return moves[index];
}

// ai_select = 0 -> Simple AI
// ai_select = 1 -> Advanced AI
int AIMove(Board b, bool player, int ai_select) {
    if (ai_select == 0) {
        int (*func)(Board, bool) = chooseRandomMoveAlg;
        return AITurn(b, player, func);
    } else {
        int (*func)(Board, bool) = chooseCornersEdgesAlg;
        return AITurn(b, player, func);
    }
}