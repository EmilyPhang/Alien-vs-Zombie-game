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
#include "Alien.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
// #include <cstring>
using namespace std;

// Class Constructor
Alien::Alien(char Logo){
    this->Life = 100; 
    this->Attack = 0;
    this->AlienLogo = Logo;
    this->isMyTurn = true;  //Alien always start first
    int kRows = pf::getBoardRow();
    int kColumns = pf::getBoardCol();
    this->AlienRow = kRows % 2 == 1 ? kRows / 2 : kRows / 2 + 1;
    this->AlienCol = kColumns % 2 == 1 ? kColumns / 2 : kColumns / 2 + 1;
}


// Class Method (set)
void Alien::setLife(int newLife){
    this->Life = max(0, newLife);
}

void Alien::setAttack(int newAttack){
    this->Attack = newAttack;
};

void Alien::setAlienRow(int newAlienRow){
    this->AlienRow = newAlienRow;
}

void Alien::setAlienCol(int newAlienCol){
    this->AlienCol = newAlienCol;
}

void Alien::setLocation(int newRow, int newCol){
    //Old location
    pf::updateBoard(this->AlienRow, this->AlienCol, '.');
    // new Location
    this->AlienRow = newRow;
    this->AlienCol = newCol;
    pf::updateBoard(this->AlienRow, this->AlienCol, this->getAlienLogo());
}

void Alien::setIsMyTurn(bool newTurn){
    this->isMyTurn = newTurn; 
}



// Class Method (get)
int Alien::getLife(){
    return this->Life;
}

int Alien::getAttack(){
    return this->Attack;
}

int Alien::getAlienRow(){
    return this->AlienRow;
}

int Alien::getAlienCol(){
    return this->AlienCol;
}

char Alien::getAlienLogo(){
    return this->AlienLogo;
}

bool Alien::getIsMyTurn(){
    return this->isMyTurn;
}

//Printer
void Alien::printDescription(){
    string sentence = "Alien   : Life "+to_string(this->Life)+",\t\tAttack "+to_string(this->Attack);
    if (this->isMyTurn){
        cout<<" > "<<sentence<<endl;
    }
    else{
        cout<<"   "<<sentence<<endl;
    }
}

//Action
bool Alien::move(string command){
    // cout<<command;
    int newRow = this->getAlienRow();
    int newCol = this->getAlienCol();
    
    if(command == "up"){
        newRow -= 1; //up
    }
    else if(command == "down"){
        newRow += 1; //down
    }
    else if (command == "left"){
        newCol -= 1; //left
    }
    else if (command == "right"){
        newCol += 1; //right
    }
    //cout<<"Next: "<<newRow<<","<<newCol<<endl;
    // Get current location item
    bool valid = moveValidation(newRow, newCol);
    //cout<<"Valid: "<<valid<<endl;   
    
    if(valid){
        // cout<<"hihi"<<endl;
        string old_command = command;
        command = touchGameObj(command, newRow, newCol);
        if (command == "rock"){
            // Change Rock to '.' so that later the reset will random generate
            int random_number = std::rand() % 7;
            char newObj = pf::CreateGameObj(random_number);
            if (newObj==' '){
                cout << "Alien discovers nothing beneath the rock." << endl;
            }
            else if(newObj == '^'){
                cout<< "Alien discovers an up arrow beneath the rock."<<endl;
            }
            else if(newObj == 'v'){
                cout<< "Alien discovers a down arrow beneath the rock."<<endl;
            }
            else if(newObj == '>'){
                cout<< "Alien discovers a right arrow beneath the rock."<<endl;
            }
            else if(newObj == '<'){
                cout<< "Alien discovers a left arrow beneath the rock."<<endl;
            }
            else if(newObj == 'p'){
                cout<< "Alien discovers a pod beneath the rock."<<endl;
            }
            else if(newObj == 'h'){
                cout<< "Alien discovers a health pack beneath the rock."<<endl;
            }
            pf::updateBoard(newRow, newCol, newObj);
            pf::updateBoard(this->AlienRow, this->AlienCol, this->getAlienLogo());
            cout<<"Press any key to continue . . . \n";
            cin.ignore();
            cin.get();
            //cin.clear();
            pf::ShowGameBoard();
            cout << "Alien's turn ends .The trail is reset." << endl;
            return false;
            // cout<<"Press any key to continue . . . \n";
            // cin.ignore();
            // cin.get();
            // cin.clear();
            //pf::ShowGameBoard();

        }
        else if (command == "attack"){
            bool zombieAlive = attackZombie(newRow, newCol);
            if (zombieAlive){
                // end turn if zombie alive
                cout << "Press any key to continue . . .  ";
                cin.ignore();
                cin.get();
                pf::ShowGameBoard();
                // pf::getBoardChar(newRow, newCol);
                cout << "Alien's turn ends .The trail is reset." << endl;
                //cout<<"hehe"<<endl;
                return false;
            }
            else{
                bool toWin = false;
                Zombie* zombiePLayer = pf::getZombiePlayer();
                for (int i = 0; i < pf::getZombieCount(); i++){
                            if(zombiePLayer[i].getLife()!=0){
                                toWin = false;
                                break;
                                }
                            else {
                                toWin = true;
                                continue;
                                }
                            }
                if (toWin == true){
                            cout << "Congratulations all zombies are dead, Alien won!" <<endl;
                            return false;
                }

                // alien keep moving if zombie die
                // cout<<"hoho"<<endl;
                move(old_command);
                return false;
                }
            
        }
        //Move to new location
        setLocation(newRow, newCol);        

        // Wait for next step
        cout<<"(Alien) Press Enter to continue . . . ";
        cin.ignore();
        cin.get();
        cin.clear();
        pf::ShowGameBoard();
        //go to next
        move(command);
    }
    else {
        // cout<<"hoho"<<endl;
        // // Wait for next step
        // setLocation(newRow, newCol);
        cout<<"Press any key to continue . . .  ";
        cin.ignore();
        // //cin.get();
        //pf::ShowGameBoard();
        // // pf::getBoardChar(newRow, newCol);
        //cout<<"Alien hits a border."<<endl;
        // //cout<<"else..."<<endl;
        //cout<<"Press any key to continue . . .  ";
        //cin.ignore();
        pf::ShowGameBoard();
        // pf::getBoardChar(newRow, newCol);
        cout << "Alien's turn ends .The trail is reset." <<endl;
        return false; // Stop
    }
    return false;

}

bool Alien::moveValidation(int newRow, int newCol){ 
    // Check if the next movement at boarder
    int boardRow = pf::getBoardRow();
    int boardCol = pf::getBoardCol();
    // cout<<"Next: "<<newRow<<","<<newCol<<endl;

    if(newRow < 0){
        cout<<"Alien hit a top border."<<endl;
        // pf::getBoardChar(newRow, newCol);
        return false;
    }
    else if (newCol < 0 ){
        cout<<"Alien hit a left border."<<endl;
        // pf::getBoardChar(newRow, newCol);
        return false;
    }
    else if (newRow >= boardRow){
        cout<<"Alien hit a bottom border."<<endl;
        // pf::getBoardChar(newRow, newCol);
        return false;
    }
    else if (newCol >= boardCol){
        cout<<"Alien hit a right border."<<endl;
        // pf::getBoardChar(newRow, newCol);
        return false;
    }

    return true;
}

string Alien::touchGameObj(string command, int newRow, int newCol){
    char gameObj = pf::getBoardChar(newRow, newCol);
    if(gameObj == '<'){
        this->Attack += 20;
        cout<<"Alien finds a left arrow. "<<endl;
        cout<<"Alien's attack is increased by 20.\n\n";
        return "left";
    }
    if(gameObj == '>'){
        this->Attack += 20;
        cout<<"Alien finds a right arrow. "<<endl;
        cout<<"Alien's attack is increased by 20.\n\n";
        return "right";
    }
    if(gameObj == '^'){
        this->Attack += 20;
        cout<<"Alien finds an upward arrow. "<<endl;
        cout<<"Alien's attack is increased by 20.\n\n";
        return "up";
    }
    if(gameObj == 'v' ){
        this->Attack += 20;
        cout<<"Alien finds a downward arrow. "<<endl;
        cout<<"Alien's attack is increased by 20.\n\n";
        return "down";
    }
    if(gameObj == 'h'){
        this->setLife(this->Life += 20);
        cout<<"Alien finds a health pack."<<endl;
        cout<<"Alien's life is increased by 20.\n\n";
     
    }
    if(gameObj == 'p'){
        cout<<"Alien finds a pod."<<endl;
        this->podBlast(newRow, newCol);
    }
    if(gameObj == 'r'){
        cout<<"Alien stumbles upon a rock."<<endl;
        return "rock";
    }
    if(gameObj == ' '){
        cout<<"Alien finds a empty space.\n\n";
    }
    
    Zombie* zombiePLayer = pf::getZombiePlayer();
    for(int i=0; i<pf::getZombieCount(); i++){
        if(zombiePLayer[i].getLife() > 0 and 
            zombiePLayer[i].getZombieRow() == newRow and 
            zombiePLayer[i].getZombieCol() == newCol){
            cout<<"Alien attack Zombie "<<zombiePLayer[i].getZombieLogo() <<endl;
            return "attack";
        }
    }

    return command;
}

void Alien::podBlast(int newRow, int newCol){
    int minDistance = this->ZombieMinDistance(newRow, newCol);
    // cout<<"Min Distance: "<<minDistance<<endl;
    Zombie* zombiePLayer = pf::getZombiePlayer();
    for(int i=0; i<pf::getZombieCount(); i++){
        int zombieLife =  zombiePLayer[i].getLife(); 
        int alienZombieDistance = pf::pointDistance(newRow, newCol, 
                                                zombiePLayer[i].getZombieRow(), zombiePLayer[i].getZombieCol());
        if(newRow !=zombiePLayer[i].getZombieRow()){
            alienZombieDistance +=1;
        }
        // cout<<zombiePLayer[i].getZombieLogo()<<" : "<<alienZombieDistance<<endl;
        if(zombieLife > 0 and alienZombieDistance==minDistance ){
            cout<<"Zombie "<<zombiePLayer[i].getZombieLogo()<<" receives a damage of 10."<<endl;
            zombieLife-=10;
            zombiePLayer[i].setLife(zombieLife);
            break;
        }
    }
}

bool Alien::attackZombie(int newRow, int newCol){
    Zombie* zombiePLayer = pf::getZombiePlayer();
    for(int i=0; i<pf::getZombieCount(); i++){
        if(zombiePLayer[i].getLife() > 0 and 
            zombiePLayer[i].getZombieRow() == newRow and 
            zombiePLayer[i].getZombieCol() == newCol){
                int zombieLife = zombiePLayer[i].getLife();
                zombieLife -= this->Attack;
                zombiePLayer[i].setLife(zombieLife);
                if (zombieLife > 0 ){
                    // The zombie alive, turn continue
                    return true;
                }

        }
    }
    return false;
}

//Formula 
int Alien::ZombieMinDistance(int newRow, int newCol){
    Zombie* zombiePLayer = pf::getZombiePlayer();
    int minDistance = pf::getBoardRow() * pf::getBoardCol(); 
    for(int i=0; i<pf::getZombieCount(); i++){
        if(zombiePLayer[i].getLife() > 0){
            
            int alienZombieDistance = pf::pointDistance(newRow, newCol, 
                                                zombiePLayer[i].getZombieRow(), zombiePLayer[i].getZombieCol());
            if(newRow !=zombiePLayer[i].getZombieRow()){
            alienZombieDistance +=1;
        }
            //cout<<"Distance: "<<alienZombieDistance<<endl;
            minDistance = min(minDistance, alienZombieDistance);
        }
    }
    //cout<<"Min Distance: "<<minDistance<<endl;
    return minDistance;
}
