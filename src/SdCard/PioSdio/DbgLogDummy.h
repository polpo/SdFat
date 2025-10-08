/**
 * Copyright (c) 2011-2025 Bill Greiman
 * This file is part of the SdFat library for SD memory cards.
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
/**
 * \file
 * \brief Classes for Debug messages.
 */
#pragma once
#include "Printable.h"

/** Character used in Num class for HEX format */
#define NUM64_HEX_A 'a'

/** Enable or disable debug messages */
#define ENABLE_DBG_MSG 0

/** Port for debug messages */
// #define DBG_LOG_PORT Serial

/** Filename to print in message. */
#if defined(DBG_FILE)
#elif defined(__FILE_NAME__)
#define DBG_FILE __FILE_NAME__
#else
#define DBG_FILE __FILE__
#endif

/** Macro for debug messages */
#if ENABLE_DBG_MSG
#define DBG_MSG(...)                                          \
  do {                                                        \
    logmsgln(F(DBG_FILE), ":", __LINE__, " ", ##__VA_ARGS__); \
  } while (0)
#else  // ENABLE_DBG_MSG
#define DBG_MSG(...) \
  do {               \
  } while (0)
#endif  // ENABLE_DBG_MSG

#if 0
/**
 * \param[in] arg Item to print.
 * \return Number of bytes printed.
 */
template <typename T>
inline size_t logmsg(T arg) {
  return DBG_LOG_PORT.print(arg);
}
/**
 * \param[in] b Item to print.
 * \return Number of bytes printed.
 */
inline size_t logmsg(bool b) { return logmsg(b ? F("true") : F("false")); }

/** \return Zero to end recursive template */
inline size_t logmsg() { return 0; }

/**
 * \param[in] var1 Next item to print.
 * \param[in] vars Rest of items to print.
 * \return number of bytes printed.
 */
template <typename T, typename... Types>
inline size_t logmsg(T var1, Types... vars) {
  size_t n = logmsg(var1);
  return n += logmsg(vars...);
}
/**
 * \param[in] vars List of items to print.
 * \return number of bytes printed.
 */
template <typename... Types>
inline size_t logmsgln(Types... vars) {
  size_t n = logmsg(vars...);
  return n + logmsg("\r\n");  // cppcheck-suppress incorrectStringBooleanError
}
#endif
