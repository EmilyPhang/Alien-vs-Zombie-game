#ifndef PF_HELPER_H
#define PF_HELPER_H
#include "Zombie.h"
#include "Alien.h"
#include <string>

namespace pf
{
    int getBoardRow();
    int getBoardCol();
    int getZombieCount();
    Zombie* getZombiePlayer();
    Alien getAlienPlayer();
    int ClearScreen();
    int Pause();
    // int generateRandomNumber();

    void CreateGameBoard(int kRows, int kColumns, int zombie_count);
    void CreateAlien(int kRows, int kColumns);
    void CreateZombie(int kRows, int kColumns, int zombie_count);
    char CreateGameObj(int random_number);
    bool validLocation(int newRow, int newCol);
    void passTurn();

    char getBoardChar(int row, int col);
    void updateBoard(int row, int col, char logo); 
    void resetBoard();
    void ShowGameBoard();
    void saveBoard();
    void loadBoard();
    void arrowChange(int targetRow, int targetCol, std::string targetDirection);
    int pointDistance(int x1, int y1, int x2, int y2);
    
    void StartGame();
}

#endif