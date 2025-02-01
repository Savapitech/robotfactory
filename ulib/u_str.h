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
char *u_strpop(char *, int);
int u_char_isalpha(char);
int u_char_isnum(char);
int u_str_isalphanum(char *);
void u_freestr(char **);
int u_strlen(char const *);
char *u_strcpy(char *, char const *);
char *u_strncpy(char *, char const *, int);
char *u_revstr(char *);
char *u_strstr(char *, char const *);
int u_strcmp(char const *, char const *);
int u_strncmp(char const *, char const *, int);
char *u_strupcase(char *);
char *u_strlowcase(char *);
char *u_strcapitalize(char *);
int u_str_isalpha(char *);
int u_str_isnum(char *);
int u_str_islower(char *);
int u_str_isupper(char *);
int u_str_isprintable(char *);
char *u_numstr(char *, int);

#endif /* STRING_H */
