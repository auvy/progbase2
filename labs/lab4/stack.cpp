#include "stack.hpp"

char* & Stack::operator[](int index)
{
  return this->array_[index];
}


int Stack::Stack_length()
{
    return this->length_;
}


void Stack::Stack_realloc(int newCapacity)
{
    char **newArray = (char**)realloc(this->array_, sizeof(char*) * newCapacity);
    if (newArray == NULL)
    {
        for (int i = 0; i < this->length_; i++)
        {
            free(this->array_[i]);
        }
        free(this->array_);
        std::cerr << "Reallocation error\n" << std::endl;
        abort();
    }
    this->array_ = newArray;
    this->capacity_ = newCapacity;
}

void Stack::Stack_push(char *string, int len)
{
    this->array_[this->length_] = (char*)malloc((len + 1) * sizeof(char));

    strcpy(this->array_[this->length_], string);

    this->length_ += 1;
    //
    if (this->length_ == this->capacity_)
    {
        int newCapacity = this->capacity_ + 1;
        this->Stack_realloc(newCapacity);
    }
}

char * Stack::Stack_pop()
{
    if (this->length_ == 0) 
    {
        std::cerr << "Stack underflow\n" << std::endl;
        abort();
    }

    char *string = this->array_[this->length_ - 1];
    this->length_ -= 1;
    return string;
}


char * Stack::Stack_peek()
{
    if (this->length_ == 0) 
    {
        std::cerr << "Stack underflow\n" << std::endl;
        abort();
    }
    char *string = this->array_[this->length_ - 1];
    return string;
}

bool Stack::Stack_isEmpty()
{
    return this->length_ == 0;
}

void Stack::Stack_print()
{
    std::cout << "Printing stack: \n" << std::endl;
    for(int i = 0; i < this->length_; i++)
    {
        std::cout << this->array_[i] << std::endl;
    }
    puts("");
}