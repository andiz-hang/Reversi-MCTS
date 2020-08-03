This is an AI Reversi that uses Monte-Carlo Tree Search to play.

To use: 
    - Make sure all files are in the same directory.
    - Open the terminal and type: 
        g++ -std=c++11 -o main functions.cpp
        ./main
    - The default is a Human vs AI game. You can play an AI vs AI game and change which 
        MCTS algorithm that the AI uses (Pure random, or with Heuristics) in the 
        "functions.cpp" file. Change the corresponding variables to "true" or "false"