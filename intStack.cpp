//Author: Sarim Qureshi
//Publication Date: 1/26/2020

/**************************************************************/
/*                  int Stack Code                            */
/**************************************************************/

#include "Header.h"

intStack::intStack()
{
    size = 2;
    stack = new int[size];
    current = -1;
}

void intStack::init()
{
    size = 2;
    stack = new int[size];
    current = -1;
}

void intStack::grow()
{
    size += 2;
    int* temp = new int[size];

    int k;
    for(k = 0; k < size; k++)
        temp[k] = stack[k];
    
    delete [] stack;
    stack = temp;
}

boolean intStack::isEmpty()
{
    if(current == -1)
        return TRUE;
    
    return FALSE;
}

void intStack::push(int data)
{
    if(current + 1 == size)
        grow();
    
    current++;
    stack[current] = data;
}

void intStack::pop()
{
    stack[current] = -1;
    current--;
}

int intStack::top()
{
    return stack[current];
}

void intStack::reset()
{
    delete [] stack;
    init();
}