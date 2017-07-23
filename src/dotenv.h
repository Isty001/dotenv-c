#ifndef DOTENV_DOTENV_H
#define DOTENV_DOTENV_H


#include <stdbool.h>

/**
 * returns 0 if the given path can be loaded, or there is a .env file, -1 otherwise
 */
int env_load(char *path, bool overwrite);


#endif
