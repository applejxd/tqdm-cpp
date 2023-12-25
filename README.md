# tqdm-cpp

Python tqdm-like header-only progress bar library in C++

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
for (const auto& elem : tqdm::Tqdm<int>({0, 1, 2, 3, 4})) {
  std::cout << elem << std::endl;
  sleep(1);
}

for (const auto& elem : tqdm::Tqdm<int>(5)) {
  std::cout << elem << std::endl;
  sleep(1);
}
```

## ToDo

- [ ] Add description
- [ ] Add syntaxes (trange and so on)
- [ ] Nested loops
- [ ] Manual control
