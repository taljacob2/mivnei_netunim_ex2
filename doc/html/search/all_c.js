//===-- sanitizer/common_interface_defs.h -----------------------*- C++ -*-===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Common part of the public sanitizer interface.
//===----------------------------------------------------------------------===//

#ifndef
SANITIZER_COMMON_INTERFACE_DEFS_H
#define
SANITIZER_COMMON_INTERFACE_DEFS_H

#include < stddef.h >
#include < stdint.h >

// GCC does not understand __has_feature.
#if
!defined(__has_feature)
# define
__has_feature(x)
0
#endif

#ifdef
__cplusplus
extern
"C"
{
    #endif
    // Arguments for __sanitizer_sandbox_on_notify() below.
    typedef
    struct
    {
        // Enable sandbox support in sanitizer coverage.
        int
        coverage_sandboxed;
// File descriptor to write coverage data to. If -1 is passed, a file will
// be pre-opened by __sanitizer_sandobx_on_notify(). This field has no
// effect if coverage_sandbo