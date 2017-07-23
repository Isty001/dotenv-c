### dotenv for c

This small package adds support for loading .env files.
Just call the `env_load` function with a valid path, you can either pass a directory,
to load a file called .env there, or directly pass the file. If no file can be
loaded, it'll return `-1`, `0` otherwise. If the second parameter is set to `true`,
already existing environment variable will be replaced with the new value.

In the file, comments can be added by starting the line with `#`.
It's also possible to nest the variables, but in that case, the used variables must be already defined.

Quotes won't be removed from the strings.

#### usage

If you don't want to include in your project, you can install with `make install` then link it `-ldotenv`.


```
# DB connection - ./.test.env
DB_HOST=localhost
DB_NAME=test_db
DSN=mysql:host=${DB_HOST};dbname=${DB_NAME}
```

```
#include <dotenv.h>

int main(void)
{
    env_load("./.test.env", false);

    char *connection = getenv("DSN");
}
```

