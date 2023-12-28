#include <unistd.h>

#include <iostream>
#include <vector>

#include "tqdm-cpp.hpp"

int main() {
  std::cout << "wrap std::vector" << std::endl;
  for (const auto& elem : tqdm::tqdm<int>({0, 1, 2, 3, 4})) {
    usleep(500000);
  }

  std::cout << "add description" << std::endl;
  for (const auto& elem : tqdm::tqdm<int>({0, 1, 2, 3, 4}, "test")) {
    usleep(500000);
  }

  std::cout << "trange syntax" << std::endl;
  for (const auto& elem : tqdm::trange(5)) {
    usleep(500000);
  }

  std::cout << "manual update" << std::endl;
  {
    auto pbar = tqdm::tqdm(100);
    for (int i = 0; i < 10; i++) {
      usleep(500000);
      pbar.update(10);
    }
  }

  return 0;
}