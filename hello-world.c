#include <stdio.h>  // scanf, printf
#include <stdlib.h> // system
#include <ctype.h>  // tolower
#include <string.h> // strcat, strcpy

#define NUM_MODES 8
#define NUM_LANGUAGES 3
#define MAX_PROMPT_LENGTH 1000
#define MAX_TIME_OF_DAY_LENGTH 20
#define MAX_INPUT_STRING_LENGTH 100

/**
 * Clears the terminal screen.
 *
 * This function executes a system command to clear the terminal. It uses "cls"
 * on Windows systems and "clear" on Unix-like systems, including Linux, macOS,
 * and other UNIX derivatives.
 *
 * Note: The behavior of this function is dependent on the underlying operating
 * system's terminal and may not work in some IDEs or non-terminal environments.
 */
void clear_screen()
{
#ifdef _WIN32
    system("cls");
#elif __linux__ || __unix__ || __APPLE__
    system("clear");
#endif
}

/**
 * Clears the input buffer.
 *
 * This function reads and discards all characters from the standard input
 * until it encounters a newline character ('\n'). It is typically used to clear
 * any remaining characters left in the input buffer, which can be useful after
 * reading user input with functions like `scanf` that may leave trailing data.
 */
void clear_input_buffer()
{
    while ((getchar()) != '\n')
        ;
}

/**
 * Builds a selection prompt with provided title and options.
 *
 * This function constructs a string that represents a menu or selection prompt
 * by concatenating a given title followed by multiple option strings. The result
 * is appended to the target buffer passed as an argument.
 *
 * @param char *target A pointer to the destination buffer where the constructed
 *                     prompt will be stored. It should have sufficient space to
 *                     hold the resulting string.
 * @param char *title A null-terminated string representing the title or main
 *                    heading of the prompt.
 * @param char **options An array of pointers to null-terminated strings, each
 *                       representing an option in the selection menu.
 * @param int num_options The number of options provided in the options array.
 *                        This should match the actual count of elements in the
 *                        options array.
 *
 * Note: Ensure that `target` has enough space allocated to hold the combined length
 * of the title, all options, and additional characters like newline '\n'. Buffer
 * overflow could occur if this is not managed properly.
 */
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

/**
 * Asks the user whether they would like to continue or not.
 *
 * This function prompts the user with "Continue (y/N): " and reads their input.
 * It uses `scanf` with a space before `%c` to ignore any leftover newline characters in the buffer,
 * then converts the input to lowercase using `tolower`. If the user inputs 'n', it returns 0, indicating
 * that they do not wish to continue. For any other input, including no input (defaulting to 'N'),
 * it returns 1, allowing continuation.
 *
 * @return int: Returns 1 if the user wants to continue, otherwise returns 0.
 */
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

/**
 * Outputs "Hello, World!" to the console repeatedly until the user decides not to continue.
 *
 * This function enters an infinite loop where it prints "Hello, World!" followed by a newline character.
 * After each message is printed, the function checks if the user wants to continue. If the user chooses not
 * to continue (by responding with any input other than 'y' or 'Y'), the loop breaks and the function ends.
 */
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

/**
 * personalized_greeting - Interactively greets a user by name.
 *
 * This function repeatedly prompts the user to enter a name and then greets them
 * with "Hello, [name]! Welcome to the program." It continues to ask for names until
 * the user decides not to continue. The function checks if the user wants to repeat
 * the greeting or exit using the can_continue() function.
 */
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

/**
 * The `time_greeting` function prompts the user to enter the current time in 24-hour format and provides an appropriate greeting based on the hour of the day.
 *
 * It continues to ask for input until a valid time is entered or the user decides not to continue. A valid time must have hours between 0 and 24, and minutes between 0 and 60.
 * Depending on the time provided, it will display "Good morning, World!", "Good afternoon, World!", "Good evening, World!", or "Good night, World!".
 *
 * The function handles invalid inputs by prompting the user to enter a valid time again. It uses `clear_input_buffer()` to discard any extra input after an incorrect entry.
 * After displaying the greeting, it asks if the user wants to continue with another input; if not, the loop breaks and the function ends.
 */
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

/**
 * Prompts the user to select a language and greets them in that language.
 *
 * The function presents three languages: English, Khmer, and French.
 * It repeatedly prompts the user to choose one of these options by entering
 * a corresponding number. Based on the input, it displays "Hello world!"
 * for English, "សួរស្តី ពិភពលោក!" for Khmer, and "Bonjour le monde!" for French.
 *
 * If the user inputs an invalid selection, they are asked to try again.
 * The loop continues until the user decides not to continue by responding negatively
 * when prompted with "Repeat or exit?". The prompt text is dynamically built using
 * `build_selection_prompt` which includes options and their indices.
 */
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

/**
 * Repeatedly prompts the user to specify how many times "Hello World!" should be printed,
 * then displays the message that number of times. Continues until the user opts not to continue.
 * Validates input to ensure it is a non-negative integer, prompting again if invalid input is detected.
 */
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

/**
 * Function Name: age_based_hello
 *
 * The docstring:
 * Interactively asks the user for their age and provides a personalized greeting based on
 * specific age groups. It continues to prompt until the user chooses not to continue.
 * Valid ages are positive integers, with customized messages for different life stages:
 * - 0-10: "Hey there, baby friend! Welcome to the world of programming!"
 * - 11-18: "Hey there, teen friend! Welcome to the world of programming!"
 * - 19-25: "Hey there, young adult friend! Welcome to the world of programming!"
 * - 26-40: "Hey there, adult friend! Welcome to the world of programming!"
 * - Above 40: "Hey there, senior friend! Welcome to the world of programming!"
 * The function ensures input validity by checking for non-negative integers and prompts again
 * if invalid data is entered. It uses `clear_input_buffer()` to clear any extraneous input
 * after a failed age entry.
 */
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

/**
 * Displays a predefined ASCII art piece consisting of six lines.
 * Continuously shows the entire art until the user chooses not to continue.
 *
 * The function uses an array of strings, each representing a line of the ASCII art,
 * and prints them sequentially. After displaying the art once, it prompts the user
 * with `can_continue()`. If the user opts not to continue, the loop breaks;
 * otherwise, the art is displayed again.
 */
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