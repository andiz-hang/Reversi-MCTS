#include <iostream>
#include "ai.h"
#include <chrono>

using namespace std;

void Benchmarking(bool ai_select, int n_moves) {
    Board b;

    for (int i = 0; i < n_moves; i += 2) {

        auto move = AIMove(b, 0, !ai_select);
        b.action(move, 0);

        move = AIMove(b, 1, !ai_select);
        b.action(move, 1);
    }

    // https://www.reddit.com/r/learnprogramming/comments/1dlxqv/c_measuring_time_elapsed_in_milliseconds/
    auto start = chrono::high_resolution_clock::now();
    auto move = AIMove(b, 0, ai_select);
    b.action(move, 0);
    auto end = chrono::high_resolution_clock::now();
    
    auto dur = end - start;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

    cout << "Time taken: \t\t" << ms << "ms\n";
    cout << "Milliseconds per playout: " << float(ms)/float(PLAYOUTS_SIMPLE) << "ms\n";
}

int main() {
    Benchmarking(0, 0);
    Benchmarking(0, 12);
    Benchmarking(0, 24);
    Benchmarking(0, 32);
    Benchmarking(0, 48);
}