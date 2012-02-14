

#include <stdio.h>
#include "Object.h"

void foo()
{

    typedef int test;

    struct my_struct{
        void operator()( test t ) { printf("HaHa\n");}

    } my_object;

    my_object(3);

    printf("Hello World!, in Foo\n");
}

int main(void)
{


    foo();

    return 0;
}
