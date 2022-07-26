## dotenv for c

![Test status](https://github.com/Isty001/dotenv-c/workflows/Test/badge.svg)


This small package adds support for loading .env files.
Just call the `env_load` function with a valid path, that contains a file named .env,
or the path of the env file itself.
If can't be loaded, it'll return `-1`, `0` otherwise. If the second parameter is set to `true`,
already existing environment variable will be replaced with the new value.

In the file, comments can be added by starting the line with `#`.
It's also possible to nest the variables, but in that case, the used variables need be already defined.

Quotes won't be removed from the strings.

### Build / install

##### cmake
```
# Build
(mkdir -p build && cd build && \
cmake .. && cmake --build .)

# Optional install
sudo make install
```

|Type       | Option        | Default | Output       |
|-----------|---------------|---------|--------------|
|Shared     | DOTENV_SHARED | __ON__  | libdotenv.so |
|Static     | DOTENV_STATIC | __ON__  | libdotenv-s.a|
|Executable | DOTENV_TEST   | __OFF__ | dotenv-test  |

###### Build and run test
```
mkdir -p build && cd build && \
cmake -DCMAKE_BUILD_TYPE=DEBUG -DDOTENV_TEST=ON .. && cmake --build . && \
cd .. && ./build/dotenv-test) 
```

##### clib
Install via clib: `clib install Isty001/dotenv-c`, or just `git clone` into your project.


##### make
Or if you don't want to include in your project, you can `git clone` then install by executing `make install` then link it with `-ldotenv`.

#### Usage
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

