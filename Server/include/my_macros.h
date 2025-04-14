/*
** EPITECH PROJECT, 2025
** Macros
** File description:
** Macros
*/

#ifndef MY_MACROS_H_
    #define MY_MACROS_H_

    #define EPITECH_SUCCESS 0
    #define EPITECH_FAILURE 84

    #define SUCCESS 0
    #define FAILURE 84

    #define FALSE 0
    #define TRUE 1

    #define BUFFSIZE 256

    #define AUTOFREE __attribute__((__cleanup__(simple_free)))
    #define AUTOFREE_SERVER __attribute__((__cleanup__(free_server)))

#endif /* ifndef MY_MACROS_H_ */
