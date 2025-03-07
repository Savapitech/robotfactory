/*
** EPITECH PROJECT, 2025
** robotfactory
** File description:
** validator
*/

#include "validator.h"

static const char *FILES[] = {
    "tests/fixtures/arg_length.s",
    "tests/fixtures/abel.s",
    "tests/fixtures/bill.s",
    "tests/fixtures/errors/chars_after_name.s",
    "tests/fixtures/errors/chars_after_comment.s",
    "tests/fixtures/errors/comment_too_long.s",
    "tests/fixtures/errors/invalid_op.s",
    "tests/fixtures/errors/missing_quote.s",
    "tests/fixtures/errors/missing_comment.s",
    "tests/fixtures/errors/missing_label.s",
    "tests/fixtures/errors/missing_name.s",
    "tests/fixtures/errors/missing_newline.s",
    "tests/fixtures/errors/missing_newline2.s",
    "tests/fixtures/errors/missing_string.s",
    "tests/fixtures/errors/empty_name.s",
    "tests/fixtures/errors/name_too_long.s",
    "tests/fixtures/errors/newline_in_comment.s",
    "tests/fixtures/errors/register_too_big.s",
    "tests/fixtures/errors/register_too_small.s",
    "tests/fixtures/errors/relative_empty.s",
    "tests/fixtures/errors/double_label_def.s",
    "tests/fixtures/errors/invalid_args.s",
    "tests/fixtures/errors/no_val_dir.s",
    "tests/fixtures/errors/no_label_char_dir.s",
    "tests/fixtures/pdd.s",
    "tests/fixtures/tyron.s",
    "tests/fixtures/jon.s",
    "tests/fixtures/jon_ind.s",
    "tests/fixtures/42.s",
    "tests/fixtures/octobre.s",
};

int file_read_n(char const *filepath, char *buff, size_t size)
{
    int fd = open(filepath, O_RDONLY);
    int rd;

    if (fd < 0)
        return fd;
    rd = read(fd, buff, size);
    close(fd);
    return rd;
}

off_t file_size(char const *filepath)
{
    struct stat fi;

    return (stat(filepath, &fi) < 0) ? -1 : fi.st_size;
}

char *file_read(char const *filepath)
{
    struct stat fi;
    char *content;

    if (stat(filepath, &fi) < 0)
        return NULL;
    content = malloc((fi.st_size + 1) * sizeof(char));
    if (content == NULL)
        return NULL;
    content[fi.st_size] = '\0';
    if (file_read_n(filepath, content, fi.st_size) == fi.st_size)
        return content;
    free(content);
    return NULL;
}

void pad_emptyness(int group, int n)
{
    for (int leftover = 16 - n; leftover > 0; leftover--) {
        printf("%s", "  ");
        if (group & 1)
            putchar(' ');
        group--;
    }
}

size_t show_memblock(char const *s[2], int j, int n)
{
    char const *mem = s[j];
    char const *oth = s[!j];
    int group = 16;
    size_t diff = 0;

    printf("%s", ": ");
    for (int k = n; k > 0; k--) {
        if (*mem != *oth) {
            printf("%s", !j ? RED : GREEN);
            diff++;
        }
        printf("%02x", (int)(unsigned char)*mem++);
        printf("%s", RESET);
        oth++;
        if (group & 1)
            printf("%c", ' ');
        group--;
    }
    pad_emptyness(group, n);
    return diff;
}

void show_ascii(char const *s[2], int j, int n)
{
    char const *mem = s[j];
    char const *oth = s[!j];

    for (; n-- > 0; mem++) {
        if (*mem != *oth)
            printf("%s", !j ? RED : GREEN);
        printf("%c" RESET, isprint(*mem) ? *mem : '.');
        oth++;
    }
}

static __attribute__((format(printf, 1, 2)))
void run_command(char const *fmt, ...)
{
    char cmd[1024] = { 0 };
    va_list ap;

    va_start(ap, fmt);
    vsnprintf(cmd, sizeof cmd, fmt, ap);
    va_end(ap);
    printf("$ [%s]\n", cmd);
    system(cmd);
}

// run_command("find . -type f -name \"*.cor?\" -delete");
// (à la fin fin du main)
int main(void)
{
    char file[1024];
    char file2[1024];
    size_t count = 0;
    size_t len;
    char *p;

    for (size_t i = 0; i < CLENGTH_OF(FILES); i++) {
        run_command("tests/asm_ref %s", FILES[i]);
        p = strrchr(FILES[i], '/') + 1;
        len = strlen(p);
        memcpy(file, p, len);
        memcpy(strrchr(file, '.'), SSTR_UNPACK(".cor"));
        len += 2;
        run_command("mv %s %s2", file, file);
        run_command("./test %s", FILES[i]);
        memcpy(file2, file, len);
        file2[len] = '2';
        file2[len + 1] = '\0';
        count += diff(file, file2);
        memset(file, '\0', sizeof file);
        printf("\n");
    }
    printf("Difference: %zu byte(s)\n", count);
}
