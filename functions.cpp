#include <iostream>
#include "reversi.h"

using namespace std;

// Set this to 'true' if you (the human) want to play against the AI.
// Note: For human games, you will play against AI2. 
const bool IS_HUMAN_GAME = true;

// Set this to 'true' if you want AI1 to use the modified MCTS algorithm
// Does nothing if IS_HUMAN_GAME is set to true
const bool ADVANCED_AI1 = true;

// Set this to 'true' if you want AI2 to use the modified MCTS algorithm
// This will be your opponent if you play a human game.
const bool ADVANCED_AI2 = true;

int main() {
    startGame(IS_HUMAN_GAME, HARD_AI1, HARD_AI2);
}