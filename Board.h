#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Direction {N = -8, E = 1, S = 8, W = -1, NE = N + E, SE = S + E, SW = S + W, NW = N + W};

struct Score {
    int score0;
    int score1;
};

string numberToGrid(int num) {
    string res = "";
    int mod = num % 8;

    switch (num / 8) {
        case 0: res += "A"; break;
        case 1: res += "B"; break;
        case 2: res += "C"; break;
        case 3: res += "D"; break;
        case 4: res += "E"; break;
        case 5: res += "F"; break;
        case 6: res += "G"; break;
        case 7: res += "H"; break;
    }

    return res += to_string(mod);
}

class Board {
private:
    /*
    Board shape:
    [00][01]...[07]
    [08][09]...[15]
    ...
    [56][57]...[63]
    */

    // which spaces are occupied
    bool occupied_board[64] = {0};

    // which colour each space is
    bool colour_board[64] = {0};

    void printRow(int row, bool player) {
        switch(row){
            case 0: cout << "A|"; break;
            case 1: cout << "B|"; break;
            case 2: cout << "C|"; break;
            case 3: cout << "D|"; break;
            case 4: cout << "E|"; break;
            case 5: cout << "F|"; break;
            case 6: cout << "G|"; break;
            case 7: cout << "H|"; break;
        }
        for (int i = 8*row; i < 8*row+8; i++) {

            auto available_moves = availableMoves(player);
            bool is_available = false;
            for (int j = 0; j < available_moves.size(); j++) {
                if (i == available_moves[j]) {
                    is_available = true;
                    break;
                }
            }

            if (is_available) {
                cout << " _ ";
            } else if (occupied_board[i] == 0) {
                cout << "   ";
            } else {
                if (colour_board[i]) {
                    cout << " X ";
                } else {
                    cout << " O ";
                }
            }
            cout << "|";
        }

        cout << "\n";
    }

    void printColNames() {
        cout << "  ";
        for (int i = 0; i < 8; i++) {

            cout << " " << i << "  ";
        }
        cout << "\n";
    }

    void printHorizontalSeparator() {
        cout << " |";
        for (int i = 0; i < 7; i++) {
            cout << "--- ";
        }
        cout << "---|\n";
    }

    bool isGridFull() {
        for (int i = 0; i < 64; i++) {
            if (!occupied_board[i]) {
                return false;
            }
        }

        return true;
    }

    // N = -8
    // S = +8
    // E = +1
    // W = -1
    int findInDirection(bool player, int starting_cell, Direction d) {
        for (int i = starting_cell + d; i >= 0 && i <= 63; i += d) {
            if (!occupied_board[i]) {
                return -1;
            }

            int prev = i - d;
            int i_col = i % 8;
            int prev_col = prev % 8;

            if ((prev_col == 0 && i_col == 7) || (prev_col == 7 && i_col == 0)) {
                return -1;
            }

            if (colour_board[i] == player) {
                return i;
            }
        }

        return -1;
    }

    // If the ending_cell is -1, do nothing
    void flipPiecesInDirection(bool player, int starting_cell, int ending_cell, Direction d) {
        if (ending_cell == -1) {
            return;
        }

        for (int i = starting_cell + d; i != ending_cell; i += d) {
            colour_board[i] = player;
        }
    }

    // Flip the pieces in 8 directions 
    void flip_pieces(bool player, int cell) {

        int end_cell = findInDirection(player, cell, N);
        flipPiecesInDirection(player, cell, end_cell, N);
        
        end_cell = findInDirection(player, cell, NE);
        flipPiecesInDirection(player, cell, end_cell, NE);
        
        end_cell = findInDirection(player, cell, E);
        flipPiecesInDirection(player, cell, end_cell, E);
        
        end_cell = findInDirection(player, cell, SE);
        flipPiecesInDirection(player, cell, end_cell, SE);
        
        end_cell = findInDirection(player, cell, S);
        flipPiecesInDirection(player, cell, end_cell, S);
        
        end_cell = findInDirection(player, cell, SW);
        flipPiecesInDirection(player, cell, end_cell, SW);
        
        end_cell = findInDirection(player, cell, W);
        flipPiecesInDirection(player, cell, end_cell, W);
        
        end_cell = findInDirection(player, cell, NW);
        flipPiecesInDirection(player, cell, end_cell, NW);

        // // N
        // for (int i = cell - 8; i >= 0; i -= 8) {

        //     // Stop if the cell is unoccupied
        //     if (!occupied_board[i]) {
        //         break;
        //     }

        //     if (colour_board[i] == player) {
        //         for (int j = i + 8; j < cell; j += 8) {
        //             setCell(j, player);
        //         }
        //         break;
        //     }
        // }

        // // NE
        // if (cell % 8 != 7) {
        //     for (int i = cell - 7; i >= 0; i -= 7) {
        //         if (!occupied_board[i]) {
        //             break;
        //         }

        //         if (colour_board[i] == player) {
        //             for (int j = i + 7; j < cell; j += 7) {
        //                 setCell(j, player);
        //             }
        //             break;
        //         }

        //         if (i % 8 == 7) {
        //             break;
        //         }
        //     }
        // }

        // // E
        // if (cell % 8 != 7) {
        //     for (int i = cell + 1; ; i += 1) {
        //         if (!occupied_board[i]) {
        //             break;
        //         }

        //         if (colour_board[i] == player) {
        //             for (int j = i - 1; j > cell; j -= 1) {
        //                 setCell(j, player);
        //             }
        //             break;
        //         }

        //         if (i % 8 == 7) {
        //             break;
        //         }
        //     }
        // }

        // // SE
        // if (cell % 8 != 7) {
        //     for (int i = cell + 9; i <= 63; i += 9) {
        //         if (!occupied_board[i]) {
        //             break;
        //         }

        //         if (colour_board[i] == player) {
        //             for (int j = i - 9; j > cell; j -= 9) {
        //                 setCell(j, player);
        //             }
        //             break;
        //         }

        //         if (i % 8 == 7) {
        //             break;
        //         }
        //     }
        // }

        // // S
        // for (int i = cell + 8; i <= 63; i += 8) {

        //     // Stop if the cell is unoccupied
        //     if (!occupied_board[i]) {
        //         break;
        //     }

        //     if (colour_board[i] == player) {
        //         for (int j = i - 8; j > cell; j -= 8) {
        //             setCell(j, player);
        //         }
        //         break;
        //     }
        // }

        // // SW
        // if (cell % 8 != 0) {
        //     for (int i = cell + 7; i <= 63; i += 7) {
        //         if (!occupied_board[i]) {
        //             break;
        //         }

        //         if (colour_board[i] == player) {
        //             for (int j = i - 7; j > cell; j -= 7) {
        //                 setCell(j, player);
        //             }
        //             break;
        //         }

        //         if (i % 8 == 0) {
        //             break;
        //         }
        //     }
        // }

        // // W
        // if (cell % 8 != 0) {
        //     for (int i = cell - 1;; i -= 1) {
        //         if (!occupied_board[i]) {
        //             break;
        //         }

        //         if (colour_board[i] == player) {
        //             for (int j = i + 1; j < cell; j += 1) {
        //                 setCell(j, player);
        //             }
        //             break;
        //         }

        //         if (i % 8 == 0) {
        //             break;
        //         }
        //     }
        // }

        // // NW
        // if (cell % 8 != 0) {
        //     for (int i = cell - 9; i >= 0; i -= 9) {
        //         if (!occupied_board[i]) {
        //             break;
        //         }

        //         if (colour_board[i] == player) {
        //             for (int j = i + 9; j < cell; j += 9) {
        //                 setCell(j, player);
        //             }
        //             break;
        //         }

        //         if (i % 8 == 0) {
        //             break;
        //         }
        //     }
        // }
    }

    void setCell(int row, int col, bool colour) {
        occupied_board[8*row + col] = 1;
        colour_board[8*row + col] = colour;
    }

    void setCell(int cell, bool colour) {
        occupied_board[cell] = 1;
        colour_board[cell] = colour;
    }

public:
    void action(int row, int col, bool colour) {
        setCell(row, col, colour);
        flip_pieces(colour, row*8+col);
    }

    void action(int cell, bool colour) {
        setCell(cell, colour);
        flip_pieces(colour, cell);
    }

    Board() {
        setCell(3, 3, 0);
        setCell(3, 4, 1);
        setCell(4, 3, 1);
        setCell(4, 4, 0);
    }

    void printBoard(bool player) {
        printColNames();
        printHorizontalSeparator();
        for (int i = 0; i < 8; i++) {
            printRow(i, player);
            printHorizontalSeparator();
        }
    }

    // A move must capture a cell
    vector<int> availableMoves(bool player) {
        vector<int> res = {};

        for (int i = 0; i < 64; i++) {
            if (occupied_board[i]) {
                continue;
            }

            Direction d = N;
            auto cell = findInDirection(player, i, d);
            if (cell != -1 && cell != i + d) {
                res.push_back(i);
                continue;
            }

            d = NE;
            cell = findInDirection(player, i, d);
            if (cell != -1 && cell != i + d) {
                res.push_back(i);
                continue;
            }

            d = E;
            cell = findInDirection(player, i, d);
            if (cell != -1 && cell != i + d) {
                res.push_back(i);
                continue;
            }

            d = SE;
            cell = findInDirection(player, i, d);
            if (cell != -1 && cell != i + d) {
                res.push_back(i);
                continue;
            }

            d = S;
            cell = findInDirection(player, i, d);
            if (cell != -1 && cell != i + d) {
                res.push_back(i);
                continue;
            }

            d = SW;
            cell = findInDirection(player, i, d);
            if (cell != -1 && cell != i + d) {
                res.push_back(i);
                continue;
            }

            d = W;
            cell = findInDirection(player, i, d);
            if (cell != -1 && cell != i + d) {
                res.push_back(i);
                continue;
            }

            d = NW;
            cell = findInDirection(player, i, d);
            if (cell != -1 && cell != i + d) {
                res.push_back(i);
                continue;
            }
        }

        return res;
    }

    void printAvailableMoves(bool player) {
        auto moves = availableMoves(player);
        cout << "Available Moves: ";
        for (int i = 0; i < moves.size(); i++) {
            auto gridName = numberToGrid(moves[i]);
            cout << gridName << " ";
        }
        cout << "\n";
    }

    // Return both the number of Xs and Os on the board
    Score getFinalScore() {
        int zero_score = 0;
        int one_score = 0;

        for (int i = 0; i < 64; i++) {
            auto colour = colour_board[i];
            if (colour == 0) {
                zero_score++;
            } else if (colour == 1) {
                one_score++;
            }
        }

        Score result = { zero_score, one_score };
        return result;
    }

    // If there are more Os, return 0
    // If there are more Xs, return 1
    // return 2 on ties
    int countColours() {
        Score res = getFinalScore();

        if (res.score0 > res.score1) {
            return 0;
        } else if (res.score1 > res.score0) {
            return 1;
        } else {
            return 2;
        }
    }

    // If the game is not finished yet, return -1
    // Else return the victor, 2 on ties
    int checkVictory(int passes) {
        if (passes < 2 && !isGridFull()) {
            return -1;
        }

        return countColours();
    }
};