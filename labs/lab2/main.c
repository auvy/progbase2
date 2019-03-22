

#include "list.h"
#include "csv.h"
#include "addon.h"


int main(int argc, char *argv[argc])
{
    bool is_Input = false;
    bool argument = false;
    int N = -1;
    bool is_Output = false;
    int out_Index = -1;

    char *inpoot;
    char *outpoot;

    parser(argc, argv, &is_Input, &argument, &N, &is_Output, &out_Index);

    if(is_Input == true)
    {
        inpoot = malloc((strlen(argv[1]) + 1) * sizeof(char));
        strcpy(inpoot, argv[1]);
        printf("INPUT: %s\n", inpoot);
    }
    else
    {
        inpoot = NULL;
        printf("NO INPUT\n");
    }

    if(argument)
    {
        printf("N: %d\n", N);
    }
    else if(!argument)
    {
        printf("NO N\n");
    }

    if(is_Output)
    {
        outpoot = malloc((strlen(argv[out_Index]) + 1) * sizeof(char));
        strcpy(outpoot, argv[out_Index]);
        printf("OUTPUT: %s\n", outpoot);
    }
    else
    {
        outpoot = NULL;
        printf("NO OUTPUT\n");
    }

    List * dinos;

    if (is_Input == false)
    {       
        dinos = createTestList();
    }
    else
    {
        if(fillStringFromFile(inpoot) == NULL)
        {
            printf("Input file was not found.\n");
            dinos = createTestList();
        }
        else
        {
            List table;
            List_init(&table);
            fill_the_table(&table, fillStringFromFile(inpoot));
            dinos = fillDinosListFromTable(&table);
            deinitTable(&table);
        }

    }

    print_dinos(dinos);

    if(argument == true)
    {
        processStructList(dinos, N);
    }

    print_dinos(dinos);


    List table2;
    List_init(&table2);

    fillFromDinos(&table2, dinos);

    printStringsTable(&table2, outpoot);

    deinitTable(&table2);

    freeDinoList(dinos);

    free(inpoot);
    free(outpoot);

    return 0;
}