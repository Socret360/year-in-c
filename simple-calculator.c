#include <stdio.h>  // printf, scanf
#include <ctype.h>  // tolower
#include <string.h> // strlen
//
#include "utils.c" // clear_screen

#define MAX_INPUT_LENGTH 100
#define MAX_VALUE_LENGTH 7 // only allow integer values up to 1_000_000
#define MAX_HISTORY 100

typedef struct
{
    float lhs;
    float rhs;
    char op;
    float result;
} Calculation;

float add(float a, float b)
{
    return a + b;
}

float subtract(float a, float b)
{
    return a - b;
}

Calculation parse_calculation(char *input_str)
{
    char lhs_str[MAX_VALUE_LENGTH] = "";
    char rhs_str[MAX_VALUE_LENGTH] = "";
    char op;
    Calculation calc;

    int is_lhs = 1;

    while (*input_str != '\0')
    {
        if (isspace(*input_str))
        {
            input_str++;
            continue;
        }

        if ((*input_str == '+') || (*input_str == '-') || (*input_str == '*') || (*input_str == '/'))
        {
            op = *input_str;
            is_lhs = 0;
            input_str++;
            continue;
        }

        if ((*input_str != '.') && !isdigit(*input_str))
        {
            break;
        }

        if (is_lhs)
        {
            int l = strlen(lhs_str);
            lhs_str[l] = *input_str;
            lhs_str[l + 1] = '\0';
        }
        else
        {
            int l = strlen(rhs_str);
            rhs_str[l] = *input_str;
            rhs_str[l + 1] = '\0';
        }

        input_str++;
    }

    float lhs = atof(lhs_str);
    float rhs = atof(rhs_str);

    calc.lhs = lhs;
    calc.rhs = rhs;
    calc.op = op;

    return calc;
}

void perform_calculation(Calculation *calculation)
{
    if (calculation->op == '+')
    {
        calculation->result = calculation->lhs + calculation->rhs;
    }
    else if (calculation->op == '-')
    {
        calculation->result = calculation->lhs - calculation->rhs;
    }
    else if (calculation->op == '*')
    {
        calculation->result = calculation->lhs * calculation->rhs;
    }
    else if (calculation->op == '/')
    {
        calculation->result = calculation->lhs / calculation->rhs;
    }
}

int main()
{
    char input_str[MAX_INPUT_LENGTH];
    Calculation history[MAX_HISTORY];
    int num_history = 0;

    while (1)
    {
        printf("Enter next calculation...\n");
        read_user_input_as_str(input_str);
        strtolower(input_str);

        if (strcmp(input_str, "exit") == 0)
        {
            printf("Thank you for using the calculator!\n");
            break;
        }

        if (strcmp(input_str, "history") == 0)
        {
            if (num_history == 0)
            {
                printf("No previous calculations");
            }
            else
            {
                for (int i = 1; i <= num_history; i++)
                {
                    Calculation c = history[num_history - i];
                    printf("%d. %.2f %c %.2f = %.2f\n", i, c.lhs, c.op, c.rhs, c.result);
                }
            }

            if (!can_continue())
            {
                break;
            }

            clear_input_buffer();
            continue;
        }

        Calculation calc = parse_calculation(input_str);

        if (!calc.op)
        {
            printf("Error: Invalid operator\n");
            continue;
        }

        if (calc.op == '/' && calc.rhs == 0)
        {
            printf("Error: Cannot divide by zero\n");
            continue;
        }

        perform_calculation(&calc);
        printf("%.2f\n", calc.result);

        history[num_history] = calc;
        num_history += 1;

        if (!can_continue())
        {
            break;
        }

        clear_input_buffer();
    }

    return 0;
}