#ifndef Included_ADMIN_H
#define Included_ADMIN_H

#include <iostream>
#include <cstring>
#include "moderator.h"

class Admin: public Moderator
{
public:
    Admin(int ID, char* user, char* ps, System* system);

    Forum* getLastFo();

    int menuArxiko();
    void viewArxiko();
    int menuForum();
    void viewForumMenu();
    int menuDiaxeirisiXriston();
    void viewDiaxeirisiXriston();

    void makeForum();
    bool moveForum();
    bool deleteForum();
    void changeTitleForum();

    void moveUser();
    void deleteUser();
    void changeNameUser();
    void changePassUser();

    void printData();
    void katigoriaUser();
    void apothikeusiKatastasis(std::ofstream& usersFile);
};

#endif
