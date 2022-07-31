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

#ifndef TAUEV_SRC_TIMESTAMP_H_
#define TAUEV_SRC_TIMESTAMP_H_

#include <cstdio>

#include <chrono>

namespace tauev {

using nanoseconds = std::chrono::nanoseconds;
using microseconds = std::chrono::microseconds;
using milliseconds = std::chrono::milliseconds;
using seconds = std::chrono::seconds;
using minutes = std::chrono::minutes;
using hours = std::chrono::hours;

using system_clock = std::chrono::system_clock;
using time_point = std::chrono::time_point<system_clock, nanoseconds>;

namespace clock {

inline time_point now() { return system_clock::now(); }

inline time_point after_now(nanoseconds _interval) { return now() + _interval; }

inline time_point before_now(nanoseconds _interval) { return now() - _interval; }

inline int to_string(char *_data, std::size_t _size) {
  auto n = system_clock::now();
  auto t_s = std::chrono::duration_cast<seconds>(n.time_since_epoch());
  auto t_ms = std::chrono::duration_cast<milliseconds>(n.time_since_epoch());
  auto ms = static_cast<int>((t_ms - t_s).count());
  auto t = system_clock::to_time_t(n);

  tm tm_time{};
  gmtime_r(&t, &tm_time);

  return snprintf(_data,
                  _size,
                  "%4d-%02d-%02dT%02d:%02d:%02d.%03dZ",
                  tm_time.tm_year + 1900,
                  tm_time.tm_mon + 1,
                  tm_time.tm_mday,
                  tm_time.tm_hour,
                  tm_time.tm_min,
                  tm_time.tm_sec,
                  ms);
}

} // namespace clock

} // tauev

#endif //TAUEV_SRC_TIMESTAMP_H_
