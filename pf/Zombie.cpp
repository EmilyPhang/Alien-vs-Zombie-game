// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT4L 
// Names: EMILY PHANG RU YING | LIM CAI QING | TEO YU JIE 
// IDs: 1211102687 | 1211102753 | 1211102751 
// Emails: 1211102687@student.mmu.edu.my | 1211102753@student.mmu.edu.my | 1211102751@student.mmu.edu.my 
// Phones: 0122270304 | 0143001623 | 0122615818 
// ********************************************************* 
#include "helper.h"
#include "Zombie.h"
#include "Alien.h"
#include <cstdlib>
#include <iostream>
using namespace std;

// Class Constructor
Zombie::Zombie(){

}

Zombie::Zombie(char Logo, int row, int col){
    this->Life = max(10, (rand()%20) * 10); 
    this->Attack = max(10, (rand()%10) * 10);
    this->ZombieLogo = Logo;
    this->isMyTurn = false;     //Alien go first
    this->ZombieRow = row;
    this->ZombieCol = col;
}

Zombie::Zombie(char Logo, bool isMyTurn, int life, int attack, int range){
    this->ZombieLogo = Logo;
    this->isMyTurn = isMyTurn; 
    this->Life = life;
    this->Attack = attack;
    this->Range = range;
}


// Class Method (set)
void Zombie::setLife(int newLife){
    this->Life = max(0, newLife); 
    if(this->Life>0){
        cout<<"Zombie "<<this->getZombieLogo()<<" is still alive."<<endl;
        
        }
    else{
        pf::updateBoard(this->getZombieRow(),this->getZombieCol(), '.');
        cout<<"Zombie "<<this->getZombieLogo()<<" is dead"<<endl;
    }
}

void Zombie::setAttack(int newAttack){
    this->Attack = newAttack;
}

void Zombie::setRange(int newRange){
    this->Range = newRange;
}

void Zombie::setZombieRow(int newZombieRow){
    this->ZombieRow = newZombieRow;
};

void Zombie::setZombieCol(int newZombieCol){
    this->ZombieCol = newZombieCol; 
};

void Zombie::setLocation(int newRow, int newCol){
    // //Old location
    // if(this->ZombieRow and this->ZombieCol)
        // cout<<"space"<<endl;
    pf::updateBoard(this->ZombieRow, this->ZombieCol, ' ');
    // new Location
    this->ZombieRow = newRow;
    this->ZombieCol = newCol;
    pf::updateBoard(this->ZombieRow, this->ZombieCol, this->getZombieLogo());
}

void Zombie::setIsMyTurn(bool newTurn){
    this->isMyTurn = newTurn;
}


// Class Method (get)
int Zombie::getLife(){
    return this->Life;
}

int Zombie::getAttack(){
    return this->Attack;
}

int Zombie::getRange(){
   return this->Range; 
}

int Zombie::getZombieRow(){
    return this->ZombieRow;
}

int Zombie::getZombieCol(){
    return this->ZombieCol;
}

char Zombie::getZombieLogo(){
    return this->ZombieLogo;
}

bool Zombie::getIsMyTurn(){
    return this->isMyTurn;
}

//Printer
void Zombie::printDescription(){
    if (this->isMyTurn){
        cout<<" > ";
    }
    else{
        cout<<"   ";
    }
    cout<<"Zombie "<<this->ZombieLogo<< ": Life " << this->Life <<",\t\tAttack "<< this->Attack<<",\tRange "<< this->Range<<endl;
}

// Action
void Zombie::move(){
    srand(time(0));
    int newRow, newCol;
    int boardRow = pf::getBoardRow();
    int boardCol = pf::getBoardCol();
    int retryCounter = 0; 
    
    do{
        newRow = this->getZombieRow();
        newCol = this->getZombieCol();
        retryCounter ++; 
        cout<<"Zombie Tried to move. Retry: " <<retryCounter<<endl;

        if(newRow==0 and newCol == 0){
        // Now at Top Left; Can move Right/Bottom
        std::rand()%2==0 ? newCol += 1 : newRow += 1; 
        }
        else if (newRow==0 and newCol == boardCol-1){
            // Now at Top Right; Can move Left/Bottom
            std::rand()%2==0 ?  newCol -= 1 : newRow += 1; 
        }
        else if (newRow == boardRow-1  and newCol == 0){
            // Now at Bottom Left; Can move Up/Right
            std::rand()%2==0 ?  newRow -= 1 :  newCol += 1;
        }
        else if (newRow == boardRow-1 and newCol == boardCol-1){
            // Now at Bottom Right; Can move up/Left
            std::rand()%2==0 ?  newRow -= 1 :  newCol -= 1;
        }
        else if(newRow==0){
            // Now at Top; Can Move Down/Left/Right
            switch (std::rand()%3)
            {
            case 0:
                newRow += 1; //down
                break;
            case 1:
                newCol -= 1; //left
                break;
            case 2:
                newCol += 1; //right
                break;
            }
        }
        else if(newRow==boardRow-1){
            // Now at Bottom; Can Move Up/Left/Right
            switch (std::rand()%3)
            {
            case 0:
                newRow -= 1; //up
                break;
            case 1:
                newCol -= 1; //left
                break;
            case 2:
                newCol += 1; //right
                break;
            }
        }
        else if(newCol==0){
            // Now at Left; Can Move Up/Down/Right
            switch (std::rand()%3)
            {
            case 0:
                newRow -= 1; //up
                break;
            case 1:
                newRow += 1; //down
                break;
            case 2:
                newCol += 1; //right
                break;
            }
        }
        else if(newCol==boardCol-1){
            // Now at Right; Can Move Up/Down/Left
            switch (std::rand()%3)
            {
            case 0:
                newRow -= 1; //up
                break;
            case 1:
                newRow += 1; //down
                break;
            case 2:
                newCol -= 1; //left
                break;
            }
        }
        else{
            // Anywhere in middle
            switch (std::rand()%4)
            {
            case 0:
                newRow -= 1; //up
                break;
            case 1:
                newRow += 1; //down
                break;
            case 2:
                newCol -= 1; //left
                break;
            case 3:
                newCol += 1; //right
                break;
            }
        }
    }while (not touchGameObj(newRow, newCol) and retryCounter<=10);

    if(retryCounter >= 10){
        cout<<"Unable to move after 10 try"<<endl;
        return; 
    }

    if(newRow - this->getZombieRow() < 0 and
        newCol == this->getZombieCol()){
        cout<<"Zombie "<<this->getZombieLogo()<<" moves up."<<endl;
    }
    else if (newRow - this->getZombieRow() > 0 and
            newCol == this->getZombieCol()){
            cout<<"Zombie "<<this->getZombieLogo()<<" moves down."<<endl;
    }
    else if(newRow == this->getZombieRow() and
            newCol - this->getZombieCol() < 0){
            cout<<"Zombie "<<this->getZombieLogo()<<" moves left."<<endl;
    }
    else if(newRow == this->getZombieRow() and
            newCol - this->getZombieCol() > 0){
            cout<<"Zombie "<<this->getZombieLogo()<<" moves right."<<endl;
    }

    this->setLocation(newRow, newCol);
}




bool Zombie::moveValidation(int newRow, int newCol){
    // Check if the next movement at boarder
    int boardRow = pf::getBoardRow();
    int boardCol = pf::getBoardCol();
    //cout<<"Next: "<<newRow<<","<<newCol<<endl;
    if(newRow < 0){
        cout<<"Zombie Hit Top Border"<<endl;
        return false;
    }
    else if (newCol < 0 ){
        cout<<"Zombie Hit Left Border"<<endl;
        return false;
    }
    else if (newRow >= boardRow){
        cout<<"Zombie Hit Bottom Border"<<endl;
        return false;
    }
    else if (newCol >= boardCol){
        cout<<"Zombie Hit Right Border"<<endl;
        return false;
    }
    bool validity = pf::validLocation(newRow, newCol);

    return validity;
}

bool Zombie::touchGameObj(int newRow, int newCol){
    char touchable[] = {' ','^','V','<','>','h','p','r'};
    for (char i: touchable){
        if (i == pf::getBoardChar(newRow, newCol)) {
            return true;
        }
    }
    return false;
}

Alien Zombie::attackAlien(){
    Alien alienPlayer = pf::getAlienPlayer(); // copy of alien
    int distance = pf::pointDistance(this->ZombieRow, this->ZombieRow, alienPlayer.getAlienRow(), alienPlayer.getAlienCol());
    if(distance <= this->Range){
        int alienLife = alienPlayer.getLife();
        alienLife -= this->Attack; 
        alienPlayer.setLife(alienLife);
        cout<<"Zombie "<<this->getZombieLogo() <<" attacked Alien with damage of "<<this->Attack<<endl;
    }
    return alienPlayer; 
}