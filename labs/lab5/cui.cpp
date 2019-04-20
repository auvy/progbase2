#include "cui.h"

using std::cout;
using std::endl;
using std::cin;




void Cui::show()
{
    bool running = true;
    int key = 0;
    while(running)
    {
        system("clear");
        cout << "/MAIN MENU/" << endl;
        cout << "1. Dinosaurs Menu" << endl;
        cout << "2. Periods Menu" << endl;
        cout << "0. Quit program" << endl;
        cin >> key;
        system("clear");
        switch (key)
        {
            case 1: dinoMainMenu(); break;
            case 2: perMainMenu(); break;
            case 0: 
            {
                running = false; 
                this->storage_->save(); 
                break;
            }
            default: break;
        }
    }
}




void printDino(Dino & d)
{
    cout << "Viewing dinosaur: " << endl;
    cout << "[" << d.id << "]" << "," << d.name << "," << d.per << "," << d.fam << "," << d.disc << "," << d.mass << endl;
}

void printCompDinoList(vector<Dino> & dinos)
{
    cout<<"/DINOSAUR MENU/" << endl;
    cout<<"Dino list (shortened):" << endl;
    for(Dino & d : dinos)
    {
        cout << "[" << d.id << "]" << d.name << endl;
    }
    cout << endl;
}

void Cui::dinoMainMenu()
{
    bool running = true;
    int key = 0;
    int id = -1;
    system("clear");
    while(running)
    {
        vector<Dino> dinos = this->storage_->getAllDinos();
        printCompDinoList(dinos);

        cout << "Options:" << endl;
        cout << "1. Dino Operations\n2. Create new dino\n0. Back\n" << endl;
        cin >> key;
        system("clear");
        switch (key)
        {
            case 1: system("clear"); dinoOperateMenu(); break;
            case 2: system("clear"); dinoCreateMenu(); break;
            case 0: running = false; this->storage_->save(); break;
            default: break;
        }
    }
}
void Cui::dinoOperateMenu()
{
    bool running = true;
    int key = 0;
    int id = -1;
    while(running)
    {
        cout << "/DINO OPERATIONS MENU/" << endl;
        cout << "1. View dino" << endl;
        cout << "2. Update dino" << endl;
        cout << "3. Remove dino" << endl;
        cout << "0. Back" << endl;
        cin >> key;
        system("clear");
        switch (key)
        {
            case 1: 
            {
                cout << "Enter id: ";
                cin >> id;
                system("clear");
                dinoViewMenu(id);
                break;
            }
            case 2:
            {
                cout << "Enter id: ";
                cin >> id;
                system("clear");
                dinoUpdateMenu(id);
                break;
            }
            case 3:
            {
                cout << "Enter id: ";
                cin >> id;
                system("clear");
                dinoRemoveMenu(id);
                break;
            }
            case 0: running = false;this->storage_->save(); break;
            default: break;
        }
    }
}
void Cui::dinoViewMenu(int id)
{
    system("clear");
    optional<Dino> d_opt = this->storage_->getDinoById(id);
    if (d_opt)
    {
        Dino & d = d_opt.value();
        printDino(d);
    }
    else
    {
        cout << "NO DINOSAUR WITH SUCH ID WAS FOUND" << endl;
    }
}
void Cui::dinoUpdateMenu(int id)
{
    system("clear");
    Dino dino;
    dino.id = id;
    cout << "Enter new name: ";
    cin >> dino.name;
    cout << "\nEnter new period: ";
    cin >> dino.per;
    cout << "\nEnter new family: ";
    cin >> dino.fam;
    cout << "\nEnter new discovery date: ";
    string disc;
    cin >> disc;
    dino.disc = stoi(disc);
    cout << "\nEnter new mass: ";
    string mass;
    cin >> mass;
    dino.mass = stod(mass);
    system("clear");

    bool success = this->storage_->updateDino(dino);
    if(success == false)
    {
        cout << "NO DINOSAUR WITH SUCH ID WAS FOUND" << endl;
    }
}

void Cui::dinoRemoveMenu(int id)
{
    bool success = this->storage_->removeDino(id);
    if(success == false)
    {
        cout << "NO DINOSAUR WITH SUCH ID WAS FOUND" << endl;
    }
}
void Cui::dinoCreateMenu()
{
    system("clear");
    Dino dino;
    cout << "Enter name: ";
    cin >> dino.name;
    cout << "\nEnter period: ";
    cin >> dino.per;
    cout << "\nEnter family: ";
    cin >> dino.fam;
    cout << "\nEnter discovery date: ";
    string disc;
    cin >> disc;
    dino.disc = stoi(disc);
    cout << "\nEnter mass: ";
    string mass;
    cin >> mass;
    dino.mass = stod(mass);
    system("clear");

    this->storage_->insertDino(dino);
}







void printPer(Per & p)
{
    cout << "Viewing period: " << endl;
    cout << "[" << p.id << "]" << "," << p.name << "," << p.time << endl;
}

void printCompPerList(vector<Per> & pers)
{
    cout<<"/PERIOD MENU/" << endl;
    cout<<"Per list (shortened):" << endl;
    for(Per & p : pers)
    {
        cout << "[" << p.id << "]" << p.name << endl;
    }
    cout << endl;
}

void Cui::perMainMenu()
{
    bool running = true;
    int key = 0;
    int id = -1;
    system("clear");
    while(running)
    {
        vector<Per> pers = this->storage_->getAllPers();
        printCompPerList(pers);

        cout << "Options:" << endl;
        cout << "1. Per Operations\n2. Create new period\n0. Back\n" << endl;
        cin >> key;
        system("clear");
        switch (key)
        {
            case 1: system("clear"); perOperateMenu(); break;
            case 2: system("clear"); perCreateMenu(); break;
            case 0: running = false; this->storage_->save(); break;
            default: break;
        }
    }
}
void Cui::perOperateMenu()
{
    bool running = true;
    int key = 0;
    int id = -1;
    while(running)
    {
        cout << "/PERIOD OPERATIONS MENU/" << endl;
        cout << "1. View per" << endl;
        cout << "2. Update per" << endl;
        cout << "3. Remove per" << endl;
        cout << "0. Back" << endl;
        cin >> key;
        system("clear");
        switch (key)
        {
            case 1: 
            {
                cout << "Enter id: ";
                cin >> id;
                system("clear");
                perViewMenu(id);
                break;
            }
            case 2:
            {
                cout << "Enter id: ";
                cin >> id;
                system("clear");
                perUpdateMenu(id);
                break;
            }
            case 3:
            {
                cout << "Enter id: ";
                cin >> id;
                system("clear");
                perRemoveMenu(id);
                break;
            }
            case 0: running = false;this->storage_->save(); break;
            default: break;
        }
    }
}
void Cui::perViewMenu(int id)
{
    system("clear");
    optional<Per> p_opt = this->storage_->getPerById(id);
    if (p_opt)
    {
        Per & p = p_opt.value();
        printPer(p);
    }
    else
    {
        cout << "NO PERIODS WITH SUCH ID WAS FOUND" << endl;
    }
}
void Cui::perUpdateMenu(int id)
{
    system("clear");
    Per per;
    per.id = id;
    cout << "Enter new name: ";
    cin >> per.name;
    cout << "\nEnter new timespan: ";
    string length;
    cin >> length;
    per.time = stod(length);
    system("clear");

    bool success = this->storage_->updatePer(per);
    if(success == false)
    {
        cout << "NO PERIOD WITH SUCH ID WAS FOUND" << endl;
    }
}

void Cui::perRemoveMenu(int id)
{
    bool success = this->storage_->removePer(id);
    if(success == false)
    {
        cout << "NO PERIOD WITH SUCH ID WAS FOUND" << endl;
    }
}
void Cui::perCreateMenu()
{
    system("clear");
    Per per;
    cout << "Enter name: ";
    cin >> per.name;
    cout << "\nEnter timespan: ";
    string length;
    cin >> length;
    per.time = stod(length);
    system("clear");

    this->storage_->insertPer(per);
}