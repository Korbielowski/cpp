#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

template <typename T> struct is_string { static const bool value = false; };

template <> struct is_string<std::vector<std::string>> {
  static const bool value = true;
};

int parse_num(std::string str, size_t index) {
  std::string buf("");
  while (isdigit(str[index]) && index < str.size()) {
    buf.push_back(str[index]);
    index++;
  }
  return std::stoi(buf);
}

bool compare(std::string lhs, std::string rhs) {
  size_t i = 0;
  size_t max_len = lhs > rhs ? lhs.size() : rhs.size();
  while (i < max_len) {
    if (isalpha(lhs[i]) && isalpha(rhs[i]) && lhs[i] > rhs[i]) {
      return true;
    } else if (isalpha(lhs[i]) && isalpha(rhs[i]) && lhs[i] < rhs[i]) {
      return false;
    } else if (isalpha(lhs[i]) && isdigit(rhs[i])) {
      return true;
    } else if (isdigit(lhs[i]) && isalpha(rhs[i])) {
      return false;
    } else if (isdigit(lhs[i]) && isdigit(rhs[i]) &&
               parse_num(lhs, i) > parse_num(rhs, i)) {
      return true;
    } else if (isdigit(lhs[i]) && isdigit(rhs[i]) &&
               parse_num(lhs, i) < parse_num(rhs, i)) {
      return false;
    }
    i++;
  }
  if (lhs.size() > rhs.size()) {
    return true;
  }
  return false;
}

template <typename T, std::enable_if_t<is_string<T>::value, bool> = true>
void insertion_sort(T &vec) {
  for (int i = 1; i < vec.size(); i++) {
    std::string key = vec[i];
    int j = i - 1;

    while (j >= 0 && compare(vec[j], key)) {
      vec[j + 1] = vec[j];
      j = j - 1;
    }
    vec[j + 1] = key;
  }
}

template <typename T> void print_all(T arg) { std::cout << arg << std::endl; }

template <typename T, typename... Targs> void print_all(T arg, Targs... args) {
  std::cout << arg << std::endl;
  print_all(args...);
}

class Silnia {
public:
  template <size_t C> constexpr size_t silnia() {
    if constexpr (C == 0 || C == 1) {
      return 1;
    } else {
      return C * silnia<C - 1>();
    }
  }
};

int main() {
  std::cout << "Zadanie 1:\n";
  std::vector vec = {std::string("z102doc"), std::string("z102doca"),
                     std::string("z102doc"), std::string("a")};
  insertion_sort(vec);
  for (const std::string x : vec) {
    std::cout << x << std::endl;
  }

  std::cout << "Zadanie 2:\n";
  Silnia s;
  std::cout << s.template silnia<30>() << std::endl;

  std::cout << "Zadanie 3:\n";
  print_all("beak", 10, 2.22, -1.f);
}
