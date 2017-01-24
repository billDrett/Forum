#ifndef Included_REGISTERUSER_H
#define Included_REGISTERUSER_H

#include <iostream>
#include <cstring>
#include "person.h"

class RegisterUser: public Person
{
protected:
    int id;
    char* name;
    char* pass;

    char* eisagwgiTitlou();
public:
    RegisterUser(int ID, char* user, char* ps, System* system);
    ~RegisterUser();

    int getID();
    char* getName();
    char* getPass();

    void setName(char* n);
    void setPass(char* p);

    int menuForum();
    void viewForumMenu();
    int menuThread();
    void viewThreadMenu();

    void makeThread(); //kane ena neo thread sto epipedo forum pou vriskete
    void makePost(); //kanei ena post sto thread pou vrisketai

    virtual void printData();
    void katigoriaUser();
    virtual void apothikeusiKatastasis(std::ofstream& usersFile);

};

#endif
