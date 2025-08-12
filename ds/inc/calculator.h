#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

typedef struct calculator calculator_t;

typedef enum calculator_status
{
    success,
    arithmetic_error,
    syntax_error

} calculator_status_t;


calculator_status_t CalculatorCreate(const char* expression, double* res);

#endif /* __CALCULATOR_H__ */