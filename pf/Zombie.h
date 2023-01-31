#ifndef ZOMBIE_H
#define ZOMBIE_H

class Zombie {
    private:
        int Life; 
        int Attack;
        int Range;
        int ZombieRow;
        int ZombieCol;
        char ZombieLogo;
        bool isMyTurn;
    public: 
        // Constructor 
        Zombie();
        Zombie(char Logo);

        //setter
        void setLife(int newLife);
        void setAttack(int newAttack);
        void setRange(int newRange);
        void setZombieRow(int newZombieRow);
        void setZombieCol(int newZombieCol);
        void setLocation(int newRow, int newCol);
        void setIsMyTurn(bool newTurn);

        //Getter 
        int getLife();
        int getAttack();
        int getRange();
        int getZombieRow();
        int getZombieCol();
        char getZombieLogo();
        bool getIsMyTurn();


        //Printer
        void printDescription();

        //Actions
        void move();
        bool moveValidation(int newRow, int newCol);
        bool touchGameObj(int newRow, int newCol);
};

#endif