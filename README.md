# ThreadContext

This is a simple library for working with threads context.

Assume that a context is a "global" variable that stores the current thread data.

For example:
 You have multiple requests, each one runs in a separate thread concurrently.

 Each request need to store its own data, for example an user id.
 You don't need to pass the user id to each function inside the thread, instead, you can save it in the thread context and access it from any function.

## Installation

You can download the .deb package from the release tab or compile it with:

    git clone https://github.com/kramer2005/thread-context.git
    cd thread-context
    mkdir build
    cd build
    cmake ..
    make
    sudo make install

## Import

In your file, import the library:

    #include <thread-context.h>

During the compilation, just use the flag `-lthread-context` to link the library.

## How to use it

First, you need to create a context, for example a struct that store the user id.

```c
typedef struct UserContext {
    int user_id;
} UserContext;
```

Then, you can save the context in the thread using the `set_context` function.

```c
UserContext *user_context = malloc(sizeof(UserContext));
user_context->user_id = 1;
set_context(&user_context);
```

To load the context, use the `get_context` function anywhere in the thread.

```c
UserContext* user_context = get_context();
```

To free the context, use the `free_context` function.

If no context is set, the function will return NULL.

You can find an example inside the `examples` folder.
Just go to the folder and compile it using:

    gcc -o example example.c -lthread-context
    ./example

## Important

If the library isn't imported, make sure to export the path using:

    sudo ldconfig

## License

This library is licensed under the MIT license.
