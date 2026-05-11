#include <stdio.h>

int main(void)
{ 

    int a = 15;
    char s[5];
    snprintf(s, 5, "%d", a);



    char str[1024] = "34. ggggggfnfn";
    char temp[1024];

    for (int i = 0; s[i] != '\0'; i++)
    {
        str[i] = s[i];
    }


    printf("%s", str);
}