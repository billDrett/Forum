#include "system.h"
#include "forum.h"
#include "thread.h"
#include "person.h"
using namespace std;

Person::Person(System* system)
{
    sys = system;
    currentThread = -1;
}

Person::~Person()
{
}

Forum* Person::getCurrentFo()
{//epistrefei to forum sto opoio vriskete
    list <int>::iterator it;
    if(currentForum.empty()==true) return NULL;
    Forum* fo = sys->getForum(currentForum.front());

    if(fo == NULL) return NULL;

    it = currentForum.begin(); //pairnei to forum apo to systima
    it++;
    for(; it != currentForum.end(); it++)
    {
        if((fo = fo->getForum(*it)) == NULL) // an prospathei na kanei get forum pou den yparxei na epistrefei NULL
        {
            return NULL;
        }
    }

    return fo;
}

Thread* Person::getCurrentTh()
{//epistrefei to thread pou vriskete
    Forum* fo;
    if(currentThread == -1) return NULL;

    fo = getCurrentFo();
    if(fo != NULL)
    {
        return fo->getThread(currentThread);
    }
    else
    {
        return NULL;
    }

}

void Person::browse()
{
    katigoriaUser();
    while(true)
    {
        if(menuArxiko() == EKSODOS)
        {
            break;
        }
    }
}

int Person::menuArxiko()
{//epiloges ston prwto epipedo
    char epilogi[10];
    int ID;

    this->print(); // diavasei ta stoixeia sto stadio pou vriskete
    this->viewArxiko(); //emfanizei tis epiloges sto prwto epipedo tou menu
    cin >>epilogi;
    cin.ignore(100000, '\n'); //katharismos buffer
    if(einaiArithmos(epilogi[0]) == true)
    {
        ID = atoi(epilogi);
        if(sys->getForum(ID) == NULL) //elenxos an antistixei se forum
        {
            return SYNEXEIA;
        }
        else
        {
            nextStageFo(ID); //neo current state

            int katastasi;
            while(true)
            {
                katastasi = menuForum();
                if(katastasi == EPANOEPIPEDO) return SYNEXEIA;
                else if(katastasi == EKSODOS) return EKSODOS;
                else if(katastasi == ARXIKO) return ARXIKO;
            }
        }
    }
    else if(epilogi[0] == 'L')
    {
        sys->apothikeusiKatastasis();
        return EKSODOS;

    }
    else if(epilogi[0] == 'X')
    {
        return EKSODOS;
    }
    else
    {
        cout<<"Lathos eisagwgi"<<endl;
        return SYNEXEIA;
    }
}

int Person::menuForum()
{
    char epilogi;
    int ID;
    Forum* fo;
    int katastasi;

    this->printCurrentState(); //emfanizei to forum pou vriskete autin tin stigmi
    this->print(); //emfanizei ta forums kai ta threads
    this->viewForumMenu();
    cin >>epilogi;
    cin.ignore(100000, '\n');
    switch(epilogi)
    {
    case 'F':
        ID = eisagwgiID();
        fo = this->getCurrentFo();
        if(fo->getForum(ID)== NULL) return SYNEXEIA;

        nextStageFo(ID);

        while(true) //proxwrame se allo forum
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
        while(true)//proxwrame se thread
        {
            katastasi = menuThread();
            if(katastasi == EPANOEPIPEDO) return SYNEXEIA;
            else if(katastasi == EKSODOS) return EKSODOS;
            else if(katastasi == ARXIKO) return ARXIKO;
        }

    case 'B'://pigainei ena epipedo panw
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

int Person::menuThread()
{
    char epilogi;

    this->printCurrentState();
    this->print();
    this->viewThreadMenu();
    cin >>epilogi;
    cin.ignore(100000, '\n');
    switch(epilogi)
    {
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

void Person::print()
{//diavazei ta stoixeia analoga me ta stadio pou vriskete
    Forum* fo;
    Thread* th;

    if(currentThread != -1) //an eimaste sto epipedo tou nimatos
    {
        th = getCurrentTh();
        if(th == NULL) return;
        th->print();
    }
    else //eimaste sto epipedo tou forum
    {
        fo = getCurrentFo();
        if(fo == NULL) //eimaste sto arxiko epipedo
        {
            sys->print();
        }
        else
        {
            fo->print();
        }
    }

}

void Person::printCurrentState()
{//emfanizei to forum kai to thread pou vriskete
    Forum* fo = getCurrentFo();
    Thread* th;
    if(fo== NULL) return;

    cout<<"Eiste sto forum: "<<fo->getTitle()<<endl;

    th = fo->getThread(currentThread);
    if(th == NULL) return;

    cout<<"Eiste sto nhma: "<<th->getTitle()<<endl;
}

bool Person::einaiArithmos(char ch)
{//elenxei an einai arithmos
    return ( '0'<=ch && ch <='9');
}

void Person::katigoriaUser()
{
    cout<<"Anikete stin katigoria episkeptis"<<endl;
}

int Person::eisagwgiID()
{
    int ID;
    cout<<"Eisagwgi ID : ";
    cin >>ID;
    cin.clear();
    cin.ignore(100000, '\n');

    return ID;
}


void Person::nextStageFo(int ID)
{
    currentForum.push_back(ID);
}

bool Person::prevStageFo()
{
    if(currentForum.empty() == true) return false;

    currentForum.pop_back();
    return true;
}

void Person::viewArxiko()
{
    //ola ta diathesima
    cout<<"Epilekste:"<<endl;
    cout<<"to ID tou forum pou epithymite na episkeftite"<<endl;
    cout<<"L, gia swsimo tis trexousas katastasis kai eksodo apo to systima"<<endl;
    cout<<"X, gia eksodo apo to systima, xwris na swthei i trexousa katastasi tou"<<endl;
}

void Person::viewForumMenu()
{
    cout<<"Epilekste:"<<endl;
    cout<<"F, gia na episkefteite ena forum apo ta parapanw"<<endl;
    cout<<"T, gia na episkefteite ena nhma apo ta parapanw"<<endl;
    cout<<"B, gia na pate ena epipedo epanw stin ierarxia tou sistimatos"<<endl;
    cout<<"H, gia epistrofi stin arxiki othoni(tin prwti pou vrainei meta tin eisodo sto systima)"<<endl;
    cout<<"L, gia swsimo tis trexousas katastasis kai eksodo apo to systima"<<endl;
    cout<<"X, gia eksodo apo to systima, xwris na swthei i trexousa katastasi tou"<<endl;
}

void Person::viewThreadMenu()
{
    cout<<"B, gia na pate ena epipedo epanw stin ierarxia tou systimatos"<<endl;
    cout<<"H, gia epistrofi stin arxiki othoni(tin prwti pou vrainei meta tin eisodo sto systima)"<<endl;
    cout<<"L, gia swsimo tis trexousas katastasis kai eksodo apo to systima"<<endl;
    cout<<"X, gia eksodo apo to systima, xwris na swthei i trexousa katastasi tou"<<endl;
}


