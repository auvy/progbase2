#pragma once

#include "storage.h"

class Cui
{
    Storage * const storage_;

    // dinos menus
    void dinoMenu(int d);
    void dinoMainMenu();
    void dinoOperateMenu();

    void dinoViewMenu(int id);
    void dinoUpdateMenu(int id);
    void dinoRemoveMenu(int id);

    void dinoCreateMenu();



    void perMenu(int p);
    void perMainMenu();
    void perOperateMenu();

    void perViewMenu(int id);
    void perUpdateMenu(int id);
    void perRemoveMenu(int id);

    void perCreateMenu();


    
public:
    Cui(Storage * storage): storage_(storage) {}
    //
    void show();
};