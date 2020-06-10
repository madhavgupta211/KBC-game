//database_class.h file
#ifndef _database_class_h
#define _database_class_h
#define NO_OF_LEVELS 12
#define SAFE_LEVELS 2
#define SAFE_LEVEL_1 2
#define SAFE_LEVEL_2 7
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

struct question{
    char question[300];
    char option[4][100];
    char id[25];
    int correct_ans;
};

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
    int get_prize_money(int x)
    {
        return prize_money[x-1];
    }
};

class game_data{
    private: 
        int cash;
        char fifty_lifeline_status;
        char changeq_lifeline_status;
        int lifelines_remaining;
        int safe_cash;
    public:
        game_data()
        {
            cash = 0;
            fifty_lifeline_status = 'y';
            changeq_lifeline_status = 'y';
            lifelines_remaining = 2;
            safe_cash = 0;
        }
        void update_cash(int x)
        {
            cash = x;
            return;
        }
        void updat_safe_cash(int x)
        {
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
        void update_lifeline_status(std::string x)
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
        std::cout<<"\n The level of the question(1-"<<NO_OF_LEVELS<<"): ";
        std::cin>>level;
        std::string name = ".\\levels\\level_" + to_string(level) + ".dat";
        std::ofstream foo(name.c_str(),std::ios::out|std::ios::binary|std::ios::app);
        if(!foo)
        {
            std::cout<<"\nFile could not open.!!";
            return;
        }
        std::cout<<"\n Enter the question: ";
        std::cin>>q.question;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        for(int i=0;i<4;i++)
        {
            std::cout<<"\n Enter the "<<i+1<<" option: ";
            std::cin>>q.option[i];
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        std::cout<<"\n Enter the correct option no.(1-4): ";
        std::cin>>q.correct_ans;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout<<"\n Enter the ID for the question(one word preferable): ";
        std::cin>>q.id;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        foo.write((char*) &q,sizeof(question));
        std::cout<<"\n Question added!";
        std::cout<<"\n Want to add more ? (y/n): ";
        std::cin>>continue_choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        foo.close();
    }
    return;
}

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
        std::ifstream fin(name.c_str(),std::ios::in|std::ios::binary);
        if(!fin)
        {
            std::cout<<"\nThe file could not be opened!";
            return;
        }
        while((fin.read((char*)&q,sizeof(question)))!=NULL)
        {
            id_list.push_back(q.id);
        }
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
        fin.open(name.c_str(),std::ios::in|std::ios::binary);
        std::ofstream fout("temp.dat",std::ios::out|std::ios::binary);
        if(!fout)
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
        fout.open(name.c_str(),std::ios::out|std::ios::binary);
        fin.open("temp.dat",std::ios::in|std::ios::binary);
        while(fin.read((char*) &q,sizeof(question))!=NULL)
        {
            fout.write((char*) &q,sizeof(question));
        }
        std::remove("temp.dat");
        std::cout<<"\nQuestion deleted!";
        std::cout<<"\nWant to continue deleting? (y/n)";
        std::cin>>continue_choice;
        fin.close();
        fout.close();
    }
    return;
}

#endif