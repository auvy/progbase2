#include "csv.h"

void printStrings(List *pl, FILE * where)
{
    for (int i = 0; i < List_size(pl); i++)
    {
        char *item = List_get(pl, i);
        if (i == 0) fprintf(where, "%s", item);
        else       fprintf(where, ",%s", item);
    }
    fprintf(where, "\n");
}

void printStringsTable(List *table, char where[])
{
    printf("PRINTING TABLE\n");

    FILE *output;

    if(where == NULL)
    {
        output = stdout;
        puts("Name,Period,Family,\"Discovered, year\",\"Weight, kg\"");
    }
    else
    {    
        output = fopen(where, "w");
    }

    for (int i = 0; i < List_size(table); i++)
    {
        List *row = List_get(table, i);
        printStrings(row, output);
    }

    fclose(output);
}

void fill_the_table(List *table, char file[])
{
    char *csvString = file;

    char buf[100];

    for (int i = 0; i < 100; i++)
    {
        buf[i] = '\0';
    }

    //BUFFER TRACKER
    int bufX = 0;

    bool state = true;
    // CsvReadState state = CsvReadState_Normal;

    //CHAR POINTER TO READ THE STRING
    char *p = csvString;

    List *curr;

    while (1)
    {
        //IF IT'S A FIRST LETTER OF
        if (p == (char *)csvString || *(p - 1) == '\n')
        {
            List *new = List_alloc();
            curr = new;
        }

        if (state == true)
        {
            if (*p == '"')
            {
                //fook it it's escape gotta move to escape rn
                state = false;
            }
            else
            {
                if (*p == '\n' || *p == ',' || *p == '\0')
                {
                    buf[bufX] = '\0';

                    List_add(curr, createOnHeap(&buf[0]));

                    for (int i = 0; i < bufX + 1; i++)
                    {
                        buf[i] = '\0';
                    }

                    if (*p == '\n' || *p == '\0')
                    {
                        List_add(table, curr);
                    }
                    //
                    bufX = 0;
                }
                else
                {
                    buf[bufX] = *p;
                    bufX += 1;
                }
            }
        }
        else // open brackets reading
        {
            if (*p == '"')
            {
                if (*(p + 1) == '"')
                {
                    buf[bufX] = '"';
                    bufX += 1;

                    p += 1;
                }
                else
                {
                    buf[bufX] = '\0';

                    List_add(curr, createOnHeap(&buf[0]));

                    for (int i = 0; i < bufX + 1; i++)
                    {
                        buf[i] = '\0';
                    }

                    bufX = 0;
                    //
                    if (*(p + 1) == ',' || *(p + 1) == '\n')
                    {
                        if (*(p + 1) == '\n')
                        {
                            List_add(table, curr);
                        }

                        p += 1;
                        state = true;
                    }

                    else
                    {
                        fprintf(stderr, "CSV format error: invalid char '%c' after escape\n", *(p + 1));
                        abort();
                    }
                }
            }
            else
            {
                buf[bufX] = *p;
                bufX += 1;
            }
        }

        if (*p == '\0')
        {
            break;
        }

        p += 1;
    }
    free(csvString);

    return;
}

void deinitTable(List * table)
{
    for (int i = 0; i < List_size(table); i++)
    {
        List *row = List_get(table, i);
        for (int j = 0; j < List_size(row); j++)
        {
            char *str = List_get(row, j);
            free(str);
        }
        List_free(row);
    }
    List_deinit(table);
}
