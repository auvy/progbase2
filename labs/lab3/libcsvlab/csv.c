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

    int commacount = 0;

    List *curr;


    while (1)
    {
        //IF IT'S A FIRST LETTER OF
        if ((p == (char *)csvString || *(p - 1) == '\n') && state == true)
        {
            //BASICALLY CREATING A NEW ROW OF STRINGS
            List *new = List_alloc();
            curr = new;
        }

        if (state == true)
        {
            if (*p == '"')
            {
                buf[bufX] = *p;
                bufX++;
                buf[bufX] = *p;
                bufX++;
            }
            else
            {
                if(*p == ' ' || *p == ',' || *p == '\n')
                {
                    if (*p == ' ')
                    {
                        for (int i = strlen(buf); i > 0; i--)
                        {
                            buf[i] = buf[i - 1];
                        }
                        buf[0] = '"';
                        bufX++;
                        buf[bufX] = *p;
                        bufX++;
                        state = false;
                    }
                    else if (*p == ',')
                    {
                        if(buf[0] == '\0')
                        {
                            buf[0] = '"';
                            buf[1] = '"';
                            buf[2] = '\0';
                            List_add(curr, createOnHeap(&buf[0]));

                            for (int i = 0; i < bufX + 1; i++)
                            {
                                buf[i] = '\0';
                            }

                            commacount++;
                            bufX = 0;
                            p++;
                            continue;
                        }
                        if (*(p + 1) == ' ' || *(p + 1) == '\n')
                        {
                            for (int i = strlen(buf); i > 0; i--)
                            {
                                buf[i] = buf[i - 1];
                            }
                            buf[0] = '"';
                            bufX++;
                            buf[bufX] = *p;
                            bufX++;
                            state = false;

                        }
                        else if (*(p+1) != ' ' || *(p+1) != '\n')
                        {
                            buf[bufX] = '\0';

                            List_add(curr, createOnHeap(&buf[0]));

                            for (int i = 0; i < bufX + 1; i++)
                            {
                                buf[i] = '\0';
                            }
                            commacount++;

                            bufX = 0;
                        }
                    }
                    else if(*p == '\n')
                    {
                        if (commacount == 5)
                        {
                            buf[bufX] = '\0';

                            List_add(curr, createOnHeap(&buf[0]));

                            for (int i = 0; i < bufX + 1; i++)
                            {
                                buf[i] = '\0';
                            }

                            List_add(table, curr);

                            commacount = 0;

                            bufX = 0;
                            p++;
                            continue;
                        }
                        else
                        {
                            state = false;
                            for (int i = strlen(buf); i > 0; i--)
                            {
                                buf[i] = buf[i - 1];
                            }
                            buf[0] = '"';
                            bufX++;
                            buf[bufX] = *p;
                            bufX++;
                        }
                    }
                }
                else
                {
                    if (*p == '\0')
                    {
                        buf[bufX] = '\0';

                        List_add(curr, createOnHeap(&buf[0]));


                        for (int i = 0; i < bufX + 1; i++)
                        {
                            buf[i] = '\0';
                        }

                        List_add(table, curr);
                  

                        bufX = 0;
                    }
                    else
                    {
                        buf[bufX] = *p;
                        bufX += 1;
                    }
                }
            }
        }
        else if(state == false) // open brackets reading
        {
            if (*p == '"')
            {
                buf[bufX] = *p;
                bufX++;
                buf[bufX] = *p;
                bufX++;
            }
            else
            {
                if(*p == ' ' || *p == ',' || *p == '\n')
                {
                    if (*p == ' ')
                    {
                        buf[bufX] = *p;
                        bufX++;
                    }
                    else if (*p == ',')
                    {
                        if (*(p + 1) == ' ' || *(p + 1) == '\n')
                        {
                            buf[bufX] = *p;
                            bufX++;
                        }
                        else
                        {
                            buf[bufX] = '"';
                            bufX++;

                            buf[bufX] = '\0';

                            state = true;

                            List_add(curr, createOnHeap(&buf[0]));

                            for (int i = 0; i < bufX + 1; i++)
                            {
                                buf[i] = '\0';
                            }
                            commacount++;
                            //
                            bufX = 0;
                        }
                    }
                    else if (*p == '\n')
                    {
                        if (commacount == 5)
                        {
                            state = true;

                            buf[bufX] = '"';
                            bufX++;
                            buf[bufX] = '\0';


                            List_add(curr, createOnHeap(&buf[0]));

                            for (int i = 0; i < bufX + 1; i++)
                            {
                                buf[i] = '\0';
                            }

                            List_add(table, curr);

                            commacount = 0;

                            bufX = 0;
                        }
                        else
                        {
                            buf[bufX] = *p;
                            bufX++;
                        }
                    }
                }
                else
                {
                    if(*p == '\0')
                    {
                        buf[bufX] = '"';
                        bufX++;
                        buf[bufX] = '\0';

                        List_add(curr, createOnHeap(&buf[0]));

                        for (int i = 0; i < bufX + 1; i++)
                        {
                            buf[i] = '\0';
                        }
                        
                        List_add(table, curr);

                        bufX = 0;
                    }
                    else
                    {
                        buf[bufX] = *p;
                        bufX += 1;
                    }
                }
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
