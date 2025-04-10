/*
** EPITECH PROJECT, 2025
** Error_handler
** File description:
** Implémentation of exception handler in C
*/

#ifndef ERROR_HANDLER_H_
    #define ERROR_HANDLER_H_

    #include <setjmp.h>

typedef struct error_s {
    jmp_buf buf;
    char *message;
} error_t;

#endif
