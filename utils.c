#include <stdlib.h> // system

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

void strtolower(char *str)
{
    while (*str)
    {
        *str = tolower(*str);
        str++;
    }
}

void read_user_input_as_str(char *buffer)
{
    if (fgets(buffer, sizeof(buffer), stdin))
    {
        // Remove trailing newline character if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[--len] = '\0';
        }
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
    scanf(" %c", &selected); // notice the SPACE character in front of %c, that is to not have scanf read left-over newline characters.
    selected = tolower(selected);

    if (selected == 'n')
    {
        return 0;
    }

    return 1;
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