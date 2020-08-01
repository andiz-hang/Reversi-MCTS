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
    b.printBoard();

    string move = "";
    int cell = -1;

    cout << "Enter your move: ";
    cin >> move;
    cell = strToCell(move);

    auto a_moves = b.availableMoves();

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
    b.printBoard();

    auto gamestate = b.checkVictory();

    if (gamestate == 0) {
        cout << "The O player has won!\n";
    } else if (gamestate == 1) {
        cout << "The X player has won!\n";
    } else {
        cout << "The game resulted in a draw\n";
    }
}

void startHumanGame() {
    Board b;

    int gamestate = -1;

    while (gamestate == -1) {

        auto p_move = playerMove(b);
        b.action(p_move, 0);

        gamestate = b.checkVictory();
        if (gamestate != -1) {
            break;
        }

        auto c_move = AITurn(b);
        b.action(c_move, 1);

        gamestate = b.checkVictory();
    }

    printWhoWon(b);
}

void startAIGame() {
    Board b;

    int gamestate = -1;

    while (gamestate == -1) {

        auto p_move = AITurn(b);
        b.action(p_move, 0);
        b.printBoard();

        gamestate = b.checkVictory();
        if (gamestate != -1) {
            break;
        }

        auto c_move = AITurn(b);
        b.action(c_move, 1);
        b.printBoard();

        gamestate = b.checkVictory();
    }

    printWhoWon(b);
}