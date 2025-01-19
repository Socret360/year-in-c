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