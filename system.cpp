#include <fstream>
#include "forum.h"
#include "person.h"
#include "registerUser.h"
#include "moderator.h"
#include "admin.h"
#include "system.h"
#include "thread.h"
#include "post.h"
using namespace std;


System::System():title("D.I.T. Lists"), MAXTHREADTITLESIZE(40), MAXUSERNAMESIZE(15), MAXPASSWORDSIZE(15)
{
    LastForumID = 1; //arxikopoihsh se periptwsi pou dn yparxoun ta arxeia gia load
    LastThreadID = 1;
    LastPostID = 1;
    LastPersonID =1;

    loadForums();
    loadThreads();
    loadUsers();
}

System::~System()
{
    list <Forum*>::iterator it1; //diagrafei ola ta forums
    for(it1 = forums.begin(); it1 != forums.end(); it1++)
    {
        delete *it1;
    }
    forums.clear();

    list <RegisterUser*>::iterator it2; //diagrafei ola ta threads
    for(it2 = xristes.begin(); it2 != xristes.end(); it2++)
    {
        delete *it2;
    }
    xristes.clear();
}

Forum* System::getForum(int ID)
{//epistregei to forum me ID
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

RegisterUser* System::getPerson(int ID)
{//epistrefei ton user me ID
    list <RegisterUser*>::iterator it;
    for(it = xristes.begin(); it != xristes.end(); it++)
    {
        if((*it)->getID() == ID)
        {
            return *it;
        }
    }

    return NULL;
}

int System::getMaxTitleSize()
{
    return MAXTHREADTITLESIZE;
}

int System::getMaxNameSize()
{
    return MAXUSERNAMESIZE;
}

int System::getMaxPasswordSize()
{
    return MAXPASSWORDSIZE;
}

int System::getLastForumID()
{
    return LastForumID;
}

int System::getLastThreadID()
{
    return LastThreadID;
}

int System::getLastPostID()
{
    return LastPostID;
}

int System::getLastPersonID()
{
    return LastPersonID;
}

void System::setLastForumID(int i)
{
    LastForumID = i;
}
void System::setLastThreadID(int i)
{
    LastThreadID = i;
}
void System::setLastPostID(int i)
{
    LastPostID = i;
}
void System::setLastPersonID(int i)
{
    LastPersonID = i;
}

void System::apothikeusiKatastasis()
{
    char ierarxia[256];
    ierarxia[0] = '\0';
    ofstream forumFile("forumhierarchy.save");
    ofstream threadFile("thread.save");
    ofstream postFile("post.save");
    ofstream usersFile("users.save");

    list <Forum*>::iterator it1;
    for(it1 = forums.begin(); it1 != forums.end(); it1++)
    {
        (*it1)->apothikeusiKatastasis(forumFile, threadFile, postFile, ierarxia);
    }

    list <RegisterUser*>::iterator it2;
    for(it2 = xristes.begin(); it2 != xristes.end(); it2++)
    {
        (*it2)->apothikeusiKatastasis(usersFile);
    }

    forumFile.close();
    threadFile.close();
    postFile.close();
    usersFile.close();
}

RegisterUser* System::eggrafiXristi()
{
    RegisterUser* p;
    char* onoma;
    char* pass;

    onoma = eisagwgiUsername(); //diavazei to username
    if(searchUsername(onoma) != NULL || strcmp(onoma, "") == 0) //an yparxei 'h einai to keno
    {
        delete[] onoma;
        return NULL;
    }

    pass = eisagwgiPassword();
    if(strcmp(pass, "") == 0) //dn mporei to pass na einai keno
    {
        delete[] onoma;
        delete[] pass;
        return NULL;
    }
    //eggegrammenos
    p = new RegisterUser (++LastPersonID, onoma, pass, this);
    xristes.push_back(p);

    delete[] onoma; //den mas xreiazontai pleon gia to user exei dika tou strings
    delete[] pass;
    return p;
}

Person* System::eisodosXristi()
{
    RegisterUser* atomo;
    char* onoma;
    char* pass;

    cout<<"Kalos hrthate sto D.I.T Lists"<<endl;
    cout<<"Parakalw dwste onoma xristi kai kwdiko prosvasis"<<endl;
    onoma = eisagwgiUsername();
    pass = eisagwgiPassword();
    if(strcmp(onoma, "") == 0 && strcmp(pass, "") == 0) //eisagwgi os aplos xristis
    {
        delete[] onoma;
        delete[] pass;
        return new Person(this);
    }

    atomo = searchUsername(onoma);
    delete[] onoma;
    if(atomo == NULL) //elenxo an yparxei to onoma
    {
        delete[] pass;
        return NULL;
    }

    if(strcmp(pass, atomo->getPass()) == 0) //an antoistoixei to password
    {
        delete[] pass;
        return atomo;
    }
    delete[] pass;
    return NULL;
}

RegisterUser* System::searchUsername(char* user)
{//psaksimo user me vasi to username tou
    list <RegisterUser*>::iterator it;
    for(it = xristes.begin(); it != xristes.end(); it++)
    {
        if(strcmp((*it)->getName(), user)== 0)
        {
            return *it;
        }
    }

    return NULL;
}
Forum* System::forumId(char* IDs, int& lastID)
{//lamvanei tin ierarxia kai epistrefei to forum pou antistoixei se autin
 //kathos kai to teleutaio noumero gia na to kanei oti thelei
    Forum* forum = NULL;
    char str[100]; //ypotheto oti to id dn ksepernaei tous 100 xaraktires
    lastID = -1;

    int j =0;
    for(int i =0; IDs[i] != '\0'; i++)
    {
        if(IDs[i] == '.') //otan sinantw teleia prepei na pernw to forum
        {
            str[j] = '\0';
            j=0;
            if(forum == NULL) //to prwto einai tou system
            {
                forum = getForum(atoi(str));
            }
            else
            {
                forum = forum->getForum(atoi(str));
            }

            if(forum == NULL)return NULL; //ypirxe kapoio sfama sto path tou forum
        }
        else
        {
            str[j] = IDs[i];
            j++;
        }
    }

    if(j != 0)//oi aritmoi pou emeinan einai o teleutaios arithmos
    {
        str[j] = '\0';
        lastID = atoi(str);
    }
    return forum;
}
Thread* System::threadId(char* IDs, int& lastID)
{//lamvanei tin ierarxia kai epistrefei to thread pou antistoixei se autin
 //kathos kai to teleutaio noumero gia na to kanei oti thelei
    Forum* forum = NULL;
    Thread* thread;
    char str[100]; //ypotheto oti to id dn ksepernaei tous 100 xaraktires
    list <int> ids; //apothikeuei ta id se mia oura
    lastID = -1;

    int j =0;
    for(int i =0; IDs[i] != '\0'; i++)
    {
        if(IDs[i] == '.')
        {
            str[j] = '\0';
            j = 0;
            ids.push_back(atoi(str)); //apothikeuw se mia oura to ID
        }
        else
        {
            str[j] = IDs[i];
            j++;
        }
    }

    if(ids.size()<2) return NULL;// prepei na einai toulaxiston 2

    forum = this->getForum(ids.front()); //to prwto id einai tou system
    ids.pop_front(); //to vgazw kai apo tin oura
    if(forum == NULL) return NULL;

    while(ids.size() != 0)
    {
        if(ids.size() == 1) //to teleutaio xrisimopoioutai gia to id tou thread
        {
            thread = forum->getThread(ids.front()); //size == 1
            ids.pop_front();
            str[j] = '\0';
            lastID = atoi(str);
            return thread;
        }
        forum = forum->getForum(ids.front());
        ids.pop_front();
        if(forum == NULL) return NULL;
    }

    return NULL;
}
Forum* System::forumID(char* IDs)
{//epistrefei to forum me vasi to string ierarxia
    int number = -1;
    Forum* forum = this->forumId(IDs, number);

    if(number == -1) return NULL;
    if(forum == NULL) //ama dn exei vrethei se allo forum einai apo to system
    {
        return getForum(number);
    }
    forum = forum->getForum(number);
    return forum;
}

Thread* System::threadID(char* IDs)
{//epistrefei to thread me vasi to string ierarxia
    int number = -1;
    Forum* forum = this->forumId(IDs, number);;
    Thread* th;

    if(number == -1) return NULL;
    if(forum == NULL) return NULL;

    th = forum->getThread(number);
    return th;
}

char* System::searchUserID(int ID)
{//psaxnei me vasi to ID tou user
    list <RegisterUser*>::iterator it;
    for(it = xristes.begin(); it != xristes.end(); it++)
    {
        if((*it)->getID() == ID)
        {
            return (*it)->getName();
        }
    }

    return NULL;
}

void System::print()
{//emfanizei ta diathesima forum
    cout<<"Diathesima forum:"<<endl;
    list <Forum*>::iterator it;
    for(it = forums.begin(); it != forums.end(); it++)
    {
        cout<<(*it)->getTitle()<<" (ID: "<<(*it)->getID()<<")"<<endl;
    }
}

void System::printUsers()
{//emfanizei tous users
    cout<<"Diathesimoi xristes:"<<endl;
    list <RegisterUser*>::iterator it;
    for(it = xristes.begin(); it != xristes.end(); it++)
    {
        (*it)->printData();
    }
}

void System::addForum(Forum* forum)
{
    forums.push_back(forum);
}

bool System::moveForum(int ID, Forum*& forum)
{//vriskei to forum me auto to ID kai to apothikeuei sto thread pou pairnei os orisma
    list <Forum*>::iterator it;
    for(it = forums.begin(); it != forums.end(); it++)
    {
        if((*it)->getID() == ID)
        {
            forum = *it;
            forums.erase(it);
            return true;
        }
    }

    forum = NULL;
    return false; //den vrethike mexri to telos
}

bool System::deleteForum(int ID)
{
    Forum* fo;
    if(moveForum(ID, fo)== true)
    {
        delete fo;
        return true;
    }
    return false;
}

void System::addUser(RegisterUser* user)
{
    xristes.push_back(user);
}

bool System::moveUser(int ID, int katigoria)
{//allazei katigoria sto xristi
    RegisterUser* user;
    if(katigoria<1 || katigoria > 3) return false;

    list <RegisterUser*>::iterator it;
    for(it = xristes.begin(); it != xristes.end(); it++)
    {
        if((*it)->getID() == ID) //vriskei to user
        {
            user = *it;
            if(katigoria == 1)//kai ton ksanadimiourgei se diaforetiki katigoria
            {
                *it = new RegisterUser(user->getID(), user->getName(), user->getPass(), this);
            }
            else if(katigoria == 2)
            {
                *it = new Moderator(user->getID(), user->getName(), user->getPass(), this);
            }
            else //katigorai ==3
            {
                *it = new Admin(user->getID(), user->getName(), user->getPass(), this);
            }
            delete user; //ton diagrafei apo tin proigoumeni katigoria pou itan
        }
    }

    return NULL;
}

bool System::deleteUser(int ID)
{
    list <RegisterUser*>::iterator it;
    for(it = xristes.begin(); it != xristes.end(); it++)
    {
        if((*it)->getID() == ID)//vriskei to user kai ton diagrafei
        {
            delete *it;
            xristes.erase(it);
            return true;
        }
    }

    return false; //den vrethike mexri to telos
}
char* System::eisagwgiUsername()
{
    char* onoma = new char[MAXUSERNAMESIZE +1];

    cout<<"Onoma xristi: "<<endl;
    cin.getline(onoma, MAXUSERNAMESIZE);
    cout<<endl;
    if(cin.good() == false)
    {
        cin.clear();
        cin.ignore(100000, '\n');
        cout<<"sfalma sto megethos tou username"<<endl;
        delete[] onoma;
        return NULL;
    }
    return onoma;
}

char* System::eisagwgiPassword()
{
    char* pass = new char[MAXPASSWORDSIZE + 1];

    cout<<"Password: "<<endl;
    cin.getline(pass, MAXPASSWORDSIZE);
    cout<<endl;
    if(cin.good() == false)
    {
        cin.clear();
        cin.ignore(100000, '\n');
        cout<<"sfalma sto megethos tou password"<<endl;
        delete[] pass;
        return NULL;
    }
    return pass;
}

void System::browse(bool eggrafi)
{
    Person* pel;
    if(eggrafi == true)
    {
        pel = eggrafiXristi();
    }
    else
    {
        pel = eisodosXristi();
    }
    if(pel == NULL)
    {
        cout<<"Den yparxei autos o xristis"<<endl;
        return;
    }

    pel->browse(); //kaleite i browse analoga tou Person, diaforetiki analoga me to ti eidous einai
}

bool System::loadForums()
{
    Forum* forum;
    Forum* newForum;
    char ierarxia[100];
    char titlos[MAXTHREADTITLESIZE];
    int lastNumber, maxLastNumber=-1;

    ifstream input("forumhierarchy.save");
    if(!input) return false; //an dn anoixtike epistrofi
    while(!input.eof())
    {//diavasma simfwna me to motivo tou arxeiou
        input >> ierarxia;
        input.ignore(1);
        input.getline(titlos, MAXTHREADTITLESIZE); //diavasma me getline giati o titlos mporei na exei kena
        if(input.fail() ==true) break;

        forum = this->forumId(ierarxia, lastNumber);
        if(lastNumber == -1) continue; //lathos stin ierarxia

        newForum = new Forum(lastNumber, titlos);
        if(forum == NULL) // to vazoume katw apo to sistima
        {
            addForum(newForum);
        }
        else
        {
            forum->addForum(newForum);
        }

        if(maxLastNumber < lastNumber) maxLastNumber = lastNumber;
    }

    LastForumID = maxLastNumber;
    return true;
}

bool System::loadThreads()
{
    list <Thread*> kleismenaThemata;
    Forum* forum;
    Thread* thread;
    char ierarxia[100];
    char titlos[MAXTHREADTITLESIZE];
    char stick, lock;
    bool sticked, locked;
    int  arithmos, lastNumber, maxLastNumber = -1;

    ifstream input("thread.save");
    if(!input) return false;
    while(!input.eof())
    {
        input >> ierarxia >> stick >>lock >> arithmos; //to arithmos dn xrisimopoihte pouthena

        input.ignore(1);
        input.getline(titlos, MAXTHREADTITLESIZE);//epeidi exw kena to diavazw me tin getiline
        if(input.fail() ==true) break;

        forum = this->forumId(ierarxia, lastNumber);
        if(forum == NULL) continue;
        if(stick != 'S' && stick != 'N') continue;
        if(lock != 'L' && lock != 'N') continue;

        if(stick == 'S')sticked = true;
        else sticked = false;

        if(lock == 'L')locked = true;
        else locked = false;

        thread = new Thread(lastNumber,titlos, forum, sticked);
        if(locked == true)//prosthesi stin lista me ta kleidomena
        {
            kleismenaThemata.push_front(thread);
        }
        forum->addThread(thread);
        if(maxLastNumber < lastNumber)
        {
            maxLastNumber = lastNumber;
        }
    }
    LastThreadID = maxLastNumber;
    loadPosts(); //fortwsi ton posts gia ta thread
    while(kleismenaThemata.empty()== false) //kleidwmena oson thread prepei na kleidwthoun
    {
        kleismenaThemata.front()->setLocked(true);
        kleismenaThemata.pop_front();
    }
    return true;
}

bool System::loadPosts()
{
    Thread* thread;
    Post* post;
    char ierarxia[100];
    char text[256];
    int idUser, idPost, maxId = -1;

    ifstream input("post.save");
    if(!input) return false;
    while(!input.eof())
    {
        input >> ierarxia >> idUser;
        input.ignore(1);
        input.getline(text, 256);//epeidi mporei na exei kena
        if(input.fail() ==true) break;

        thread = threadId(ierarxia, idPost); //vrisko to thread pou antistoixi stin ierarxia
        if(thread == NULL) continue;

        post = new Post(idPost, text, idUser,this);
        thread->addPost(post);//to prosthetw sto thread
        if(maxId < idPost)
        {
            maxId = idPost;
        }
    }

    LastPostID = maxId;
    return true;
}

bool System::loadUsers()
{
    RegisterUser* xristis;
    char user[MAXUSERNAMESIZE];
    char pass[MAXPASSWORDSIZE];
    int id, maxId = -1, katigoria;

    ifstream input("users.save");
    if(!input) return false;
    while(!input.eof())
    {
        input >> id >> user >>pass >> katigoria;
        if(input.fail() ==true) break;

        if(katigoria < 1 || katigoria >3) continue;

        if(katigoria == 1)//analoga me tin katigoria na dimiourgite o analogos xristis
        {
            xristis = new RegisterUser(id, user, pass, this);
        }
        else if(katigoria == 2)
        {
            xristis = new Moderator(id, user, pass, this);
        }
        else
        {
            xristis = new Admin(id, user, pass, this);
        }https://d1b10bmlvqabco.cloudfront.net/attach/ikvdqntis1d341/ifie6zo4ial2rx/il485y95t9gx/dataset100.txt

        this->addUser(xristis);

        if(maxId < id)
        {
            maxId = id;
        }
    }

    LastPersonID = maxId;
    return true;
}
