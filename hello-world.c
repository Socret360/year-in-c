#include <stdio.h>  // scanf, printf
#include <stdlib.h> // system()
#include <ctype.h>  // tolower()

#define MAX_NAME_LENGTH 100
#define NUM_MODES 8

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#elif __linux__ || __unix__ || __APPLE__
    system("clear");
#endif
}

int can_continue()
{
    printf("Continue (y/N): ");

    char selected = 'N';
    int result = scanf(" %c", &selected); // notice the SPACE character in front of %c, that is to not have scanf read left-over newline characters.
    selected = tolower(selected);

    if (selected == 'n')
    {
        return 0;
    }

    return 1;
}

void basic_hello()
{
    clear_screen();
    while (1)
    {
        printf("Hello, World!");
        printf("\n");
        if (!can_continue())
        {
            break;
        }
    }

    clear_screen();
}

void personalized_greeting()
{
    clear_screen();
    while (1)
    {
        printf("Who am I greeting?: ");

        char name[MAX_NAME_LENGTH];
        scanf(" %s", name); // notice that name is an array of characters. when passed into scanf it does not need & since an array will decay into a pointer.

        printf("Hello, %s! Welcome to the program.", name);
        printf("\n");

        if (!can_continue())
        {
            break;
        }
    }

    clear_screen();
}

int main()
{
    char *modes[NUM_MODES] = {
        "1. Basic Hello",
        "2. Personalized Hello",
        "3. Time Greeting",
        "4. Multi-language",
        "5. Repeat Hello",
        "6. Age-based Hello",
        "7. ASCII Art",
        "8. Exit",
    };

    while (1)
    {

        printf("Mode:\n");
        for (int i = 0; i < NUM_MODES; i++)
        {
            printf("%s\n", modes[i]);
        }

        printf("Select a mode: ");
        //
        int mode = -1;
        int result = scanf("%d", &mode);

        if (result == 0 || mode == 8)
        {
            break;
        }

        if (mode == 1)
        {
            basic_hello();
            continue;
        }

        if (mode == 2)
        {
            personalized_greeting();
            continue;
        }

        clear_screen();
        printf("Mode %d is not yet unsupported\n", mode);
    }

    return 0;
}