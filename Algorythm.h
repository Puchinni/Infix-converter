#include "MyStack.h"

class Algorythm
{
private:
    void AddToString(char *result, char *element);
    int GetPriority(char symbol);
    int Calculation(MyStack &stack, char *token, int &error);

public:
    void ONPconvert(char *result, char *input, MyStack &stack);
    int CalculateONP(char *result, MyStack &stack);
};
