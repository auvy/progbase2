#include "xml_storage.h"



using namespace std;

Dino domElementToDino(QDomElement & element)
{
    Dino d;
    d.id = element.attributeNode("id").value().toInt();
    d.name = element.attributeNode("name").value().toStdString();
    d.per = element.attributeNode("period").value().toStdString();
    d.fam = element.attributeNode("family").value().toStdString();
    d.disc = element.attributeNode("discovery").value().toInt();
    d.mass = element.attributeNode("mass").value().toFloat();
    return d;
}

Per domElementToPer(QDomElement & element)
{
    Per p;
    p.id = element.attributeNode("id").value().toInt();
    p.name = element.attributeNode("name").value().toStdString();
    p.time = element.attributeNode("time").value().toFloat();
    return p;
}

bool errorcheck(QString & text, QDomDocument & doc)
{
    QString errorMessage;
    int errorLine;
    int errorCol;
    bool is_parsed = doc.setContent(text, &errorMessage, &errorLine, &errorCol);
    if(!is_parsed)
    {
        qDebug() << "Error parsing xml: " << errorMessage;
        qDebug() << "In line:  " << errorLine;
        qDebug() << "In colu:  " << errorCol;
        return false;
    }
    return true;
}

bool XmlStorage::loadfromstr(string filename, int strtype)
{
    QString s_filename = QString::fromStdString(filename);
    QFile s_file(s_filename);
    bool is_opened = s_file.open(QFile::ReadOnly);
    if (!is_opened)
    {
        cout << "file wasnt found" << endl;
       return false;
    }

    QTextStream ts(&s_file);
    QString text = ts.readAll();
    QDomDocument doc;
    if(!errorcheck(text, doc))
    {
        return false;
    }

    QDomElement root = doc.documentElement();
    for(int i = 0; i < root.childNodes().size(); i++)
    {
        QDomNode node = root.childNodes().at(i);
        if(node.isElement())
        {
            QDomElement element = node.toElement();
            if(strtype == 1)
            {
                Dino dino = domElementToDino(element);
                this->dinos_.push_back(dino);
            }
            if(strtype == 2)
            {
                Per per = domElementToPer(element);
                this->pers_.push_back(per);
            }

        }
    }

    s_file.close();
    return true;
}




bool XmlStorage::open()
{
    string filename = this->dir_name_ + "/data.xml";
    if(!loadfromstr(filename, 1))
    {
        return false;
    }
    string filename2 = this->dir_name_ + "/data2.xml";
    if(!loadfromstr(filename2, 2))
    {
        return false;
    }
    return true;
}


QDomElement dinoToDomEl(QDomDocument & doc, Dino & dino)
{
    QDomElement dino_el = doc.createElement("dino");

    dino_el.setAttribute("id", dino.id);
    dino_el.setAttribute("name", dino.name.c_str());
    dino_el.setAttribute("period", dino.per.c_str());
    dino_el.setAttribute("family", dino.fam.c_str());
    dino_el.setAttribute("discovery", dino.disc);
    dino_el.setAttribute("mass", dino.mass);

    return dino_el;
}

QDomElement perToDomEl(QDomDocument & doc, Per & per)
{
    QDomElement per_el = doc.createElement("period");

    per_el.setAttribute("id", per.id);
    per_el.setAttribute("name", per.name.c_str());
    per_el.setAttribute("time", per.time);

    return per_el;
}


bool tofile(QDomDocument & doc, string & filename)
{
    QString xml_text = doc.toString(4);

    QString s_filename = QString::fromStdString(filename);
    QFile file(s_filename);
    if(!file.open(QFile::WriteOnly))
    {
        qDebug() << "Couldn't open file to write : " << s_filename;
        return false;
    }
    QTextStream ts(&file);
    ts << xml_text;
    file.close();

    return true;
}

bool XmlStorage::close()
{
    QDomDocument doc;
    QDomElement root = doc.createElement("dinos");

    for(Dino & dino : this->dinos_)
    {
        QDomElement dino_el =  dinoToDomEl(doc, dino);
        root.appendChild(dino_el);
    }

    doc.appendChild(root);
    string filename = this->dir_name_ + "/data.xml";
    tofile(doc, filename);


    QDomDocument doc2;
    QDomElement root2 = doc2.createElement("periods");

    for(Per & per : this->pers_)
    {
        QDomElement per_el =  perToDomEl(doc2, per);
        root2.appendChild(per_el);
    }

    doc2.appendChild(root2);
    string filename2 = this->dir_name_ + "/data2.xml";
    tofile(doc2, filename2);

    return true;
}






int XmlStorage::getNewDinoId()
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


bool XmlStorage::removeDino(int Dino_id)
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


vector<Dino> XmlStorage::getAllDinos()
{
    return this->dinos_;
}

optional<Dino> XmlStorage::getDinoById(int Dino_id)
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

int XmlStorage::insertDino(const Dino &dvno)
{
    int new_id = this->getNewDinoId();
    Dino copy = dvno;
    copy.id = new_id;
    this->dinos_.push_back(copy);
    return new_id;
}

bool XmlStorage::updateDino(const Dino &dvno)
{
    int Dino_id = dvno.id;
    for(Dino & c : this->dinos_)
    {
        if(c.id == Dino_id)
        {
            c.name = dvno.name;
            c.per = dvno.per;
            c.fam = dvno.fam;
            c.disc = dvno.disc;
            c.mass = dvno.mass;
            return true;
        }
    }
    return false;

}












vector<Per> XmlStorage::getAllPers()
{
    return this->pers_;
}

optional<Per> XmlStorage::getPerById(int id)
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

bool XmlStorage::removePer(int id)
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

int XmlStorage::getNewPerId()
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

int XmlStorage::insertPer(const Per &pr)
{
    int new_id = this->getNewPerId();
    Per copy = pr;
    copy.id = new_id;
    this->pers_.push_back(copy);
    return new_id;
}

bool XmlStorage::updatePer(const Per &pr)
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
