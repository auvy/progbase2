
#include <QDebug>
#include <QtXml>

struct Student
{
   int id;
   QString name;
   float score;
};

int main()
{
   Student student = {1, "Anna", 100};

   QDomDocument doc;

   QDomElement studentEl = doc.createElement("student");
   studentEl.setAttribute("id", student.id);
   studentEl.setAttribute("name", student.name);
   studentEl.setAttribute("score", student.score);

   doc.appendChild(studentEl);

   QString qStr = doc.toString(4);  // indentation (spaces)
   qDebug().noquote() << qStr;
   QString qStr2 = doc.toString(-1);  // for no indentation at all
   qDebug().noquote() << qStr2;
}

Для зручності винесемо логіку формування XML елемента з об’єкта студента у функцію:
// <student id="1" score="99.1" name="Anna"/>
QDomElement studentToXmlElement(QDomDocument & doc, Student & student)
{
   QDomElement studentEl = doc.createElement("student");
   studentEl.setAttribute("id", student.id);
   studentEl.setAttribute("name", student.name);
   studentEl.setAttribute("score", student.score);
   return studentEl;
}

Парсинг одного об’єкта

Код для розбору з XML-тексту з даними студента (з атрибутами) у об’єкт студента:
// <student id="1" score="99.1" name="Anna"/>
Student xmlElementToStudent(QDomElement & studentEl)
{
    Student student;
    student.id = studentEl.attribute("id").toInt();
    student.name = studentEl.attribute("name");
    student.score = studentEl.attribute("score").toFloat();
    return student;
}
#include <QDebug>
#include <QtXml>

struct Student
{
   int id;
   QString name;
   float score;
};

Student xmlElementToStudent(QDomElement & studentEl);

int main()
{
   QString xmlText = "<student id=\"1\" name=\"Anna\" score=\"99.1\"/>";

   QDomDocument doc;
   QString errorMessage;
   if (!doc.setContent(xmlText, &errorMessage)) {
       qDebug() << "error parsing xml: " << errorMessage;
       return 1;
   }
   QDomElement studentEl = doc.documentElement();
   Student student = xmlElementToStudent(studentEl);
   qDebug() << student.id << " | " << student.name << " | " << student.score;
}

Форматування вектора об’єктів
Створення xml-тексту з вектора сутностей з розміщенням даних у атрибутах:
#include <QDebug>
#include <QtXml>

struct Student
{
   int id;
   QString name;
   float score;
};

QDomElement studentToXmlElement(QDomDocument & doc, Student & student);

int main()
{
   std::vector<Student> students = {
       {1, "Anna", 100},
       {2, "Taras", 80.3}
   };

   QDomDocument doc;

   QDomElement rootEl = doc.createElement("students");
   for (const Student & student: students) {
         QDomElement studentEl = studentToXmlElement(student);
         rootEl.appendChild(studentEl);
   }

   doc.appendChild(rootEl);

   QString qStr = doc.toString(4);  // indentation (spaces)
   qDebug().noquote() << qStr;
   QString qStr2 = doc.toString(-1);  // for no indentation at all
   qDebug().noquote() << qStr2;
}
<students>
    <student id="1" score="100" name="Anna"/>
    <student id="2" score="80.3" name="Taras"/>
</students>
<students><student id="1" name="Anna" score="100"/><student id="2" name="Taras" score="80.3"/></students>

Парсинг вектора об’єктів
Парсинг з xml-рядка у вектор сутностей:
#include <QDebug>
#include <QtXml>

struct Student
{
   int id;
   QString name;
   float score;
};

Student xmlElementToStudent(QDomElement & studentEl);

int main()
{
   QString xmlText = "<students><student id=\"1\" name=\"Anna\" score=\"100\"/><student id=\"2\" name=\"Taras\" score=\"80.3\"/></students>";
   std::vector<Student> students;

   QDomDocument doc;
   QString errorMessage;
   if (!doc.setContent(xmlText, &errorMessage)) {
       qDebug() << "error parsing xml: " << errorMessage;
       return 1;
   }
   QDomElement rootEl = doc.documentElement();
   QDomNodeList rootElChildren = rootEl.childNodes();
   for (int i = 0; i < rootElChildren.length(); i++) {
         QDomNode studentNode = rootElChildren.at(i);
         QDomElement studentEl = studentNode.toElement();
         Student student = xmlElementToStudent(studentEl);
         students.push_back(student);
   }

   for (Student & s: students) {
       qDebug() << s.id << " | " << s.name << " | " << s.score;
   }
}
1  |  "Anna"  |  100
2  |  "Taras"  |  80.3

Інший приклад

Типи даних:
struct Student
{
    QString name;
    int 	age;
};

struct Group
{
    QString name;
    vector<Student> students;
};

Очікуваний вигляд XML-документу з даними:
<group name="KP-73">
    <student name="Nastya" age="17"></student>
    <student name="Igor" age="18" />
</group>

Код прикладу
#include <QDebug>
#include <QtXml>
#include <vector>
#include <iostream>
#include "mytypes.h"
using namespace std;

string groupToXmlString(const Group & g);
Group xmlStringToGroup(string & str);
void printGroup(const Group & g);

int main(int argc, char *argv[]) {
    Group g;
    g.name = "KP-73";
    g.students.push_back(Student{ "Nastya", 17 });
    g.students.push_back(Student{ "Igor", 18 });

    printGroup(g);

    string str = groupToXmlString(g);
    cout << "--------------"
           << endl << str << endl
           << "--------------" << endl;

    Group g2 = xmlStringToGroup(str);
    printGroup(g2);
}

void printGroup(const Group & g) {
    cout << g.name.toStdString() << endl << "students: " << endl;
    for (const Student & s : g.students) {
          cout << "  student: " << s.name.toStdString() << " | " << s.age << endl;
    }
}


string groupToXmlString(const Group & g) {
    QDomDocument doc;
    QDomElement groupEl = doc.createElement("group");
    groupEl.setAttribute("name", g.name);

    for (const Student & s: g.students) {
          QDomElement studentEl = doc.createElement("student");
          studentEl.setAttribute("name", s.name);
          studentEl.setAttribute("age", s.age);
          groupEl.appendChild(studentEl);
    }

    doc.appendChild(groupEl);
    return doc.toString().toStdString();
}

Group xmlStringToGroup(string & str) {
    QDomDocument doc;
    if (!doc.setContent(QString::fromStdString(str))) {
          cerr << "error parsing xml!" << endl;
          return Group();
    }
    Group g;
    QDomElement root = doc.documentElement();
    QString nameAttrValue = root.attribute("name");
    g.name = nameAttrValue;

    for (int i = 0; i < root.childNodes().length(); i++) {
          QDomNode studentNode = root.childNodes().at(i);
          QDomElement studentEl = studentNode.toElement();
          Student s;
          s.name = studentEl.attribute("name");
          s.age = studentEl.attribute("age").toInt();
          g.students.push_back(s);
    }

    return g;
}
