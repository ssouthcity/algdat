#include <fstream>
#include <iostream>
#include <stdio.h>

struct StackNode
{
    char value;
    StackNode *next;
};

class Stack
{
private:
    StackNode *top;

public:
    ~Stack();
    char peek();
    void push(char v);
    void pop();
    bool empty();
};

Stack::~Stack()
{
    while (!empty())
        pop();
}

char Stack::peek()
{
    return top->value;
}

void Stack::push(char v)
{
    auto *node = new StackNode;
    node->value = v;
    node->next = top;
    top = node;
}

void Stack::pop()
{
    auto *tmp = top;
    top = top->next;
    delete tmp;
}

bool Stack::empty()
{
    return top == NULL;
}

bool opening(char a)
{
    return a == (char)40 || a == (char)91 || a == (char)123;
}

bool closing(char a)
{
    return a == (char)41 || a == (char)93 || a == (char)125;
}

bool matching(char a, char b)
{
    return (
        (a == (char)40 && b == (char)41) ||
        (a == (char)91 && b == (char)93) ||
        (a == (char)123 && b == (char)125));
}

bool fileBalanced(char *filename)
{
    std::fstream fin(filename, std::fstream::in);
    Stack brackets;
    char c;

    while (fin >> std::noskipws >> c)
    {
        if (opening(c))
            brackets.push(c);
        else if (closing(c))
            if (!brackets.empty() && matching(brackets.peek(), c))
                brackets.pop();
            else
                return false;
    }

    return brackets.empty();
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "First argument is a file to check" << std::endl;
        return 1;
    }

    if (fileBalanced(argv[1]))
    {
        std::cout << "File is balanced" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "File is imbalanced" << std::endl;
        return 1;
    }
}