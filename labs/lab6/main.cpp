#include "csv.h"
#include "csv_storage.h"
#include "xml_storage.h"

#include "storage.h"
#include "cui.h"

using namespace std;

int main()
{

    XmlStorage xml_storage("../lab6/data/xml");
    Storage * storagex = &xml_storage;
    storagex->load();

//    CsvStorage csv_storage("../lab6/data/csv");
//    Storage * storage = &csv_storage;
//    storage->load();

    Cui cui(storagex);
    cui.show();

    return 0;
}
