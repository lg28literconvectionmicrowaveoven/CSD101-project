#ifndef UTILS_H // Header guard to prevent multiple inclusion
#define UTILS_H

// Checks if a file exists at the specified path
// Parameters:
//   - char *: Path to the file to check
// Returns:
//   - int: 1 if file exists, 0 if it doesn't
int exists(char *);

// Safely reads user input with bounds checking
// Parameters:
//   - char *buf: Buffer to store the input
//   - char *prompt: Message to display to user
//   - int num: Maximum number of characters to read
// Returns: void
void input(char *buf, char *prompt, int num);

// Reads entire contents of a file into memory
// Parameters:
//   - char *path: Path to the file to read
// Returns:
//   - char *: Dynamically allocated string containing file contents
//            (caller must free the memory)
char *readFile(char *path);

// Writes a string to a file
// Parameters:
//   - char *str: String to write to file
//   - char *path: Path to the file to write
// Returns:
//   - void *: Likely should be void return type (possible typo in original)
void *writeFile(char *str, char *path);

#endif // UTILS_H  // End of header guard
