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

#include "tauev/logger.h"

#include <unistd.h>

#include <chrono>
#include <thread>

int main() {
  {
    LOG_BASE(STDOUT_FILENO, tauev::logger::Level::TRACE, __FILE__, __LINE__, false, "%s", "LOG_BASE");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    LOG_SYS(STDERR_FILENO, __FILE__, __LINE__, false, "%s", "LOG_SYS");
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  {
    tauev::logger::set_log_fd(STDOUT_FILENO);
    tauev::logger::set_log_level(tauev::logger::Level::TRACE);
    TRACE("%s", "TRACE");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    DEBUG("%s", "DEBUG");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    INFO("%s", "INFO");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    WARN("%s", "WARN");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ERROR("%s", "ERROR");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
//    FATAL("%s", "FATAL");
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  {
    tauev::logger::set_log_fd(STDERR_FILENO);
    SYSERR("%s", "SYSERR");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
//    SYSFATAL("%s", "SYSFATAL");
  }
  return 0;
}
