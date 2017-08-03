### dotenv for c

This small package adds support for loading .env files.
Just call the `env_load` function with a valid path, that contains a file named .env,
or the path of the env file itself.
loaded, it'll return `-1`, `0` otherwise. If the second parameter is set to `true`,
already existing environment variable will be replaced with the new value.

In the file, comments can be added by starting the line with `#`.
It's also possible to nest the variables, but in that case, the used variables need be already defined.

Quotes won't be removed from the strings.

#### usage

If you don't want to include in your project, you can install by executing `make install` then link it with `-ldotenv`.


```
# DB connection
DB_HOST=localhost
DB_NAME=test_db
DSN=mysql:host=${DB_HOST};dbname=${DB_NAME}
```

```c
#include <dotenv.h>

int main(void)
{
    env_load(".", false);

    char *connection = getenv("DSN");
}
```

