/*
** EPITECH PROJECT, 2025
** Error_handler
** File description:
** Implémentation of exception handler in C
*/

#ifndef ERROR_HANDLER_H_
    #define ERROR_HANDLER_H_

    #include <setjmp.h>

/**
 * @struct error_s
 * @brief Error context for try/catch emulation.
 *
 * @details
 * Contains the jump buffer for setjmp/longjmp and an error
 * message describing the exception that was thrown.
 */
typedef struct error_s {
    jmp_buf buf;
    char *message;
} error_t;

#endif
