#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include "Cell.h"

class Grid {
private:
    std::vector<std::vector<Cell>> board;
    int size;

public:
    Grid(int n) : size(n) {
        board = std::vector<std::vector<Cell>>(size, std::vector<Cell>(size));
        srand(time(0));
    }

    void printBoard() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                board[i][j].display();
            }
            std::cout << std::endl;
        }
    }

    void addRandomTile() {
        std::vector<std::pair<int, int>> emptyCells;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j].isEmpty()) {
                    emptyCells.emplace_back(i, j);
                }
            }
        }
        if (!emptyCells.empty()) {
            int index = rand() % emptyCells.size();
            int value = (rand() % 2 + 1) * 2;
            board[emptyCells[index].first][emptyCells[index].second].setValue(value);
        }
    }

    void leftAction() {
        system("cls");
        for (int i = 0; i < size; i++) {
            for (int j = 1; j < size; j++) {
                if (!board[i][j].isEmpty()) {
                    //  k permet de ne pas faire 2 fusions consécutive
                    int k = j;
                    while (k > 0 && board[i][k - 1].isEmpty()) {
                        k--;
                    }
                    if (k > 0 && board[i][k - 1].getValue() == board[i][j].getValue()) {
                        board[i][k - 1].setValue(board[i][k - 1].getValue() * 2);
                        board[i][j].setValue(0);
                    }
                    else if (k != j) {
                        board[i][k].setValue(board[i][j].getValue());
                        board[i][j].setValue(0);
                    }
                }
            }
        }
    }

    void rightAction() {
        system("cls");
        for (int i = 0; i < size; i++) {
            for (int j = size - 2; j >= 0; j--) {
                if (!board[i][j].isEmpty()) {
                    int k = j;
                    while (k < size - 1 && board[i][k + 1].isEmpty()) {
                        k++;
                    }
                    if (k < size - 1 && board[i][k + 1].getValue() == board[i][j].getValue()) {
                        board[i][k + 1].setValue(board[i][k + 1].getValue() * 2);
                        board[i][j].setValue(0);
                    }
                    else if (k != j) {
                        board[i][k].setValue(board[i][j].getValue());
                        board[i][j].setValue(0);
                    }
                }
            }
        }
    }

    void topAction() {
        system("cls");
        for (int j = 0; j < size; j++) {
            for (int i = 1; i < size; i++) {
                if (!board[i][j].isEmpty()) {
                    int k = i;
                    while (k > 0 && board[k - 1][j].isEmpty()) {
                        k--;
                    }
                    if (k > 0 && board[k - 1][j].getValue() == board[i][j].getValue()) {
                        board[k - 1][j].setValue(board[k - 1][j].getValue() * 2);
                        board[i][j].setValue(0);
                    }
                    else if (k != i) {
                        board[k][j].setValue(board[i][j].getValue());
                        board[i][j].setValue(0);
                    }
                }
            }
        }
    }

    void bottomAction() {
        system("cls");
        for (int j = 0; j < size; j++) {
            for (int i = size - 2; i >= 0; i--) {
                if (!board[i][j].isEmpty()) {
                    int k = i;
                    while (k < size - 1 && board[k + 1][j].isEmpty()) {
                        k++;
                    }
                    if (k < size - 1 && board[k + 1][j].getValue() == board[i][j].getValue()) {
                        board[k + 1][j].setValue(board[k + 1][j].getValue() * 2);
                        board[i][j].setValue(0);
                    }
                    else if (k != i) {
                        board[k][j].setValue(board[i][j].getValue());
                        board[i][j].setValue(0);
                    }
                }
            }
        }
    }

    void checkWin() {
        //  si 2048 atteind win
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j].getValue() == 2048) {
                    std::cout << "WIN !!! 2^11 HAS BEEN REACHED" << std::endl;
                    return;
                }
            }
        }
    }
    void checkLoose() {
        int loose = 0;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j].isEmpty()) {
                    return; // si case vide, le jeu n'est pas perdu
                }

                if (i < size - 1 && board[i][j].getValue() == board[i + 1][j].getValue()) {
                    return; // si tuile fusionnable en bas, le jeu n'est pas perdu
                }

                if (j < size - 1 && board[i][j].getValue() == board[i][j + 1].getValue()) {
                    return; //si tuile fusionnable à droite, le jeu n'est pas perdu
                }
            }
        }
        std::cout << "\nYOU LOSE !!!" << std::endl;
    }
};


    void performAction(Grid& game, void (Grid::* action)()) {
        (game.*action)();
        game.addRandomTile();
        game.printBoard();
        game.checkWin();
        game.checkLoose();
        Sleep(100);
    }

int main() {
    Grid game(4);
    Cell cell;
    game.addRandomTile();
    game.addRandomTile();
    game.printBoard();

    while (true) {
        if (GetKeyState(VK_LEFT) & 0x8000) {
            performAction(game, &Grid::leftAction);
        }
        else if (GetKeyState(VK_RIGHT) & 0x8000) {
            performAction(game, &Grid::rightAction);
        }
        else if (GetKeyState(VK_UP) & 0x8000) {
            performAction(game, &Grid::topAction);
        }
        else if (GetKeyState(VK_DOWN) & 0x8000) {
            performAction(game, &Grid::bottomAction);
        }
    }

    return 0;
}
