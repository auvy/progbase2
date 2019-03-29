#include <list.h>
#include <csv.h>
#include <addon.h>
#include <strmap.h>
#include <btree.h>


int main(int argc, char *argv[argc])
{
    bool is_Input = false;
    bool argument = false;
    int N = -1;
    bool is_Output = false;
    int out_Index = -1;
    bool totree = false;

    char *inpoot;
    char *outpoot;

    parser(argc, argv, &is_Input, &argument, &N, &is_Output, &out_Index, &totree);

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

    if(totree)
    {
        printf("COPY TO TREE: TRUE\n");
    }
    else
    {
        printf("COPY TO TREE: FALSE\n");
    }
    
    puts("");

    List * dinos;

    if (is_Input == false)
    {       
        dinos = createTestList();
    }
    else
    {
        char * fill = fillStringFromFile(inpoot);
        if(fill == NULL)
        {
            printf("Input file was not found.\n");
            dinos = createTestList();
            free(fill);
        }
        else
        {
            List table;
            List_init(&table);
            fill_the_table(&table, fill);
            dinos = fillDinosListFromTable(&table);
            deinitTable(&table);
        }

    }

    printDinosMapList(dinos, NULL);


    int len = (int)List_size(dinos);
    if(totree)
    {
        BSTree bst;
        BSTree_init(&bst);

        for (int i = 0; i < len; i++)
        {
            StrMap *dino = List_get(dinos, i);
            BSTree_insert(&bst, dino);
        }

        printTree(bst.root);

        if (argument == true)
        {
            printf("\nPROCESSING...\n");
            traverseAndDelet(bst.root, N, &bst);
            printTree(bst.root);
            printf("\n");
        }
        clearBinTree(bst.root);

    }
    else
    {
        if(argument == true)
        {
            processMapList(dinos, N);
            printDinosMapList(dinos, NULL);
        }
    }
    
    if(is_Output)
    {
        printDinosMapList(dinos, outpoot);
    }


    freeListOMaps(dinos);


    free(inpoot);
    free(outpoot);

    return 0;
}

