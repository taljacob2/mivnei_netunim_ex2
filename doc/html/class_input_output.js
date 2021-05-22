/* Thread and mutex controls for Objective C.
   Copyright (C) 1996-2019 Free Software Foundation, Inc.
   Contributed by Galen C. Hunt (gchunt@cs.rochester.edu)

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

#ifndef
__thread_INCLUDE_GNU
#define
__thread_INCLUDE_GNU

#include
"objc.h"

#ifdef
__cplusplus
extern
"C"
{
    #endif /* __cplusplus */

    /*************************************************************************
     *  Universal static variables:
     */
    extern
    int
    __objc_thread_exit_status;      /* Global exit status.   */

    /********
     *  Thread safe implementation types and functions.
     */

    /* Thread priorities */
    #define
    OBJC_THREAD_INTERACTIVE_PRIORITY
    2
    #define
    OBJC_THREAD_BACKGROUND_PRIORITY
    1
    #define
    OBJC_THREAD_LOW_PRIORITY
    0

    /* A thread */
    typedef
    void * objc_thread_t;

    /* This structure represents a single mutual exclusion lock. */
    struct
    objc_mutex
    {
        volatile
        objc_thread_t
        owner;     /* Id of thread that owns. */
        volatile
        int
        depth;               /* # of acquires. */
        v