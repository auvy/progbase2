#include "csv_storage.h"
#include <fstream>
#include <iostream>

using namespace std;


string fillStringFromFile(string fromw)
{
    string csv;

    string line;
    ifstream myfile(fromw);

    string::iterator it = line.end();

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            line+="\n";
            csv += line;
        }

        myfile.close();
    }
    else 
    {
        cerr << "File was not found" << endl;
        abort();
    }

    it = csv.end();
    it--;
    *it = '\0';


    return csv;
}


void writeToFile(string from, string tofile)
{
    ofstream myfile(tofile);
    if(myfile.is_open())
    {
        myfile << from;
        myfile.close();
    }
    else
    {
        cout << "Cannot open file\n"
             << endl;
        abort();
    }
}


bool CsvStorage::load()
{
    string dinos_filename = this->dir_name_ + "/data.csv";
    string dinos_csv = fillStringFromFile(dinos_filename);

    CsvTable dinos_table = Csv::createTableFromString(dinos_csv);

    for(CsvRow & row : dinos_table)
    {
        Dino newone;
        newone.id = stoi(row[0]);
        newone.name = row[1];
        newone.per = row[2];
        newone.fam = row[3];
        newone.disc = stoi(row[4]);
        newone.mass = stod(row[5]);
        this->dinos_.push_back(newone);
    }


    string pers_filename = this->dir_name_ + "/data2.csv";
    string pers_csv = fillStringFromFile(pers_filename);

    CsvTable pers_table = Csv::createTableFromString(pers_csv);

    for(CsvRow & row2 : pers_table)
    {
        Per newone;
        newone.id = stoi(row2[0]);
        newone.name = row2[1];
        newone.time = stod(row2[2]);
        this->pers_.push_back(newone);
    }
    return true;
}


bool CsvStorage::save()
{
    string dinos_filename = this->dir_name_ + "/data.csv";
    CsvTable newt;
    for(Dino & a : this->dinos_)
    {
        CsvRow row;
        row.push_back(to_string(a.id));
        row.push_back(a.name);
        row.push_back(a.per);
        row.push_back(a.fam);
        row.push_back(to_string(a.disc));
        row.push_back(to_string(a.mass));

        newt.push_back(row);
    }
    string csv_txt = Csv::createStringFromTable(newt);
    
    writeToFile(csv_txt, dinos_filename);


    string pers_filename = this->dir_name_ + "/data2.csv";
    CsvTable newt2;
    for(Per & p : this->pers_)
    {
        CsvRow row;
        row.push_back(to_string(p.id));
        row.push_back(p.name);
        row.push_back(to_string(p.time));

        newt2.push_back(row);
    }
    string csv_txt2 = Csv::createStringFromTable(newt2);
    
    writeToFile(csv_txt2, pers_filename);

    return true;
}


vector<Dino> CsvStorage::getAllDinos()
{
    return this->dinos_;
}

optional<Dino> CsvStorage::getDinoById(int Dino_id)
{
    for(Dino & c : this->dinos_)
    {  
        if(c.id == Dino_id)
        {
            return c;
        }
    }
    return nullopt;
}

bool CsvStorage::removeDino(int Dino_id)
{
    int index = -1;
    for(int i = 0; i < this->dinos_.size(); i++)
    {
        if(this->dinos_[i].id == Dino_id)
        {
            index = i;
            break;
        }
    }
    if(index >= 0)
    {
        this->dinos_.erase(this->dinos_.begin() + index);
        return true;
    }
    return false;
}

int CsvStorage::getNewDinoId()
{
    int max_id = 0;
    for(Dino & d : this->dinos_)
    {
        if(d.id > max_id)
        {
            max_id = d.id;
        }
    }
    int new_id = max_id + 1;
    return new_id;
}



int CsvStorage::insertDino(const Dino &dvno)
{
    int new_id = this->getNewDinoId();
    Dino copy = dvno;
    copy.id = new_id;
    this->dinos_.push_back(copy);
    return new_id;
}

bool CsvStorage::updateDino(const Dino &dvno)
{
    int Dino_id = dvno.id;
    for(Dino & c : this->dinos_)
    {  
        if(c.id == Dino_id)
        {
            c.disc = dvno.disc;
            c.fam = dvno.fam;
            c.mass = dvno.mass;
            c.name = dvno.name;
            c.per = dvno.per;
            return true;
        }
    }
    return false;

}







vector<Per> CsvStorage::getAllPers()
{
    return this->pers_;
}

optional<Per> CsvStorage::getPerById(int id)
{
    for(Per & p : this->pers_)
    {  
        if(p.id == id)
        {
            return p;
        }
    }
    return nullopt;
}

bool CsvStorage::removePer(int id)
{
    int index = -1;
    for(int i = 0; i < this->pers_.size(); i++)
    {
        if(this->pers_[i].id == id)
        {
            index = i;
            break;
        }
    }
    if(index >= 0)
    {
        this->pers_.erase(this->pers_.begin() + index);
        return true;
    }
    return false;
}

int CsvStorage::getNewPerId()
{
    int max_id = 0;
    for(Per & p : this->pers_)
    {
        if(p.id > max_id)
        {
            max_id = p.id;
        }
    }
    int new_id = max_id + 1;
    return new_id;
}

int CsvStorage::insertPer(const Per &pr)
{
    int new_id = this->getNewPerId();
    Per copy = pr;
    copy.id = new_id;
    this->pers_.push_back(copy);
    return new_id;
}

bool CsvStorage::updatePer(const Per &pr)
{
    int Per_id = pr.id;
    for(Per & p : this->pers_)
    {  
        if(p.id == Per_id)
        {
            p.name = pr.name;
            p.time = pr.time;
            return true;
        }
    }
    return false;

}



