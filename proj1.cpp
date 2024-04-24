#include "Algorythm.h"

int main()
{
    char input[15];
    Algorythm algorythm;
    MyStack stack;
    char result[1000000];
    result[0] = '\0';
    int n = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        result[0] = '\0';
        input[0] = '\0';
        while (strcmp(input, ".") != 0)
        {
            scanf("%14s", input);
            algorythm.ONPconvert(result, input, stack);
        }
        printf("%s\n", result);
        int errorValue = algorythm.CalculateONP(result, stack);
        if (errorValue == 1)
        {
            printf("ERROR\n");
            stack.clear();
        }
        printf("\n");
    }
    return 0;
}
