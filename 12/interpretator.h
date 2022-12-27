#ifndef INTERPRETATOR_H
#define INTERPRETATOR_H

#include "commands.h"
#include "parser.h"

int exCommand(const int type, const int comNum)
{
    switch (type)
    {
    case LD:
    {
        return ld();
        break;
    }
    case LDN:
    {
        return ldn();
        break;
    }
    case ST:
    {
        return st();
        break;
    }
    case STN:
    {
        return stn();
        break;
    }
    case ANDN:
    {
        return andn(q_commands[comNum].value);
        break;
    }
    case ORN:
    {
        return orn(q_commands[comNum].value);
        break;
    }
    case XORN:
    {
        return xorn(q_commands[comNum].value);
        break;
    }
    case ADD:
    {
        return add(q_commands[comNum].value);
        break;
    }
    case SUB:
    {
        return sub(q_commands[comNum].value);
        break;
    }
    case MUL:
    {
        return mul(q_commands[comNum].value);
        break;
    }
    case DIV:
    {
        return Div(q_commands[comNum].value);
        break;
    }
    case GT:
    {
        printf("%d \n", q_commands[comNum].value);
        return gt(q_commands[comNum].value);
        break;
    }
    case GE:
    {
        return ge(q_commands[comNum].value);
        break;
    }
    case EQ:
    {
        return eq(q_commands[comNum].value);
        break;
    }
    case NE:
    {
        return ne(q_commands[comNum].value);
        break;
    }
    case LE:
    {
        return le(q_commands[comNum].value);
        break;
    }
    case OR:
    {
        return or (q_commands[comNum].value);
        break;
    }
    case AND:
    {
        return and (q_commands[comNum].value);
        break;
    }
    case NOT:
    {
        not();
        break;
    }
    case XOR:
    {
        return xor (q_commands[comNum].value);
        break;
    }
    case LT:
    {
        return lt(q_commands[comNum].value);
        break;
    }
    case JMP:
    {
        return jmp(comNum);
        break;
    }
    case JMPC:
    {
        return jmpc(comNum);
        break;
    }
    case JMPCN:
    {
        return jmpcn(comNum);
        break;
    }
    case RET:
    {
        ret();
        break;
    }
    case RETC:
    {
        return retc();
        break;
    }
    case RETCN:
    {
        return retcn();
        break;
    }
    }
}

int runProgramm(const int comSize)
{
    int programState = 0;
    for (int i = 1; i < comSize; ++i)
    {
        if (q_commands[i].id == JMP || q_commands[i].id == JMPC || q_commands[i].id == JMPCN)
        {
            int res = exCommand(q_commands[i].id, i);
            if (res != -1)
            {
                i = res - 1;
            }
            else
            {
                return 1;
            }
        }
        else if (q_commands[i].id == RET)
        {
            return 1;
        }
        else if (q_commands[i].id == RETC || q_commands[i].id == RETCN)
        {
            int res = exCommand(q_commands[i].id, i);
            if (res == 0)
            {
                return 0;
            }
        }
        else
        {
            programState = exCommand(q_commands[i].id, i);
            if (programState == 1)
            {
                return 1;
            }
        }
    }
    return programState;
}

#endif 
