#include "csv.h"
#include "csv_storage.h"
#include "xml_storage.h"
#include "sqlite_storage.h"


#include "storage.h"
#include "cui.h"

using namespace std;


Storage * createStorage(const QString & qpath);


int main()
{

//    CsvStorage csv_storage("../lab8/data/csv");
//    Storage * storage_ptr = &csv_storage;
//    storage_ptr->open();

//    XmlStorage xml_storage("../lab8/data/xml");
//    Storage * storage_ptr = &xml_storage;
//    storage_ptr->open();


    SqliteStorage sql_storage("../lab8/data/sql");
    Storage * storage_ptr = &sql_storage;
    storage_ptr->open();


    Cui cui(storage_ptr);
    cui.show();

    return 0;
}





//Storage * createStorage(const QString & qpath)
//{
//    if (qpath.endsWith("xml"))
//    {
//        XmlStorage * storage = new XmlStorage(qpath.toLocal8Bit().constData);
//        return storage;
//    }
//    else if (qpath.endsWith("csv"))
//    {
//        CsvStorage * storage = new CsvStorage(qpath.toLocal8Bit().constData);
//        return storage;
//    }
//    else if (qpath.endsWith("sql"))
//    {
//        SqliteStorage * storage = new SqliteStorage(qpath.toLocal8Bit().constData);
//        return storage;
//    }

//    else
//    {
//        qDebug() << "Unknown storage type: " << qpath;
//        abort();
//    }

//}
