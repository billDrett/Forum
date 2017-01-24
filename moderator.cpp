#include <fstream>
#include "system.h"
#include "forum.h"
#include "thread.h"
#include "moderator.h"
#include "post.h"
using namespace std;

Moderator::Moderator(int ID, char* user, char* ps, System* system):RegisterUser(ID, user, ps, system)
{
}

int Moderator::menuThread()
{
//akrivos to idio me tou Person omos exei prostethei tis periptwseis tou moderator
    char epilogi;
    int ID;

    this->printCurrentState();
    this->print();
    this->viewThreadMenu();
    cin>>epilogi;
    cin.ignore(100000, '\n');
    switch(epilogi)
    {
    case 'R':
        this->makePost();
        return SYNEXEIA;
    case 'B':
        currentThread = -1;
        return EPANOEPIPEDO;
    case 'H':
        currentForum.clear(); //pame sto arxiko stadio
        currentThread = -1;
        return ARXIKO;
    case 'L':
        sys->apothikeusiKatastasis();
        return EKSODOS;
    case 'X':
        return EKSODOS;
    case 'D':
        if(this->deleteNima() == true) return EPANOEPIPEDO;//an diagrafike tote na paei sto panw epipedo
        cout<<"Apotixia diagrafis"<<endl;
        return SYNEXEIA;
    case 'M':
        if(this->moveNima() == true) return EPANOEPIPEDO;//an metakinithike tote na paei sto panw epipedo
        cout<<"Apotyxia metaforas"<<endl;
        return SYNEXEIA;
    case 'E':
        this->changeTitleNimatos();
        return SYNEXEIA;
    case 'Y':
        this->stickNima();
        return SYNEXEIA;
    case 'K':
        this->lockNima();
        return SYNEXEIA;
    case 'A':
        ID = eisagwgiID();

        this->deleteMinima(ID);
        return SYNEXEIA;
    case 'S':
        ID = eisagwgiID();

        this->moveMinima(ID);
        return SYNEXEIA;

    default:
        cout<<"Lathos eisagwgi"<<endl;
        return SYNEXEIA;
    }
}

void Moderator::viewThreadMenu()
{
    RegisterUser::viewThreadMenu();
    cout<<"D, gia na diagrapsete ena nima"<<endl;
    cout<<"M, gia na metakinisete to nima"<<endl;
    cout<<"E, gia na allaksete ton titlo tou nimatos"<<endl;
    cout<<"Y, gia na gini to nima ypomnima 'h na min einai pleon ypomnima"<<endl;
    cout<<"K, gia na kleidwsete 'h na ksekleidwsete to nima"<<endl;
    cout<<"A, gia na diagrapsete ena minima"<<endl;
    cout<<"S, gia na metakinisete ena minima"<<endl;
}

bool Moderator::deleteNima()
{
    Forum* fo = getCurrentFo();
    if(fo == NULL) return false;
    if(currentThread == -1) return false;

    fo->deleteThread(currentThread); //diagrafw to current thread
    currentThread = -1; //dn vriskomaste se thread
    return true;
}

bool Moderator::moveNima()
{
    Forum* fo1 = getCurrentFo();
    Forum* fo2;
    Thread* th;
    char ierarxia[50];

    if(fo1 == NULL) return false;

    cout<<"Eisagete tin ierarxia tou forum"<<endl;
    cin>>ierarxia;
    cin.ignore(100000, '\n');

    fo2 = sys->forumID(ierarxia); //vriskei to forum me autin tin ierarxia
    if(fo2 == NULL) return false;
    if(fo1->moveThread(currentThread, th) == false) return false;
    currentThread = -1; //pame ena epipedo panw
    fo2->addThread(th); //to prosthetw stin nea tou thesi
    return true;
}

void Moderator::changeTitleNimatos()
{
    char* titlos;
    Thread* th;

    titlos = eisagwgiTitlou();
    if(titlos == NULL) return;

    th = getCurrentTh();
    if(th == NULL) return;
    th->setTitle(titlos);

    delete[] titlos;
}

void Moderator::stickNima()
{
    Thread* th = getCurrentTh();
    if(th == NULL) return;

    th->setSticked(!th->getSticked()); //to thetw se antitheti katastasi apo auti pou vriskete
}

void Moderator::lockNima()
{
    Thread* th = getCurrentTh();
    if(th == NULL) return;

    th->setLocked(!th->getLocked()); //to thetw se antitheti katastasi apo auti pou vriskete
}

void Moderator::deleteMinima(int ID)
{
    Thread* th = getCurrentTh();
    if(th == NULL) return;

    th->delPost(ID);
}

void Moderator::moveMinima(int ID)
{
    Thread* th1 = getCurrentTh();
    Thread* th2;
    Post* p;
    char ierarxia[50];

    if(th1 == NULL) return;

    cout<<"Eisagete tin ierarxia tou nimatos"<<endl;
    cin>>ierarxia;
    cin.ignore(100000, '\n');

    th2 = sys->threadID(ierarxia); //epistrefei to forum me tin ierarxia
    if(th2 == NULL) return;
    if(th1->movePost(ID, p) == false) return; //pernoume to post
    th2->addPost(p); //to post metaferete se auto to thread
}

void Moderator::printData()
{
    cout<<id<<". "<<name<<" 2"<<endl;
}

void Moderator::katigoriaUser()
{
    cout<<"Anikete stin katigoria syntonistis"<<endl;
}

void Moderator::apothikeusiKatastasis(std::ofstream& usersFile)
{
    usersFile << id<<" " << name << " "<< pass<< " 2"<<endl;
}
