#ifndef Included_post_H
#define Included_post_H

#include <iostream>
#include <cstring>
//#include "system.h"

class System;
class Post
{
private:
    System* system;
    int id;
    char* text;
    int userId;

public:
    Post(int id, char* txt, int userId, System* sys);
    ~Post();

    //accessors
    int getID();
    char* getText();
    char* getUsername();
    int getUserID();

    //mutators
    void setText(char* txt);

    void print();
    void apothikeusiKatastasis(std::ofstream& postFile, char* ierarxia);
};

#endif
