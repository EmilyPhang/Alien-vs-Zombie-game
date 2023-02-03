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
#include "Zombie.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

namespace pf
{
    // Create 2D char array
    static int boardRow;
    static int boardCol;
    static int zombieCount;
    static char **kBoardPointer;
    static Alien alienPlayer = Alien('A');  //initial constructor
    static Zombie *zombiePlayer;

    int getBoardRow()
    {
        return boardRow;
    }

    int getBoardCol()
    {
        return boardCol;
    }

    int getZombieCount()
    {
        return zombieCount;
    }
    Zombie* getZombiePlayer()
    {
        return zombiePlayer;
    }
    Alien getAlienPlayer(){
        return alienPlayer;
    }

    static string horozontalBoarder(string s, int n)
    {
        string repeat;

        for (int i = 0; i < n; i++)
            repeat += s;

        // If odd number add another one at the end
        if (n % 2 == 1)
            repeat += s[0];

        return repeat;
    }

    static string onesColumnCount(int n)
    {
        string repeat;

        for (int i = 0; i < n; i++)
            repeat += " " + to_string((i + 1) % 10);

        return repeat;
    }

    static string tensColumnCount(int n)
    {
        string repeat;

        for (int i = 0; i < n; i++)
            if ((i + 1) / 10 == 0)
            {
                repeat += "  ";
            }
            else
            {
                repeat += " " + to_string(int((i + 1) / 10));
            }

        return repeat;
    }

    int ClearScreen()
    {
#if defined(_WIN32)
        return std::system("cls");
#elif defined(__linux__) || defined(__APPLE__)
        return std::system("clear");
#endif
    }

    int Pause()
    {
#if defined(_WIN32)
        return std::system("pause");
#elif defined(__linux__) || defined(__APPLE__)
        return std::system(R"(read -p "Press any key to continue . . . " dummy)");
#endif
    }

    void CreateGameBoard(int kRows, int kColumns, int zombie_count)
    {
        // Generate random seed
        srand(time(0));

        // Constant row and Column for init 2D array
        const int kRows_const = kRows;
        const int kColumns_const = kColumns;

        pf::boardRow = kRows;
        pf::boardCol = kColumns;
        pf::zombieCount = zombie_count;

        // Create 2D char array Rows
        kBoardPointer = new char *[kRows_const];

        // Create 2D char array Column for each column
        for (int i = 0; i < kRows_const; i++)
        {
            kBoardPointer[i] = new char[kColumns_const];
        }

        // Generate the body of the Array
        for (int row = 0; row < kRows_const; row++)
        {
            for (int col = 0; col < kColumns_const; col++)
            {
                // for random item inside the board/2d array
                int random_number = std::rand() % 8;
                pf::kBoardPointer[row][col] = CreateGameObj(random_number);
            }
        }
        // if(pf::getBoardChar(0,0)=='.'){
        //     cout<<"nooooo"<<endl;
        // }
        pf::CreateAlien(kRows_const, kColumns_const);
        // if(pf::getBoardChar(0,0)=='.'){
        //     cout<<"nooooo1"<<endl;
        // }
        pf::CreateZombie(kRows_const, kColumns_const, zombie_count);

        
    }

    void CreateAlien(int kRows, int kColumns)
    {
        // Generate Alien
        pf::alienPlayer = Alien('A');       // Actual constructor to create the location with the board
        pf::updateBoard(pf::alienPlayer.getAlienRow(), pf::alienPlayer.getAlienCol(), pf::alienPlayer.getAlienLogo());
        // int alienRow = kRows % 2 == 1 ? kRows / 2 : kRows / 2 + 1;
        // int alienCol = kColumns % 2 == 1 ? kColumns / 2 : kColumns / 2 + 1;
        // pf::alienPlayer.setLocation(alienRow, alienCol);
        // pf::alienPlayer.setAlienRow(alienRow);
        // pf::alienPlayer.setAlienCol(alienCol);
        // pf::updateBoard(alienRow, alienCol, pf::alienPlayer.getAlienLogo());
    }

    void CreateZombie(int kRows, int kColumns, int zombie_count)
    {
        pf::zombiePlayer = new Zombie[zombie_count];
        // Generate Zombie
        for (int zombie_index = 0; zombie_index < zombie_count; zombie_index++)
        {
            pf::zombiePlayer[zombie_index] = Zombie(char(zombie_index + 49),0 ,0);
            int range = max(rand() % (min(kRows, kColumns)), 1);
            pf::zombiePlayer[zombie_index].setRange(range);
            int zombieRow, zombieCol; 
            bool validity = true; 
            while(validity){
                zombieRow = std::rand() % kRows;
                zombieCol = std::rand() % kColumns;
                cout<<"hihi" << zombieRow <<","<<zombieCol<<endl;
                validity = validLocation(zombieRow,zombieCol);
                cout<<"Valid: "<<validity<<endl;
            }
           

            pf::zombiePlayer[zombie_index].setZombieRow(zombieRow);
            pf::zombiePlayer[zombie_index].setZombieCol(zombieCol);
            pf::updateBoard(zombieRow, zombieCol, pf::zombiePlayer[zombie_index].getZombieLogo());
        }
    }

    char CreateGameObj(int random_number)
    {
        if (random_number == 0)
            return ' ';

        else if (random_number == 1)
            return '^';

        else if (random_number == 2)
            return 'v';

        else if (random_number == 3)
            return '>';

        else if (random_number == 4)
            return '<';

        else if (random_number == 5)
            return 'h';

        else if (random_number == 6)
            return 'p';

        else if (random_number == 7)
            return 'r';
        return ' ';
    }

    bool validLocation(int newRow, int newCol){
        Zombie* zombiePlayer =  pf::getZombiePlayer();
        Alien alienPlayer = pf::getAlienPlayer(); 
        cout<<endl;
        cout<<"Next: "<<newRow <<","<<newCol<<endl;
        cout<<"Alien: "<<alienPlayer.getAlienRow()<<","<< alienPlayer.getAlienCol()<<endl;
        for(int i=0; i<pf::getZombieCount(); i++){
            cout<<"Zombie "<<i<<" : "<<zombiePlayer[i].getZombieRow()<<","<<zombiePlayer[i].getRange()<<endl;
            if (alienPlayer.getAlienRow() == newRow and
                alienPlayer.getAlienCol() == newCol )
                {
                    cout<<"Retry"<<endl;
                    return true; 
                }
            if(
                zombiePlayer[i].getZombieRow() == newRow and 
                zombiePlayer[i].getZombieCol() == newCol 
                ){
                    cout<<"Retry"<<endl;
                    return true; 
                }
        }
        return false; 
    }

    void passTurn(){
        cout<<"Passing world"<<endl;
        if(pf::alienPlayer.getIsMyTurn()){
            //Alien to Zombie
            pf::alienPlayer.setIsMyTurn(false);
            // Search for a valid zombie to pass to
            for(int i =0 ; i<pf::getZombieCount() ; i++){
                if (pf::zombiePlayer[i].getLife()>0){
                    cout<<"Alien pass to Zombie "<<i+1<<endl;
                    pf::zombiePlayer[i].setIsMyTurn(true);
                    return ; 
                }
            }
        }
        else{
            //Zombie to Zombie
            for(int i =0 ; i<pf::getZombieCount() ; i++){
                if(pf::zombiePlayer[i].getIsMyTurn()){
                    pf::zombiePlayer[i].setIsMyTurn(false);
                    // i is current i+1 is next
                    for(int next = i+1 ; next <= pf::getZombieCount() ; next++){
                         //Last zombie pass back to alien
                        if(next==pf::getZombieCount()){
                            cout<<"Zombie "<<pf::zombiePlayer[i].getZombieLogo()<<" pass to Alien"<<endl;
                            pf::alienPlayer.setIsMyTurn(true);
                            return ; 
                        }
                        if(pf::zombiePlayer[next].getLife()>0){
                            cout<<"Zombie "<<pf::zombiePlayer[i].getZombieLogo()<<" pass to Zombie "<<pf::zombiePlayer[next].getZombieLogo()<<endl;
                            pf::zombiePlayer[next].setIsMyTurn(true);
                            return ; 
                        }
                    }
                }
            }
        }
    }

    char getBoardChar(int row, int col)
    {
        return pf::kBoardPointer[row][col];
    }

    void updateBoard(int row, int col, char logo)
    {
        pf::kBoardPointer[row][col] = logo;
    }

    void resetBoard()
    {
        int kRows = pf::boardRow;
        int kColumns = pf::boardCol;

        for (int row = 0; row < kRows; row++)
        {
            for (int col = 0; col < kColumns; col++)
            {
                if (pf::kBoardPointer[row][col] == '.')
                {
                    int random_number = std::rand() % 8;
                    pf::kBoardPointer[row][col] = CreateGameObj(random_number);
                }
            }
        }
        pf::kBoardPointer[pf::alienPlayer.getAlienRow()][pf::alienPlayer.getAlienCol()] = pf::alienPlayer.getAlienLogo();
    }

    void ShowGameBoard()
    {
        int kRows = pf::boardRow;
        int kColumns = pf::boardCol;
        int width = kRows % 2 == 1 ? kRows / 2 : kRows / 2 + 1;
        //kRows % 2 == 1 ? kRows / 2 : kRows / 2 + 1;
        //cout <<setw((kColumns)*2);
        cout <<setw(29);
        cout << ".: Alien vs Zombie :. " << endl;
        for (int row = 0; row < kRows; row++)
        {
            std::cout << "\t" << pf::horozontalBoarder("+-", kColumns) << endl;
            for (int col = 0; col < kColumns; col++)
            {
                if (col == 0)
                {
                    std::cout << row + 1 << "\t";
                }
                std::cout << "|" << pf::kBoardPointer[row][col];
                // if (pf::kBoardPointer[row][col]=='^')
                // {
                //     cout<<"up!!!"<<row<<","<<col<<endl;
                // }
                
            }
            std::cout << "|" << std::endl;
        }
        // Last row of horizontal bar
        std::cout << "\t" << pf::horozontalBoarder("+-", int(kColumns / 2) * 2 + 1) << endl;
        std::cout << "\t" << pf::tensColumnCount(int(kColumns)) << endl;
        std::cout << "\t" << pf::onesColumnCount(int(kColumns)) << endl
                  << endl;

        pf::alienPlayer.printDescription();
        // cout<<"Alien "<<pf::alienPlayer.getAlienLogo()<<" : "<<pf::alienPlayer.getAlienRow()<<" , "<<pf::alienPlayer.getAlienCol()<<endl;
        for (int zombie_index = 0; zombie_index < pf::zombieCount; zombie_index++)
        {
            pf::zombiePlayer[zombie_index].printDescription();
            // cout<<"Zombie "<< pf::zombiePlayer[zombie_index].getZombieLogo() <<" : " << pf::zombiePlayer[zombie_index].getZombieRow() <<" , "<<pf::zombiePlayer[zombie_index].getZombieCol()<<endl;
        }
        
    }

    void saveBoard(){
        cout<<"saving"<<endl;
        ofstream myfile;
        int kRows = pf::boardRow;
        int kColumns = pf::boardCol;
        myfile.open ("board.txt");
                
        myfile<<alienPlayer.getIsMyTurn()<<","<<alienPlayer.getLife()<<","<<alienPlayer.getAttack()<<endl;
        for (int i = 0; i < pf::getZombieCount(); i++){
            myfile<<zombiePlayer[i].getIsMyTurn()<<","<<zombiePlayer[i].getLife()<<","<<zombiePlayer[i].getAttack()<<","<<zombiePlayer[i].getRange()<<endl;
        }
        myfile<<"===\n";
        for (int row = 0; row < kRows; row++)
        {
            for (int col = 0; col < kColumns; col++)
            {
                myfile<<getBoardChar(row, col);
            }
            myfile<<"\n";
        }

        myfile.close();
    }

    void loadBoard(){
        cout<<"loading"<<endl;
        string line;
        int numRows=0;    // Variable to keep count of each line
        int rowCount = 0; 
        int numZombie = 0;
        bool boardInfo = false; 
        // Read from the text file
        ifstream ReadLineFile("board.txt");

        // Get Row in file
        if(ReadLineFile.is_open())
        {
            while(ReadLineFile.peek()!=EOF)
            {
                getline(ReadLineFile, line);
                if(line == "==="){
                    boardInfo = true;
                }
                if(boardInfo){
                    numRows++;
                }
                else{
                    numZombie++;
                }
            }
            ReadLineFile.close();
        }
        else
            cout<<"Couldn't open the file\n";

        numZombie -= 1; // Remove alien 
        numRows -= 1; // Remove "==="
        cout<<"Number of lines in the file are: "<<numRows<<endl;
        cout<<"Number of Zombie: "<<numZombie<<endl;

        // create board 2d array
        kBoardPointer = new char *[numRows];         //row
        for (int i = 0; i < numRows; i++)
        {
            kBoardPointer[i] = new char[line.length()];     //cols
        }
        pf::zombiePlayer = new Zombie[numZombie];
        pf::boardRow = numRows;
        pf::zombieCount = numZombie;

        ifstream ReadContentFile("board.txt");
        boardInfo = false; 
        int zombieCounter = 0; 
        rowCount = 0;
        if(ReadContentFile.is_open())
        {
            while(ReadContentFile.peek()!=EOF)
            {
                getline(ReadContentFile, line);
                
                if(line=="==="){
                    boardInfo = true; 
                }
                if(boardInfo){
                    // Load board
                    if(line != "==="){
                        for(int col=0; col<line.length(); col++){
                            if (line[col] =='A'){
                                pf::alienPlayer.setAlienRow(rowCount);
                                pf::alienPlayer.setAlienCol(col);
                                pf::updateBoard(rowCount, col, pf::alienPlayer.getAlienLogo());
                            }
                            else if (isdigit(line[col])){
                                int zombieIndex = line[col]- 49 ; 
                                pf::zombiePlayer[zombieIndex].setZombieRow(rowCount);
                                pf::zombiePlayer[zombieIndex].setZombieCol(col);
                                pf::updateBoard(rowCount, col, pf::zombiePlayer[zombieIndex].getZombieLogo());
                            }
                            pf::kBoardPointer[rowCount][col] = line[col];
                        }
                        rowCount++;
                        pf::boardCol = line.length();
                    }
                }
                else if(isdigit(line[0])){
                    // load player
                    vector<string> v;
                    bool isMyTurn; 
                    int life, attack, range; 
                    stringstream ss(line);
                    while (ss.good()) {
                        string substr;
                        getline(ss, substr, ',');
                        v.push_back(substr);
                    }
                    // Alien status 
                    if(v.size() == 3){
                        istringstream(v[0]) >> isMyTurn; 
                        istringstream(v[1]) >> life; 
                        istringstream(v[2]) >> attack; 
                        // cout<<"Alien: "<<isMyTurn << "<" <<life << "," <<attack<<endl;
                        alienPlayer.setIsMyTurn(isMyTurn);
                        alienPlayer.setLife(life);
                        alienPlayer.setAttack(attack);
                    }
                    // Zombie status
                    else if (v.size() == 4){
                        istringstream(v[0]) >> isMyTurn; 
                        istringstream(v[1]) >> life; 
                        istringstream(v[2]) >> attack; 
                        istringstream(v[3]) >> range; 
                        // cout<<"Zombie "<<zombieCounter<<" is created"<<endl;
                        pf::zombiePlayer[zombieCounter] = Zombie(char(zombieCounter + 49), isMyTurn, life, attack, range);
                        zombieCounter++; 
                    }
                    v.clear();
                }
                
            }
        
            ReadContentFile.close();
        }
        else
            cout<<"Couldn't open the file\n";
    }

    void arrowChange(int targetRow, int targetCol, std::string targetDirection){
        char targetChar;
        char currentChar = getBoardChar(targetRow, targetCol);

        if(
            currentChar == '^' or
            currentChar == 'v' or
            currentChar == '<' or
            currentChar == '>' 
        ){
            if (targetDirection == "up"){
                targetChar = '^';
            }
            else if (targetDirection == "down"){
                targetChar = 'v';
            }
            else if (targetDirection == "left"){
                targetChar = '<';
            }
            else if (targetDirection == "right"){
                targetChar = '>';
            }
            else{
                cout<<"Diretion Invalid"<<endl; 
                return; 
            }
            
            cout<< "Arrow "<< currentChar <<" is switched to ."<<targetChar;
            pf::updateBoard(targetRow, targetCol, targetChar);
            cout<<"\nPress any key to continue . . .  "<<endl;
            cin.ignore();
            cin.get();
        }
        else{
            cout<<"Target Area is not an arrow"<<endl;
            return ;
        }
    }

    int pointDistance(int x1, int y1, int x2, int y2){
        return (pow((x2-x1),2 ) + pow((y2-y1),2));
    }



    void StartGame()
    {
        bool toQuit = false;
        
        while (not toQuit)
        {
            // cout<<"hoho" <<pf::zombiePlayer[0].getZombieRow()<<" , "<<pf::zombiePlayer[0].getZombieCol()<<endl;
            // cout<<"hoho" <<pf::zombiePlayer[1].getZombieRow()<<" , "<<pf::zombiePlayer[1].getZombieCol()<<endl;
            // cout<<"hoho" <<pf::zombiePlayer[2].getZombieRow()<<" , "<<pf::zombiePlayer[2].getZombieCol()<<endl;
            pf::ShowGameBoard();
            string command, anyKey;
            cout << "command:";
            cin >> (command);
            
            if (command == "quit")
            {
                toQuit = true;
            }
            else if (command == "help")
            {
                cout << endl;
                cout << "Commands" << endl;
                cout << "1. up      -Move up." << endl;
                cout << "2. down    -Move down." << endl;
                cout << "3.left     -Move left." << endl;
                cout << "4.right    -Move right." << endl;
                cout << "5.arrow    -Change the direction of an arrow." << endl;
                cout << "6.help     -Display these user commands." << endl;
                cout << "7.save     -Save the game." << endl;
                cout << "8.load     -Load a game." << endl;
                cout << "9.quit     -Quit the game" << endl;
                cout<<"Press any key to continue . . . \n ";
                cin.ignore();
                cin.get();
                cin.clear();
                // pf::ShowGameBoard();
                // string userHelp;
                // cout << "Help Command:";
                // cin >> (userHelp); 
                //pf::ShowGameBoard();
            }
            else if(command == "save"){
                saveBoard();
            }
            else if (command =="load"){
                loadBoard();
            }
            else if (command =="arrow"){
                int targetRow, targetCol;
                string direction; 
                cout<<"Enter row, column, and direction:"<<endl;
                cin >> targetRow >>targetCol >> direction; 
                arrowChange(targetRow-1, targetCol-1, direction);
            }
            if(command=="left" or command=="right" or command =="up" or command=="down"){
                // Find who's turn
                if (pf::alienPlayer.getIsMyTurn())
                {   
                    bool toWin = false;
                    // Alien Turn
                    if (pf::alienPlayer.move(command) == false)
                    {
                        // change turn when move is false
                        cout << "(Player) Press any key to continue . . .  \n";
                        cin.ignore();
                        cin.get();
                        cin.clear();
                        pf::alienPlayer.setAttack(0);
                        //Check if Alien wins
                        
                        for (int i = 0; i < pf::getZombieCount(); i++){
                            if(pf::zombiePlayer[i].getLife()!=0){
                                toWin = false;
                                break;
                                }
                            else {
                                toWin = true;
                                continue;
                                }
                            }
                        }
                        if (toWin == true){
                            
                            break;
                        }
                        pf::resetBoard();
                        pf::passTurn();
                    }
                }
                
                for (int i = 0; i < pf::getZombieCount(); i++)
                {
                    if (pf::zombiePlayer[i].getIsMyTurn() and pf::zombiePlayer[i].getLife()>0)
                    {
                        pf::ShowGameBoard();
                        pf::zombiePlayer[i].move();
                        pf::alienPlayer = pf::zombiePlayer[i].attackAlien();
                        cout << "(Player) Press any key to continue . . .  \n";
                        cin.ignore();
                        cin.get();
                        cin.clear();
                        int alienLife = alienPlayer.getLife();
                        if(alienLife ==0){
                            pf::ShowGameBoard();

                            cout<< "Alien died. Game over." << endl;

                            break; //////////////////////
                        }
        
                        pf::passTurn();

                        cout << "(Player) Press any key to continue . . .  \n";
                        cin.ignore();
                        cin.get();
                        cin.clear();
                    }
                }
                int alienLife = alienPlayer.getLife();
                if(alienLife ==0){
                    break;
                    }
                }
            }


            }
        
    

