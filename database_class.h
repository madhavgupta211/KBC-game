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

//15 files needed to be created..for 15 levels. Each file stores the same level
//questions of which one would be randomly selected in-game

struct question{
    char question[300];
    char option[4][100];
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
    foo.write((char *) &q,sizeof(q));
    std::cout<<"\n Question added!";
    getch();
    foo.close();
    return;
}

#endif