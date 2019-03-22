#include "addon.h"

void print_dinos(List * dinos)
{
    printf("PRINTING LIST OF STRUCTURES\n");
    for(int i = 0; i < (int)List_size(dinos); i++)
    {
        Dino * din = List_get(dinos, i);
        if(!printf("%s, %s, %s, %s, %s\n", din->name, din->per, din->fam, din->disc, din->mass))
        {
            printf("UNSUCCESSFUL\n");
        }
    }
    puts("");
    return;
}

void parser(int argc, char *argv[argc], bool * is_Input, bool * argument, int * N, bool * is_Output, int * out_Index)
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
                if(strcmp(argv[i], "-o") != 0 || i != argc - 1)
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
                else if(strcmp(argv[i], "-n") != 0 && i < argc)
                {
                    *is_Output = true;
                    *out_Index = i;
                }

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

    char *csvString = malloc(count * sizeof(char));

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

void processStructList(List * list, int N)
{
    int i = 0;
    while(i < List_size(list))
    {
        Dino *dino = List_get(list, i);

        if(atoi(dino->mass) < N)
        {
            free(dino->name);
            free(dino->per);
            free(dino->fam);
            free(dino->disc);
            free(dino->mass);
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

List * createTestList()
{
    List * dinos = List_alloc();

    Dino * dino1 = malloc(sizeof(Dino));
    dino1->name = createOnHeap("Dinasaur");
    dino1->per  = createOnHeap("A long time ago");
    dino1->fam  = createOnHeap("Rawr XD");
    dino1->disc = createOnHeap("1337");
    dino1->mass = createOnHeap("228");
    List_add(dinos, dino1);

    Dino * dino2 = malloc(sizeof(Dino));
    dino2->name = createOnHeap("Diego");
    dino2->per  = createOnHeap("1800s");
    dino2->fam  = createOnHeap("Brando");
    dino2->disc = createOnHeap("1870");
    dino2->mass = createOnHeap("78");
    List_add(dinos, dino2);

    Dino * dino3 = malloc(sizeof(Dino));
    dino3->name = createOnHeap("Dr. Ferdinand");
    dino3->per  = createOnHeap("1800s");
    dino3->fam  = createOnHeap("Unknown");
    dino3->disc = createOnHeap("1800s");
    dino3->mass = createOnHeap("80");
    List_add(dinos, dino3);

    return dinos;
}

void freeDinoList(List * list)
{
    for (int i = 0; i < List_size(list); i++)
    {
        Dino * din = List_get(list, i);
        free(din->name);
        free(din->per);
        free(din->fam);
        free(din->disc);
        free(din->mass);
        free(din);
    }
    List_free(list);
}

void fillFromDinos(List * table, List * dinos)
{
    for(int i = 0; i < List_size(dinos); i++)
    {
        Dino * dino = List_get(dinos, i);
        List *newrow = List_alloc();

        List_add(newrow, createOnHeap(dino->name));
        List_add(newrow, createOnHeap(dino->per));
        List_add(newrow, createOnHeap(dino->fam));
        List_add(newrow, createOnHeap(dino->disc));
        List_add(newrow, createOnHeap(dino->mass));

        List_add(table, newrow);
    }
}

List * fillDinosListFromTable(List * table)
{
    List * dinos = List_alloc();

    for(int i = 0; i < (int)table->length; i++)
    {
        Dino * dino = malloc(sizeof(Dino));

        List *row = List_get(table, i);

        dino->name = createOnHeap(List_get(row, 0));
        dino->per  = createOnHeap(List_get(row, 1));
        dino->fam  = createOnHeap(List_get(row, 2));
        dino->disc = createOnHeap(List_get(row, 3));
        dino->mass = createOnHeap(List_get(row, 4));

        List_add(dinos, dino);
    }

    return dinos;
}