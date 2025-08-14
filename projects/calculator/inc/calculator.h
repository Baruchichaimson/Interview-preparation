#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

typedef enum calculator_status
{
    CALC_SUCCESS,
    CALC_ARITHMETIC_ERROR,
    CALC_SYNTAX_ERROR
} calc_status_t;

typedef enum state
{
    STATE_NUMBER,
    STATE_OPERATOR,
    NUM_STATES
} state_t;

typedef enum event
{
    EVENT_DIGIT,
    EVENT_OPERATOR,
    EVENT_LPAREN,
    EVENT_RPAREN,
    EVENT_SPACE,
    EVENT_END,
    NUM_EVENTS
} event_t;


calc_status_t Calculator(const char* expression, double* res);

#endif /* __CALCULATOR_H__ */