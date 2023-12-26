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

```cpp
  std::cout << "wrap std::vector" << std::endl;
  for (const auto& elem : tqdm::tqdm<int>({0, 1, 2, 3, 4})) {
    sleep(1);
  }

  std::cout << "add description" << std::endl;
  for (const auto& elem : tqdm::tqdm<int>({0, 1, 2, 3, 4}, "test")) {
    sleep(1);
  }

  std::cout << "trange syntax" << std::endl;
  for (const auto& elem : tqdm::trange(5)) {
    sleep(1);
  }

  std::cout << "manual update" << std::endl;
  {
    auto pbar = tqdm::tqdm(100);
    for (int i = 0; i < 10; i++) {
      sleep(1);
      pbar.update(20);
    }
    pbar.close();
  }
```

## ToDo

- [ ] Nested loops
- [ ] Loop and printing compatibility
