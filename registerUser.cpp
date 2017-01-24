#include <fstream>
#include "registerUser.h"
#include "forum.h"
#include "thread.h"
#include "system.h"
#include "post.h"
using namespace std;

RegisterUser::RegisterUser(int ID, char* user, char* ps, System* system): Person(system)
{
    id = ID;

    name = new char[strlen(user)+1];
    strcpy(name, user);

    pass = new char[strlen(ps)+1];
    strcpy(pass, ps);
}

RegisterUser::~RegisterUser()
{
    delete[] name;
    delete[] pass;
}

int RegisterUser::getID()
{
    return id;
}

char* RegisterUser::getName()
{
    return name;
}

char* RegisterUser::getPass()
{
    return pass;
}

void RegisterUser::setName(char* n)
{
    delete[] name;
    name = new char[strlen(n)+1];
    strcpy(name, n);
}

void RegisterUser::setPass(char* p)
{
    delete[] pass;
    pass = new char[strlen(p)+1];
    strcpy(pass, p);
}

void RegisterUser::makeThread()
{//dimiourgei thread sto forum pou vriskete o xristis
    char* titlos;
    char keimeno[256]; //to megethos tou keimenou den kseperna tous 256 xaraktires
    Thread* th;
    Post* post;

    titlos = eisagwgiTitlou();
    if(titlos == NULL) return; //an proekipse sfalma na epistrepsei

    cout<<"Eisagete to keimeno ";
    cin.getline(keimeno, sizeof(keimeno));
    cout<<endl;
//cout<<"AS "<<sys->getLastThreadID()<<endl;
    sys->setLastThreadID(sys->getLastThreadID() + 1);
    th = new Thread(sys->getLastThreadID(), titlos, this->getCurrentFo()); //dimiourgia tou thread


    sys->setLastPostID(sys->getLastPostID()+1);
    post = new Post(sys->getLastPostID(), keimeno, this->id, this->sys); //dimiourgia tou post

    th->addPost(post); //prosthetei to post sto thread
    getCurrentFo()->addThread(th); // prosthetei to thread sto forum pou vriskete o user

    delete[] titlos;
}

void RegisterUser::makePost()
{//ftiaxnei ena post sto thread pou vriskete o user
    char keimeno[256]; //to megethos tou keimenou den kseperna tous 256 xaraktires
    Post* post;
    if(currentThread == -1)return;

    cout<<"Eisagete to keimeno ";
    cin.getline(keimeno, sizeof(keimeno));
    cout<<endl;

    sys->setLastPostID(sys->getLastPostID()+1);
    post = new Post(sys->getLastPostID(), keimeno, this->id, this->sys);
    if(getCurrentTh()->addPost(post) == false)
    {
        sys->setLastPostID(sys->getLastPostID()-1);
        cout<<"To thread einai kleidwmeno"<<endl;
        delete post;
    }

}

int RegisterUser::menuForum()
{//akrivos to idio me tou Person omos exei prostethei i periptwsi pou patise C
    char epilogi;
    int ID;
    Forum* fo;
    int katastasi;

    this->printCurrentState();
    this->print();
    this->viewForumMenu();
    cin >>epilogi;
    cin.ignore(100000, '\n');

    switch(epilogi)
    {
    case 'C':
        this->makeThread();
        return SYNEXEIA;
    case 'F':
        ID = eisagwgiID();
        fo = this->getCurrentFo();
        if(fo->getForum(ID)== NULL) return SYNEXEIA;

        nextStageFo(ID);

        while(true)
        {
            katastasi = menuForum();
            if(katastasi == EPANOEPIPEDO) return SYNEXEIA;
            else if(katastasi == EKSODOS) return EKSODOS;
            else if(katastasi == ARXIKO) return ARXIKO;
        }
    case 'T':
        ID = eisagwgiID();
        fo = this->getCurrentFo();
        if(fo->getThread(ID)== NULL) return SYNEXEIA;

        currentThread = ID;

        while(true)
        {
            katastasi = menuThread();
            if(katastasi == EPANOEPIPEDO) return SYNEXEIA;
            else if(katastasi == EKSODOS) return EKSODOS;
            else if(katastasi == ARXIKO) return ARXIKO;
        }

    case 'B':
        prevStageFo();
        return EPANOEPIPEDO;
    case 'H':
        currentForum.clear(); //pame sto arxiko stadio
        return ARXIKO;
    case 'L':
        sys->apothikeusiKatastasis();
        return EKSODOS;
    case 'X':
        return EKSODOS;
    default:
        cout<<"Lathos eisagwgi"<<endl;
        return SYNEXEIA;
    }
}

int RegisterUser::menuThread()
{//akrivos to idio me tou Person omos exei prostethei i periptwsi pou patise R
    char epilogi;

    this->printCurrentState();
    this->print();
    this->viewThreadMenu();
    cin >>epilogi;
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
    default:
        cout<<"Lathos eisagwgi"<<endl;
        return SYNEXEIA;
    }
}

void RegisterUser::viewForumMenu()
{
    Person::viewForumMenu();
    cout<<"C, gia na dimiourgisete ena neo nhma"<<endl;
}

void RegisterUser::printData()
{
    cout<<id<<". "<<name<<" 1"<<endl;
}

void RegisterUser::katigoriaUser()
{
    cout<<"Anikete stin katigoria eggegramenos xristis"<<endl;
}

char* RegisterUser::eisagwgiTitlou()
{
    char* titlos = new char[sys->getMaxTitleSize()+1];
    cout<<"Eisagwgi titlou ";
    cin.getline(titlos, sys->getMaxTitleSize()); //diavazei ton titlo me kena
    cout<<endl;
    if(cin.good() == false)
    {
        cin.clear();
        cin.ignore(100000, '\n'); //agnoeise ola ta ypoleipa
        cout<<"sfalma sto megethos tou titlou"<<endl;
        delete[] titlos;
        return NULL;
    }
    return titlos;
}

void RegisterUser::viewThreadMenu()
{
    Person::viewThreadMenu();
    cout<<"R, gia na apantisete sto nhma"<<endl;
}

void RegisterUser::apothikeusiKatastasis(std::ofstream& usersFile)
{
    usersFile << id<<" " << name << " "<< pass<< " 1"<<endl;
}
