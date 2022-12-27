#ifndef COMMANDS_H
#define COMMANDS_H

#include "stdio.h"
#include "string.h"
#include <climits>

static long accumulator = 0;

typedef struct _command
{
    int id; 
    int value; 
    int markId;
} command;

static command q_commands[10000];
char q_marks[10000][10];
char q_marks_jmp[10000][10];

static const char* string_commands[] =
{ "LD", "LDN", "ST", "STN", "AND", "ANDN", "OR", "ORN", "XOR", "XORN",
 "NOT", "ADD", "SUB", "MUL", "DIV", "GT", "GE", "EQ", "NE", "LE", "LT",
 "JMP", "JMPC", "JMPCN", "RET", "RETC", "RETCN" };

typedef enum _commands
{
    LD = 0, 
    LDN, 
    ST, 
    STN, 
    AND, 
    ANDN, 
    OR, 
    ORN, 
    XOR, 
    XORN, 
    NOT, 
    ADD, 
    SUB, 
    MUL, 
    DIV, 
    GT, 
    GE, 
    EQ, 
    NE, 
    LE, 
    LT, 
    JMP, 
    JMPC, 
    JMPCN, 
    RET, 
    RETC, 
    RETCN 
} commands;

typedef enum _stream
{
    IN = 27, 
    OUT = 28 
} stream;

typedef enum _commands_type
{
    COM_COMMON = 29, 
    COM_MARK = 30 
} commands_type;

int ld()
{
    printf("Input:");
    scanf("%d", &accumulator);
    return 0;
}

int ldn()
{
    printf("Input string:");
    scanf("%d", &accumulator);
    accumulator = ~accumulator;
    return 0;
}

int st()
{
    printf("%d\n", accumulator);
    return 0;
}

int stn()
{
    printf("%d\n", ~accumulator);
    return 0;
}

int andn(const int input)
{
    accumulator &= ~input;
    return 0;
}

int orn(const int input)
{
    accumulator |= ~input;
    return 0;
}

int xorn(const int input)
{
    accumulator ^= ~input;
    return 0;
}

int add(const int input)
{
    if (INT_MAX - input < accumulator)
    {
        return 1;
    }
    else
    {
        accumulator += input;
        return 0;
    }
}

int sub(const int input)
{
    if (INT_MAX - input < accumulator)
    {
        return 1;
    }
    else
    {
        accumulator -= input;
        return 0;
    }
    return 0;
}

int mul(const int input)
{
    if (INT_MAX / input < accumulator)
    {
        return 1;
    }
    else
    {
        accumulator *= input;
        return 0;
    }
}

int Div(const int input)
{
    if (input == 0)
    {
        return 1;
    }
    else
    {
        accumulator /= input;
        return 0;
    }
}

int gt(const int input)
{
    accumulator = (accumulator > input);
    return 0;
}

int ge(const int input)
{
    accumulator = (accumulator >= input);
    return 0;
}

int eq(const int input)
{
    accumulator = (accumulator == input);
    return 0;
}

int ne(const int input)
{
    accumulator = (accumulator != input);
    return 0;
}

int le(const int input)
{
    accumulator = (accumulator <= input);
    return 0;
}

int or (const int input)
{
    accumulator |= input;
    return 0;
}

int and (const int input)
{
    accumulator &= input;
    return 0;
}

int not()
{
    accumulator = ~accumulator;
    return 0;
}

int xor (const int input)
{
    accumulator ^= input;
    return 0;
}

int lt(const int input)
{
    accumulator = (accumulator < input);
    return 0;
}

int jmp(const int input)
{
    for (size_t i = 0; i < 10000; ++i)
    {
        if (strcmp(q_marks_jmp[input], q_marks[i]) == 0)
        {
            return i;
        }
    }
    printf("Invalid mark:%s\n", q_marks_jmp[input]);
    return -1;
}

int jmpc(const int input)
{
    if (accumulator == 1)
    {
        for (size_t i = 0; i < 10000; ++i)
        {
            if (strcmp(q_marks_jmp[input], q_marks[i]) == 0)
            {
                return i;
            }
        }
        printf("Invalid mark:%s\n", q_marks_jmp[input]);
    }
    return -1;
}

int jmpcn(const int input)
{
    if (accumulator == 0)
    {
        for (size_t i = 0; i < 10000; ++i)
        {
            if (strcmp(q_marks_jmp[input], q_marks[i]) == 0)
            {
                return i;
            }
        }
        printf("Invalid mark:%s\n", q_marks_jmp[input]);
    }
    return -1;
}

int ret()
{
    return 0;
}

int retc()
{
    if (accumulator == 1)
    {
        return 0;
    }
    return 1;
}

int retcn()
{
    if (accumulator != 1)
    {
        return 0;
    }
    return 1;
}

#endif
