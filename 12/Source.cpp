#include <stdio.h>

#include "parser.h"
#include "interpretator.h"

int main()
{
    // ��������� ���� �� ����� � ����� ���������
    int parseRes = parseFile("C:/Users/supre/OneDrive/Documents/Intepretator/template.txt");

    // ���� ������ �������� ���, �� ����� ��������� ���
    if (parseRes != -1)
    {
        parseRes = runProgramm(parseRes);
    }

    if (parseRes == 0)
    {
        printf("Everything good");
    }
    else
    {
        printf("Runtime error");
    }
    return 0;
}
