#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>

#include "calculator.h"
#include "stack.h"

/* ---- Calculator Data ---- */
typedef struct calc_data
{
    const char* p;
    stack_t* nums;
    stack_t* ops;
    int sign; 
    calc_status_t status;
} calc_data_t;

/* ---- Operators LUT ---- */
typedef struct
{
    int precedence;
    double (*operate)(double, double);
} operator_lut_t;

/* ---- State Machine ---- */
typedef calc_status_t (*event_handler_t)(calc_data_t* calc);

/* ---- handlers ---- */
static calc_status_t handle_number(calc_data_t* calc);
static calc_status_t handle_operator(calc_data_t* calc);
static calc_status_t handle_rparen(calc_data_t* calc);
static calc_status_t handle_lparen(calc_data_t* calc);
static calc_status_t handle_space(calc_data_t* calc);
static calc_status_t handle_end(calc_data_t* calc);

/* ================ Lookup Tables ============================ */

static unsigned char sign_lut[256];
static unsigned char digit_lut[256];
static operator_lut_t op_lut[256];
static event_t char_to_event[256];
static char matching_paren[256];
static unsigned char AS[256];

/* ================= Tables ==================================== */

static event_handler_t state_table[NUM_STATES][NUM_EVENTS];
static state_t next_state[NUM_STATES][NUM_EVENTS];

/* ================== Operator Functions ===================== */

static double add(double a, double b) { return a + b; }
static double sub(double a, double b) { return a - b; }
static double mul(double a, double b) { return a * b; }
static double divide(double a, double b) { return a / b; }
static double power(double a, double b) { return pow(a, b); }

/* ================== init luts ================================ */

static void init_op_lut(void)
{
    operator_lut_t op = { 0 };

    op.precedence = 1; 
    op.operate = add;
    op_lut['+'] = op;

    op.precedence = 1;
    op.operate = sub;
    op_lut['-'] = op;

    op.precedence = 2;
    op.operate = mul;
    op_lut['*'] = op;

    op.precedence = 2;
    op.operate = divide;
    op_lut['/'] = op;

    op.precedence = 3;
    op.operate = power; 
    op_lut['^'] = op;

}

static void init_luts(void)
{
    int i;
    for (i = 0; i < 256; i++)
    {
        sign_lut[i] = 0;
        digit_lut[i] = 0;
    }

    sign_lut[(unsigned char)'+'] =  1;
    sign_lut[(unsigned char)'-'] = (unsigned char)-1; 

    digit_lut[(unsigned char)'.'] = 1;
    for (i = '0'; i <= '9'; i++)
    {
        digit_lut[(unsigned char)i] = 1;
    }
}

static void init_AS(void)
{
    int i;
    for (i = 0; i < 256; i++)
    {
        AS[i] = 0;
    }
    AS['^'] = 1;
}

static void init_matching_paren(void)
{
    int i;
    for (i = 0; i < 256; i++)
    {
        matching_paren[i] = '\0';
    }
    matching_paren[')'] = '(';
    matching_paren[']'] = '[';
    matching_paren['}'] = '{';
    matching_paren['('] = '(';
    matching_paren['['] = '[';
    matching_paren['{'] = '{';
}

/* ================== init tables ========================= */

static void init_tables(void)
{
    int i = 0;
    for (i = 0; i < 256; i++)
    {
        char_to_event[i] = EVENT_END;
    }
    for (i = '0'; i <= '9'; i++) 
    {
        char_to_event[i] = EVENT_DIGIT;
    }
    char_to_event['.'] = EVENT_DIGIT;
    char_to_event['+'] = char_to_event['-'] = char_to_event['*'] = char_to_event['/'] = char_to_event['^'] = EVENT_OPERATOR;
    char_to_event['('] = EVENT_LPAREN;
    char_to_event['['] = EVENT_LPAREN;
    char_to_event['{'] = EVENT_LPAREN;
    char_to_event[')'] = EVENT_RPAREN;
    char_to_event[']'] = EVENT_RPAREN;
    char_to_event['}'] = EVENT_RPAREN;
    char_to_event[' '] = EVENT_SPACE;
    char_to_event['\0'] = EVENT_END;

    /* STATE_NUMBER */
    state_table[STATE_NUMBER][EVENT_DIGIT]    = handle_number;  
    next_state[STATE_NUMBER][EVENT_DIGIT]    = STATE_OPERATOR;

    state_table[STATE_NUMBER][EVENT_OPERATOR]    = handle_number; 
    next_state[STATE_NUMBER][EVENT_OPERATOR] = STATE_NUMBER;

    state_table[STATE_NUMBER][EVENT_LPAREN]   = handle_lparen;   
    next_state[STATE_NUMBER][EVENT_LPAREN]   = STATE_NUMBER;

    state_table[STATE_NUMBER][EVENT_SPACE]    = handle_space;    
    next_state[STATE_NUMBER][EVENT_SPACE]    = STATE_NUMBER;

    state_table[STATE_NUMBER][EVENT_END]      = handle_end;      
    next_state[STATE_NUMBER][EVENT_END]      = STATE_NUMBER;

    state_table[STATE_NUMBER][EVENT_RPAREN]   = handle_rparen;   
    next_state[STATE_NUMBER][EVENT_RPAREN]   = STATE_OPERATOR;

    /* STATE_OPERATOR */
    state_table[STATE_OPERATOR][EVENT_OPERATOR] = handle_operator; 
    next_state[STATE_OPERATOR][EVENT_OPERATOR] = STATE_NUMBER;

    state_table[STATE_OPERATOR][EVENT_RPAREN]   = handle_rparen;  
    next_state[STATE_OPERATOR][EVENT_LPAREN] = STATE_NUMBER; 

    state_table[STATE_OPERATOR][EVENT_LPAREN]   = handle_lparen;
    next_state[STATE_OPERATOR][EVENT_RPAREN]   = STATE_OPERATOR;

    state_table[STATE_OPERATOR][EVENT_SPACE]    = handle_space;    
    next_state[STATE_OPERATOR][EVENT_SPACE]    = STATE_OPERATOR;

    state_table[STATE_OPERATOR][EVENT_END]      = handle_end;      
    next_state[STATE_OPERATOR][EVENT_END]      = STATE_OPERATOR;
}


/* ================ Stack Function Helpers ======================= */

static void num_push(stack_t *s, double v)
{
    assert(s);

    StackPush(s, &v);
}

static double num_pop(stack_t *s)
{
    double val = *(double *)StackPeek(s);
    StackPop(s);
    return val;
}

static void op_push(stack_t *s, char c)
{
    assert(s);

    StackPush(s, &c);
}

static char op_pop(stack_t *s)
{
    char val = *(char *)StackPeek(s);
    StackPop(s);
    return val;
}

static char op_peek(stack_t *s)
{
    return *(char *)StackPeek(s);
}

static void apply_top_op(calc_data_t* calc)
{
    double b = 0.0;
    double a = 0.0;
    char op = 0;

    if (StackSize(calc->ops) < 1 || StackSize(calc->nums) < 2)
    {
        calc->status = CALC_SYNTAX_ERROR;
        return;
    }

    b = num_pop(calc->nums);
    a = num_pop(calc->nums);
    op = op_pop(calc->ops);

    if (op == '/' && b == 0.0)
    {
        calc->status = CALC_ARITHMETIC_ERROR;
        return; 
    }
    num_push(calc->nums, op_lut[(unsigned char)op].operate(a, b));
}

/* ========================== Handlers ======================================= */

static calc_status_t handle_number(calc_data_t* calc)
{
    int sign = 1;
    double val = 0.0;

    init_luts();

    while (sign_lut[(unsigned char)*calc->p])
    {
        sign *= (signed char)sign_lut[(unsigned char)*calc->p];
        calc->p++;
    }

    calc->status = (digit_lut[(unsigned char)*calc->p] ? CALC_SUCCESS : CALC_SYNTAX_ERROR);

    val = strtod(calc->p, (char**)&calc->p);

    num_push(calc->nums, val * sign);
    return calc->status;
}

static calc_status_t handle_operator(calc_data_t* calc)
{
    char op = *calc->p;

    init_AS();

    while (StackSize(calc->ops) > 0 && (op_lut[(unsigned char)op_peek(calc->ops)].precedence >= op_lut[(unsigned char)op].precedence + AS[(unsigned char)op_peek(calc->ops)]))
    {
        apply_top_op(calc);
    }

    if (calc->status != CALC_SUCCESS)
    {
        return calc->status;
    }
    op_push(calc->ops, op);
    calc->p++;
    return CALC_SUCCESS;
}




static calc_status_t handle_lparen(calc_data_t* calc)
{
    char lparen = 0;

    init_matching_paren();

    lparen = matching_paren[(unsigned char)*calc->p];

    op_push(calc->ops, lparen);

    calc->p++;

    return calc->status;
}


static calc_status_t handle_rparen(calc_data_t* calc)
{
    char lparen = 0;

    init_matching_paren();

    lparen = matching_paren[(unsigned char)*calc->p];

    while (calc->status == CALC_SUCCESS && StackSize(calc->ops) > 0 && op_peek(calc->ops) != lparen)
    {
        if (matching_paren[(unsigned char)op_peek(calc->ops)] == op_peek(calc->ops))
        {
            return CALC_SYNTAX_ERROR;
        }
        apply_top_op(calc);    
    }
    
    if (StackSize(calc->ops) == 0)
    {
        return CALC_SYNTAX_ERROR;
    }
    op_pop(calc->ops); /* remove '(' */
    calc->p++;
    return CALC_SUCCESS;
}

static calc_status_t handle_space(calc_data_t* calc)
{
    calc->p++;
    return CALC_SUCCESS;
}

static calc_status_t handle_end(calc_data_t* calc)
{
    while (StackSize(calc->ops) > 0)
    {
        if(calc->status != CALC_SUCCESS)
        {
            return calc->status;
        }
        if (op_peek(calc->ops) == '(' || op_peek(calc->ops) == '[' || op_peek(calc->ops) == '{') 
        {
            calc->status = CALC_SYNTAX_ERROR;
            return calc->status;  
        }
       
        apply_top_op(calc);
    }
    return calc->status;
}

/* ---- Public API ---- */
calc_status_t Calculator(const char *expression, double *res)
{
    calc_data_t* calc = NULL;
    state_t state = STATE_NUMBER;
    event_t ev = EVENT_END;
    event_handler_t handler = NULL;
    size_t len = 0;

    len = strlen(expression);
    
    calc = malloc(sizeof(calc_data_t));
    if (!calc)
    {
        return CALC_SYNTAX_ERROR;
    }
    
    calc->nums = NULL;
    calc->ops = NULL;
    calc->status = CALC_SUCCESS;
    calc->p = expression;
    
    calc->nums = StackCreate(len, sizeof(double));
    if (!calc->nums)
    {
        free(calc);
        return CALC_SYNTAX_ERROR;
    }
    calc->ops  = StackCreate(len, sizeof(char));
    if (!calc->ops)
    {
        StackDestroy(calc->nums);
        free(calc);
        return CALC_SYNTAX_ERROR;
    }
    
    init_op_lut();
    init_tables();

    while (calc->status == CALC_SUCCESS)
    {
        ev = char_to_event[(unsigned char)*calc->p];
        handler = state_table[state][ev];
        if (!handler)
        {
            calc->status = CALC_SYNTAX_ERROR;
            break;
        }

        calc->status = handler(calc);

        state = next_state[state][ev];

        if (ev == EVENT_END) 
        {
            break;
        }
    }

    if (calc->status == CALC_SUCCESS && StackSize(calc->nums) == 1)
    {
        *res = num_pop(calc->nums);
    }
    else if (calc->status == CALC_SUCCESS)
    {
        calc->status = CALC_SYNTAX_ERROR;
    }

    StackDestroy(calc->nums);
    StackDestroy(calc->ops);
    return calc->status;
}
