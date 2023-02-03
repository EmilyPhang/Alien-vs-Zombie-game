#ifndef ALIEN_H
#define ALIEN_H
#include "Zombie.h"
#include <string>


class Alien {
    private:
        int Life; 
        int Attack;
        int AlienRow;
        int AlienCol;
        char AlienLogo;
        bool isMyTurn;
    public: 
        // Constructor 
        Alien(char Logo);

        //setter
        void setLife(int newLife);
        void setAttack(int newAttack);
        void setAlienRow(int newAlienRow);
        void setAlienCol(int newAlienCol);
        void setLocation(int newRow, int newCol);
        void setIsMyTurn(bool newTurn);
        
        //Getter 
        int getLife();
        int getAttack();
        int getAlienRow();
        int getAlienCol();
        char getAlienLogo();
        bool getIsMyTurn();

        //Printer
        void printDescription();
        // void printNextLocation();

        //Actions
        bool move(std::string command);
        bool moveValidation(int newRow, int newCol);
        std::string touchGameObj(std::string command, int newRow, int newCol);
        void podBlast(int newRow, int newCol);
        bool attackZombie(int newRow, int newCol);

        // Formula
        int ZombieMinDistance(int newRow, int newCol);
};

#endif