#include <cstdio>
#include <fstream>
#include "post.h"
#include "forum.h"
#include "thread.h"
using namespace std;

Thread::Thread(int ID, char* Title,Forum* f, bool stick)
{
    id = ID;
    sticked = stick;
    locked = false;
    forum = f;

    title = new char[strlen(Title)+1];
    strcpy(title, Title);
}

Thread::~Thread()
{
    list <Post*>::iterator it;
    for(it = lista.begin(); it != lista.end(); it++)
    {
        delete *it;
    }
    lista.clear();

    delete[] title;
}

int Thread::getID()
{
    return id;
}

char* Thread::getTitle()
{
    return title;
}

Post* Thread::getPost(int ID)
{//vriskei to post pou exei auto to ID
    list <Post*>::iterator it;
    for(it = lista.begin(); it != lista.end(); it++)
    {
        if((*it)->getID() == ID)
        {
            return *it;
        }
    }
    return NULL;
}

bool Thread::getLocked()
{
    return locked;
}

bool Thread::getSticked()
{
    return sticked;
}

char* Thread::getDimiourgos()
{//epistrefei ton dimiourgo tou thread
    if(lista.empty()==true) return NULL;
    return lista.front()->getUsername();
}

int Thread::getDimiourgosID()
{
    if(lista.empty()==true) return -1;
    return lista.front()->getUserID();
}

void Thread::setTitle(char* titl)
{
    delete[] title;
    title = new char[strlen(titl)+1];
    strcpy(title, titl);
}

void Thread::setLocked(bool lock)
{
    locked = lock;
}

void Thread::setSticked(bool stick)
{
    sticked = stick;
    if(sticked == true)
    {
        forum->setThreadSticked(id); //prepei na mpei stin arxi tis listas tou forum pou to periexei
    }
}

bool Thread::addPost(Post* post)
{//prosthetei to post sto telos tis listas
    if(locked == true) return false;

    lista.push_back(post);
    return true;
}

bool Thread::movePost(int ID, Post*& post)
{//vriskei to post me ID kai to apothikeuei sto post
    list <Post*>::iterator it;
    for(it = lista.begin(); it != lista.end(); it++)
    {
        if((*it)->getID() == ID)
        {
            post = *it; //to apothikeuei edw
            lista.erase(it); //to afairei apo tin lista
            return true;
        }
    }

    post = NULL;
    return false; //den vrethike mexri to telos
}

bool Thread::delPost(int ID)
{
    Post* p;

    if(movePost(ID, p) == true)
    {
        delete p; //to diagrafei
        return true;
    }
    return false;
}

void Thread::print()
{//emfanizei ola ta minimata tou thread
    cout<<"Minymata:"<<endl;
    list <Post*>::iterator it;
    for(it = lista.begin(); it != lista.end(); it++) //emfanisi olon ton stoixeiwn tis listas
    {
        (*it)->print();
    }
}

void Thread::apothikeusiKatastasis(ofstream& threadFile, ofstream& postFile, char* ierarxia)
{
    char buffer [10];
    int thesi = strlen(ierarxia);
    char lock, stick;

    ierarxia[thesi] = '.'; //prepei na exei kai to id tou thread
    ierarxia[thesi+1] = '\0';
    sprintf (buffer, "%d", id);//to metatrepoume se string
    strcat(ierarxia, buffer); //i ierarxia exei pleon kai to id tou thread

    if(locked == true) lock = 'L';
    else lock = 'N';

    if(sticked == true) stick = 'S';
    else stick = 'N';

    threadFile << ierarxia <<" "<< stick <<" "<< lock <<" "<<getDimiourgosID()<<" "<< title<<endl;

    list <Post*>::iterator it;
    for(it = lista.begin(); it != lista.end(); it++)//egrafi twn post sto arxeio
    {
        (*it)->apothikeusiKatastasis(postFile, ierarxia);
    }

    ierarxia[thesi] = '\0'; //afairw apo tin ierarxia to id tou thread
}
