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

/* Use Custom Vuili Features Prefix */
#define VUILI_FEATURE_PREFIX       1
#undef VUILI_FEATURE_PREFIX
#define VUILI_PREFIX V_


/*
* #define VUILI_FUNCTION_PREFIX to enable function prefixes
*/
#ifdef VUILI_FEATURE_PREFIX
    #define __CONCAT_I(x, y) x ## y
    #define __CONCAT(x, y) __CONCAT_I(x, y)
    #define VFP(x) __CONCAT(VUILI_PREFIX, x)
#else
    #define VFP(x) x
#endif

#define MAX_VIEWPORTS               64
#define MAX_CHILD_VIEWPORTS         8
#define MAX_WINDOWS                 8
#define MAX_MOUSE_BUTTONS           8
#define KEY_DOUBLE_PRESS_TIMEOUT    .5

/* On windows this will help set framerate to desired rate */
#define USE_HIGH_RES_TIMER          1

#endif //_VUILI_CONFIG_H
