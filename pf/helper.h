#ifndef PF_HELPER_H
#define PF_HELPER_H
#include "Zombie.h"

namespace pf
{
    int getBoardRow();
    int getBoardCol();
    int getZombieCount();
    Zombie* getZombiePlayer();
    int ClearScreen();
    int Pause();
    // int generateRandomNumber();

    void CreateGameBoard(int kRows, int kColumns, int zombie_count);
    void CreateAlien(int kRows, int kColumns);
    void CreateZombie(int kRows, int kColumns, int zombie_count);
    char CreateGameObj(int random_number);

    char getBoardChar(int row, int col);
    void updateBoard(int row, int col, char logo); 
    void resetBoard();
    void ShowGameBoard();
    void saveBoard();
    void loadBoard();

    void StartGame();
}

#endif