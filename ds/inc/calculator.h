#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

typedef struct calculator calculator_t;

typedef enum calculator_status
{
    SUCCESS,
    ARITHMETIC_ERROR,
    SYNTAX_ERROR,
    MEMORY_ERROR

} calculator_status_t;

typedef enum operators
{
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    POWER,
    OPEN_PARENTHESIS,
    CLOSE_PARENTHESIS,
    EQUAL
} operators_t;



calculator_status_t CalculatorCreate(const char* expression, double* res);

#endif /* __CALCULATOR_H__ */