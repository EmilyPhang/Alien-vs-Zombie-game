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
    Zombie *getZombiePlayer()
    {
        return zombiePlayer;
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
            pf::zombiePlayer[zombie_index] = Zombie(char(zombie_index + 49));
            int range = max(rand() % (min(kRows, kColumns)), 1);
            pf::zombiePlayer[zombie_index].setRange(range);
            int zombieRow, zombieCol; 
            do
            {
                zombieRow = std::rand() % kRows;
                zombieCol = std::rand() % kColumns;
            } while (zombieRow == pf::alienPlayer.getAlienRow() and zombieCol == pf::alienPlayer.getAlienCol());
            

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
        cout <<setw((kColumns)*2);
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

        for (int zombie_index = 0; zombie_index < pf::zombieCount; zombie_index++)
        {
            pf::zombiePlayer[zombie_index].printDescription();
        }
    }

    void saveBoard(){
        cout<<"saving"<<endl;
        ofstream myfile;
        int kRows = pf::boardRow;
        int kColumns = pf::boardCol;
        myfile.open ("board.txt");
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

        // Read from the text file
        ifstream ReadLineFile("board.txt");

        // Get Row in file
        if(ReadLineFile.is_open())
        {
            while(ReadLineFile.peek()!=EOF)
            {
                getline(ReadLineFile, line);
                numRows++;
            }
        
            ReadLineFile.close();
        }
        else
            cout<<"Couldn't open the file\n";

        cout<<"Number of lines in the file are: "<<numRows<<endl;
        // create board 2d array
        kBoardPointer = new char *[numRows];         //row
        for (int i = 0; i < numRows; i++)
        {
            kBoardPointer[i] = new char[line.length()];     //cols
        }

        ifstream ReadContentFile("board.txt");
        rowCount = 0; 
        if(ReadContentFile.is_open())
        {
            while(ReadContentFile.peek()!=EOF)
            {
                getline(ReadContentFile, line);
                
                for(int col=0; col<line.length(); col++){
                    if (line[col] =='A'){
                        pf::alienPlayer.setAlienRow(rowCount);
                        pf::alienPlayer.setAlienCol(col);
                        pf::updateBoard(rowCount, col, pf::alienPlayer.getAlienLogo());
                    }
                    else if (isdigit(line[col])){
                        pf::zombiePlayer[line[col]-1].setZombieRow(rowCount);
                        pf::zombiePlayer[line[col]-1].setZombieCol(col);
                        pf::updateBoard(rowCount, col, pf::zombiePlayer[line[col]-1].getZombieLogo());
                    }
                    pf::kBoardPointer[rowCount][col] = line[col];
                    
                    cout<<line[col];
                    
                }
                cout<<endl;
                rowCount++;
            }
            cout<<"here"<<pf::kBoardPointer[0][0]<<endl;
        
            ReadContentFile.close();
        }
        else
            cout<<"Couldn't open the file\n";
    }

    void StartGame()
    {
        bool toQuit = false;
        
        while (not toQuit)
        {
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
            if(command=="left" or command=="right" or command =="up" or command=="down"){
                // Find who's turn
                if (pf::alienPlayer.getIsMyTurn())
                {
                    // Alien Turn
                    if (pf::alienPlayer.move(command) == false)
                    {
                        // change turn when move is false
                        cout << "(Player) Press any key to continue . . .  \n";
                        cin.ignore();
                        cin.get();
                        cin.clear();
                        //cout << "Alien's turn ends .The trail is reset." << endl;
                        //pf::ShowGameBoard();
                        //cout << "Alien's turn ends .The trail is reset." << endl;
                        //cout << "(Player) Press any key to continue . . .  \n";
                        //cin.ignore();
                        //cin.get();
                        //cin.clear();
                        pf::alienPlayer.setAttack(0);
                        pf::resetBoard();
                        pf::alienPlayer.setIsMyTurn(false);
                        pf::zombiePlayer[0].setIsMyTurn(true);
                    }
                }
                for (int i = 0; i < pf::getZombieCount(); i++)
                {
                    if (pf::zombiePlayer[i].getIsMyTurn())
                    {
                        pf::ShowGameBoard();
                        pf::zombiePlayer[i].move();
                        pf::zombiePlayer[i].setIsMyTurn(false);
                        if ((i + 1) % pf::getZombieCount() == 0)
                        {
                            pf::alienPlayer.setIsMyTurn(true);
                        }
                        else
                        {
                            pf::zombiePlayer[(i + 1) % pf::getZombieCount()].setIsMyTurn(true);
                        }

                        cout << "(Player) Press any key to continue . . .  \n";
                        cin.ignore();
                        //cin.get();
                        //cin.clear();
                    }
                }
            }
        }
    }
}
