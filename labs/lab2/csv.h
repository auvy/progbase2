#include "list.h"  // generic list (array implementation)

void fill_the_table(List *table, char file[]);
void deinitTable(List * table);

void printStrings(List *pl, FILE * where);
void printStringsTable(List *table, char where[]);
