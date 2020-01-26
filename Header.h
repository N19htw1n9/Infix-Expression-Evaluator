//Author: Sarim Qureshi
//Publication Date: 1/26/2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cstdio>
#include <cstring>
#include <cctype>

typedef enum {FALSE = 0, TRUE = 1} boolean;

class intStack
{
    private:
        int* stack;
        int size;
        int current;
        
    public:
        intStack();
        void init();
        void grow();
        boolean isEmpty();
        void push(int);
        void pop();
        int top();
        void reset();
};

class charStack
{
    private:
        char* stack;
        int size;
        int current;
        
    public:
        charStack();
        void init();
        void grow();
        boolean isEmpty();
        void push(char);
        void pop();
        char top();
        void reset();
};