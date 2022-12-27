#ifndef ERRORS_H
#define ERRORS_H

typedef enum _parse_errors
{
    ERROR_INVALID_SYNTAXSIS = 31,
    ERROR_INVALID_COMMAND = 32,
    ERROR_INVALID_OPERAND = 33,
    ERROR_INVALID_MARK_SIZE = 34,
    ERROR_THIS_MARK_ALREADY_EXIST = 35,
    OK = 36
} parse_errors;

static const char* string_parse_errors[] = { "Invalid syntaxis",
                                            "Invalid command",
                                            "Invalid operand",
                                            "Invalid mark size",
                                            "This mark already exist",
                                            "OK" };
#endif 