//fundamentals.h file
#ifndef _fundamentals_h
#define _fundamentals_h
#include <iostream>
#include <Windows.h> //for getting the rows and columns of terminal window
#include <string>
#include <iomanip>

// display_intro asks from the user whether he wants to access
// developer page or just wants to play the game
// returns 1 if admin page is chosen, 2 otherwise  
int display_intro()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;   //windows.h object
    int rows,columns,access_value;                  
    GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;              //calculated the no. of rows and columns of the terminal window
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;                 //by using windows.h header file
    std::string title = "KBC: The Game";
    std::cout<<std::setw((columns/2)+title.length()/2)<<std::right<<std::setfill('*');  //center aligned the title line
    std::cout<< title;
    for(int i=0;i<((columns/2)-title.length()/2);i++)
    {
        std::cout<<"*";
    }
    std::cout<<"\n\n\n";
    std::string admin = "1. Admin Access";
    std::string game = "2. Play the game ";
    std::cout<<std::setw((columns/2)+admin.length()/2)<<std::right<<std::setfill(' ');
    std::cout<< admin;
    std::cout<<"\n";
    std::cout<<std::setw((columns/2)+game.length()/2)<<std::right<<std::setfill(' ');
    std::cout<< game;
    std::cout<<"\n";
    std::cout<<std::setw(columns/2)<<std::right<<std::setfill(' ');
    std::cout<<" ";
    std::cin>>access_value;
    return access_value;
}

#endif