//database_classc.h file
#ifndef _database_classc_h
#define _database_classc_h
#define NO_OF_LEVELS 12         //change no. of levels here, it will be changed accordingly,just add according prize money in prize_list
#define SAFE_LEVELS 2          //no. of safe_questions made in the game
#define SAFE_LEVEL_1 2         //first safe_level
#define SAFE_LEVEL_2 7         //second safe level
//to add more than two safe levels you have to change the if condition in line 398 of fundamentals.h and also the display_rules() func.
#define TITLE "KBC: The Game"
#define TIMER_1 31
#define TIMER_2 46
#undef max

#include <stdio.h>
#include <string.h>
/* strcat()
   strcpy()
   strcmp()  */
#include <stdlib.h>
/* itoa()  */
#include <conio.h>
/* getch() */

//global array stores the prize money for all corresponding levels
int prize_money[NO_OF_LEVELS + 1];

//15 files needed to be created..for 15 levels. Each file stores the same level
//questions of which one would be randomly selected in-game

//the core struct for any question, a question array, four options array, an id to address a question quickly in remove_question()
//correct answer is stored as an integer, 1 for A, 4 for D
typedef struct questions{
    char ques[300];
    char option[4][100];
    char id[25];
    int correct_ans;
} question;

//Struct game_data stores all the important data for a particular game in the play_game()
//function. the contents are refreshed after every question.
typedef struct games_data{
    int cash;                          //stores the cash player gets if he quits at a certain level or wins the game 
    char fifty_lifeline_status;        // y if still available , n if used
    char chageq_lifeline_status;       // y if still available , n if used
    int lifelines_remaining;
    int safe_cash;                     //stores the cash player gets if he incorrectly answers the current question
} game_data;


//adds the question into the specific file asked for
void add_question()
{
    char continue_choice = 'y';
    while( continue_choice == 'y' || continue_choice == 'Y')
    {
        question q;
        int level;
        printf("\n The level of the question (1-%d) : ",NO_OF_LEVELS);
        scanf("%d",&level);                   
        while((getchar())!='\n');               //flushes input buffer stream
        printf("\n Enter the question: ");
        scanf("%[^\n]%*c",q.ques);              //takes string input until \n is encountered
        //the question is stored
        for(int i=0; i<4 ; i++)
        {
            printf("\n Enter the %d option: ",i+1);
            scanf("%[^\n]%*c",q.option[i]);
        }
        printf("\n Enter the correct option no.(1-4): ");
        scanf("%d",&q.correct_ans);
        while((getchar())!='\n');
        printf("\n Enter the ID for the question(one word preferable): ");
        scanf("%[^\n]%*c",q.id);
        char level_name[35] = ".\\levels\\level_";
        char numerix[3];                    //creating the name of the file 
        itoa(level,numerix,10);                 //converting int to char string
        strcat(level_name, numerix);
        strcat( level_name,".dat");            //filename created of tempate "level_0.dat" 
        FILE *fout;                           
        fout = fopen(level_name,"ab");         //corresponding file is opened
        if(fout==NULL)
        {
            printf("\n File could not open.!!");
            return;
        }
        fwrite(&q,sizeof(question),1,fout);           //question inserted in the file
        printf("\n Question added!");          
        printf("\n Want to add more ? (y/n): ");
        scanf("%c",&continue_choice);               //continue_choice updated
        while((getchar())!='\n');
        fclose(fout);
    }
    return;
}

// remove_question() allows admin to remove any question from a particular file.
// All ids are displayed of a file to make the user choose the one to be deleted.
void remove_question()
{
    char continue_choice = 'y';
    while(continue_choice=='y'||continue_choice=='Y')
    {
        question q;
        int level,present_flag=0,del_element_pos;
        char delete_id[25];              //stores the id to be deleted as entered by the user
        char id_list[25][25];            //stores all ids of questions in a particular file
        printf("\nThe level of the question(1-%d) : ",NO_OF_LEVELS);
        scanf("%d",&level);
        while((getchar())!='\n');              //flushes input buffer stream
        char level_name[35] = ".\\levels\\level_";
        char numerix[3];                       //creating the name of the file 
        itoa(level,numerix,10);                //converting int to char string
        strcat(level_name, numerix);
        strcat( level_name,".dat");            //filename created of template "level_0.dat"
        FILE *fin;
        fin = fopen(level_name,"rb");          //corresponding file opened in read mode to store id_s 
        if(fin==NULL)                          
        {
            printf("\nFile could not open.!!");
            return;
        }
        int counter = 0;                       // counts no. of ids in the file
        while(1==fread(&q,sizeof(question),1,fin))  //reads all questions one by one
        {
            strcpy(id_list[counter],q.id);     //stores all id names in an array
            counter++;                 
        }
        for(int i = 0; i<counter; i++)         //prints every id for the user to choose from
        {
            printf("\n %s",id_list[i]);
        }
        printf("\nEnter ID for question you want to delete: ");  //asks user to type id of question they want to delete
        scanf("%[^\n]%*c",delete_id);          //stores the id input
        while((getchar())!='\n');              //flushes input buffer stream
        for(int i=0; i < counter;i++)          //matches input id to every element in the id list
        {
            if(strcmp(id_list[i],delete_id) == 0)
            {
                del_element_pos = i + 1;       //stores the position of id to be deleted
                present_flag = 1;              //stores that id has matched
                break;
            }
        }
        if(present_flag==0)                    //if id does not match
        {
            printf("\nThe question corresponding to input id not found.");
            getch();
            fclose(fin);
            return;
        }
        fclose(fin);                           //input stream from file closed
        FILE *fout;
        fout = fopen(".\\levels\\temp.dat","wb");   //opened a temporary file to copy contents except the particular question to be deleted
        if(fout==NULL)
        {
            printf("\nFile could not open.!!");
            return;
        }
        fin = fopen(level_name,"rb");          //opened the corresponding level file in read mode
        for(int i=1;i<=counter;i++)           
        {
            fread(&q,sizeof(question),1,fin);  //every element copied except the one to be deleted in temp.dat 
            if(i!=del_element_pos)
            {
                fwrite(&q,sizeof(question),1,fout);
            }
        }
        fclose(fin);                          //closed the corresponding level file
        fclose(fout);                         //closed the temp file stream
        fout = fopen(level_name,"wb");        //opened the corresponding level file in overwrite mode
        fin = fopen(".\\levels\\temp.dat","rb");  //opened temp file in read binary mode
        while(1==fread(&q,sizeof(question),1,fin))  //copied all contents of temp file in the original level file, thereby overwriting it
        {
            fwrite(&q,sizeof(question),1,fout);
        }
        printf("\nQuestion deleted!");                 
        printf("\nWant to continue deleting? (y/n)");   //updating continue_choice
        scanf("%c",&continue_choice);
        while((getchar())!='\n');    //flushing input stream
        fclose(fin);                 //closed temp file stream
        fclose(fout);                //closed original file stream
    }
    return;
}

#endif