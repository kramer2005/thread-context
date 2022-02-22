#include <thread-context.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char *name;
} Context;

void print_name(Context *ctx)
{
    if (ctx)
        printf("My name is: %s\n", ctx->name);
    else
        printf("Don't know my name :/\n");
}

void john_doe()
{
    printf("\nSecondary thread\n");

    // Print no context
    Context *ctx = get_context();
    printf("No context created\n");
    print_name(ctx);

    // Set context John Doe
    char *name = "John Doe";
    ctx = malloc(sizeof(Context));
    ctx->name = name;
    set_context(ctx);

    // Get context John Doe and print it
    ctx = NULL;
    ctx = get_context();
    printf("Context created\n");
    print_name(ctx);


    // Release context John Doe
    free(free_context());
    ctx = NULL;
    ctx = get_context();
    printf("Freed context\n");
    print_name(ctx);
}

int main()
{
    printf("Main thread\n");

    // Print no context
    Context *ctx = get_context();
    printf("No context created\n");
    print_name(ctx);

    // Set context Jane Doe
    char *name = "Jane Doe";
    ctx = malloc(sizeof(Context));
    ctx->name = name;
    set_context(ctx);

    // Print actual context Jane Doe
    ctx = NULL; // Just to show that it's recovering the context
    ctx = get_context();
    printf("Context created\n");
    print_name(ctx);

    // Create thread for John Doe
    pthread_t thread;
    pthread_create(&thread, NULL, (void *)john_doe, NULL);
    pthread_join(thread, NULL);

    printf("\nMain thread\n");
    // Print actual context Jane Doe again
    ctx = NULL;
    ctx = get_context();
    print_name(ctx);

    free(free_context());
    return 0;
}