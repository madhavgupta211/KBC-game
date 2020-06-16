#include <stdio.h>
#include <conio.h>
/* getch() */
#include "fundamentalsc.h"     
/* custom header file called to use:
   display_intro()
   admin_login() 
   admin_menu()
   play_game()
*/
#include <stdbool.h>          //used to treat bool values as language literals
#define NO_OF_ATTEMPTS 5      //no. of attempts to login
#define PASSWORD "cholosolo"  //change admin's password from here

int main()
{
    int access_type = 1;     
    /* Intro screen provides user with three options
       admin access(1),play game(2),exit application(3).
       access_type stores the option chosen by the user to guide him to the correct window
       using if-else block. Default value intitialized as one so as to make the control
       enter inside the while loop atleast once.*/                            
    while(access_type!=3)
    {
        access_type = display_intro();
        if(access_type==1)
        {
            bool admin_access_status = false;          // is assigned true only when user enters correct password in admin_login()
            for(int i = NO_OF_ATTEMPTS; i > 0; i--)
            {
                admin_access_status = admin_login(PASSWORD,i);
                if(admin_access_status)               // checks if user entered correct password in the attempt
                {
                    break;         // if user entered correct password in (n-i)th attempt, transfer control to admin window
                }
            }
            if(admin_access_status == false) //if password entered incorrectly after all attempts 
            {
                printf("\nAccess Denied!! No attempts left!! Returning..");
                access_type = 3;
            }
            else
            {
                int admin_menu_action = 1;
                /* Admin_menu offers three options to the user:
                   Add question(1),Remove question(2),exit admin mode(3)
                   default value 1 assigned so the loop can run atleast once */
                printf("\nAccess granted.");
                getch();
                while(admin_menu_action != 3)
                {
                    admin_menu_action = admin_menu();
                }
            }
            
        }
        else if(access_type == 2)
        {
            char game_continue = 'y';   // if user wants to play again, corresponding input is taken and the loop keeps running
            int prize_money = 0;        // final prize money won in the last game
            while(game_continue == 'y' || game_continue == 'Y')
            {
                prize_money = play_game();
                printf("\nYou cashed out with Rs. %d ",prize_money);  
                printf("\nWant to play again ? (y/n)");
                scanf("%c",&game_continue);     //will keep on restarting the game until input !y
            }
        }
    }
    return 0;
}