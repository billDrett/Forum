#ifndef Included_thread_H
#define Included_thread_H

#include <iostream>
#include <list>
#include <cstdlib>
#include <cstring>
//#include "post.h"
//#include "forum.h"
class Forum;
class Post;

class Thread
{
private:
    Forum* forum; //gia tin allagi thesis otan ginei stick
    int id;
    std::list <Post*> lista;
    char* title;
    bool locked;
    bool sticked;


public:
    Thread(int ID, char* Title, Forum* f, bool stick = false);
    ~Thread();

    //accesors
    int getID();
    Post* getPost(int ID);
    char* getTitle();
    bool getLocked();
    bool getSticked();
    char* getDimiourgos();
    int getDimiourgosID();

    //mutators
    void setTitle(char* titl);
    void setLocked(bool lock = true);
    void setSticked(bool stick = true);

    bool addPost(Post* post); //an einai kleidwmeno tote dn tha yparxei epilogi gia eggrafi
    bool movePost(int ID, Post*& post);
    bool delPost(int ID);

    void print();
    void apothikeusiKatastasis(std::ofstream& threadFile, std::ofstream& postFile, char* ierarxia);
};

#endif
