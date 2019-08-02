#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    int d= rand()/100 %100;
    while(d!=100){

    printf("%d\n", d);
    d= rand()/100 %100;
    }
    return 0;
}
