//database_class.h file
#ifndef _database_class_h
#define _database_class_h
#define NO_OF_LEVELS 15
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
        std::cout<<"\n The level of the question(1-15): ";
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
        std::cout<<"\n The level of the question(1-15): ";
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