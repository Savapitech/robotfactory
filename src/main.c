/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "common.h"
#include "compiler.h"
#include "u_str.h"

static
char *read_file(char const *path)
{
    FILE *file = fopen(path, "r");
    struct stat st;
    char *buffer;

    if (file == NULL)
        return NULL;
    if (stat(path, &st) < 0)
        return (fclose(file), NULL);
    buffer = malloc(st.st_size + 1);
    if (buffer == NULL)
        return (fclose(file), NULL);
    fread(buffer, sizeof *buffer, st.st_size, file);
    buffer[st.st_size] = '\0';
    return (fclose(file), buffer);
}

static
bool handle_file(char const *path)
{
    char *buffer = read_file(path);

    if (buffer == NULL)
        return (WRITE_CONST(STDERR_FILENO, "Error: file not exist\n"), false);
    prepare_compilation(buffer);
    free(buffer);
    return true;
}

int main(int ac, char **av)
{
    bool status = true;

    if (ac < 2)
        return 0;
    for (int i = 1; i < ac; i++)
        status &= handle_file(av[i]);
    return status ? RETURN_SUCCESS : RETURN_FAILURE;
}
