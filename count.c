#include <stdio.h>

int main(void)
{
    char a[1024] = "1. ggggggfnfn";
    if (a[0] == 1)
    {
        a[0] = '4';
    }
    printf("%s", a);
}