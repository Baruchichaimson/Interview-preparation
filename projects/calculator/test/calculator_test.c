#include <stdio.h>
#include "calculator.h"

int main(void)
{
    double res;
    /* ========== TEST 1 =======================*/

    if (Calculator("(-3) + (-4) * 20 - (5 + 1) / (5) ^ 2 * (7 - 4 / 2)", &res) == CALC_SUCCESS)
    {
        printf("Result: %f\n", res);
    }
    else if(Calculator("(-3) + (-4) * 20 - (5 + 1) / (5) ^ 2 * (7 - 4 / 2)", &res) == CALC_SYNTAX_ERROR)
    {
        printf("Error in expression\n");
    }
    else if(Calculator("(-3) + (-4) * 20 - (5 + 1) / (5) ^ 2 * (7 - 4 / 2)", &res) == CALC_ARITHMETIC_ERROR)
    {
        printf("Arithmetic error in expression\n");
    }

    /* ========== TEST 2 =======================*/

    if (Calculator("3.5 + 4 * 20 ", &res) == CALC_SUCCESS)
    {
        printf("Result: %f\n", res);
    }
    else if(Calculator("3.5 + 4 * 20 ", &res) == CALC_SYNTAX_ERROR)
    {
        printf("Error in expression\n");
    }
    else if(Calculator("3.5 + 4 * 20 ", &res) == CALC_ARITHMETIC_ERROR)
    {
        printf("Arithmetic error in expression\n");
    }

    /* ========== TEST 3 =======================*/

    if (Calculator("3.5 - 4 - 20 ", &res) == CALC_SUCCESS)
    {
        printf("Result: %f\n", res);
    }
    else if(Calculator("3.5 - 4 - 20 ", &res) == CALC_SYNTAX_ERROR)
    {
        printf("Error in expression\n");
    }
    else if(Calculator("3.5 - 4 - 20 ", &res) == CALC_ARITHMETIC_ERROR)
    {
        printf("Arithmetic error in expression\n");
    }

    /* ========== TEST 4 =======================*/

    if (Calculator("3 ^ 4 ^ 2 ", &res) == CALC_SUCCESS)
    {
        printf("Result: %f\n", res);
    }
    else if(Calculator("3 ^ 4 ^ 2 ", &res) == CALC_SYNTAX_ERROR)
    {
        printf("Error in expression\n");
    }
    else if(Calculator("3 ^ 4 ^ 2 ", &res) == CALC_ARITHMETIC_ERROR)
    {
        printf("Error in expression\n");
    }

    /* ========== TEST 5 =======================*/

    if (Calculator("5--7 ", &res) == CALC_SUCCESS)
    {
        printf("Result: %f\n", res);
    }
    else if(Calculator("5--7 ", &res) == CALC_SYNTAX_ERROR)
    {
        printf("Error in expression\n");
    }
    else if(Calculator("5--7 ", &res) == CALC_ARITHMETIC_ERROR)
    {
        printf("Error in expression\n");
    }

    /* ========== TEST 6 =======================*/

    if (Calculator("(-5) + 7 ", &res) == CALC_SUCCESS)
    {
        printf("Result: %f\n", res);
    }
    else if(Calculator("(-5) + 7 ", &res) == CALC_SYNTAX_ERROR)
    {
        printf("Error in expression\n");
    }
    else if(Calculator("(-5) + 7 ", &res) == CALC_ARITHMETIC_ERROR)
    {
        printf("Error in expression\n");
    }

    /* ========== TEST 7 =======================*/

    if (Calculator("4 / 0 + 1", &res) == CALC_SUCCESS)
    {
        printf("Result: %f\n", res);
    }
    else if(Calculator("4 / 0 + 1", &res) == CALC_SYNTAX_ERROR)
    {
        printf("Error in expression\n");
    }
    else if(Calculator("4 / 0 + 1", &res) == CALC_ARITHMETIC_ERROR)
    {
        printf("Arithmetic error in expression\n");
    }

    /* ========== TEST 8 =======================*/

    if (Calculator("3 + 5 * 2", &res) == CALC_SUCCESS)
    {
        printf("Result: %f\n", res);
    }
    else if(Calculator("3 + 5 * 2", &res) == CALC_SYNTAX_ERROR)
    {
        printf("Error in expression\n");
    }
    else if(Calculator("3 + 5 * 2", &res) == CALC_ARITHMETIC_ERROR)
    {
        printf("Arithmetic error in expression\n");
    }

    /* ========== TEST 9 =======================*/

    if (Calculator("(3) + [5] * {2}", &res) == CALC_SUCCESS)
    {
        printf("Result: %f\n", res);
    }
    else if(Calculator("(3) + [5] * {2}", &res) == CALC_SYNTAX_ERROR)
    {
        printf("Error in expression\n");
    }
    else if(Calculator("(3) + [5] * {2}", &res) == CALC_ARITHMETIC_ERROR)
    {
        printf("Arithmetic error in expression\n");
    }

    /* ========== TEST 10 =======================*/

    if (Calculator("(3 + 5] * {2}", &res) == CALC_SUCCESS)
    {
        printf("Result: %f\n", res);
    }
    else if(Calculator("(3 + 5] * {2}", &res) == CALC_SYNTAX_ERROR)
    {
        printf("Error in expression\n");
    }
    else if(Calculator("(3 + 5] * {2}", &res) == CALC_ARITHMETIC_ERROR)
    {
        printf("Arithmetic error in expression\n");
    }

    /* ========== TEST 11 =======================*/

    if (Calculator("[5 + 2]", &res) == CALC_SUCCESS)
    {
        printf("Result: %f\n", res);
    }
    else if(Calculator("[5 + 2]", &res) == CALC_SYNTAX_ERROR)
    {
        printf("Error in expression\n");
    }
    else if(Calculator("[5 + 2]", &res) == CALC_ARITHMETIC_ERROR)
    {
        printf("Arithmetic error in expression\n");
    }

    /* ========== TEST 12 =======================*/

    if (Calculator("2 +-3", &res) == CALC_SUCCESS)
    {
        printf("Result: %f\n", res);
    }
    else if(Calculator("2 +-3", &res) == CALC_SYNTAX_ERROR)
    {
        printf("Error in expression\n");
    }
    else if(Calculator("2 +-3", &res) == CALC_ARITHMETIC_ERROR)
    {
        printf("Arithmetic error in expression\n");
    }

    /* ========== TEST 13 =======================*/

    if (Calculator("+-3", &res) == CALC_SUCCESS)
    {
        printf("Result: %f\n", res);
    }
    else if(Calculator("+-3", &res) == CALC_SYNTAX_ERROR)
    {
        printf("Error in expression\n");
    }
    else if(Calculator("+-3", &res) == CALC_ARITHMETIC_ERROR)
    {
        printf("Arithmetic error in expression\n");
    }

    /* ========== TEST 14 =======================*/

    if (Calculator("0 ^ -1", &res) == CALC_SUCCESS)
    {
        printf("Result: %f\n", res);
    }
    else if(Calculator("0 ^ -1", &res) == CALC_SYNTAX_ERROR)
    {
        printf("Error in expression\n");
    }
    else if(Calculator("0 ^ -1", &res) == CALC_ARITHMETIC_ERROR)
    {
        printf("Arithmetic error in expression\n");
    }

    /* ========== TEST 15 =======================*/

    if (Calculator(" 0 ^ 0", &res) == CALC_SUCCESS)
    {
        printf("Result: %f\n", res);
    }
    else if(Calculator(" 0 ^ 0", &res) == CALC_SYNTAX_ERROR)
    {
        printf("Error in expression\n");
    }
    else if(Calculator(" 0 ^ 0", &res) == CALC_ARITHMETIC_ERROR)
    {
        printf("Arithmetic error in expression\n");
    }

    /* ========== TEST 16 =======================*/

    if (Calculator("(3.5 + 4) - 20 ", &res) == CALC_SUCCESS)
    {
        printf("Result: %f\n", res);
    }
    else if(Calculator("(3.5 + 4) - 20 ", &res) == CALC_SYNTAX_ERROR)
    {
        printf("Error in expression\n");
    }
    else if(Calculator("(3.5 + 4) - 20 ", &res) == CALC_ARITHMETIC_ERROR)
    {
        printf("Arithmetic error in expression\n");
    }

    /* ========== TEST 17 =======================*/
    if (Calculator("7 - 4 / 2", &res) == CALC_SUCCESS)
    {
        printf("Result: %f\n", res);
    }
    else if(Calculator("7 - 4 / 2", &res) == CALC_SYNTAX_ERROR)
    {
        printf("Error in expression\n");
    }
    else if(Calculator("7 - 4 / 2", &res) == CALC_ARITHMETIC_ERROR)
    {
        printf("Arithmetic error in expression\n");
    }

    /* ========== TEST 18 =======================*/
    if (Calculator("7 c- 4 / 2", &res) == CALC_SUCCESS)
    {
        printf("Result: %f\n", res);
    }
    else if(Calculator("7 c- 4 / 2", &res) == CALC_SYNTAX_ERROR)
    {
        printf("Error in expression\n");
    }
    else if(Calculator("7 c- 4 / 2", &res) == CALC_ARITHMETIC_ERROR)
    {
        printf("Arithmetic error in expression\n");
    }

    /* ========== TEST 19 =======================*/
    if (Calculator("[(7 - 4) / 2]", &res) == CALC_SUCCESS)
    {
        printf("Result: %f\n", res);
    }
    else if(Calculator("[(7 - 4) / 2]", &res) == CALC_SYNTAX_ERROR)
    {
        printf("Error in expression\n");
    }
    else if(Calculator("[({7} - 4) / 2]", &res) == CALC_ARITHMETIC_ERROR)
    {
        printf("Arithmetic error in expression\n");
    }
    return 0;
}