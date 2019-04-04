#include "list.hpp"

char* & List::operator[](int index)
{
  return this->array_[index];
}


int List::List_length()
{
    return this->length_;
}

void List::List_realloc(int newCapacity)
{
    char **newArray = (char**)realloc((this->array_), sizeof(char*) * newCapacity);

    if (newArray == NULL)
    {
        free(this->array_);
        std::cerr << "Reallocation error\n" << std::endl;
        abort();
    }

    this->array_ = newArray;
    this->capacity_ = newCapacity;
}

void List::List_add(char *string, int len)
{
    this->array_[this->length_] = (char*)malloc((len + 1) * sizeof(char));

    strcpy(this->array_[this->length_], string);
    //
    this->length_ += 1;
    //
    if (this->length_ == this->capacity_)
    {
        int newCapacity = this->capacity_ + 1;
        this->List_realloc(newCapacity);
    }
}

void List::List_print()
{
    std::cout << "Printing list:\n " << std::endl;
    for(int i = 0; i < this->length_; i++)
    {
        std::cout << this->array_[i] << std::endl;
    }
    puts("");
}

void List::List_sort()
{
    std::cout << "Sorting...\n " << std::endl;
    char *bufpoint;

    for(int i = 0; i < this->length_; i++)
    {
        if((strstr(this->array_[i], " the ") != NULL))
        {
            bufpoint = this->array_[i];

            for(int j = i; j < this->length_; j++)
            {
                if((strstr(this->array_[j], " the ") == NULL))
                {
                    this->array_[i] = this->array_[j];
                    this->array_[j] = bufpoint;
                    break;
                }
            }
        }
    }
}

void List::List_fwrite()
{
    FILE *file;

    char buf[256] = {'\0'};

    int bufc = 0;

    file = fopen("data.txt", "r");

    while (fgets(buf, 256, file))
    {
        while (buf[bufc] != '\0')
        {
            if (buf[bufc] == '\n') buf[bufc] = '\0';
            bufc++;
        }

        this->List_add(buf, bufc);

        for(int i = 0; i < bufc; i++)
        {
            buf[i] = '\0';
        }
        bufc = 0;
    }

    fclose(file);
}
