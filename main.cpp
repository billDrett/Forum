#include <iostream>
#include "system.h"
#include "forum.h"
#include "thread.h"
#include "post.h"
#include <cstdlib>
#include "registerUser.h"
#include "moderator.h"
#include "admin.h"
using namespace std;

int main(int argc, char* argv[])
{
    if(argc > 2)
    {
        cout<<"Lathos eisagwgi orismaton"<<endl;
        return -1;
    }
    System* sys = new System;

    if(argc == 2)
    {
        if(strcmp(argv[1], "-R") == 0)
        {
            sys->browse(true);
        }
        else
        {
            cout<<"Lathos eisagwgi"<<endl;
        }
    }
    else
    {
        sys->browse(false);
    }

    delete sys;
}
