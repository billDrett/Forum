#ifndef Included_MODERATOR_H
#define Included_MODERATOR_H

#include <iostream>
#include <list>
#include <string>
#include <cstring>
//#include "system.h"
//#include "forum.h"
//#include "thread.h"
#include "registerUser.h"

class Moderator: public RegisterUser
{
protected:

public:
    Moderator(int ID, char* user, char* ps, System* system);

    int menuThread();
    void viewThreadMenu();

    bool deleteNima();
    bool moveNima();
    void changeTitleNimatos();
    void stickNima();
    void lockNima();

    void deleteMinima(int ID);
    void moveMinima(int ID);

    void printData();
    void katigoriaUser();
    void apothikeusiKatastasis(std::ofstream& usersFile);

};

#endif
