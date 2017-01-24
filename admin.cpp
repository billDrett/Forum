#include <fstream>
#include "system.h"
#include "forum.h"
#include "thread.h"
#include "admin.h"
#include "post.h"

using namespace std;

Admin::Admin(int ID, char* user, char* ps, System* system): Moderator(ID, user, ps, system)
{
}

Forum* Admin::getLastFo()
{//epistrefei to forum pou vriskete panw apo to currentForum
    list <int>::iterator it, itEnd;
    if(currentForum.size() <= 1) return NULL;
    Forum* fo = sys->getForum(currentForum.front());
    if(fo == NULL) return NULL;

    it = currentForum.begin();
    it++;//prosthesa me prwto apo to system
    itEnd = currentForum.end();
    itEnd--; //thelw to prw teleutaio
    for(; it != itEnd; ++it) //ola ta forum ektos apo to teleutaio
    {
        if((fo = fo->getForum(*it)) == NULL)
        {
            return NULL;
        }
    }

    return fo;
}

int Admin::menuArxiko()
{//idio me tou person apla exei prostethei i epilogi gia dimiourgia forum, kai diaxeirisi xristwn
    char epilogi[10];
    int ID;

    this->printCurrentState();
    this->print();
    this->viewArxiko();
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
    else if(epilogi[0] == 'N')
    {
        this->makeForum();
        return SYNEXEIA;
    }
    else if(epilogi[0] == 'U')
    {
        while(true)
        {
            if(menuDiaxeirisiXriston() == EKSODOS) return EKSODOS;
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

void Admin::viewArxiko()
{
    Moderator::viewArxiko();
    cout<<"N, gia dimiourgia neou forum"<<endl;
    cout<<"U, gia diaxeirisi xriston"<<endl;
}

int Admin::menuForum()
{//ektos apo tis leitourgies tou registeruser exoun prostethei kai autes tou admin
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
    case 'N':
        this->makeForum();
        return SYNEXEIA;
    case 'E':
        this->changeTitleForum();
        return SYNEXEIA;
    case 'D':
        if(this->deleteForum()== true) return EPANOEPIPEDO;
        cout<<"Apotyxia digrafis"<<endl;
        return SYNEXEIA;
    case 'M':
        if(this->moveForum()== true) return EPANOEPIPEDO;
        cout<<"Apotyxia metaforas"<<endl;
        return SYNEXEIA;
    default:
        cout<<"Lathos eisagwgi"<<endl;
        return SYNEXEIA;
    }
}
void Admin::viewForumMenu()
{
    Moderator::viewForumMenu();
    cout<<"N, gia dimiourgia neou forum"<<endl;
    cout<<"E, gia na allaksete ton titlo tou forum"<<endl;
    cout<<"D, gia na diagrapsete to forum, mazi me ola ta periexomena tou"<<endl;
    cout<<"M, gia na metakinisete to forum"<<endl;
}

int Admin::menuDiaxeirisiXriston()
{
    char epilogi;

    this->viewDiaxeirisiXriston(); //emfanizei tis epiloges
    cin >>epilogi;
    cin.ignore(100000, '\n');

    switch(epilogi)
    {
    case 'C':
        sys->printUsers();
        return SYNEXEIA;
    case 'M':
        this->moveUser();
        return SYNEXEIA;
    case 'D':
        this->deleteUser();
        return SYNEXEIA;
    case 'U':
        this->changeNameUser();
        return SYNEXEIA;
    case 'P':
        this->changePassUser();
        return SYNEXEIA;
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

void Admin::viewDiaxeirisiXriston()
{
    cout<<"C, gia na deite ton katalogo olon ton xriston"<<endl;
    cout<<"M, gia na allaksete katigoria gia ena xristi"<<endl;
    cout<<"D, gia na diagrapsete ena xristi"<<endl;
    cout<<"U, gia na allaksete to onoma enos xristi"<<endl;
    cout<<"P, gia na allaksete ton kwdiko prosvasis enos xristi"<<endl;
    cout<<"L, gia swsimo tis trexousas katastasis kai eksodo apo to systima"<<endl;
    cout<<"X, gia eksodo apo to systima, xwris na swthei i trexousa katastasi tou"<<endl;

}

void Admin::printData()
{
    cout<<id<<". "<<name<<" 3"<<endl;
}

void Admin::katigoriaUser()
{
    cout<<"Anikete stin katigoria diaxeiristis"<<endl;
}

void Admin::makeForum()
{
    if(currentThread != -1) return;//eimaste sto epipedo tou thread
    char* titlos = new char[sys->getMaxTitleSize()+1];
    Forum* fo;
    Forum* currentFo = getCurrentFo();

    titlos = eisagwgiTitlou();
    if(titlos == NULL) return;

    sys->setLastForumID(sys->getLastForumID() + 1);
    fo = new Forum(sys->getLastForumID(), titlos);

    if(currentFo == NULL)//eimaste sto epipedo tou system
    {
        sys->addForum(fo);
    }
    else
    {
        currentFo->addForum(fo);
    }

    delete[] titlos;
}

bool Admin::moveForum()
{
    Forum* fo1 = getCurrentFo();
    Forum* fo2;
    Forum* fo3;
    char ierarxia[50];

    if(fo1 == NULL) return false;

    cout<<"Eisagete tin ierarxia tou forum"<<endl;
    cin>>ierarxia;
    cin.ignore(100000, '\n');

    if(strcmp(ierarxia, "S") == 0) //na to metaferw sto system
    {
        fo2 = getLastFo(); // vriskoupe to forum pou einai ena epipedo panw apo to currentForum
        if(fo2 == NULL) return false; //vriskete idi katw apo to systima
        fo2->moveForum(fo1->getID(), fo3);
        sys->addForum(fo3); //mpike katw apo to systima

        this->prevStageFo(); //pame ena epipedo panw
        return true;
    }

    fo3 = sys->forumID(ierarxia); //katw apo poio forum tha paei
    if(fo3 == NULL) return false;

    fo2 = getLastFo();
    if(fo2 == NULL) //einai katw apo to sistima
    {
        sys->moveForum(fo1->getID(), fo1); //apothikeuw to forum sto fo1
    }
    else
    {
        fo2->moveForum(fo1->getID(), fo1);
    }

    if(fo1 == NULL) return false;
    this->prevStageFo(); //pame ena epipedo panw
    fo3->addForum(fo1);
    return true;
}

bool Admin::deleteForum()
{
    Forum* currentFo = getCurrentFo();
    Forum* lastFo = getLastFo();

    if(currentFo == NULL) return false;

    if(lastFo == NULL) //eimaste ena epipedo katw apo to sistima
    {
        sys->deleteForum(currentFo->getID());
        this->prevStageFo(); //pame ena epipedo panw
        return true;
    }

    lastFo->deleteForum(currentFo->getID());
    this->prevStageFo(); //pame ena epipedo panw
    return true;
}

void Admin::changeTitleForum()
{
    char* titlos = new char[sys->getMaxTitleSize()+1];
    Forum* fo;

    titlos = eisagwgiTitlou();
    if(titlos == NULL) return;

    fo = getCurrentFo();
    if(fo == NULL) return;
    fo->setTitle(titlos);

    delete[] titlos;
}

void Admin::moveUser()
{
    int ID, katigoria;

    ID = eisagwgiID();
    if(ID == this->id) return; //den epitrepete allagei stin katigoria tou xristi pou prospela to menu
                              //giati sto move ginete delete

    cout<<"Eisagete tin katigoria tou xristi anamesa sto 1-3 "<<endl;
    cin>> katigoria;
    cin.ignore(100000, '\n');
    if(katigoria<1 || katigoria > 3) return;

    sys->moveUser(ID, katigoria);
}

void Admin::deleteUser()
{
    int ID;

    ID =eisagwgiID();
    if(ID == this->id) return; //den epitrepete na diagrafei o xristi pou prospela to menu

    sys->deleteUser(ID);
}

void Admin::changeNameUser()
{
    char* n;
    RegisterUser* user;
    int ID;

    ID = eisagwgiID();

    user = sys->getPerson(ID);
    if(user == NULL) return; //elenxos an ontos yparxei

    n = new char[sys->getMaxNameSize()];
    cout<<"Eisagete to username tou xristi "<<endl;
    cin>>n;
    cin.ignore(100000, '\n');

    user->setName(n);
    delete[] n;
}

void Admin::changePassUser()
{
    char* n;
    RegisterUser* user;
    int ID;

    ID = eisagwgiID();

    user = sys->getPerson(ID);
    if(user == NULL) return;

    n = new char[sys->getMaxNameSize()];
    cout<<"Eisagete to password tou xristi "<<endl;

    cin>>n;
    cin.ignore(100000, '\n');

    user->setPass(n);
    delete[] n;
}

void Admin::apothikeusiKatastasis(std::ofstream& usersFile)
{
    usersFile << id<<" " << name << " "<< pass<< " 3"<<endl;
}
