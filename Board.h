#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

    void printRow(int row) {
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

            auto available_moves = availableMoves();
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

    bool isGridFull() {
        for (int i = 0; i < 64; i++) {
            if (!occupied_board[i]) {
                return false;
            }
        }

        return true;
    }

    void flip_pieces(bool player, int cell) {
        // N
        for (int i = cell - 8; i >= 0; i -= 8) {

            // Stop if the cell is unoccupied
            if (!occupied_board[i]) {
                break;
            }

            if (colour_board[i] == player) {
                for (int j = i + 8; j < cell; j += 8) {
                    setCell(j, player);
                }
                break;
            }
        }

        // NE
        if (cell % 8 != 7) {
            for (int i = cell - 7; i >= 0; i -= 7) {
                if (!occupied_board[i]) {
                    break;
                }

                if (colour_board[i] == player) {
                    for (int j = i + 7; j < cell; j += 7) {
                        setCell(j, player);
                    }
                    break;
                }

                if (i % 8 == 7) {
                    break;
                }
            }
        }

        // E
        if (cell % 8 != 7) {
            for (int i = cell + 1; ; i += 1) {
                if (!occupied_board[i]) {
                    break;
                }

                if (colour_board[i] == player) {
                    for (int j = i - 1; j > cell; j -= 1) {
                        setCell(j, player);
                    }
                    break;
                }

                if (i % 8 == 7) {
                    break;
                }
            }
        }

        // SE
        if (cell % 8 != 7) {
            for (int i = cell + 9; i <= 63; i += 9) {
                if (!occupied_board[i]) {
                    break;
                }

                if (colour_board[i] == player) {
                    for (int j = i - 9; j > cell; j -= 9) {
                        setCell(j, player);
                    }
                    break;
                }

                if (i % 8 == 7) {
                    break;
                }
            }
        }

        // S
        for (int i = cell + 8; i <= 63; i += 8) {

            // Stop if the cell is unoccupied
            if (!occupied_board[i]) {
                break;
            }

            if (colour_board[i] == player) {
                for (int j = i - 8; j > cell; j -= 8) {
                    setCell(j, player);
                }
                break;
            }
        }

        // SW
        if (cell % 8 != 0) {
            for (int i = cell + 7; i <= 63; i += 7) {
                if (!occupied_board[i]) {
                    break;
                }

                if (colour_board[i] == player) {
                    for (int j = i - 7; j > cell; j -= 7) {
                        setCell(j, player);
                    }
                    break;
                }

                if (i % 8 == 0) {
                    break;
                }
            }
        }

        // W
        if (cell % 8 != 0) {
            for (int i = cell - 1;; i -= 1) {
                if (!occupied_board[i]) {
                    break;
                }

                if (colour_board[i] == player) {
                    for (int j = i + 1; j < cell; j += 1) {
                        setCell(j, player);
                    }
                    break;
                }

                if (i % 8 == 0) {
                    break;
                }
            }
        }

        // NW
        if (cell % 8 != 0) {
            for (int i = cell - 9; i >= 0; i -= 9) {
                if (!occupied_board[i]) {
                    break;
                }

                if (colour_board[i] == player) {
                    for (int j = i + 9; j < cell; j += 9) {
                        setCell(j, player);
                    }
                    break;
                }

                if (i % 8 == 0) {
                    break;
                }
            }
        }
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

    void printBoard() {
        printColNames();
        printHorizontalSeparator();
        for (int i = 0; i < 8; i++) {
            printRow(i);
            printHorizontalSeparator();
        }
    }

    vector<int> availableMoves() {
        vector<int> res = {};

        for (int i = 0; i < 64; i++) {
            if (occupied_board[i]) {
                continue;
            }

            // Check up
            if (i >= 8 && occupied_board[i-8]) {
                res.push_back(i);
                continue;
            }

            // Check down
            if (i <= 55 && occupied_board[i+8]) {
                res.push_back(i);
                continue;
            }

            // Check left
            if (i % 8 != 0 && occupied_board[i-1]) {
                res.push_back(i);
                continue;
            }

            // Check right
            if (i % 8 != 7 && occupied_board[i+1]) {
                res.push_back(i);
                continue;
            }

            // Check NW
            if (i % 8 != 0 && i >= 8 && occupied_board[i-9]) {
                res.push_back(i);
                continue;
            }
            // Check NE
            if (i % 8 != 7 && i >= 8 && occupied_board[i-7]) {
                res.push_back(i);
                continue;
            }

            // Check SE
            if (i % 8 != 7 && i <= 55 && occupied_board[i+9]) {
                res.push_back(i);
                continue;
            }

            // Check SW
            if (i % 8 != 0 && i <= 55 && occupied_board[i+7]) {
                res.push_back(i);
                continue;
            }
        }

        return res;
    }

    void printAvailableMoves() {
        auto moves = availableMoves();
        cout << "Available Moves: ";
        for (int i = 0; i < moves.size(); i++) {
            auto gridName = numberToGrid(moves[i]);
            cout << gridName << " ";
        }
        cout << "\n";
    }

    // If the game is not finished yet, return -1
    // If player 0 wins, return 0
    // If player 1 wins, return 1
    // Ties return 2
    int checkVictory() {
        if (!isGridFull()) {
            return -1;
        }

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

        if (zero_score > one_score) {
            return 0;
        } else if (one_score > zero_score) {
            return 1;
        } else {
            return 2;
        }
    }
};