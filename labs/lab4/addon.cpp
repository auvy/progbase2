#include "addon.hpp"

void Write_to_stacks(Stack *self1, Stack *self2, List *self)
{
    std::cout << "Writing into stacks...\n " << std::endl;
    for(int i = 0; i < self->List_length(); i++)
    {
        if(i % 2 == 0)
        {
            self1->Stack_push(self->operator[](i), (int)strlen(self->operator[](i)));
        }
        else if(i % 2 != 0)
        {
            self2->Stack_push(self->operator[](i), (int)strlen(self->operator[](i)));
        }
    }
}

void Write_to_list(Stack *stack, List *dlist)
{
    std::cout << "Writing into list...\n " << std::endl;

    for(int i = 0; i < stack->Stack_length(); i++)
    {
        dlist->List_add(stack->operator[](i), (int)strlen(stack->operator[](i)));
    }
}

List::List()
{
  this->length_ = 0;
  this->capacity_ = 2;
  this->array_ = (char **)malloc(this->capacity_ * sizeof(char *));
  if (this->array_ == NULL)
  {
    std::cerr << "Allocation error\n" << std::endl;
    abort();
  }
}

List::~List()
{
    for(int i = 0; i < this->length_; i++)
    {
        free(this->array_[i]);
    }
    free(this->array_);
}

Stack::Stack()
{
  this->length_ = 0;
  this->capacity_ = 4;
  this->array_ = (char **)malloc(this->capacity_ * sizeof(char *));
  if (this->array_ == NULL)
  {
    std::cerr << "Allocation error\n" << std::endl;
    abort();
  }
}

Stack::~Stack()
{
  for (int i = 0; i < this->length_; i++)
  {
    free(this->array_[i]);
  }
  free(this->array_);
}