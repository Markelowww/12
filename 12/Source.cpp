#include <stdio.h>
#include "parser.h"
#include "interpretator.h"

int main()
{
    int parseRes = parseFile("C:/Users/BAZOOK/Documents/Intepretator/template.txt");
    if (parseRes != -1)
    {
        parseRes = runProgramm(parseRes);
    }
    if (parseRes == 0)
    {
        printf("Everything works");
    } 
    else
    {
        printf("Runtime error");
    }
    return 0;
}
