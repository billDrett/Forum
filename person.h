#ifndef Included_person_H
#define Included_person_H

#include <iostream>
#include <list>
#include <cstring>
//#include "system.h"
//#include "forum.h"
//#include "thread.h"
class Thread;
class Forum;
class System;
class Person
{
protected:
    System* sys;

    std::list<int> currentForum; //apothikeuei ta epipeda pou vriskete o xristis se mia lista
    int currentThread; //an einai -1 tote dn einai se thread

    void nextStageFo(int ID);
    bool prevStageFo();
    bool einaiArithmos(char ch);
    int eisagwgiID();
public:
    Person(System* system);
    virtual ~Person();

    Forum* getCurrentFo();
    Thread* getCurrentTh();

    void browse();
    virtual int menuArxiko();
    virtual void viewArxiko();
    virtual int menuForum();
    virtual void viewForumMenu();
    virtual int menuThread();
    virtual void viewThreadMenu();

    virtual void katigoriaUser();
    void print();
    void printCurrentState();
};

enum simata
{
    EKSODOS = -1,
    SYNEXEIA = 0,
    EPANOEPIPEDO = 2,
    ARXIKO = 3

};

#endif
