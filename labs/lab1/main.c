#include "list.h"
#include "stack.h"
#include "addon.h"


int main(int argc, char *argv[argc])
{
    List dlist;
    List_init(&dlist);

    List_fwrite(&dlist);

    List_print(&dlist);

    List_sort(&dlist);

    List_print(&dlist);

    Stack stack1;    
    Stack_init(&stack1);

    Stack stack2;
    Stack_init(&stack2);

    List dlist2;
    List_init(&dlist2);

    Write_to_stacks(&stack1, &stack2, &dlist);

    Stack_print(&stack1);

    Stack_print(&stack2);

    Write_to_list(&stack1, &dlist2);
    Write_to_list(&stack2, &dlist2);

    List_print(&dlist2);

    List_deinit(&dlist);
    List_deinit(&dlist2);
    Stack_deinit(&stack1);
    Stack_deinit(&stack2);

    printf("Fin.\n");

    return 0;
}