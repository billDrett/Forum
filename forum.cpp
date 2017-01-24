#include <cstdio>
#include <fstream>
#include "thread.h"
#include "forum.h"

using namespace std;

Forum::Forum(int ID, char* titl)
{
    id = ID;
    title = new char[strlen(titl)+1];
    strcpy(title, titl);
}

Forum::~Forum()
{
    list <Forum*>::iterator it1; //diagrafei ola ta forums
    for(it1 = forums.begin(); it1 != forums.end(); it1++)
    {
        delete *it1;
    }
    forums.clear();

    list <Thread*>::iterator it2; //diagrafei ola ta threads
    for(it2 = themata.begin(); it2 != themata.end(); it2++)
    {
        delete *it2;
    }
    themata.clear();

    delete[] title;
}

int Forum::getID()
{
    return id;
}

char* Forum::getTitle()
{
    return title;
}

Forum* Forum::getForum(int ID)
{//epistrefei to forum me ID
    list <Forum*>::iterator it;
    for(it = forums.begin(); it != forums.end(); it++)
    {
        if((*it)->getID() == ID)
        {
            return *it;
        }
    }

    return NULL;
}

Thread* Forum::getThread(int ID)
{//epistrefei to Thread me ID
    list <Thread*>::iterator it;
    for(it = themata.begin(); it != themata.end(); it++)
    {
        if((*it)->getID() == ID)
        {
            return *it;
        }
    }

    return NULL;
}

void Forum::setTitle(char* titl)
{
    delete[] title;
    title = new char[strlen(titl)+1];
    strcpy(title, titl);
}

 void Forum::setThreadSticked(int ID)
 {
    list <Thread*>::iterator it;

    for(it = themata.begin(); it != themata.end(); it++)
    {
        if((*it)->getID() == ID) //vriskei to thread me ID
        {
            themata.push_front(*it); //to vazei mposta stin lista
            themata.erase(it);//to afairw apo tin thesi pou itan kai to vazw stin arxi
            return;
        }
    }
 }

void Forum::addForum(Forum* forum)
{
    forums.push_back(forum);
}

void Forum::addThread(Thread* thread)
{
    if(thread->getSticked() == true)
    {
        themata.push_front(thread);
        return;
    }

    themata.push_back(thread);
}

bool Forum::moveForum(int ID, Forum*& forum)
{//vriskei to forum me auto to ID kai to apothikeuei sto forum pou pairnei os orisma
    list <Forum*>::iterator it;
    for(it = forums.begin(); it != forums.end(); it++)
    {
        if((*it)->getID() == ID)
        {
            forum = *it; //to vazei ston pointer forum
            forums.erase(it); //kai to afairei apo tin lista
            return true;
        }
    }

    forum = NULL;
    return false; //den vrethike mexri to telos
}

bool Forum::moveThread(int ID, Thread*& thread)
{//vriskei to thread me auto to ID kai to apothikeuei sto thread pou pairnei os orisma
    list <Thread*>::iterator it;
    for(it = themata.begin(); it != themata.end(); it++)
    {
        if((*it)->getID() == ID)
        {
            thread = *it;
            themata.erase(it);
            return true;
        }
    }

    thread = NULL;
    return false; //den vrethike mexri to telos
}

bool Forum::deleteForum(int ID)
{
    Forum* fo;
    if(moveForum(ID, fo)== true)
    {
        delete fo;
        return true;
    }
    return false;
}

bool Forum::deleteThread(int ID)
{
    Thread* t;
    if(moveThread(ID, t) == true)
    {
        delete t;
        return true;
    }
    return false;
}

void Forum::print()
{//emfanizei ta perienxomena tou forum
    cout<<"Diathesima forum:"<<endl;
    list <Forum*>::iterator it1;
    for(it1 = forums.begin(); it1 != forums.end(); it1++) //emfanisi olon ton stoixeiwn tis listas forum
    {
        cout<<(*it1)->getTitle()<<" (ID: "<<(*it1)->getID()<<")"<<endl;
    }

    cout<<"Diathesima nhmata:"<<endl;
    list <Thread*>::iterator it2;
    for(it2 = themata.begin(); it2 != themata.end(); it2++) //emfanisi olon ton stoixeiwn tis listas thread
    {
        if((*it2)->getSticked() == true)
        {
            cout<<"Ypomnima:";
        }
        if((*it2)->getDimiourgos() ==NULL)
        {
            cout<<(*it2)->getTitle()<<" (ID:"<<(*it2)->getID()<<")"<<endl;
        }
        else
        {
            cout<<(*it2)->getTitle()<<" apo "<<(*it2)->getDimiourgos()<< " (ID:"<<(*it2)->getID()<<")"<<endl;
        }
    }

}

void Forum::apothikeusiKatastasis(std::ofstream& forumFile,std::ofstream& threadFile, std::ofstream& postFile, char* ierarxia)
{
    char buffer [10];
    int thesi = strlen(ierarxia);

    if(thesi != 0)
    {
        ierarxia[thesi] = '.'; //prepei na exei kai to id tou thread
    }
    sprintf (buffer, "%d", id);//metatrepoume to id se string
    ierarxia[thesi+1] = '\0';
    strcat(ierarxia, buffer); //i ierarxia exei pleon kai to id tou thread

    forumFile <<ierarxia<<" "<<title<<endl; //egrafei tws xaraktiristikwn tou forum sto arxeio

    list <Forum*>::iterator it1;
    for(it1 = forums.begin(); it1 != forums.end(); it1++) //apothikeusi gia kathe forum
    {
        (*it1)->apothikeusiKatastasis(forumFile, threadFile, postFile, ierarxia);
    }

    list <Thread*>::iterator it2;
    for(it2 = themata.begin(); it2 != themata.end(); it2++) //apothikeusi gia kathe thread
    {
        (*it2)->apothikeusiKatastasis(threadFile, postFile, ierarxia);
    }

    ierarxia[thesi] = '\0'; //afairesi apo tin ierarxia tou id tou forum
}

