#include <stdio.h>

#include "parser.h"
#include "interpretator.h"

int main()
{
    // указываем путь до файла с кодом программы
    int parseRes = parseFile("C:/Users/supre/OneDrive/Documents/Intepretator/template.txt");

    // если ошибок парсинга нет, то можно выполнять код
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
