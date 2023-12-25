#include <unistd.h>

#include <iostream>
#include <vector>

#include "tqdm-cpp.hpp"

int main() {
  for (const auto& elem : tqdm::Tqdm<int>({0, 1, 2, 3, 4})) {
    std::cout << elem << std::endl;
    sleep(1);
  }

  for (const auto& elem : tqdm::Tqdm<int>({0, 1, 2, 3, 4}, "test")) {
    std::cout << elem << std::endl;
    sleep(1);
  }

  for (const auto& elem : tqdm::trange(5)) {
    std::cout << elem << std::endl;
    sleep(1);
  }

  return 0;
}