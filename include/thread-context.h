/**
 * @file context-manager.h
 * @author Wagner J. Kramer Vieira (wagner@kramer.dev.br)
 * @brief ThreadContext is a simple context manager based on pthreads.
 * @version 1.0
 * @date 2022-02-17
 *
 */

#ifndef __CONTEXT_MANAGER_H__
#define __CONTEXT_MANAGER_H__

#include <pthread.h>

typedef struct ThreadContext
{
    pthread_t thread;           // The thread this context is running on. (Just a unsigned long)
    struct ThreadContext *next; // The next context in the list.
    void *data;                 // The data this context is running with.
} ThreadContext;

/**
 * @brief Get the context object
 *
 * @return void* The context object.
 */
void *get_context();

/**
 * @brief Set the context object
 *
 * @param data The data to set the context to.
 * @return void* The context object.
 */
void *set_context(void *data);

#endif // __CONTEXT_MANAGER_H__