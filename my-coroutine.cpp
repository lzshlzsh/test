/**
 * @file my-coroutine.cpp
 * @brief
 * @version 1.0
 * @date 11/10/2015 11:16:20 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2015 Tencent. All Rights Reserved.
 */
#include <ucontext.h>
#include <stdio.h>
#include <stdlib.h>

#include "co_routine.h"

// 64kB stack
#define FIBER_STACK 1024*64

#ifdef __cplusplus
extern "C" {
#endif
extern void co_swapcontext(ucontext_t *, ucontext_t *) asm("co_swapcontext");

#ifdef __cplusplus
}
#endif

ucontext_t child, parent, child2;

// The child thread will execute this function
void threadFunction()
{
    printf("%s\n", __FUNCTION__);
//    printf( "Child fiber yielding to parent\n" );
//    swapcontext( &child, &parent );
//    printf( "Child thread exiting\n" );
//    swapcontext( &child, &parent );
}

void threadFunction2() {
    printf("%s\n", __FUNCTION__);
}

int main()
{
    // Get the current execution context

    child.uc_stack.ss_size = 123;
    child.uc_stack.ss_sp = (void *)456;

    getcontext( &child );
    getcontext( &child2 );

    printf("%zd, %ld\n", child.uc_stack.ss_size, (long int)child.uc_stack.ss_sp);

    child2.uc_link = 0;
    child2.uc_stack.ss_sp = malloc( FIBER_STACK );
    child2.uc_stack.ss_size = FIBER_STACK;
    child2.uc_stack.ss_flags = 0; 

    // Modify the context to a new stack
    child.uc_link = &child2;
    child.uc_stack.ss_sp = malloc( FIBER_STACK );
    child.uc_stack.ss_size = FIBER_STACK;
    child.uc_stack.ss_flags = 0; 
    if ( child.uc_stack.ss_sp == 0 )
    {
        perror( "malloc: Could not allocate stack" );
        exit( 1 );
    }

    // Create the new context
    printf( "Creating child fiber\n" );
    makecontext( &child, &threadFunction, 0 );
    makecontext( &child2, &threadFunction2, 0 );

    // Execute the child context
    printf( "Switching to child fiber\n" );
//    swapcontext( &parent, &child );
    co_swapcontext( &parent, &child );
    printf( "Switching to child fiber again\n" );
    swapcontext( &parent, &child );

    // Free the stack
    free( child.uc_stack.ss_sp );
    free( child2.uc_stack.ss_sp );

    printf( "Child fiber returned and stack freed\n" );

    return 0;
}

