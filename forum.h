#ifndef Included_forum_H
#define Included_forum_H

#include <iostream>
#include <list>
#include <cstdlib>
#include <cstring>
//#include "thread.h"

class Thread;
class Forum
{
private:
    int id;
    char* title;
    std::list<Forum*> forums;
    std::list<Thread*> themata;

public:
    Forum(int ID, char* titl);
    ~Forum();

    int getID();
    char* getTitle();
    Forum* getForum(int ID);
    Thread* getThread(int ID);

    void setTitle(char* titl);
    void setThreadSticked(int ID); //prepei na emfanizete prin apo ta alla threads

    void addForum(Forum* forum);
    void addThread(Thread* thread);

    bool moveForum(int ID, Forum*& forum);
    bool moveThread(int ID, Thread*& thread);

    bool deleteForum(int ID);
    bool deleteThread(int ID);

    void print();
    void apothikeusiKatastasis(std::ofstream& forumFile,std::ofstream& threadFile, std::ofstream& postFile, char* ierarxia);
};

#endif

