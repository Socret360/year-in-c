#include <stdio.h>  // scanf, printf
#include <stdlib.h> // system
#include <ctype.h>  // tolower
#include <string.h> // strcat, strcpy

#define NUM_MODES 8
#define NUM_LANGUAGES 3
#define MAX_PROMPT_LENGTH 1000
#define MAX_TIME_OF_DAY_LENGTH 20
#define MAX_INPUT_STRING_LENGTH 100

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#elif __linux__ || __unix__ || __APPLE__
    system("clear");
#endif
}

void clear_input_buffer()
{
    while ((getchar()) != '\n')
        ;
}

void build_selection_prompt(char *target, char *title, char **options, int num_options)
{
    strcat(target, title);
    strcat(target, "\n");

    for (int i = 0; i < num_options; i++)
    {
        strcat(target, options[i]);
        strcat(target, "\n");
    }
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
    while (1)
    {
        printf("Hello, World!");
        printf("\n");
        if (!can_continue())
        {
            break;
        }
    }
}

void personalized_greeting()
{
    while (1)
    {
        printf("Who am I greeting?: ");

        char name[MAX_INPUT_STRING_LENGTH];
        scanf(" %s", name); // notice that name is an array of characters. when passed into scanf it does not need & since an array will decay into a pointer.

        printf("Hello, %s! Welcome to the program.", name);
        printf("\n");

        if (!can_continue())
        {
            break;
        }
    }
}

void time_greeting()
{
    while (1)
    {
        printf("Enter current time (24h format, e.g. 14:00): ");

        int current_time_h, current_time_min;
        int matches = scanf(" %d:%d", &current_time_h, &current_time_min);

        if (matches != 2)
        {
            printf("Please enter a valid time.\n");
            clear_input_buffer();
            continue;
        }

        int hour_in_range = current_time_h >= 0 && current_time_h <= 24;
        int min_in_range = current_time_min >= 0 && current_time_min <= 60;

        if (!hour_in_range || !min_in_range)
        {
            printf("Please enter a valid time.\n");
            clear_input_buffer();
            continue;
        }

        char time_of_day[MAX_TIME_OF_DAY_LENGTH];
        if (current_time_h > 0 && current_time_h <= 11)
        {
            strcpy(time_of_day, "morning");
        }
        else if (current_time_h > 11 && current_time_h <= 16)
        {
            strcpy(time_of_day, "afternoon");
        }
        else if (current_time_h > 16 && current_time_h <= 18)
        {
            strcpy(time_of_day, "evening");
        }
        else if (current_time_h > 18)
        {
            strcpy(time_of_day, "night");
        }

        printf("Good %s, World!", time_of_day);
        printf("\n");

        if (!can_continue())
        {
            break;
        }
    }
}

void multi_language_hello()
{
    char *languages[NUM_LANGUAGES] = {
        "1. English",
        "2. Khmer",
        "3. French",
    };
    char prompt[MAX_PROMPT_LENGTH];
    build_selection_prompt(prompt, "Language:", languages, NUM_LANGUAGES);

    while (1)
    {
        printf("%s", prompt);
        printf("\n");
        printf("Select a language: ");

        int language;
        int matches = scanf("%d", &language);

        if (matches != 1)
        {
            printf("Please select a valid language.\n");
            clear_input_buffer();
            continue;
        }

        if (language == 1)
        {
            printf("Hello world!");
        }

        if (language == 2)
        {
            printf("សួរស្តី ពិភពលោក!");
        }

        if (language == 3)
        {
            printf("Bonjour le monde!");
        }

        printf("\n");

        if (!can_continue())
        {
            break;
        }
    }
}

void repeated_greeting()
{
    while (1)
    {
        printf("How many times should I repeat?: ");

        int num_repeats;
        int matches = scanf("%d", &num_repeats);

        if (matches != 1 || num_repeats < 0)
        {
            printf("Please enter a valid value.\n");
            clear_input_buffer();
            continue;
        }

        for (int i = 0; i < num_repeats; i++)
        {
            printf("Hello World!\n");
        }

        printf("\n");

        if (!can_continue())
        {
            break;
        }
    }
}

void age_based_hello()
{
    while (1)
    {
        printf("How old are you?: ");

        int age;
        int matches = scanf("%d", &age);

        if (matches != 1 || age <= 0)
        {
            printf("Please enter a valid age.\n");
            clear_input_buffer();
            continue;
        }

        if (age > 0 && age <= 10)
        {
            printf("Hey there, baby friend! Welcome to the world of programming!\n");
        }
        else if (age > 10 && age <= 18)
        {
            printf("Hey there, teen friend! Welcome to the world of programming!\n");
        }
        else if (age > 18 && age <= 25)
        {
            printf("Hey there, young adult friend! Welcome to the world of programming!\n");
        }
        else if (age > 25 && age <= 40)
        {
            printf("Hey there, adult friend! Welcome to the world of programming!\n");
        }
        else
        {
            printf("Hey there, senior friend! Welcome to the world of programming!\n");
        }

        printf("\n");

        if (!can_continue())
        {
            break;
        }
    }
}

void ascii_art()
{
    char *art[6] = {
        " _    _      _ _         _    _            _     _ _ ",
        "| |  | |    | | |       | |  | |          | |   | | |",
        "| |__| | ___| | | ___   | |  | | ___  _ __| | __| | |",
        "|  __  |/ _ \\ | |/ _ \\  | |/\\| |/ _ \\| '__| |/ _` | |",
        "| |  | |  __/ | | (_) | \\  /\\  / (_) | |  | | (_| |_|",
        "|_|  |_|\\___|_|_|\\___/   \\/  \\/ \\___/|_|  |_|\\__,_(_)",
    };

    while (1)
    {
        for (int i = 0; i < 6; i++)
        {
            printf("%s\n", art[i]);
        }

        printf("\n");

        if (!can_continue())
        {
            break;
        }
    }
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

    char prompt[MAX_PROMPT_LENGTH];
    build_selection_prompt(prompt, "Mode:", modes, NUM_MODES);

    while (1)
    {
        printf("%s", prompt);
        printf("\n");
        printf("Select a mode: ");
        //
        int mode = -1;
        int matches = scanf("%d", &mode);

        if (mode == 8)
        {
            break;
        }

        clear_screen();

        if (matches == 0)
        {
            printf("Please enter a valid mode\n");
            clear_input_buffer();
            continue;
        }

        if (mode == 1)
        {
            basic_hello();
            clear_screen();
            continue;
        }

        if (mode == 2)
        {
            personalized_greeting();
            clear_screen();
            continue;
        }

        if (mode == 3)
        {
            time_greeting();
            clear_screen();
            continue;
        }

        if (mode == 4)
        {
            multi_language_hello();
            clear_screen();
            continue;
        }

        if (mode == 5)
        {
            repeated_greeting();
            clear_screen();
            continue;
        }

        if (mode == 6)
        {
            age_based_hello();
            clear_screen();
            continue;
        }

        if (mode == 7)
        {
            ascii_art();
            clear_screen();
            continue;
        }

        clear_screen();
        printf("Mode %d is not yet unsupported\n", mode);
    }

    return 0;
}