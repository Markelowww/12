#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "interpretator.h"

#define MAX_COMMAND_SIZE 100

int parseFile(const char* fileName);
int checkCommand(const char* curName, const size_t comLen);
int checkCommandType(const char* curCom);
int parseMark(const char* curCom, const int strNum);
int parseCommand(const char* comName, int comAddr, const int strNum);
int parseNumericValue(char* comValue, const int spaceId, long* value);
int parseStreamValue(char* comValue, const int spaceId);
int parseJumpMark(char* comValue, const int spaceId, const int strNum);

int parseFile(const char* filename)
{
    FILE* mf;
    char str[MAX_COMMAND_SIZE];
    char* curPtrCommand;
    int lineCounter = 0;
    printf("Open file ");
    mf = fopen(filename, "r");
    if (mf == NULL)
    {
        printf("Error open file\n");
        lineCounter = -1;
    }
    else
    {
        printf("Complete \n");
    }
    while (1)
    {
        curPtrCommand = fgets(str, sizeof(str), mf);
        if (curPtrCommand == NULL)
        {
            break;
        }
        ++lineCounter;
        switch (checkCommandType(str))
        {
        case COM_COMMON:
        {
            int res = parseCommand(str, 0, lineCounter);
            break;
        }
        case COM_MARK:
        {
            int markId = parseMark(str, lineCounter);
            int res = parseCommand(str, markId, lineCounter);
            break;
        }
        }
    }

    return lineCounter + 1;
}

int checkCommand(const char* curName, const size_t comLen)
{
    char* curCom = (char*)malloc(comLen + 1);
    strncpy(curCom, curName, comLen);
    curCom[comLen] = '\0';
    for (size_t i = 0; i < 27; ++i)
    {
        if (strcmp(curCom, string_commands[i]) == 0)
        {
            free(curCom);
            return i;
        }
    }
    return ERROR_INVALID_COMMAND;
}

int checkCommandType(const char* curCom)
{
    for (size_t i = 0; i < strlen(curCom) - 1; ++i)
    {
        if (curCom[i] != ' ' && (curCom[i + 1] == ' ' || curCom[i + 1] == '\n'))
        {
            if (checkCommand(curCom, i + 1) != ERROR_INVALID_COMMAND)
            {
                return COM_COMMON;
            }
            else
            {
                return COM_MARK;
            }
        }
    }
    return ERROR_INVALID_COMMAND;
}

int parseMark(const char* curCom, const int strNum)
{
    int markId = -1;
    int parseState = 0;
    for (size_t i = 0; i < strlen(curCom) - 1; ++i)
    {
        if (curCom[i] != ' ' && curCom[i + 1] == ' ' && parseState == 0)
        {
            if (i > 9)
            {
                return ERROR_INVALID_MARK_SIZE;
            }
            char* curMark = (char*)malloc(i + 2);
            strncpy(curMark, curCom, i + 1);
            curMark[i + 1] = '\0';
            for (int j = 1; j < strNum; ++j)
            {
                if (strcmp(curMark, q_marks[j]) == 0)
                {
                    return ERROR_THIS_MARK_ALREADY_EXIST;
                }
            }
            strcpy(q_marks[strNum], curMark);
            free(curMark);
            ++parseState;
        }

        if (curCom[i] == ' ' && curCom[i + 1] != ' ' && parseState == 1)
        {
            markId = i;
            break;
        }
    }
    return markId + 1;
}

int parseCommand(char* comName, int comAddr, const int strNum)
{
    long* curValue = (long*)malloc(1);
    // парсим первую часть строки
    for (size_t i = comAddr + 1; i < strlen(comName) - 1; ++i)
    {
        if (comName[i] != ' ' && (comName[i + 1] == ' ' || comName[i + 1] == '\n'))
        {
            // проверяем, что перед нами команда
            int comId = checkCommand(&comName[comAddr], i - comAddr + 1);
            // команды, где нужно использовать поток ввода (in)
            if (comId == LD || comId == LDN)
            {
                int resStream = parseStreamValue(comName, i + 1);
                q_commands[strNum].id = comId;
                q_commands[strNum].value = *curValue;
                free(curValue);
            }
            // команда, где нужно использовать поток вывода (out)
            else if (comId == ST || comId == STN)
            {
                int resStream = parseStreamValue(comName, i + 1);
                // добавляем команду ST, STN
                q_commands[strNum].id = comId;
                q_commands[strNum].value = *curValue;
                free(curValue);
                return OK;
            }
            // команды без аргументов
            else if (comId == NOT || comId == RET || comId == RETC || comId == RETCN)
            {
                // добавляем команду
                q_commands[strNum].id = comId;
                q_commands[strNum].value = *curValue;
                free(curValue);
                return OK;
            }
            else if (comId == JMP || comId == JMPC || comId == JMPCN)
            {
                // обрабатываем прыжки
                int resValue = parseJumpMark(comName, i + 1, strNum);
                q_commands[strNum].id = comId;
                return OK;
            }
            else
            {
                int parseRes = parseNumericValue(comName, i, curValue);
                q_commands[strNum].id = comId;
                q_commands[strNum].value = *curValue;
                free(curValue);
                return OK;
            }
            break;
        }
    }

    return ERROR_INVALID_COMMAND;
}

int parseNumericValue(char* comValue, const int spaceId, long* value)
{
    int parseState = 0;
    char* curValue = NULL;
    for (size_t i = spaceId; i < strlen(comValue) - 1; ++i)
    {
        if (comValue[i] == ' ' && (comValue[i + 1] >= '0' && comValue[i + 1] <= '9') && parseState == 0)
        {
            curValue = comValue + i + 1;
            ++parseState;
            ++i;
        }
        if (parseState == 1)
        {
            if (comValue[i] < '0' || comValue[i] > '9')
            {
                break;
            }
            else if (comValue[i + 1] == ';' || comValue[i + 1] == '\n' || comValue[i + 1] == ' ')
            {
                ++parseState;
            }
            ++i;
        }
        if (parseState == 2)
        {
            if (comValue[i] == ';')
            {
                ++parseState;
                break;
            }
            else if ((comValue[i] == ' ' || (comValue[i] >= '0' && comValue[i] <= '9')) && comValue[i + 1] == '\n')
            {
                ++parseState;
            }
            else if (comValue[i] == '\n')
            {
                ++parseState;
                break;
            }
            else if (comValue[i] != ' ')
            {
                break;
            }
        }
    }

    if (parseState < 3)
    {
        return ERROR_INVALID_OPERAND;
    }
    else
    {
        *value = strtol(curValue, NULL, 10);
        return OK;
    }
}

int parseStreamValue(char* comValue, const int spaceId)
{
    int parseState = 0;
    for (size_t i = spaceId; i < strlen(comValue) - 1; ++i)
    {
        if (comValue[i] == ' ' && (comValue[i + 1] == 'i' || comValue[i + 1] == 'o') && parseState == 0)
        {
            if (comValue[i + 1] == 'i' && (strlen(comValue) - i > 3) && comValue[i + 2] == 'n')
            {
                parseState += 2;
                i += 3;
            }
            else if (comValue[i + 1] == 'o' && (strlen(comValue) - i > 4) && comValue[i + 2] == 'u' && comValue[i + 3] == 't')
            {
                parseState += 3;
                i += 4;
            }
        }
        if (parseState == 2 || parseState == 3)
        {
            if (comValue[i] == ';')
            {
                ++parseState;
                break;
            }
            else if (comValue[i] == ' ' && comValue[i + 1] == '\n')
            {
                ++parseState;
                break;
            }
            else if (comValue[i] == '\n')
            {
                ++parseState;
                break;
            }
            else if (comValue[i] != ' ')
            {
                break;
            }
        }
    }

    if (parseState == 3)
    {
        return IN;
    }
    else if (parseState == 4)
    {
        return OUT;
    }
}

int parseJumpMark(char* comValue, const int spaceId, const int strNum)
{
    int parseState = 0;
    for (size_t i = spaceId; i < strlen(comValue) - 1; ++i)
    {
        if (comValue[i] != ' ' && (comValue[i + 1] == ' ' || comValue[i + 1] == '\n') && parseState == 0)
        {
            strncpy(q_marks_jmp[strNum], &comValue[spaceId + 1], i - spaceId);
            q_commands[strNum].markId = strNum;
            ++parseState;
            ++i;
        }
        if (parseState == 1)
        {
            //printf("char:%cop", comValue[i]);
            if (comValue[i] == ';')
            {
                ++parseState;
                break;
            }
            else if (comValue[i] == ' ' && comValue[i + 1] == '\n')
            {
                ++parseState;
                break;
            }
            else if (comValue[i] == '\n')
            {
                ++parseState;
                break;
            }
            else if (comValue[i] != ' ')
            {
                break;
            }
        }
    }
    return OK;
}
#endif // PARSER_H
