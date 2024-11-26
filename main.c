#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef enum
{
    false,
    true
} bool;


typedef struct
{
    int *data;
    size_t size;
    size_t capacity;
} Stack;


Stack make_empty()
{
    Stack stack;
    stack.data = NULL;
    stack.size = 0;
    stack.capacity = 0;
    return stack;
}

Stack make_of_size(size_t capacity)
{
    Stack stack;
    stack.data = (int *)malloc(capacity * sizeof(int));
    stack.size = 0;
    stack.capacity = capacity;
    return stack;
}

Stack make_from_array(const int array[], size_t size)
{
    Stack stack;
    stack.data = (int *)malloc(size * sizeof(int));
    stack.size = size;
    stack.capacity = size;
    for (size_t i = 0; i < size; ++i)
    {
        stack.data[i] = array[i];
    }
    return stack;
}

Stack make_copy(const Stack *original)
{
    Stack copy;
    copy.data = (int *)malloc(original->capacity * sizeof(int));
    copy.size = original->size;
    copy.capacity = original->capacity;
    for (size_t i = 0; i < original->size; ++i)
    {
        copy.data[i] = original->data[i];
    }
    return copy;
}

void clear(Stack *stack)
{
    free(stack->data);
    stack->data = NULL;
    stack->size = 0;
    stack->capacity = 0;
}


int at(const Stack *stack, int index)
{

    if (index < 0)
    {
        index = stack->size + index;
    }

    if (index < 0)
    {
        return stack->data[0];
    }
    if ((size_t)index >= stack->size)
    {
        return stack->data[stack->size - 1];
    }
    return stack->data[index];
}


bool is_equal(const Stack *a, const Stack *b)
{
    if (a->size != b->size)
    {
        return false;
    }

    for (size_t i = 0; i < a->size; ++i)
    {
        if (a->data[i] != b->data[i])
        {
            return false;
        }
    }

    return true;
}


int main(int argc, char const *argv[])
{
    int array[] = {1, 4, 7, 9};

    Stack a = make_from_array(array, 4);

    assert(9 == at(&a, 3));
    assert(9 == at(&a, -1));
    assert(9 == at(&a, 13));
    assert(1 == at(&a, -13));

    Stack b = make_copy(&a);

    assert(is_equal(&a, &b));

    clear(&a);
    clear(&b);

    return 0;
}