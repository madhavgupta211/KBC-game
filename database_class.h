//database_class.h file
#ifndef _database_class_h
#define _database_class_h
#define NO_OF_LEVELS 12         //change no. of levels here, it will be changed accordingly,just add according prize money in prize_list
#define SAFE_LEVELS 2          //no. of safe_questions made in the game
#define SAFE_LEVEL_1 2         //first safe_level
#define SAFE_LEVEL_2 7         //second safe level
//to add more than two safe levels you have to change the if condition in line 398 of fundamentals.h and also the display_rules() func.
#define TITLE "KBC: The Game"
#define TIMER_1 31
#define TIMER_2 46
#undef max

#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <sstream>
#include <limits>
#include <vector>
#include <cstdio>

//15 files needed to be created..for 15 levels. Each file stores the same level
//questions of which one would be randomly selected in-game

//the core struct for any question, a question array, four options array, an id to address a question quickly in remove_question()
//correct answer is stored as an integer, 1 for A, 4 for D
struct question{              
    char ques[300];
    char option[4][100];
    char id[25];
    int correct_ans;
};

//contains the prize money. to change the no. of safe levels.. add corresponding prize_money here too.
class prize_list{
    private:
    int prize_money[NO_OF_LEVELS];
    public:
    prize_list()
    {
        prize_money[0]=5000;
        prize_money[1]=10000;
        prize_money[2]=20000;
        prize_money[3]=40000;
        prize_money[4]=80000;
        prize_money[5]=160000;
        prize_money[6]=320000;
        prize_money[7]=640000;
        prize_money[8]=1250000;
        prize_money[9]=2500000;
        prize_money[10]=5000000;
        prize_money[11]=10000000;
    }
    int get_prize_money(int x)              //returns prize money corresponding to the certain level
    {
        return prize_money[x-1];
    }
};

//stores game data like money banked in, lifelines status, one object of it is created 
//anytime the play_game() function is called.
class game_data{
    private: 
        int cash;                          //stores the cash player gets if he quits or wins the game at any point
        char fifty_lifeline_status;        // y if still available , n if used
        char changeq_lifeline_status;      // y if still available, n if used
        int lifelines_remaining;           
        int safe_cash;                     //stores the cash player gets if he incorrectly answers the current question
    public:
        game_data()                        //initializes data to default values
        {
            cash = 0;
            fifty_lifeline_status = 'y';     
            changeq_lifeline_status = 'y';
            lifelines_remaining = 2;
            safe_cash = 0;
        }
        void update_cash(int x)           //updates cash variable acc to the answer obtained of the current question
        {                                 //used in correct answer block of fundamentals.h 
            cash = x;
            return;
        }
        void update_safe_cash(int x)      //updates safe cash variable whenever player correctly answers the safe level question
        {                                 //used in correct answer block of fundamentals.h
            safe_cash=x;                 
            return;
        }
        int get_lifeline_status()                //returns 0 if no lifeline available, returns 1 if both available, returns 2 if 50-50
        {                                         //available only, returns 3 if change question available only
            if(lifelines_remaining == 0)
            {
                return 0;
            }
            else if(lifelines_remaining == 2)
            {
                return 1;
            }
            else if(lifelines_remaining == 1 && changeq_lifeline_status == 'y')
            {
                return 3;
            }
            else
            {
                return 2;
            } 
        }
        void update_lifeline_status(std::string x)    // updates lifeline status in the game data as soon as a lifeline is used
        {
            if(x.compare("fifty")==0)
            {
                fifty_lifeline_status = 'n';
                lifelines_remaining -= 1;
            }
            if(x.compare("change")==0)
            {
                changeq_lifeline_status = 'n';
                lifelines_remaining -= 1;
            }
            return;
        }
        int get_cash()
        {
            return cash;
        }
        int get_safe_cash()
        {
            return safe_cash;
        }

};

//Converts any given non string data type into a string
template <typename T>
std::string to_string(T val)
{
    std::stringstream stream;
    stream << val;
    return stream.str();
}

//adds the question into the specific file asked for
void add_question()
{
    char continue_choice='y';
    while( continue_choice == 'y' || continue_choice == 'Y')
    {
        question q;
        int level;
        std::cout<<"\n The level of the question(1-"<<NO_OF_LEVELS<<"): ";        //taking in new question data
        std::cin>>level;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout<<"\n Enter the question: ";
        std::cin.getline(q.ques, 300);
        for(int i=0;i<4;i++)
        {
            std::cout<<"\n Enter the "<<i+1<<" option: ";
            std::cin.getline(q.option[i],100);
        }
        std::cout<<"\n Enter the correct option no.(1-4): ";
        std::cin>>q.correct_ans;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout<<"\n Enter the ID for the question(one word preferable): ";
        std::cin.getline(q.id,25);
        std::string name = ".\\levels\\level_" + to_string(level) + ".dat";
        std::ofstream foo(name.c_str(),std::ios::out|std::ios::binary|std::ios::app);
        if(!foo)
        {
            std::cout<<"\nFile could not open.!!";
            return;
        }
        foo.write((char*) &q,sizeof(question));
        std::cout<<"\n Question added!";
        std::cout<<"\n Want to add more ? (y/n): ";
        std::cin>>continue_choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        foo.close();
    }
    return;
}

//the feature allows admin to remove any question from a particular file.
//delete by the id given to every question 
void remove_question()
{
    char continue_choice = 'y';
    while(continue_choice=='y'||continue_choice=='Y')
    {
        question q;
        int level,present_flag=0,del_element_pos;
        char delete_id[25];
        std::vector<std::string> id_list;
        std::cout<<"\nThe level of the question(1-"<<NO_OF_LEVELS<<"): ";
        std::cin>>level;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::string name = ".\\levels\\level_" + to_string(level) + ".dat";
        std::ifstream fin(name.c_str(),std::ios::in|std::ios::binary);      //opens corresponding level binary file in input mode
        if(!fin)
        {
            std::cout<<"\nThe file could not be opened!";
            return;
        }
        while((fin.read((char*)&q,sizeof(question)))!=NULL)
        {
            id_list.push_back(q.id);                                       // stores the question of all id's to be displayed to
        }                                                                  // to the admin later 
        for(int i=0;i<id_list.size();i++)
        {
            std::cout<<"\n"<<id_list[i];
        }
        std::cout<<"\nEnter ID for question you want to delete: ";
        std::cin>>delete_id;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        for(int i=0;i<id_list.size();i++)
        {
            if(strcmp(id_list[i].c_str(),delete_id) == 0)
            {
                del_element_pos = i + 1;
                present_flag = 1;
                break;
            }
        }
        if(present_flag==0)
        {
            std::cout<<"\nThe question corresponding to input id not found.";
            getch();
            return;
        }
        fin.close();
        fin.open(name.c_str(),std::ios::in|std::ios::binary);                     //prepares to read the input level file
        std::ofstream fout("temp.dat",std::ios::out|std::ios::binary);            //opens the temporary file in which all contents will 
        if(!fout)                                                                 //except the question to be removed.
        {
            std::cout<<"\nThe file could not be opened!";
            return;
        }
        for(int i=1; i<=id_list.size();i++)
        {
            fin.read((char*) &q,sizeof(question));
            if(i!=del_element_pos)
            {
                fout.write((char*) &q,sizeof(question));
            }
        }
        fin.close();
        fout.close();
        fout.open(name.c_str(),std::ios::out|std::ios::binary);                  //deletes all content of original file
        fin.open("temp.dat",std::ios::in|std::ios::binary);                      //and copies the content of temporary file
        while(fin.read((char*) &q,sizeof(question))!=NULL)
        {
            fout.write((char*) &q,sizeof(question));
        }
        std::remove("temp.dat");                                                 //deletes temp files
        std::cout<<"\nQuestion deleted!";
        std::cout<<"\nWant to continue deleting? (y/n)";
        std::cin>>continue_choice;
        fin.close();
        fout.close();
    }
    return;
}

#endif