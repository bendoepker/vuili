#ifndef _V_LOG_H
#define _V_LOG_H

/* NOTE: Unreadable log messages will be written when multiple threads are writing to
*        stdout / stderr at the same time, use with caution on multithreaded functions
*/

#include "../config.h"
#include <stdarg.h>
#ifdef __cplusplus
extern "C" {
#endif

void __log(const char* s, ...);
void __print(const char* s, ...);

#ifdef __cplusplus
}
#endif

//General Log Statements
#if defined USE_LOGGING
#define LOG_GEN(fmt, ...) \
    __log("[LOG] " fmt, ##__VA_ARGS__)
#else 
#define LOG_GEN(fmt, ...)
#endif

//Error Log Statements
#if defined USE_LOGGING
#define LOG_ERR(fmt, ...) \
    __log("[ERROR] " fmt, ##__VA_ARGS__)
#else
#define LOG_ERR(fmt, ...)
#endif

//Function Log Statements
#if defined USE_LOGGING
#define LOG_FUNC(fmt, ...) \
    __log("[FUNC] " fmt, ##__VA_ARGS__)
#else
#define LOG_FUNCTION(fmt, ...)
#endif

//PRINT does not print any [identifier]s and prints to stdout rather than stderr
#if defined USE_LOGGING
#define PRINT(fmt, ...) \
    __print("" fmt, ##__VA_ARGS__)
#else
#define PRINT(fmt, ...)
#endif

#if defined USE_LOGGING
#define LOG_CUSTOM(specifier, fmt, ...) \
    __print("[" specifier "] " fmt, ##__VA_ARGS__)
#else
#define LOG_CUSTOM(specifier, fmt, ...)
#endif

#endif
