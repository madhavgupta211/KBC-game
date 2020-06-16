//fundamentalsc.h file
#ifndef _fundamentalsc_h
#define _fundamentalsc_h
#include <stdio.h>
#include <Windows.h>
//for getting the rows and columns of terminal window
#include <stdbool.h>
/* included to use standar bool macros */
#include <string.h>
/* strlen()
   strcat()
   strcmp() */
#include <stdlib.h>
/* system() 
   itoa()  */
#include <conio.h>
/* getch() */
#include <time.h>
/* time()  */
#include "database_classc.h"


// center_print() takes input a pointer to a char array and prints it out to stdout centrally aligned.
// it takes another argument, the fill character. Default value is set to whitespace
// third argument takes a bool value, to determine if follow up characters needed to be printed or not.
void center_print( char* x, char y, bool newline)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;   //windows.h object
    int rows,columns,length,fill_length;                  
    GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;              //calculated the no. of rows and columns of the terminal window
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;                 //by using windows.h header file
    length = strlen(x);
    fill_length = (columns/2) - (length/2);  //fill_length stores the no. of times fill character needs to be printed before and after the string input
    for( int i = 0; i < fill_length; i++)
    {
        printf("%c",y);  //printing fill character before the string
    }
    printf("%s",x);   // printing the string
    if(newline)
    {
        for( int i = 0; i < (fill_length - 1); i++)
        {
            printf("%c",y);  //printing fill character after the string
        }
        printf("\n");
    }
    return;
}

/* display_intro asks from the user whether he wants to access
   admin_page(1),play the game(2),exit the application(3)
   returns the value chosen by the user  */
int display_intro()
{
    system("cls");      //clears the display screen
    int access_value;   
    center_print(TITLE,'*',true);
    printf("\n\n");
    center_print("1. Admin Access",' ',true);
    center_print("2. Play the game",' ',true);
    center_print("3. Exit the application",' ',true);
    center_print(" ",' ',false);
    scanf("%d",&access_value);
    return access_value;
}

/* admin_login displays the login screen for admin framework and asks for password
   returns true if login is successful, otherwise false */
bool admin_login( char* password, int no_of_attempts)
{
    system("cls");
    int compare_result;    //0 if pasword matches, non-zero otherwise
    int text_counter = 0;
    center_print(TITLE,'*',true);
    char password_single;  //takes in password input by user character by character using 
    char input_text[25];   //stores the text entered by user
    printf("\n\n");       
    char attempt_count[50] = "No. of attempts remaining : " ;
    char numerix[3] ;     
    itoa(no_of_attempts,numerix,10);    //converting integer to char string
    strcat(attempt_count, numerix);
    center_print(attempt_count,' ',true);
    center_print("Enter Password: ",' ',false);
    do
    {
        input_text[text_counter] = getch();
        if(input_text[text_counter]!='\r')
        {
            printf("*");
        }
        text_counter++;
    }
    while(input_text[text_counter-1]!='\r');
    input_text[text_counter-1]='\0';
    compare_result = strcmp(password,input_text);
    if(compare_result == 0)
    {
        return true;
    }
    printf("\nAccess denied! Try again");
    getch();
    return false;
}

/* admin_menu displays the admin menu screen. user can choose three actions:
   add question(1),remove question(2),exit admin mode(3).
   The function returns the choice entered by the user, after performing the corresponding action*/
int admin_menu()
{
    system("cls");
    int action_choice;       // stores the choice of admin_menu and controls the flow accordingly
    center_print(TITLE,'*',true);
    printf("\n\n");
    center_print("1. Add a question",' ',true);
    center_print("2. Remove a question",' ',true);
    center_print("3. Exit admin mode",' ',true);
    center_print(" ",' ',false);
    scanf("%d",&action_choice);
    if(action_choice == 1)
    {
        add_question();        // in database_classc.h
    }
    else if(action_choice == 2)
    {
        remove_question();     // in database_classc.h
    }
    return action_choice;
}

// display_rules() displays the rules of the game to the user 
// the function retrns nothing.
void display_rules()
{
    system("cls");
    center_print(TITLE,'*',true);
    printf("\n\n");
    printf("1. The game contains %d questions which get progressively difficult",NO_OF_LEVELS);
    printf("\n2. Answering each question correctly grants you more and more prize. There are %d safe-questions in the game. They are at:",SAFE_LEVELS);
    printf("\n\t - Q2. Rs. 10,000\n\t - Q7 Rs. 3,20,000");
    printf("\n3. Every question has 4 options. To respond to a question, write the option no. (1-4) in the space provided.");
    //printf("\n4. Till Q2, there is a 30 second timer, after that a 45 second timer till Q7. Then the timer will be removed.");
    printf("\n4. If the question is answered incorrectly, the game ends and the prize money corresponds to last safe-question crossed.");
    printf("\n5. There are 2 lifelines, 50-50 and change-the-question. To use 50-50, enter 5 as answer. To use the latter, enter 6.");
    printf("\n6. If you dont want to attempt a question and want to quit with the prize money you have, enter answer as 7.");
    printf("\nPress enter to begin the game.");
    getch();
    return;
}

// play_game() is the main function that handles the game and input output, returning 
// prize_money won by the user in the end of each game
int play_game()
{
    game_data storage;                     //game_data struct initialized for the game
    storage.cash = 0;                      // initial values set
    storage.fifty_lifeline_status = 'y';
    storage.chageq_lifeline_status = 'y';
    storage.lifelines_remaining = 2;
    storage.safe_cash = 0;
    prize_money[1]=5000;                  // prize money for all levels stored in the global
    prize_money[2]=10000;                 // array declared in database_classc.h 
    prize_money[3]=20000;
    prize_money[4]=40000;
    prize_money[5]=80000;
    prize_money[6]=160000;
    prize_money[7]=320000;
    prize_money[8]=640000;
    prize_money[9]=1250000;
    prize_money[10]=2500000;
    prize_money[11]=5000000;
    prize_money[12]=10000000;
    display_rules();                    //rules are displayed to the user
    for(int i=1;i<=NO_OF_LEVELS;i++)
    {
        system("cls");
        question q;
        int life_checker;
        center_print(TITLE,'*',true);
        printf("\n\n");
        printf("Q.%d",i);
        printf("\nPrize earned if you quit: %d\t\tPrize earned if you answer incorrectly: %d",storage.cash,storage.safe_cash);
        printf("\n\nPrize earned if you answer correctly: %d",prize_money[i]);
        printf("\n\nLifelines Remaining:");
        if(storage.fifty_lifeline_status == 'y')
        {
            printf("\t\t50-50 (5)");
        }
        if(storage.chageq_lifeline_status == 'y')
        {
            printf("\t\tflip-the-question (6)");
        }
        char level_name[35] = ".\\levels\\level_";
        char numerix[3];                    //creating the name of the file 
        itoa(i,numerix,10);                 //converting int to char string
        strcat(level_name, numerix);
        strcat( level_name,".dat");            //filename created of tempate "level_0.dat"
        FILE *fin;
        fin = fopen(level_name,"rb");
        if(fin==NULL)
        {
            printf("\nThe questions could not be loaded.");
            getch();
            return 0;
        }
        int question_counter = 0;           //stores the total no. of questions in the file
        int question_no;                    //stores the number of the question in the list selected randomly
        int answer;                         //stores input of the user after reading the question
        question ques_data[50];
        while(1 == fread(&ques_data[question_counter],sizeof(question),1,fin))  //read the corresponding file and store it in the array
        {
            question_counter++;            //update after every read
        }            
        fclose(fin);                       //closes the input stream from corresponding file
        srand(time(0));                    //creates random number algorithm 
        question_no = (rand() % question_counter);   //chooses one question randomly out of the database
        printf("\n\nQues: ");
        printf("%s",ques_data[question_no].ques);    //prints the question
        printf("\n\n1. %s",ques_data[question_no].option[0]);   // all options are printed
        printf("\n\n2. %s",ques_data[question_no].option[1]);
        printf("\n\n3. %s",ques_data[question_no].option[2]);
        printf("\n\n4. %s",ques_data[question_no].option[3]);
        printf("\n\nEnter Answer: ");
        scanf("%d",&answer);               //taking user response to question
        while((getchar())!='\n');          //flushing input buffer stream
        while(1)
        {
            if(answer>=1 && answer<=4)     //if definite answer recieved, then proceed further 
            {                               
                break;
            }
            if(answer == 5)
            {
                if(storage.fifty_lifeline_status != 'y')   //checking for lifeline availability
                {
                    printf("\nYou have already used the lifeline!");
                    printf("\nEnter Answer: ");    
                    scanf("%d",&answer);           //taking input from user
                    while((getchar())!='\n');      //flushing input buffer stream
                    continue;
                }
                storage.fifty_lifeline_status = 'n';   //updating lifeline status
                system("cls");                         //reprinting the screen
                center_print(TITLE,'*',true);
                printf("\n\n");
                printf("Q.%d",i);
                printf("\nPrize earned if you quit: %d\t\tPrize earned if you answer incorrectly: %d",storage.cash,storage.safe_cash);
                printf("\n\nPrize earned if you answer correctly: %d",prize_money[i]);
                printf("\n\nLifelines Remaining:");
                if(storage.fifty_lifeline_status == 'y')
                {
                    printf("\t\t50-50 (5)");
                }
                if(storage.chageq_lifeline_status == 'y')
                {
                    printf("\t\tflip-the-question (6)");
                }
                printf("\n\nQues: ");
                printf("%s",ques_data[question_no].ques);    //prints the question
                int correct = ques_data[question_no].correct_ans;  //stores the correct answer of the question to remove the incorrect ones
                int ore[2];
                if(correct==1)                        //picks out the incorrect options to be removed
                {
                    ore[0]=4;
                    ore[1]=2;
                }
                else if(correct==2||correct==3)
                {
                    ore[0]=correct-1;
                    ore[1]=correct+1;
                }
                else
                {
                    ore[0]=3;
                    ore[1]=1;
                }
                printf("\n\n1. ");
                if(ore[0]!=1 && ore[1]!=1)    //tests and prints first option
                {
                    printf("%s",ques_data[question_no].option[0]);
                }
                printf("\n\n2. ");
                if(ore[0]!=2 && ore[1]!=2)    //tests and prints second option
                {
                    printf("%s",ques_data[question_no].option[1]);
                }
                printf("\n\n3. ");
                if(ore[0]!=3 && ore[1]!=3)    //tests and prints third option
                {
                    printf("%s",ques_data[question_no].option[2]);
                }
                printf("\n\n4. ");
                if(ore[0]!=4 && ore[1]!=4)    //tests and prints first option
                {
                    printf("%s",ques_data[question_no].option[3]);
                }
                printf("\n\nEnter Answer: ");
                scanf("%d",&answer);          //updating input of user after using lifeline
                while((getchar())!='\n');     //flushing input buffer stream
            }
            if(answer == 6)
            {
                if(storage.chageq_lifeline_status != 'y')   //checking for lifeline availability
                {
                    printf("\nYou have already used the lifeline!");
                    printf("\nEnter Answer: ");    
                    scanf("%d",&answer);           //taking input from user
                    while((getchar())!='\n');      //flushing input buffer stream
                    continue;
                }
                storage.chageq_lifeline_status = 'n';   //updating lifeline status
                system("cls");                         //reprinting the screen
                center_print(TITLE,'*',true);
                printf("\n\n");
                printf("Q.%d",i);
                printf("\nPrize earned if you quit: %d\t\tPrize earned if you answer incorrectly: %d",storage.cash,storage.safe_cash);
                printf("\n\nPrize earned if you answer correctly: %d",prize_money[i]);
                printf("\n\nLifelines Remaining:");
                if(storage.fifty_lifeline_status == 'y')
                {
                    printf("\t\t50-50 (5)");
                }
                if(storage.chageq_lifeline_status == 'y')
                {
                    printf("\t\tflip-the-question (6)");
                }
                printf("\n\nQues: "); 
                if(question_no == (question_counter - 1))     //changing the question no to print out a different question
                {
                    question_no--;
                }
                else
                {
                    question_no++;
                }
                printf("%s",ques_data[question_no].ques);    //prints the question
                printf("\n\n1. %s",ques_data[question_no].option[0]);   // all options are printed
                printf("\n\n2. %s",ques_data[question_no].option[1]);
                printf("\n\n3. %s",ques_data[question_no].option[2]);
                printf("\n\n4. %s",ques_data[question_no].option[3]);
                printf("\n\nEnter Answer: ");
                scanf("%d",&answer);               //updating input 
                while((getchar())!='\n');
            }
            if(answer == 7)
            {
                char quit_choice = 'y';
                printf("\nWant to quit with the current prize money (Rs. %d ) ? (y/n) :",storage.cash);
                scanf("%c",&quit_choice);
                while((getchar())!='\n');          //flushing input buffer stream
                if(quit_choice == 'y' || quit_choice == 'Y')
                {
                    return storage.cash;
                } 
                else
                {
                    printf("\n\nEnter Answer: ");
                    scanf("%d",&answer);          //updating user input
                    while((getchar())!='\n');     //flushing input buffer stream
                }
                
            }
        }
        if(answer == ques_data[question_no].correct_ans)  //if user inputs correct answer
        {
            storage.cash = prize_money[i];        //updates the cash won field in game data
            if(i==SAFE_LEVEL_1||i==SAFE_LEVEL_2)  //if user cleared a safe-question, updates safe cash too
            {
                storage.safe_cash = prize_money[i];
            }
            printf("\n\nCongratulations!! Correct answer. You win Rs.%d !!",prize_money[i]);
            if(i!=NO_OF_LEVELS)
            {
                printf("\nPress enter to proceed to the next question.");
                getch();
            }
            else                       //if user enters last question correctly
            {
                printf("\nYou have successfully reached the end. Thanks for playing!!");
                return storage.cash;
            }
        }
        else                          //if users answer a question incorrectly
        {
            printf("\n\nSorry...This is not the correct answer...The correct answer is %d.",ques_data[question_no].correct_ans);
            printf("\nYou have dropped back to Rs.%d.",storage.safe_cash);
            return storage.safe_cash;            //the previous safe-lavel cash is returned
        }     
    }
    return storage.safe_cash;
}

#endif