// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT4L 
// Names: EMILY PHANG RU YING | LIM CAI QING | TEO YU JIE 
// IDs: 1211102687 | 1211102753 | 1211102751 
// Emails: 1211102687@student.mmu.edu.my | 1211102753@student.mmu.edu.my | 1211102751@student.mmu.edu.my 
// Phones: 0122270304 | 0143001623 | 0122615818 
// ********************************************************* 

#include "pf/helper.h"
#include <iostream>
using namespace std;

void DisplayGameSettings(int row,int col,int zombie_count)
{
    cout << "DEFAULT GAME SETTINGS" << endl;
    cout << "---------------------" << endl;
    cout << "Board  Rows   : " << row << endl; // need to add cout for inputed rows..
    cout << "Board  Columns: " << col << endl;
    cout << "Zombie Count  : " << zombie_count << endl;
    cout << "\nDo you wish to change the game settings (y/n)? => ";
}

int main()
{   
    int row = 5 ; //default
    int col = 21 ; //default
    int zombie_count = 3 ; //default
    bool setting_option = false ; 
    string option = "N";
    cout << "Assignment (Part 1)" << endl;
    cout << "Let's Get Started!" << endl;
    DisplayGameSettings(row, col, zombie_count);
    cin >> option;
    // cout << endl;
    if ((option == "Y") || (option == "y"))
    {
        setting_option = true;
    }
    //cout << setting_option; //need to remove
    if(setting_option == true)
    {   
        int i = 0;
        cout << "Board Settings" <<endl;
        cout << "--------------" << endl;
        while (i == 0)
          {
            cout << "Enter Rows => ";
            cin >> row;

            if (row % 2 == 0)
            {
              i = 0;
              cout << " Pls fill an odd number " << endl;
              continue;
            }
            else 
            {
              i = 1;
              break;
            }
            
          }
        
        /*if (row%2 == 0){
          cout << "Please enter an odd number"
        }*/
      
        /*cout << "Enter columns => " ;
        cin >> col;*/
        i = 0;
        while (i == 0)
          {
            cout << "Enter columns => ";
            cin >> col;

            if (col % 2 == 0)
            {
              i = 0;
              cout << " Pls fill an odd number " << endl;
              continue;
            }
            else 
            {
              i = 1;
              break;
            }
            
          }
        cout << endl;
        
        i = 0;
        while (i == 0)
          {
            cout << "Zombie Settings" <<endl;
            cout << "---------------" << endl;
            cout << "Enter number of zombies => " ;
            cin >> zombie_count;
            cout << endl;
            if (zombie_count == 0 | zombie_count > 9)
            {
              i = 0;
              cout << "Please enter a number from 1 to 9." << endl;
              cout << endl;
              continue;
            }
            else 
            {
              i = 1;
              break;
            }
          }
        cout << endl;
        cout << "Settings Updated.\n" ;
        cout << endl;
        
        pf::Pause();
    }
    
    //DisplayGameSettings(row, col, zombie_count); //remove
    pf::CreateGameBoard(row, col, zombie_count);
    // pf::ShowGameBoard();
        
    pf::StartGame();
    //pf::Pause();
}