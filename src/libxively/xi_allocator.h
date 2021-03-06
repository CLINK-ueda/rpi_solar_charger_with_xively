// Copyright (c) 2003-2013, LogMeIn, Inc. All rights reserved.
// This is part of Xively C library, it is under the BSD 3-Clause license.

/**
 * \file	xi_allocator.h
 * \author  Olgierd Humenczuk
 * \brief   Our custom `alloc()` and `free()`
 *
 *    This is a faced built for future use when limitation of certain embedded
 *    devices require custom memory management, e.g. pooling and leak detection.
 */

#ifndef __XI_ALLOCATOR_H__
#define __XI_ALLOCATOR_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief   Behaves like usual `malloc()`, which is supposed to allocate a chunk
 * 		    of memory and return the pointer to it.
 *
 * \return  Pointer to allocated memory or null in case of any error.
 */
void* xi_alloc( size_t bytes );

/**
 * \brief   Behaves like usual `free()`, it frees previously allocated chunk of
 * 		    of memory.
 */
void xi_free( void* pointer );

#ifdef __cplusplus
}
#endif

#endif
