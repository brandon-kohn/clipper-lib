#pragma once

#ifdef CLIPPER_STATIC_LIB
    #define CLIPPER_API 
#else
    #ifdef _WIN32
        #ifdef CLIPPER_EXPORTS_API
            #define CLIPPER_API __declspec(dllexport)
        #else
            #define CLIPPER_API __declspec(dllimport)
        #endif
    #else
        #ifdef CLIPPER_EXPORTS_API
            #define CLIPPER_API __attribute__ ((visibility ("default")))
        #else
            #define CLIPPER_API
        #endif
    #endif
#endif
