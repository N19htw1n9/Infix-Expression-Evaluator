//Author: Sarim Qureshi
//Publication Date: 1/26/2020

/**************************************************************/
/*                 char Stack Code                            */
/**************************************************************/

#include "Header.h"

charStack::charStack()
{
    size = 2;
    stack = new char[size];
    current = -1;
}

void charStack::init()
{
    size = 2;
    stack = new char[size];
    current = -1;
}

void charStack::grow()
{
    size += 2;
    char* temp = new char[size];

    int k;
    for(k = 0; k < size; k++)
        temp[k] = stack[k];
    
    delete [] stack;
    stack = temp;
}

boolean charStack::isEmpty()
{
    if(current == -1)
        return TRUE;
    
    return FALSE;
}

void charStack::push(char data)
{
    if(current + 1 == size)
        grow();
    
    current++;
    stack[current] = data;
}

void charStack::pop()
{
    stack[current] = '?';
    current--;
}

char charStack::top()
{
    return stack[current];
}

void charStack::reset()
{
    delete [] stack;
    init();
}