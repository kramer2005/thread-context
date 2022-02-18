/**
 * @file context-manager.c
 * @author Wagner J. Kramer Vieira (wagner@kramer.dev.br)
 * @brief Implements the context manager.
 * @version 1.0
 * @date 2022-02-17
 *
 */

#include <thread-context.h>
#include <stdlib.h>

#ifdef DEBUG
#include <stdio.h>
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

ThreadContext *context_manager_root = NULL;

void *get_context()
{
    pthread_t id = pthread_self();
    ThreadContext *context_manager = context_manager_root;
    while (context_manager != NULL)
    {
        if (context_manager->thread == id)
        {
            DEBUG_PRINT("Found context for thread %lu\n", id);
            return context_manager->data;
        }
        context_manager = context_manager->next;
    }
    DEBUG_PRINT("No context found for thread %lu\n", id);
    return NULL;
}

void *set_context(void *data)
{
    pthread_t id = pthread_self();
    ThreadContext *context_manager = context_manager_root;
    while (context_manager != NULL)
    {
        if (context_manager->thread == id)
        {
            context_manager->data = data;
            DEBUG_PRINT("Context updated for thread %lu\n", id);
            return context_manager->data;
        }
        context_manager = context_manager->next;
    }
    context_manager = malloc(sizeof(ThreadContext));
    context_manager->thread = id;
    context_manager->data = data;
    context_manager->next = context_manager_root;
    context_manager_root = context_manager;
    DEBUG_PRINT("ThreadContext: Created new context for thread %lu\n", id);
    return context_manager->data;
}