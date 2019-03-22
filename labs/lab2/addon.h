#pragma once

#include "list.h"
#include "csv.h"

typedef struct  dino
{
    char * name;
    char * per;
    char * fam;
    char * disc;
    char * mass;
} Dino;

void parser(int argc, char *argv[], bool * is_Input, bool * argument, int * N, bool * is_Output, int * out_Index);
void processStructList(List * list, int N);
char * fillStringFromFile(char from[]);
List * createTestList();
void print_dinos(List * dinos);
void freeDinoList(List * list);
void fillFromDinos(List * table, List * dinos);

List * fillDinosListFromTable(List * table);
