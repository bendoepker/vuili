#ifndef _VUILI_CONFIG_H
#define _VUILI_CONFIG_H

/* Set the Platform Variables */
#if defined(_WIN32)
    #if defined(_WIN64)
        #define PLATFORM WINDOWS
    #else
        #error 32 Bit applications are not supported
    #endif
#elif defined(__linux__)
    #if defined(__ANDROID__)
        #define PLATFORM ANDROID
        #error Android is not supported
    #else
        #define PLATFORM LINUX
    #endif
#elif defined(__APPLE__)
    #if defined(__MACH__)
        #define PLATFORM MACOSX
    #else
        #define PLATFORM IOS
        #error iOS is not supported
    #endif
#endif
#if !defined(PLATFORM)
    #error Unknown platform
#endif //PLATFORM

/* Use Logging Functions */
#define USE_LOGGING

#define MAX_VIEWPORTS       64
#define MAX_WINDOWS         8

/* On windows this will help set framerate to desired rate */
#define USE_HIGH_RES_TIMER  1

#endif //_VUILI_CONFIG_H
