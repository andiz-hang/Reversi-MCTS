#include <iostream>
#include "reversi.h"

using namespace std;

// Set this to 'true' if you (the human) want to play against the AI.
// Note: For human games, you will play against "X" AI. 
const bool IS_HUMAN_GAME = true;

// Set this to 'true' if you want the "O" AI to use the modified MCTS algorithm
// Does nothing if IS_HUMAN_GAME is set to true
const bool ADVANCED_O_AI = true;

// Set this to 'true' if you want "X" AI to use the modified MCTS algorithm
// This will be your opponent if you play a human game.
const bool ADVANCED_X_AI = true;

int main() {
    startGame(IS_HUMAN_GAME, ADVANCED_O_AI, ADVANCED_X_AI);
}