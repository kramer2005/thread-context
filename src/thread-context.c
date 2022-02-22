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
    ThreadContext *aux = context_manager_root;
    while (context_manager != NULL)
    {
        if (context_manager->thread == id)
        {
            DEBUG_PRINT("Found context for thread %lu\n", id);
            context_manager->data = data;
            return context_manager->data;
        }
        aux = context_manager;
        context_manager = context_manager->next;
    }

    ThreadContext *new_context = malloc(sizeof(ThreadContext));
    new_context->thread = id;
    new_context->data = data;
    new_context->next = NULL;
    new_context->prev = aux;
    if (aux != NULL)
    {
        aux->next = new_context;
    }
    else
    {
        context_manager_root = new_context;
    }
    DEBUG_PRINT("ThreadContext: Created new context for thread %lu\n", id);
    return new_context->data;
}

void *free_context()
{
    pthread_t id = pthread_self();
    ThreadContext *context_manager = context_manager_root;
    while (context_manager != NULL)
    {
        if (context_manager->thread == id)
        {
            void *ret = context_manager->data;
            if (context_manager->prev != NULL)
                context_manager->prev->next = context_manager->next;
            if (context_manager->next != NULL)
                context_manager->next->prev = context_manager->prev;
            free(context_manager);
            DEBUG_PRINT("ThreadContext: Removed context for thread %lu\n", id);
            return ret;
        }
        context_manager = context_manager->next;
    }
    DEBUG_PRINT("ThreadContext: No context found for thread %lu\n", id);
    return NULL;
}