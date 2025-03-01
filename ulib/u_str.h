/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#ifndef STRING_H
    #define STRING_H
    #include <stddef.h>

typedef struct {
    char *str;
    int sz;
} buff_t;

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
int u_spacelen(char const *str);
int u_strcspn(char const *str, char c);
size_t u_strspn(const char *s, const char *accept);
char *u_strchr(const char *s, char c);
size_t u_strccspn(const char *s, const char *reject);
int u_strnum(char *strp, int *n);

#endif /* STRING_H */
