/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#ifndef STRING_H
    #define STRING_H

int u_getnbr(char const *);
char *u_strcat(char *, char const *);
char *u_strncat(char *, char const *, int);
char *u_strdup(char const *);
int u_strlen(char const *);
char *u_strcpy(char *, char const *);
char *u_strncpy(char *, char const *, int);
char *u_revstr(char *);
char *u_strstr(char *, char const *);
int u_strcmp(char const *, char const *);
int u_strncmp(char const *, char const *, int);
char *u_numstr(char *, int);

#endif /* STRING_H */
