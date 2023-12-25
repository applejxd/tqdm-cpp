#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

#define TQDM_MAJOR_VERSION 0
#define TQDM_MINOR_VERSION 1

namespace {

void print_gauge(double x) {
  // write percentage
  std::cout << std::setfill(' ') << std::right << std::setw(3) << int(x * 100)
            << "%|";

  // write gauge
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
    // corresponds to begin() and end() methods in Tqdm class
    iterator(T* ptr, int size, std::string desc)
        : _ptr(ptr),
          _size(size),
          _desc(desc),
          _start_time(std::chrono::system_clock::now()) {}

    // The same with normal iterators
    T& operator*() { return *_ptr; }
    bool operator==(const iterator& rhs) { return _ptr == rhs._ptr; }
    bool operator!=(const iterator& rhs) { return _ptr != rhs._ptr; }

    iterator operator++();

    iterator operator++(int junk) {
      _ptr++;

      const auto curr_time = std::chrono::system_clock::now();
      _pre_time = curr_time;
      _counter++;
      return *this;
    }

   private:
    T* _ptr;
    int _size;
    // description for tqdm
    std::string _desc;

    int _counter{0};
    std::chrono::system_clock::time_point _start_time;
    std::chrono::system_clock::time_point _pre_time;
    std::time_t total_time{0};
  };

  Tqdm(const std::vector<T>& vec) : _size(vec.size()) {
    _data = new T[_size];
    for (int i = 0; i < _size; i++) _data[i] = vec[i];
  }
  // with description
  Tqdm(const std::vector<T>& vec, const std::string& desc)
      : _size(vec.size()), _desc(desc) {
    _data = new T[_size];
    for (int i = 0; i < _size; i++) _data[i] = vec[i];
  }
  // for manual
  Tqdm(int size) : _size(size) {
    _data = new T[_size];
    for (int i = 0; i < _size; i++) _data[i] = i;
  }
  // for manual with description
  Tqdm(int size, const std::string& desc) : _size(size), _desc(desc) {
    _data = new T[_size];
    for (int i = 0; i < _size; i++) _data[i] = i;
  }
  ~Tqdm() { std::cout << std::endl; }

  // begin() and end() method defines the way to create iterator
  iterator begin() { return iterator(_data, _size, _desc); }
  iterator end() { return iterator(_data + _size, _size, _desc); }

 private:
  T* _data;
  int _size;
  // description for tqdm
  std::string _desc = "";
};

template <typename T>
typename Tqdm<T>::iterator Tqdm<T>::iterator::operator++() {
  // The same with usual iterators
  iterator i = *this;
  _ptr++;

  // ----- custom ----- //
  _counter++;

  std::cout << "\r";

  // description
  if (!(_desc.empty())) std::cout << _desc << ": ";

  // gauge progress
  print_gauge(double(_counter) / double(_size));

  const auto curr_time = std::chrono::system_clock::now();

  // total time [ms] from beginning
  const auto total_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                            curr_time - _start_time)
                            .count();
  // total time [s] from beginning
  const auto total_s =
      std::chrono::duration_cast<std::chrono::seconds>(curr_time - _start_time)
          .count();
  // total time [min] when it is devided into min and sec
  const auto total_time_m = int(total_s / 60);
  // total time [s] when it is devided into min and sec
  const auto total_time_s = total_s % 60;

  // estimated remaining time [s]
  const auto remain_s =
      int(total_s * double(_size - _counter) / double(_counter));
  // estimated remaining time [min] when it is devided into min and sec
  const auto remain_time_m = int(remain_s / 60);
  // estimated remaining time [s] when it is devided into min and sec
  const auto remain_time_s = remain_s % 60;

  // iteration number progress
  std::cout << " " << _counter << "/" << _size;
  // current time consumption
  std::cout << " [" << std::setfill('0') << std::right << std::setw(2)
            << total_time_m << ":" << std::setfill('0') << std::right
            << std::setw(2) << total_time_s << "<";
  // estimated remaining time consumption
  std::cout << std::setfill('0') << std::right << std::setw(2) << remain_time_m
            << ":" << std::setfill('0') << std::right << std::setw(2)
            << remain_time_s << ",  ";
  // average time consumption for each time consumptions
  std::cout << std::fixed << std::setprecision(2)
            << double(total_ms) * 1e-3 / double(_counter) << "s/it]"
            << std::flush;

  _pre_time = curr_time;
  // ----- custom ----- //

  return i;
}

Tqdm<int> trange(int num) {
  std::vector<int> v(num);
  std::iota(v.begin(), v.end(), 0);
  return Tqdm<int>(v);
}

}  // namespace tqdm