#include <iostream> 
#include <conio.h>
#include "fundamentals.h"
#define NO_OF_ATTEMPTS 5      //no. of attempts to login
#define PASSWORD "cholosolo"  //change admin's password from here

using namespace std; 

int main()
{
    int access_type = 1;
    while(access_type!=3)
    {
        access_type = display_intro();                                   //displays start screen
        if(access_type==1)
        {
            bool admin_access_status = false;
            int admin_menu_action = 1;
            for(int i=NO_OF_ATTEMPTS;i>0;i--)
            {
                admin_access_status = admin_login(PASSWORD,i);            //handles login window
                if(admin_access_status)
                {
                    break;
                }
            }
            if(admin_access_status == false)
            {
                cout<<"\nAccess Denied!! No attempts left!! Exiting...";
                exit(1);
            }
            cout<<"\nAccess granted.";
            getch();
            while(admin_menu_action != 3)
            {
            admin_menu_action = admin_menu();
            }
        }
        else if(access_type == 2)
        {
            char game_continue = 'y';
            int prize_money=0;
            while(game_continue == 'y' || game_continue == 'Y')
            {
                prize_money = play_game();
                std::cout<<"\nYou cashed out with Rs. "<<prize_money;
                std::cout<<"\nWant to play again? (y/n)";
                std::cin>>game_continue;
            }
        }
    }
    return 0;
}