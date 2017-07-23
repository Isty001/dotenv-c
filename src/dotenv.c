#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dotenv.h>


#define VAR_OPEN_TAG "${"
#define VAR_CLOSE_TAG "}"
#define COMMENT_CHAR '#'

/* strtok() won't remove the whole ${ part, only the $ */
#define remove_bracket(name) name + 1


static char *concat(char *buffer, char *string)
{
    if (!buffer) {
        return strdup(string);
    }
    if (string) {
        size_t length = strlen(buffer) + strlen(string) + 1;
        char *new = realloc(buffer, length);

        return strcat(new, string);
    }

    return buffer;
}

static bool is_nested(char *value)
{
    return strstr(value, VAR_OPEN_TAG) && strstr(value, VAR_CLOSE_TAG);
}

static char *parse_value(char *value)
{
    char *search = value, *parsed = NULL;
    char *name;

    if (value && is_nested(value)) {
        while (1) {
            parsed = concat(parsed, strtok(search, "${"));
            name = strtok(NULL, "}");

            if (!name) {
                break;
            }
            parsed = concat(parsed, getenv(remove_bracket(name)));
            search = NULL;
        }
        return parsed;
    }
    return value;
}

static bool is_commented(char *line)
{
    if (COMMENT_CHAR == line[0]) {
        return true;
    }

    int i = 0;
    while (' ' == line[i]) {
        if (COMMENT_CHAR == line[++i]) {
            return true;
        }
    }

    return false;
}

static void set_variable(char *name, char *original, bool overwrite)
{
    char *parsed;

    if (original) {
        parsed = parse_value(original);
        setenv(name, parsed, overwrite);

        if (original != parsed) {
            free(parsed);
        }
    }
}

static void parse(FILE *file, bool overwrite)
{
    char *name, *original, *line = NULL;
    size_t len = 0;

    while (-1 != getline(&line, &len, file)) {
        if (!is_commented(line)) {
            name = strtok(line, "=");
            original = strtok(NULL, "\n");

            set_variable(name, original, overwrite);
        }
    }
    free(line);
}

static FILE *open_default(char *base_path)
{
    char path[strlen(base_path) + 5];
    sprintf(path, "%s/.env", base_path);

    return fopen(path, "r");
}

int env_load(char *path, bool overwrite)
{
    FILE *file = open_default(path);

    if (!file) {
        file = fopen(path, "r");

        if (!file) {
            return -1;
        }
    }
    parse(file, overwrite);
    fclose(file);

    return 0;
}

