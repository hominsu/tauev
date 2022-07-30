// MIT License
//
// Copyright (c) 2022 HominSu
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

//
// Created by Homin Su on 2022/7/28.
//

#ifndef TAUEV_INCLUDE_TAUEV_TAUEV_H_
#define TAUEV_INCLUDE_TAUEV_TAUEV_H_

#ifndef TAUEV_ASSERT
#include <cassert>
#define TAUEV_ASSERT(x) assert(x)
#endif // TAUEV_ASSERT

#ifndef TAUEV_LENGTH
#define TAUEV_LENGTH(CONST_ARRAY) sizeof(CONST_ARRAY) / sizeof(CONST_ARRAY[0])
#endif // TAUEV_LENGTH

#ifndef TAUEV_STR_LENGTH
#if defined(_MSC_VER)
#define TAUEV_STR_LENGTH(CONST_STR) _countof(CONST_STR)
#else
#define TAUEV_STR_LENGTH(CONST_STR) sizeof(CONST_STR) / sizeof(CONST_STR[0])
#endif
#endif // TAUEV_STR_LENGTH

#if defined(_WIN64) || defined(WIN64) || defined(_WIN32) || defined(WIN32)
#if defined(_WIN64) || defined(WIN64)
#define TAUEV_ARCH_64 1
#else
#define TAUEV_ARCH_32 1
#endif
#define TAUEV_PLATFORM_STRING "windows"
#define TAUEV_WINDOWS 1
#elif defined(__linux__)
#define TAUEV_PLATFORM_STRING "linux"
#define TAUEV_LINUX 1
#ifdef _LP64
#define TAUEV_ARCH_64 1
#else /* _LP64 */
#define TAUEV_ARCH_32 1
#endif /* _LP64 */
#elif defined(__APPLE__)
#define TAUEV_PLATFORM_STRING "osx"
#define TAUEV_APPLE 1
#ifdef _LP64
#define TAUEV_ARCH_64 1
#else /* _LP64 */
#define TAUEV_ARCH_32 1
#endif /* _LP64 */
#endif

#ifndef TAUEV_WINDOWS
#define TAUEV_WINDOWS 0
#endif
#ifndef TAUEV_LINUX
#define TAUEV_LINUX 0
#endif
#ifndef TAUEV_APPLE
#define TAUEV_APPLE 0
#endif

#endif //TAUEV_INCLUDE_TAUEV_TAUEV_H_
