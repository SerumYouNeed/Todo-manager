#include <stdio.h>
#include <threads.h>

int main(void)
{
    char a[1024] = "1. ggggggggg";
    if (a[0] == 1)
    {
        a[0] = '4';
    }
    printf("%s", a);
}