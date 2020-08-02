#include <iostream>
#include "ai.h"
#include <string>

using namespace std;

int strToCell(string str) {
    if (tolower(str[0]) < 97 || tolower(str[0]) > 104) {
        return -1;
    }

    if (str[1] < 48 || str[1] > 55) {
        return -1;
    }

    int row = tolower(str[0]) - 97;
    int col = str[1] - 48;

    return row * 8 + col;
}

int playerMove(Board b) {
    b.printBoard(0);

    string move = "";
    int cell = -1;

    auto a_moves = b.availableMoves(0);
    if (a_moves.size() == 0) {
        cout << "No available moves. Passing to your opponent";
        return -1;
    }

    cout << "Enter your move: ";
    cin >> move;
    cell = strToCell(move);

    bool is_available = false;
    for (int i = 0; i < a_moves.size(); i++) {
        if (a_moves[i] == cell) {
            is_available = true;
        }
    }

    while (cell == -1 || !is_available) {
        cout << "\n Move invalid. Please try again: ";
        cin >> move;
        cell = strToCell(move);

        for (int i = 0; i < a_moves.size(); i++) {
            if (a_moves[i] == cell) {
                is_available = true;
            }
        }
    }

    return cell;
}

void printWhoWon(Board b) {
    b.printBoard(0);

    auto gamestate = b.checkVictory(0);

    if (gamestate == 0) {
        cout << "The O player has won!\n";
    } else if (gamestate == 1) {
        cout << "The X player has won!\n";
    } else {
        cout << "The game resulted in a draw\n";
    }
}

void startGame(bool is_human_game) {
    // Generate a new seed for random
    srand(time(NULL));

    Board b;

    int gamestate = -1;
    int pass_counter = 0;

    while (gamestate == -1) {
        int p_move;
        if (is_human_game) {
            p_move = playerMove(b);
        } else {
            p_move = AITurn(b, 0);
        }

        if (p_move == -1) {
            pass_counter += 1;
        } else {
            b.action(p_move, 0);
            pass_counter = 0;
        }

        gamestate = b.checkVictory(pass_counter);
        if (gamestate != -1) {
            break;
        }

        auto c_move = AITurn(b, 1);
        if (c_move == -1) {
            pass_counter += 1;
        } else {
            b.action(c_move, 1);
            pass_counter = 0;
        }

        gamestate = b.checkVictory(pass_counter);
    }

    printWhoWon(b);
}