//fundamentals.h file
#ifndef _fundamentals_h
#define _fundamentals_h
#include <iostream>
#include <Windows.h> //for getting the rows and columns of terminal window
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <conio.h>
#include "database_class.h"

// display_intro asks from the user whether he wants to access
// developer page or just wants to play the game
// returns 1 if admin page is chosen, 2 otherwise  
int display_intro()
{
    system("cls");
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
    std::string exit = "3. Exit the Application";
    std::cout<<std::setw((columns/2)+admin.length()/2)<<std::right<<std::setfill(' ');
    std::cout<< admin;
    std::cout<<"\n";
    std::cout<<std::setw((columns/2)+game.length()/2)<<std::right<<std::setfill(' ');
    std::cout<< game;
    std::cout<<"\n";
    std::cout<<std::setw((columns/2)+exit.length()/2)<<std::right<<std::setfill(' ');
    std::cout<< exit;
    std::cout<<"\n";
    std::cout<<std::setw(columns/2)<<std::right<<std::setfill(' ');
    std::cout<<" ";
    std::cin>>access_value;
    return access_value;
}

// admin_login displays the login screen for admin framework and asks for password
//return true if login successful, otherwise false
bool admin_login(std::string password, int no_of_attempts)
{
    system("cls");
    CONSOLE_SCREEN_BUFFER_INFO csbi;   //windows.h object
    int rows,columns,compare_result;
    char password_single;
    std::string input_text;                                              //password entered by user to be checked                  
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
    std::string number = "No. of attempts remaining :";
    std::cout<<std::setw((columns/2)+number.length()/2)<<std::right<<std::setfill(' ');
    std::cout<<number<<" "<<no_of_attempts;
    std::cout<<"\n";
    std::string enter = "Enter Password:";
    std::cout<<std::setw((columns/2)+enter.length()/2)<<std::right<<std::setfill(' ');
    std::cout<<enter;
    password_single=getch();                                            // takes input the password from user
    while(password_single != 13)
    {
        input_text.push_back(password_single);
        std::cout<<"*";
        password_single=getch();
    }
    compare_result = input_text.compare(password);
    if(compare_result==0)
    {
        return true;
    }
    std::cout<<"Access Denied! Try again";
    getch();
    return false;
}

int admin_menu()
{
    system("cls");
    CONSOLE_SCREEN_BUFFER_INFO csbi;   //windows.h object
    int rows,columns,action_choice;                  
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
    std::string add = "1. Add a question";
    std::cout<<std::setw((columns/2)+add.length()/2)<<std::right<<std::setfill(' ');
    std::cout<<add<<"\n";
    std::string remove = "2. Remove a question";
    std::cout<<std::setw((columns/2)+remove.length()/2)<<std::right<<std::setfill(' ');
    std::cout<<remove<<"\n";
    std::string exit = "3. Exit admin mode";
    std::cout<<std::setw((columns/2)+exit.length()/2)<<std::right<<std::setfill(' ');
    std::cout<<exit<<"\n";
    std::cout<<std::setw(columns/2)<<std::right<<std::setfill(' ');
    std::cout<<" ";
    std::cin>>action_choice;
    if(action_choice==1)
    {
        add_question();
    }
    else if(action_choice==2)
    {
        remove_question();
    }
    return action_choice;
}

void display_rules()
{
    system("cls");
    CONSOLE_SCREEN_BUFFER_INFO csbi;   //windows.h object
    int rows,columns;                  
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
    std::cout<<"1. The game contains "<<NO_OF_LEVELS<<" which get progressively difficult.";
    std::cout<<"\n2. Answering each question correctly grants you more and more prize. there are "<<SAFE_LEVELS<<"safe-questions in the game. They are at:";
    std::cout<<"\n\t - Q2. Rs. 10,000\n\t - Q7 Rs. 3,20,000";
    std::cout<<"\n3. Every question has 4 options. To respond to a question, write the option no. (1-4) in the space provided.";
    std::cout<<"\n4. Till Q2, there is a 30 second timer, after that a 45 second timer till Q7. Then the timer will be removed.";
    std::cout<<"\n5. If the question is answered incorrectly, the game ends and the prize money corresponds to last safe-question crossed.";
    std::cout<<"\n6. There are 2 lifelines, 50-50 and change-the-question. To use 50-50, enter f as answer. To use the latter, enter c.";
    std::cout<<"\n7. If you dont want to attempt a question and want to quit with the prize money you have, enter answer as q";
    std::cout<<"\nPress enter to begin the game.";
    return;
}

int play_game()
{
    game_data storage;
    display_rules();
    return 0;
}
#endif