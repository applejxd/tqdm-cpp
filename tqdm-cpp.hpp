#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

#define TQDM_MAJOR_VERSION 0
#define TQDM_MINOR_VERSION 1

namespace {

void print_gauge(double x) {
  std::cout << "\r" << std::setfill(' ') << std::right << std::setw(3)
            << int(x * 100) << "%|";

  for (uint i = 0; i < 20; ++i) {
    if (double(i) / 20. < x) {
      std::cout << "█";
    } else {
      std::cout << " ";
    }
  }
  std::cout << "|";
}

}  // namespace

namespace tqdm {

/**
 * tqdm class by overriding "range-based for" syntax
 * (https://en.cppreference.com/w/cpp/language/range-for)
 */
template <typename T>
class Tqdm {
 public:
  /**
   * override iterator syntax
   * (https://gist.github.com/jeetsukumaran/307264)
   */
  class iterator {
   public:
    iterator(T* ptr, int size)
        : _ptr(ptr),
          _size(size),
          _start_time(std::chrono::system_clock::now()) {}

    T& operator*() { return *_ptr; }

    iterator operator++() {
      iterator i = *this;
      _ptr++;
      _counter++;

      const auto curr_time = std::chrono::system_clock::now();
      const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
          curr_time - _start_time);
      const auto total_s = std::chrono::duration_cast<std::chrono::seconds>(
                               curr_time - _start_time)
                               .count();
      const auto curr_s = total_s % 60;
      const auto curr_m = int(total_s / 60);
      const auto remain_s =
          int(total_s * double(_size - _counter) / double(_counter));
      const auto est_s = remain_s % 60;
      const auto est_m = int(remain_s / 60);

      // gauge progress
      print_gauge(double(_counter) / double(_size));
      // iteration number progress
      std::cout << " " << _counter << "/" << _size;
      // current time consumption
      std::cout << " [" << std::setfill('0') << std::right << std::setw(2)
                << curr_m << ":" << std::setfill('0') << std::right
                << std::setw(2) << curr_s << "<";
      // estimated remaining time consumption
      std::cout << std::setfill('0') << std::right << std::setw(2) << est_m
                << ":" << std::setfill('0') << std::right << std::setw(2)
                << est_s << ",  ";
      // average time consumption for each time consumptions
      std::cout << std::fixed << std::setprecision(2)
                << double(ms.count()) * 1e-3 / double(_counter) << "s/it]"
                << std::flush;

      _pre_time = curr_time;
      return i;
    }

    iterator operator++(int junk) {
      _ptr++;

      const auto curr_time = std::chrono::system_clock::now();
      _pre_time = curr_time;
      _counter++;
      return *this;
    }

    bool operator==(const iterator& rhs) { return _ptr == rhs._ptr; }
    bool operator!=(const iterator& rhs) { return _ptr != rhs._ptr; }

   private:
    T* _ptr;
    int _size;
    int _counter{0};
    std::chrono::system_clock::time_point _start_time;
    std::chrono::system_clock::time_point _pre_time;
    std::time_t total_time{0};
  };

  Tqdm(int size) : _size(size) {
    _data = new T[_size];
    for (int i = 0; i < _size; i++) _data[i] = i;
  }
  Tqdm(const std::vector<T>& vec) : _size(vec.size()) {
    _data = new T[_size];
    for (int i = 0; i < _size; i++) _data[i] = vec[i];
  }
  ~Tqdm() { std::cout << std::endl; }

  iterator begin() { return iterator(_data, _size); }
  iterator end() { return iterator(_data + _size, _size); }

 private:
  T* _data;
  int _size;
};

}  // namespace tqdm