#include <iostream> 
#include "fundamentals.h"
#define NO_OF_ATTEMPTS 5      //no. of attempts to login
#define PASSWORD "cholosolo"  //change admin's password from here

using namespace std; 

int main()
{
    int access_type;
    access_type = display_intro();
    if(access_type==1)
    {
        bool admin_access_status = false;
        for(int i=NO_OF_ATTEMPTS;i>0;i--)
        {
            admin_access_status = admin_login(PASSWORD,i);
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
    }
    return 0;
}