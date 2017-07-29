#ifndef DOTENV_DOTENV_H
#define DOTENV_DOTENV_H


#include <stdbool.h>

/**
 * @param path Can be a directory containing a file named .env, or the path of the env file itself
 * @param overwrite Existing variables will be overwritten
 * @return 0 on success, -1 if can't open the file
 */
int env_load(char *path, bool overwrite);


#endif
