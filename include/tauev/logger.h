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
// Created by Homin Su on 2022/7/29.
//

#ifndef TAUEV_INCLUDE_TAUEV_LOGGER_H_
#define TAUEV_INCLUDE_TAUEV_LOGGER_H_

#include "tauev/tauev.h"
#include "noncopyable.h"

#include <cerrno>
#include <cstdio>
#include <cstring>

#include <sstream>

#define LOG_LEVEL(TAUEV) \
  TAUEV(TRACE)           \
  TAUEV(DEBUG)           \
  TAUEV(INFO)            \
  TAUEV(WARN)            \
  TAUEV(ERROR)           \
  TAUEV(FATAL)           \
  //

namespace tauev::logger {

enum Level {
#define LOG_NAME(_name) _name,
  LOG_LEVEL(LOG_NAME)
#undef LOG_NAME
};

extern Level log_level;
extern int log_fd;

void set_log_level(Level _level);
void set_log_fd(int _fd);

void timestamp(char *_buf, std::size_t size);

inline const char *level_str(Level _level) {
  const static char *level_str_table[] = {
#define LOG_STR(_name) #_name,
      LOG_LEVEL(LOG_STR)
#undef LOG_STR
  };

  TAUEV_ASSERT(_level >= 0 && _level < TAUEV_LENGTH(level_str_table));
  return level_str_table[_level];
}

} // namespace logger

#undef LOG_LEVEL

#define LOG_BASE(_log_fd_, _level_, _file_, _line_, _abort_, _formatter_, ...) \
  do {                                                                         \
    char buf[32]{0};                                                           \
    tauev::logger::timestamp(buf, sizeof(buf));                                \
    int err = dprintf((_log_fd_), "[%s] [%s] "#_formatter_" - %s:%d\n", tauev::logger::level_str((_level_)), buf, ##__VA_ARGS__, strrchr((_file_), '/') + 1, (_line_)); \
    if (err == -1) {                                                           \
      fprintf(stderr, "log failed");                                           \
    }                                                                          \
    if ((_abort_)) {                                                           \
      abort();                                                                 \
    }                                                                          \
  } while (0)                                                                  \
  //

#define LOG_SYS(_log_fd_, _file_, _line_, _abort_, _formatter_, ...) \
  do {                                                               \
    char buf[32]{0};                                                 \
    tauev::logger::timestamp(buf, sizeof(buf));                      \
    dprintf((_log_fd_), "[%s] [%s] "#_formatter_": %s - %s:%d\n", (_abort_) ? "SYSFA" : "SYSER", buf, ##__VA_ARGS__, strerror(errno), strrchr((_file_), '/') + 1, (_line_)); \
    if ((_abort_)) {                                                 \
      abort();                                                       \
    }                                                                \
  } while (0)                                                        \
  //

#define TRACE(_formatter_, ...) \
  do {                          \
    if (tauev::logger::log_level <= tauev::logger::Level::TRACE) { \
      LOG_BASE(tauev::logger::log_fd, tauev::logger::Level::TRACE, __FILE__, __LINE__, false, _formatter_, ##__VA_ARGS__); \
    }                           \
  } while (0)                   \
  //

#define DEBUG(_formatter_, ...) \
  do {                          \
    if (tauev::logger::log_level <= tauev::logger::Level::DEBUG) { \
      LOG_BASE(tauev::logger::log_fd, tauev::logger::Level::DEBUG, __FILE__, __LINE__, false, _formatter_, ##__VA_ARGS__); \
    }                           \
  } while (0)                   \
  //

#define INFO(_formatter_, ...) \
  do {                         \
    if (tauev::logger::log_level <= tauev::logger::Level::INFO) { \
      LOG_BASE(tauev::logger::log_fd, tauev::logger::Level::INFO, __FILE__, __LINE__, false, _formatter_, ##__VA_ARGS__); \
    }                          \
  } while (0)                  \
  //

#define WARN(_formatter_, ...) \
  do {                         \
    if (tauev::logger::log_level <= tauev::logger::Level::WARN) { \
      LOG_BASE(tauev::logger::log_fd, tauev::logger::Level::WARN, __FILE__, __LINE__, false, _formatter_, ##__VA_ARGS__); \
    }                          \
  } while (0)                  \
  //

#define ERROR(_formatter_, ...) LOG_BASE(tauev::logger::log_fd, tauev::logger::Level::ERROR, __FILE__, __LINE__, false, _formatter_, ##__VA_ARGS__)

#define FATAL(_formatter_, ...) LOG_BASE(tauev::logger::log_fd, tauev::logger::Level::FATAL, __FILE__, __LINE__, true, _formatter_, ##__VA_ARGS__)

#define SYSERR(_formatter_, ...) LOG_SYS(tauev::logger::log_fd, __FILE__, __LINE__, false, _formatter_, ##__VA_ARGS__)

#define SYSFATAL(_formatter_, ...) LOG_SYS(tauev::logger::log_fd, __FILE__, __LINE__, true, _formatter_, ##__VA_ARGS__)

#endif //TAUEV_INCLUDE_TAUEV_LOGGER_H_
