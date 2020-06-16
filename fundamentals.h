//fundamentals.h file
#ifndef _fundamentals_h
#define _fundamentals_h
#include <iostream>
#include <Windows.h> //for getting the rows and columns of terminal window
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <time.h>
#include "database_class.h"

// title_display() displays the title of the game 
// center aligned according to window size
// obsolete function, no longer needed, replaced by more universally applicable center_print()
int title_display()
{
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
    return columns;
} 

// center_print() takes input a string variable and prints it to stdout centrally aligned.
// it takes another argument, the fill character. Default value is set to whitespace
// it does not return anything
void center_print(std::string x,char y = ' ',bool newline = true)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;   //windows.h object
    int rows,columns;                  
    GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;              //calculated the no. of rows and columns of the terminal window
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;                 //by using windows.h header file
    std::cout<<std::setw((columns/2)+x.length()/2)<<std::right<<std::setfill(y);
    std::cout<<x;
    if(newline)
    {
        for(int i=0;i<((columns/2)-x.length()/2);i++)
        {
        std::cout<<y;
        }
        std::cout<<"\n";
    }
    return;
}


// display_intro asks from the user whether he wants to access
// developer page or just wants to play the game
// returns 1 if admin page is chosen, 2 otherwise  
int display_intro()
{
    system("cls");
    int access_value;
    std::string title = TITLE ;
    center_print(title,'*');
    std::cout<<"\n\n";
    std::string admin = "1. Admin Access";
    std::string game = "2. Play the game ";
    std::string exit = "3. Exit the Application";
    std::string space = " ";
    center_print(admin);
    center_print(game);
    center_print(exit);
    center_print(space,' ',false);
    std::cin>>access_value;
    return access_value;
}

// admin_login displays the login screen for admin framework and asks for password
//return true if login successful, otherwise false
bool admin_login(std::string password, int no_of_attempts)
{
    system("cls");
    int compare_result;
    std::string title = TITLE ;
    center_print(title,'*');
    char password_single;
    std::string input_text;                                              //password entered by user to be checked                  
    std::cout<<"\n\n\n";
    std::string number = "No. of attempts remaining : " + to_string(no_of_attempts);
    center_print(number);
    std::string enter = "Enter Password:";
    center_print(enter,' ',false);
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
    int action_choice;
    std::string title = TITLE ;
    center_print(title,'*');
    std::cout<<"\n\n";
    std::string add = "1. Add a question";
    center_print(add);
    std::string remove = "2. Remove a question";
    center_print(remove);
    std::string exit = "3. Exit admin mode";
    center_print(exit);
    std::string space = " ";
    center_print(space,' ',false);
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
    std::string title = TITLE ;
    center_print(title,'*');
    std::cout<<"\n\n";
    std::cout<<"1. The game contains "<<NO_OF_LEVELS<<" questions which get progressively difficult.";
    std::cout<<"\n2. Answering each question correctly grants you more and more prize. there are "<<SAFE_LEVELS<<" safe-questions in the game. They are at:";
    std::cout<<"\n\t - Q2. Rs. 10,000\n\t - Q7 Rs. 3,20,000";
    std::cout<<"\n3. Every question has 4 options. To respond to a question, write the option no. (1-4) in the space provided.";
    std::cout<<"\n4. Till Q2, there is a 30 second timer, after that a 45 second timer till Q7. Then the timer will be removed.";
    std::cout<<"\n5. If the question is answered incorrectly, the game ends and the prize money corresponds to last safe-question crossed.";
    std::cout<<"\n6. There are 2 lifelines, 50-50 and change-the-question. To use 50-50, enter 5 as answer. To use the latter, enter 6.";
    std::cout<<"\n7. If you dont want to attempt a question and want to quit with the prize money you have, enter answer as 7.";
    std::cout<<"\nPress enter to begin the game.";
    getch();
    return;
}

int play_game()
{
    game_data storage;
    prize_list list;
    display_rules();
    for(int i=1;i<=NO_OF_LEVELS;i++)
    {
        system("cls");
        question q;
        int life_checker,timer_time;
        int left_time = 100000;
        int time_elapsed;
        bool apply_timer = false;
        std::string title = TITLE ;
        if(i<=SAFE_LEVEL_1)
        {
            timer_time = TIMER_1;
            apply_timer = true;
        }
        else if(i<=SAFE_LEVEL_2)
        {
            timer_time = TIMER_2;
            apply_timer = true;
        }
        center_print(title,'*');
        std::cout<<"\n\n";
        std::cout<<"Q."<<i;
        std::cout<<"\nPrize earned if you quit: "<<storage.get_cash()<<"\t\tPrize earned if you answer incorrectly: "<<storage.get_safe_cash();
        std::cout<<"\nPrize earned if you answer correctly: "<<list.get_prize_money(i);
        std::cout<<"\nLifelines Remaining:";
        life_checker = storage.get_lifeline_status();
        if(life_checker == 1)
        {
            std::cout<<"\t\t\t50-50 (5)\t\t\tchange-the-question (6)";
        }
        if(life_checker == 2)
        {
            std::cout<<"\t\t\t50-50 (5)";
        }
        if(life_checker == 3)
        {
            std::cout<<"\t\t\tchange-the-question (6)";
        }
        std::string name = ".\\levels\\level_" + to_string(i) + ".dat";
        std::ifstream fin(name.c_str(),std::ios::in|std::ios::binary);
        if(!fin)
        {
            std::cout<<"\nThe questions could not be loaded";
            getch();
            return 0;
        }
        std::vector<question> question_list;
        int question_no;
        int answer;
        int count=0;
        while(fin.read((char*) &q,sizeof(question))!=NULL)
        {
            question_list.push_back(q);
        }
        fin.close();
        srand(time(0));
        question_no = (rand() % question_list.size());
        std::cout<<"\nQues: ";
        std::cout<<question_list[question_no].ques;
        std::cout<<"\nA. "<<question_list[question_no].option[0];
        std::cout<<std::endl<<"B. "<<question_list[question_no].option[1];
        std::cout<<std::endl<<"C. "<<question_list[question_no].option[2];
        std::cout<<std::endl<<"D. "<<question_list[question_no].option[3];
        std::cout<<"\n\nEnter Answer: ";
        if(apply_timer)
        {
            answer = 8;       // answer = timer_input(timer_time, 8,left_time);
            clock_t start;
            int flag =0;
            start = clock();
            while(1)
            {
                time_elapsed = (int)((clock() - start)/(double) CLOCKS_PER_SEC);
                left_time = std::min(timer_time - time_elapsed,left_time);
                if(left_time == 45)
                {
                    std::cout<<"\n45 seconds remaining";
                    left_time--;
                }
                if(left_time == 30)
                {
                    std::cout<<"\n30 seconds remaining";
                    left_time--;
                }
                if(left_time == 20)
                {
                    std::cout<<"\n20 seconds remaining";
                    left_time--;
                }
                if(left_time == 10)
                {
                    std::cout<<"\n10 seconds remaining";
                    left_time--;
                }
                if(left_time == 5)
                {
                    std::cout<<"\n5 seconds remaining";
                    left_time--;
                }
                if(kbhit())
                {
                    flag=1;
                    break;
                }
                if(time_elapsed>=timer_time)
                    break;
            }
            if(flag==1)
            {
                std::cin>>answer;
            }
        }
        else
        {
            std::cin>>answer;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        while(1)
        {
            if((answer>=1 && answer<=4)||answer==8)
            {
                break;
            }
            if(answer==5)
            {
                int status_checker;
                std::string res= "fifty";
                status_checker = storage.get_lifeline_status();
                if(status_checker == 0 | status_checker == 3)
                {
                    std::cout<<"\nYou have already used the lifeline!";
                    std::cout<<"\nEnter Answer: ";
                    std::cin>>answer;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    continue;
                }
                storage.update_lifeline_status(res);
                system("cls");
                std::string title = TITLE ;
                center_print(title,'*');
                std::cout<<"\n\n";
                std::cout<<"Q."<<i;
                std::cout<<"\nPrize earned if you quit: "<<storage.get_cash()<<"\tPrize earned if you lose: "<<storage.get_safe_cash();
                std::cout<<"\nLifelines Remaining:";
                life_checker = storage.get_lifeline_status();
                if(life_checker == 1)
                {
                    std::cout<<"\t\t50-50\t\tchange-the-question";
                }
                if(life_checker == 2)
                {
                    std::cout<<"\t\t50-50";
                }
                if(life_checker == 3)
                {
                    std::cout<<"\t\tchange-the-question";
                }
                std::cout<<"\nQues: ";
                std::cout<<question_list[question_no].ques;
                int correct = question_list[question_no].correct_ans;
                int ore[2];
                if(correct==1)
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
                std::cout<<"\nA. ";
                if(ore[0]!=1&&ore[1]!=1)
                {
                    std::cout<<question_list[question_no].option[0];
                }
                std::cout<<"\nB. ";
                if(ore[0]!=2&&ore[1]!=2)
                {
                    std::cout<<question_list[question_no].option[1];
                }
                std::cout<<"\nC. ";
                if(ore[0]!=3&&ore[1]!=3)
                {
                    std::cout<<question_list[question_no].option[2];
                }
                std::cout<<"\nD. ";
                if(ore[0]!=2&&ore[1]!=2)
                {
                    std::cout<<question_list[question_no].option[3];
                }
                std::cout<<"\n\nEnter Answer: ";
                std::cin>>answer;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            }
            if(answer==6)
            {
                int status_checker;
                std::string res= "change";
                status_checker = storage.get_lifeline_status();
                if(status_checker == 0 | status_checker == 2)
                {
                    std::cout<<"\nYou have already used the lifeline!";
                    std::cout<<"\nEnter Answer: ";
                    std::cin>>answer;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    continue;
                }
                storage.update_lifeline_status(res);
                system("cls");
                std::string title = TITLE ;
                center_print(title,'*');
                std::cout<<"\n\n\n";
                std::cout<<"Q."<<i;
                std::cout<<"\nPrize earned if you quit: "<<storage.get_cash()<<"\tPrize earned if you lose: "<<storage.get_safe_cash();
                std::cout<<"\nLifelines Remaining:";
                life_checker = storage.get_lifeline_status();
                if(life_checker == 1)
                {
                    std::cout<<"\t\t50-50\t\tchange-the-question";
                }
                if(life_checker == 2)
                {
                    std::cout<<"\t\t50-50";
                }
                if(life_checker == 3)
                {
                    std::cout<<"\t\tchange-the-question";
                }
                std::cout<<"\nQues: ";
                if(question_no==(question_list.size()-1))
                {
                    question_no--;
                }
                else
                {
                    question_no++;
                }
                std::cout<<question_list[question_no].ques;
                std::cout<<"\nA. "<<question_list[question_no].option[0];
                std::cout<<std::endl<<"B. "<<question_list[question_no].option[1];
                std::cout<<std::endl<<"C. "<<question_list[question_no].option[2];
                std::cout<<std::endl<<"D. "<<question_list[question_no].option[3];
                std::cout<<"\n\nEnter Answer: ";
                if(apply_timer)
                {
                    answer = 8;
                    clock_t start;
                    int flag =0;
                    start = clock();
                    while(1)
                    {
                        time_elapsed = (int)((clock() - start)/(double) CLOCKS_PER_SEC);
                        left_time = std::min(timer_time - time_elapsed , left_time);
                        if(left_time == 45)
                        {
                            std::cout<<"\n45 seconds remaining";
                            left_time--;
                        }
                        if(left_time == 30)
                        {
                            std::cout<<"\n30 seconds remaining";
                            left_time--;
                        }
                        if(left_time == 20)
                        {
                            std::cout<<"\n20 seconds remaining";
                            left_time--;
                        }
                        if(left_time == 10)
                        {
                            std::cout<<"\n10 seconds remaining";
                            left_time--;
                        }
                        if(left_time == 5)
                        {
                            std::cout<<"\n5 seconds remaining";
                            left_time--;
                        }
                        if(kbhit())
                        {
                            flag=1;
                            break;
                        }
                        if(time_elapsed>=timer_time)
                            break;
                    }
                    if(flag==1)
                    {
                        std::cin>>answer;
                    }
                }
                else
                {
                    std::cin>>answer;
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            }
            if(answer==7)
            {
                char quit_choice = 'y';
                std::cout<<"\nWant to quit with the current prize money (Rs. "<<storage.get_cash()<<" ) ? (y/n) : ";
                std::cin>>quit_choice;
                if(quit_choice=='y' || quit_choice=='Y')
                {
                    return storage.get_cash();
                }   
                else
                {
                    std::cout<<"\n\nEnter Answer: ";
                    if(apply_timer)
                    {
                        answer = 8;
                        clock_t start;
                        int flag =0;
                        start = clock();
                        while(1)
                        {
                            left_time = std::min(timer_time - time_elapsed,left_time);
                            time_elapsed = (int)((clock() - start)/(double) CLOCKS_PER_SEC);
                            if(left_time == 45)
                            {
                                std::cout<<"\n45 seconds remaining";
                                left_time--;
                            }
                            if(left_time == 30)
                            {
                                std::cout<<"\n30 seconds remaining";
                                left_time--;
                            }
                            if(left_time == 20)
                            {
                                std::cout<<"\n20 seconds remaining";
                                left_time--;
                            }
                            if(left_time == 10)
                            {
                                std::cout<<"\n10 seconds remaining";
                                left_time--;
                            }
                            if(left_time == 5)
                            {
                                std::cout<<"\n5 seconds remaining";
                                left_time--;
                            }
                            if(kbhit())
                            {
                                flag=1;
                                break;
                            }
                            if(time_elapsed>=left_time)
                                break;
                        }
                        if(flag==1)
                        {
                            std::cin>>answer;
                        }
                    }
                    else
                    {
                        std::cin>>answer;
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                }   
            }
        }
        if(answer == question_list[question_no].correct_ans)
        {
            int new_amount;
            new_amount = list.get_prize_money(i);
            storage.update_cash(new_amount);
            if(i==SAFE_LEVEL_1||i==SAFE_LEVEL_2)
            {
                storage.update_safe_cash(new_amount);
            }
            std::cout<<"\nCongratulations!! Correct answer. You win Rs."<<new_amount<<" !!";
            if(i!=NO_OF_LEVELS)
            {
                std::cout<<"\nPress enter to proceed to the next question.";
                getch();
            }
            else
            {
                std::cout<<"\nYou have successfully reached the end. Thanks for playing.";
                return storage.get_cash();
            }
            
        }
        else if(answer == 8)
        {
            std::cout<<"\nYou failed to answer within the time limit. Game over.";
            std::cout<<"\nYou have dropped back to Rs."<<storage.get_safe_cash()<<".";
            return storage.get_safe_cash();
        }
        else
        {
            std::cout<<"\nSorry...This is not the correct answer...The correct answer is "<<question_list[question_no].correct_ans<<".";
            std::cout<<"\nYou have dropped back to Rs."<<storage.get_safe_cash()<<".";
            return storage.get_safe_cash();
        }
    }
    return storage.get_safe_cash();
}
#endif