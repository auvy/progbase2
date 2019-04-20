#include "csv.h"
#include "storage.h"
#include "cui.h"

using namespace std;

int main(int argc, char *argv[])
{

    Storage storage("./data");
    storage.load();

    Cui cui(&storage);
    cui.show();

    return 0;
}