#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum
{
    NUMBER,
    SYMBOL,
} NodeType;

struct Node
{
    NodeType type;
    union
    {
        int number;
        char *symbol;
    } data;
    Node *next;

    Node(NodeType nodeType, int value);
    Node(NodeType nodeType, char *value);
};

class MyStack
{
private:
    Node *top;

public:
    MyStack();
    ~MyStack();
    void clear();
    Node *getTop();
    bool isEmpty();
    void push(NodeType type, int value);
    void push(NodeType type, char *value);
    void pop();
    void print();
};
