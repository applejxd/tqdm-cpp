# tqdm-cpp

Python [tqdm](https://github.com/tqdm/tqdm)-like header-only progress bar library in C++

## Installtion

For global installation, please run one of the following commands:

```bash
# by wget
sudo wget https://raw.githubusercontent.com/applejxd/tqdm-cpp/main/tqdm-cpp.hpp -P /usr/local/include
# by curl
sudo curl https://raw.githubusercontent.com/applejxd/tqdm-cpp/main/tqdm-cpp.hpp -o /usr/local/include/tqdm-cpp.hpp
```

For local installation, please download the above file to your project folder and include it directly.

## How to use

You can use this tqdm library with range-based for sytax.
Look at [sample.cpp](./sample.cpp).

```cpp
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
```

## ToDo

- [ ] Nested loops
- [ ] Loop and printing compatibility
