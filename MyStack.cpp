#include "MyStack.h"

Node::Node(NodeType nodeType, int value) : next(NULL)
{
    this->type = nodeType;
    data.number = value;
}

Node::Node(NodeType nodeType, char *value) : next(NULL)
{
    this->type = nodeType;
    data.symbol = value;
}

MyStack::MyStack() : top(NULL) {}

MyStack::~MyStack()
{
    while (!isEmpty())
    {
        pop();
    }
}

void MyStack::clear()
{
    while (!isEmpty())
    {
        pop();
    }
}

Node *MyStack::getTop()
{
    return top;
}

bool MyStack::isEmpty()
{
    return top == NULL;
}

void MyStack::push(NodeType type, int value)
{
    Node *newNode = new Node(type, value);
    if (newNode == NULL)
        return;
    newNode->next = top;
    top = newNode;
}

void MyStack::push(NodeType type, char *value)
{
    char *newValue = new char[strlen(value) + 1];
    strcpy(newValue, value);
    Node *newNode = new Node(type, newValue);
    if (newNode == NULL)
        return;
    newNode->next = top;
    top = newNode;
}

void MyStack::pop()
{
    if (!isEmpty())
    {
        Node *temporary = top;
        top = top->next;
        if (temporary->type == SYMBOL)
        {
            delete[] temporary->data.symbol;
        }
        delete temporary;
    }
    else
        return;
}

void MyStack::print()
{
    Node *temporary = top;
    while (temporary != NULL)
    {
        if (temporary->type == NUMBER)
        {
            printf("%d ", temporary->data.number);
        }
        else
        {
            printf("%s ", temporary->data.symbol);
        }
        temporary = temporary->next;
    }
    printf("\n");
}
