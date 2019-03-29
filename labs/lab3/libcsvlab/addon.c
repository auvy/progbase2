#include "addon.h"

void parser(int argc, char *argv[argc], bool * is_Input, bool * argument, int * N, bool * is_Output, int * out_Index, bool * totree)
{
    if(argc > 1)
    {
        for(int i = 1; i < argc; i++)
        {
            if(i == 1)
            {
              if(strstr(argv[1], "."))
              {
                  *is_Input = true;
              } 
            }

            if(strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "-N") == 0)
            {
                i++;
                if(strcmp(argv[i], "-o") != 0 || i != argc - 1 || strcmp(argv[i], "-b") != 0)
                {
                    *argument = true;
                    *N = atoi(argv[i]);
                }
            }

            if(strcmp(argv[i], "-o") == 0)
            {
                i++;
                if(i == argc)
                {
                    *is_Output = false;
                    puts("No file was found.");
                }
                else if(strcmp(argv[i], "-n") != 0 && i < argc && strcmp(argv[i], "-b") != 0)
                {
                    *is_Output = true;
                    *out_Index = i;
                }

            }
            if(strcmp(argv[i], "-b") == 0)
            {
                *totree = true;
            }
        }
    }
}

char * fillStringFromFile(char from[])
{

    char ch = 0;

    int count = 0;

    FILE *file;


    if((file = fopen(from, "r")) == NULL)
    {
        return NULL;
    }


    while((ch = fgetc(file)) != EOF)
    {
        if(ch == '\r')
        {
            //THANK YOU, CSV, VERY COOL
        }
        else
        {
            count++;
        }
    }
    count++;

    fclose(file);

    file = fopen(from, "r");

    char *csvString = malloc(sizeof(char) * count);

    for(int i = 0; i < count; i++)
    {
        csvString[i] = '\0';
    }

    char *roll = csvString; 

    while((ch = fgetc(file)) != EOF)
    {
        if(ch == '\r')
        {
            //THANK YOU, CSV, VERY COOL
        }
        else
        {
            *roll = ch;
            roll++;
        }
    }
    *(roll-1) = '\0';

    fclose(file);


    return csvString;
}

void processMapList(List * list, int N)
{
    int i = 0;
    while(i < List_size(list))
    {
        StrMap *dino = List_get(list, i);

        char copy[100];
        strcpy(copy, StrMap_getVal(dino, "mass"));
        int mass = atoi(copy);
        printf("\n(%d)\n", mass);

        if(mass < N)
        {
            for(int k = 0; k < 6; k++)
            {
                free((char*)dino->items[k].value);
            }
            free(dino->items);
            free(dino);

            for(int j = i; j < List_size(list) - 1; j++)
            {
                list->items[j] = list->items[j+1];
            }

            list->length--;
        }

        else
        {
            i++;
        }
        
    }
}


char * String_allocCopy(const char * value)
{
    char *meme = malloc(sizeof(char) * (strlen(value) + 1));
    strcpy(meme, value);
    return meme;
}
char * String_allocFromInt(int value)
{
    char meme[10];
    sprintf(meme, "%d", value);
    return String_allocCopy(meme);
}
char * String_allocFromDouble(double value)
{
    char buf[100];
    sprintf(buf, "%f", value);
    char * meme = String_allocCopy(buf);
    return meme;
}

StrMap * createDinoMap(Dino * dino)
{
    char * idValue = String_allocFromInt(dino->id);
    char * fullnameValue = String_allocCopy(dino->name);
    char * existed = String_allocCopy(dino->per); 
    char * family = String_allocCopy(dino->fam);
    char * discovery = String_allocFromInt(dino->disc);
    char * massval = String_allocFromDouble(dino->mass);

    // printf("%s\n", idValue);
    // printf("%s\n", fullnameValue);
    // printf("%s\n", existed);
    // printf("%s\n", family);
    // printf("%s\n", discovery);
    // printf("%s\n", massval);

    StrMap * map = StrMap_alloc();
    StrMap_add(map, "id", idValue);
    StrMap_add(map, "name", fullnameValue);
    StrMap_add(map, "period", existed);
    StrMap_add(map, "family", family);
    StrMap_add(map, "discovered", discovery);
    StrMap_add(map, "mass", massval);

    assert(StrMap_contains(map, "id"));
    assert(StrMap_contains(map, "name"));
    assert(StrMap_contains(map, "period"));
    assert(StrMap_contains(map, "family"));
    assert(StrMap_contains(map, "discovered"));
    assert(StrMap_contains(map, "mass"));

        // for(int i = 0; i < 6; i++)
        // {
        //     printf("|%s - ", map->items[i].value);
        // }
        // printf("\n\n");

    return map;
}

void printDinosMapList(List * DinoMaps, char * where)
{
    printf("PRINTING List\n");

    FILE *output;

    if(where == NULL)
    {
        output = stdout;
        puts("Id,Name,Period,Family,\"Discovered, year\",\"Weight, kg\"");
    }
    else
    {    
        output = fopen(where, "w");
    }


    for(int i = 0; i < List_size(DinoMaps); i++)
    {
        StrMap * doono = List_get(DinoMaps, i);
        fprintf(output, "%s,%s,%s,%s,%s,%s\n", StrMap_getVal(doono, "id"), 
        StrMap_getVal(doono, "name"), StrMap_getVal(doono, "period"),
        StrMap_getVal(doono, "family"), StrMap_getVal(doono, "discovered"),
        StrMap_getVal(doono, "mass"));
    }
    puts("");
    if(where != NULL)
    {
        fclose(output);
    }
}

void fillDinoMapList(List * list, int DinoArrLen, Dino DinosArr[])
{
    for (int i = 0; i < DinoArrLen; i++)
    {
        Dino * dino = &DinosArr[i];
        StrMap * studentMap = createDinoMap(dino);
        List_add(list, studentMap);
    }
}


List * createTestList()
{
    List * dinos = List_alloc();

    Dino DinosArr[] = {
        {223, "Dinosaur", "A long time ago", "Rawr XD", 1337, 228},
        {56, "Diego", "1800s", "Brando", 1870, 78},
        {47, "Dr. Ferdinand", "1800s", "Unknown", 1800, 70},
    };
    const int DinosArrLen = sizeof(DinosArr) / sizeof(DinosArr[0]);

    fillDinoMapList(dinos, DinosArrLen, DinosArr);

    return dinos;
}

void fillFromDinos(List * table, List * dinos)
{
    for(int i = 0; i < List_size(dinos); i++)
    {
        Dino * dino = List_get(dinos, i);
        List *newrow = List_alloc();

        char id[100];
        char disc[100];
        char mass[100];
        sprintf(id, "%i", dino->id);
        sprintf(disc, "%i", dino->disc);
        sprintf(mass, "%f", dino->mass);

        List_add(newrow, createOnHeap(id));
        List_add(newrow, createOnHeap(dino->name));
        List_add(newrow, createOnHeap(dino->per));
        List_add(newrow, createOnHeap(dino->fam));
        List_add(newrow, createOnHeap(disc));
        List_add(newrow, createOnHeap(mass));

        List_add(table, newrow);
    }
}

List * fillDinosListFromTable(List * table)
{
    List * dinos = List_alloc();

    for(int i = 0; i < (int)table->length; i++)
    {
    List *row = List_get(table, i);

    char * idValue = String_allocCopy(List_get(row, 0));
    // printf("%s\n", idValue);
    char * fullnameValue = String_allocCopy(List_get(row, 1));
    // printf("%s\n", fullnameValue);
    char * existed = String_allocCopy(List_get(row, 2));
    // printf("%s\n", existed);
    char * family = String_allocCopy(List_get(row, 3));
    // printf("%s\n", family);
    char * discovery = String_allocCopy(List_get(row, 4));
    // printf("%s\n", discovery);
    char * massval = String_allocCopy(List_get(row, 5));
    // printf("%s\n\n", massval);


    StrMap * map = StrMap_alloc();
    StrMap_add(map, "id", idValue);
    StrMap_add(map, "name", fullnameValue);
    StrMap_add(map, "period", existed);
    StrMap_add(map, "family", family);
    StrMap_add(map, "discovered", discovery);
    StrMap_add(map, "mass", massval);


    List_add(dinos, map);
    }

    return dinos;
}


void freeListOMaps(List * maps)
{
    printf("{FREEING %d MAPS}\n", (int)List_size(maps));
    for(int i = 0; i < (int)List_size(maps); i++)
    {
        StrMap *dino = List_get(maps, i);

        for (int k = 0; k < 6; k++)
        {
            free((char*)dino->items[k].value);
        }
        free(dino->items);
        free(dino);
    }
    free(maps->items);
    free(maps);
}