#ifndef Included_system_H
#define Included_system_H

#include <iostream>
#include <list>
#include <cstring>
//#include "forum.h"
//#include "person.h"
//#include "registerUser.h"

class Thread;
class RegisterUser;
class Person;
class Forum;
class System
{
private:
    const char* const title;
    std::list <Forum*> forums;
    std::list <RegisterUser*> xristes;
    //IDs
    const int MAXTHREADTITLESIZE;
    const int MAXUSERNAMESIZE;
    const int MAXPASSWORDSIZE;
    int LastForumID;
    int LastThreadID;
    int LastPostID;
    int LastPersonID;

    RegisterUser* searchUsername(char* user);
    char* eisagwgiUsername();
    char* eisagwgiPassword();
    Forum* forumId(char* IDs, int& lastID);
    Thread* threadId(char* IDs, int& lastID); //epistrefei to thread xwris to teleutaio noumero ierarxias
    bool loadForums();
    bool loadThreads();
    bool loadPosts();
    bool loadUsers();
public:
    //kataskeui apo arxeio allages
    System();
    ~System();


    Forum* getForum(int ID);
    RegisterUser* getPerson(int ID);
    int getMaxTitleSize();
    int getMaxNameSize();
    int getMaxPasswordSize();
    int getLastForumID();
    int getLastThreadID();
    int getLastPostID();
    int getLastPersonID();

    void setLastForumID(int i);
    void setLastThreadID(int i);
    void setLastPostID(int i);
    void setLastPersonID(int i);

    void addForum(Forum* forum);
    bool moveForum(int ID, Forum*& forum);
    bool deleteForum(int ID);

    void addUser(RegisterUser* user);
    bool moveUser(int ID, int katigoria);
    bool deleteUser(int ID);

    void apothikeusiKatastasis();
    RegisterUser* eggrafiXristi();
    Person* eisodosXristi();

    Forum* forumID(char* IDs);
    Thread* threadID(char* IDs);
    char* searchUserID(int ID);

    void print();
    void printUsers();
    void browse(bool eggrafi);
};

#endif
