#include <stdio.h>
/*  is included for handling variable arguments in functions 
using va_list, va_start, va_arg, and va_end macros.*/
#include <stdarg.h>

// Define log types
typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_CRITICAL
} LogLevel;

FILE *logOutput = NULL;
LogLevel logLevel = LOG_INFO;

void log_Setout(FILE *output) {
    logOutput = output;
}

void log_SetLevel(LogLevel level) {
    logLevel = level;
}

void log_write(LogLevel level, const char *format, ...) {
    if (level >= logLevel) {
        const char *prefix = "";
        const char *color = "";
        switch (level) {
            case LOG_INFO:
                prefix = "INFO: ";
                color = "\x1b[37m"; // white
                break;
            case LOG_WARNING:
                prefix = "WARNING: ";
                color = "\x1b[33m"; // yellow
                break;
            case LOG_ERROR:
                prefix = "ERROR: ";
                color = "\x1b[31m"; // red
                break;
            case LOG_CRITICAL:
                prefix = "CRITICAL: ";
                color = "\x1b[31m"; // red
                break;
        }

        va_list args;
        va_start(args, format);
        fprintf(logOutput, "%s%s", color, prefix);
        vfprintf(logOutput, format, args);
        va_end(args);
        fprintf(logOutput, "\x1b[0m\n"); // reset color
    }
}

int main() {
    FILE *logFile = fopen("log.txt", "a+");
    if (logFile == NULL) {
        perror("Error opening log file");
        return 1;
    }
    // Set output destination
    /* to write in file */
      log_Setout(logFile);
    // Set log level
    log_SetLevel(LOG_INFO);

    // Example variables
    int var = 42;
    const char *name = "John Doe";

    // Log messages of different types
    log_write(LOG_INFO, "This is an informational message: %d, %s", var, name);
    log_write(LOG_WARNING, "This is a warning message: %d, %s", var, name);
    log_write(LOG_ERROR, "This is an error message: %d, %s", var, name);
    log_write(LOG_CRITICAL, "This is a critical message: %d, %s", var, name);
    fclose(logFile);

    /* to write on the console */
    log_Setout(stdout);
   // Set log level
    log_SetLevel(LOG_INFO);
    // Log messages of different types
    log_write(LOG_INFO, "This is an informational message: %d, %s", var, name);
    log_write(LOG_WARNING, "This is a warning message: %d, %s", var, name);
    log_write(LOG_ERROR, "This is an error message: %d, %s", var, name);
    log_write(LOG_CRITICAL, "This is a critical message: %d, %s", var, name);   
    
    return 0;
}
