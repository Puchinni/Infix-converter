#include "Algorythm.h"

void Algorythm::AddToString(char *result, char *element)
{
    if (strlen(result) + strlen(element) >= 1000000)
    {
        printf("String is too long\n");
    }
    char whitespace[2];
    whitespace[0] = ' ';
    whitespace[1] = '\0';
    if (strlen(result) > 0)
    {
        strcat(result, whitespace);
    }
    strcat(result, element);
}

int Algorythm::GetPriority(char symbol)
{
    if (symbol == ',')
    {
        return 0;
    }
    else if (symbol == '+' || symbol == '-')
    {
        return 1;
    }
    else if (symbol == '*' || symbol == '/')
    {
        return 2;
    }
    else if (symbol == 'I' || symbol == 'N' || symbol == 'M')
    {
        return 3;
    }
    else
    {
        return 4;
    }
}

// wyklad AiSD nr 2
void Algorythm::ONPconvert(char *result, char *input, MyStack &stack)
{
    if (input[0] == '.')
    {
        while (!stack.isEmpty())
        {
            Node *tmp = stack.getTop();
            AddToString(result, tmp->data.symbol);
            stack.pop();
        }
    }
    else if (input[0] >= '0' && input[0] <= '9')
    {
        AddToString(result, input);
    }
    else if (input[0] == '(')
    {
        stack.push(SYMBOL, input);
    }
    else if (input[0] == ')')
    {
        int commas = 0;
        while (!stack.isEmpty())
        {
            Node *tmp = stack.getTop();
            if (tmp->data.symbol[0] == '(')
            {
                if (tmp->next != NULL && tmp->next->data.symbol[0] == 'M')
                {
                    commas++;
                    tmp->next->data.symbol[3] = (char)(commas + '0');
                    tmp->next->data.symbol[4] = '\0';
                    AddToString(result, tmp->next->data.symbol);
                    stack.pop();
                }
                stack.pop();
                break;
            }
            else
            {
                if (tmp->data.symbol[0] != ',')
                {
                    AddToString(result, tmp->data.symbol);
                }
                else
                    commas++;
                stack.pop();
            }
        }
    }
    else if (input[0] == 'N' || input[0] == 'I' || input[0] == 'M')
    {
        stack.push(SYMBOL, input);
    }
    else
    {
        int priority = GetPriority(input[0]);
        while (!stack.isEmpty())
        {
            char tmpSymbol[10];
            strcpy(tmpSymbol, stack.getTop()->data.symbol);
            stack.pop();
            if (tmpSymbol[0] == '(' || GetPriority(tmpSymbol[0]) < priority)
            {
                stack.push(SYMBOL, tmpSymbol);
                break;
            }
            else if (tmpSymbol[0] != ',')
            {
                AddToString(result, tmpSymbol);
            }
            else
            {
                stack.push(SYMBOL, input);
                break;
            }
        }
        stack.push(SYMBOL, input);
    }
}

// wyklad AiSD nr 2
int Algorythm::CalculateONP(char *result, MyStack &stack)
{
    int error = 0;
    char *token = strtok(result, " ");
    int tokenNumber = 0;
    while (token != NULL)
    {
        tokenNumber = atoi(token);
        if (token[0] >= '0' && token[0] <= '9')
        {
            stack.push(NUMBER, tokenNumber);
        }
        else
        {
            stack.push(SYMBOL, token);
            stack.print();
            stack.pop();
            int calcRes = Calculation(stack, token, error);
            if (error == 1)
            {
                return 1;
            }
            stack.push(NUMBER, calcRes);
        }
        token = strtok(NULL, " ");
    }
    printf("%d\n", stack.getTop()->data.number);
    stack.pop();
    return 0;
}

int Algorythm::Calculation(MyStack &stack, char *token, int &error)
{
    int result = 0;
    int firstValue = stack.getTop()->data.number;
    stack.pop();
    if (firstValue == 0 && token[0] == '/')
    {
        error = 1;
        return 1;
    }
    else if (token[0] == 'N')
    {
        result = -firstValue;
    }
    else if (token[0] == 'M')
    {
        int minmaxValue = token[3] - '0';
        for (int i = 0; i < minmaxValue - 1; i++)
        {
            int tmpValue = stack.getTop()->data.number;
            stack.pop();
            if (token[1] == 'A')
            {
                if (tmpValue > firstValue)
                {
                    firstValue = tmpValue;
                }
            }
            else if (token[1] == 'I')
            {
                if (tmpValue < firstValue)
                {
                    firstValue = tmpValue;
                }
            }
        }
        result = firstValue;
    }
    else
    {
        int secondValue = stack.getTop()->data.number;
        stack.pop();
        if (token[0] == 'I')
        {
            int thirdValue = stack.getTop()->data.number;
            stack.pop();
            result = (thirdValue > 0) ? secondValue : firstValue;
        }
        else if (token[0] == '+')
        {
            result = secondValue + firstValue;
        }
        else if (token[0] == '-')
        {
            result = secondValue - firstValue;
        }
        else if (token[0] == '*')
        {
            result = secondValue * firstValue;
        }
        else if (token[0] == '/')
        {
            result = secondValue / firstValue;
        }
    }
    return result;
}