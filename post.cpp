#include <fstream>
#include "system.h"
#include "post.h"
using namespace std;

Post::Post(int id1, char* txt, int userID, System* sys)
{
    id = id1;
    userId = userID;
    system = sys;

    text = new char[strlen(txt)+1];
    strcpy(text, txt);
}

Post::~Post()
{
    delete[] text;
}

int Post::getID()
{
    return id;
}

char* Post::getText()
{
    return text;
}

char* Post::getUsername()
{
    return system->searchUserID(userId);
}

int Post::getUserID()
{
    return userId;
}
void Post::setText(char* txt)
{
    delete[] text;
    text = new char[strlen(txt)+1];
    strcpy(text, txt);
}

void Post::print()
{//emfanizei to post
    char* name = system->searchUserID(userId);
    if(name == NULL) return;

    cout<<name<<":"<<text<<" ("<<id<<")"<<endl;
}

void Post::apothikeusiKatastasis(ofstream& postFile, char* ierarxia)
{
    postFile << ierarxia <<"."<< id<< " "<<userId <<" "<< text<<endl;
}
