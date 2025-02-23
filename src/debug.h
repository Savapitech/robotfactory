/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#ifndef DEBUG_H
    #define DEBUG_H
    #include <stdio.h>

    #define OMIT

    #define ESC "\033"
    #define CFMT(n) ESC "[" #n "m"

    #define RESET CFMT(0)
    #define BOLD CFMT(1)

    #define RED CFMT(31)
    #define GREEN CFMT(32)
    #define YELLOW CFMT(33)
    #define BLUE CFMT(34)
    #define PURPLE CFMT(35)
    #define CYAN CFMT(36)

    #ifdef U_DEBUG_MODE
        #define HEAD __FILE_NAME__, __LINE__

        #define HEAD_FMT_FILE BOLD BLUE "%s" RESET
        #define HEAD_FMT_LINE ":" BOLD PURPLE "%d" RESET

        #define HEAD_FMT HEAD_FMT_FILE HEAD_FMT_LINE "  "

        #define ERR(fmt, ...) printf(fmt, __VA_ARGS__)
        #define DEBUG_INTERNAL(fmt, ...) ERR(HEAD_FMT fmt, HEAD, __VA_ARGS__)

        #define U_DEBUG(fmt, ...) DEBUG_INTERNAL(fmt, __VA_ARGS__)
        #define U_DEBUG_MSG(msg) DEBUG_INTERNAL("%s\n", msg)
    #else

        #define U_DEBUG_MSG(msg) OMIT
        #define U_DEBUG(fmt, ...) OMIT

        #define U_DEBUG_CALL(func, ...) OMIT
        #define U_DEBUG_USED __attribute__((unused))
    #endif

#endif /* DEBUG_H */
