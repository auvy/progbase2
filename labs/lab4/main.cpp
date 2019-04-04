#include "list.hpp"
#include "stack.hpp"
#include "addon.hpp"

int main()
{
    List dlist;

    dlist.List_fwrite();

    dlist.List_print();

    dlist.List_sort();

    dlist.List_print();

    Stack stack1;

    Stack stack2;

    List dlist2;

    Write_to_stacks(&stack1, &stack2, &dlist);

    stack1.Stack_print();

    stack2.Stack_print();

    Write_to_list(&stack1, &dlist2);
    Write_to_list(&stack2, &dlist2);

    dlist2.List_print();

    std::cout << "End of program. " << std::endl;

    return 0;
}