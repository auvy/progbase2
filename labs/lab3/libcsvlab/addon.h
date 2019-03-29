#pragma once

#include "list.h"
#include "csv.h"
#include "strmap.h"
#include <assert.h>

typedef struct  dino
{
    int id;
    char * name;
    char * per;
    char * fam;
    int disc;
    double mass;
} Dino;

void parser(int argc, char *argv[], bool * is_Input, bool * argument, int * N, bool * is_Output, int * out_Index, bool * totree);
void processMapList(List * list, int N);
char * fillStringFromFile(char from[]);
List * createTestList();
void freeDinoList(List * list);
void fillFromDinos(List * table, List * dinos);

List * fillDinosListFromTable(List * table);


char * String_allocCopy(const char * value);
char * String_allocFromInt(int value);
char * String_allocFromDouble(double value);


StrMap * createDinoMap(Dino * dino);
void printDinosMapList(List * DinoMaps, char * where);
void fillDinoMapList(List * list, int DinoArrLen, Dino DinosArr[]);

void freeListOMaps(List * maps);
