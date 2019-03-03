#include "addon.h"

void Write_to_stacks(Stack *self1, Stack *self2, List *self)
{
    printf("Writing into stacks: \n");
    for(int i = 0; i < self->length; i++)
    {
        if(i % 2 == 0)
        {
            Stack_push(self1, self->array[i], (int)strlen(self->array[i]));
        }
        else if(i % 2 != 0)
        {
            Stack_push(self2, self->array[i], (int)strlen(self->array[i]));
        }
    }
}

void Write_to_list(Stack *stack, List *dlist)
{
    printf("Writing into list..\n");

    for(int i = 0; i < stack->length; i++)
    {
        List_add(dlist, stack->array[i], (int)strlen(stack->array[i]));
    }
}