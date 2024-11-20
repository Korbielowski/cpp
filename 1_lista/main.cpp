#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>

template <typename T, typename C> T my_max(T a, T b, C comp) {
  return comp(a, b);
}

// Time complexity n^2
template <typename T> void insertion_sort(std::vector<T> &vec) {
  for (int i = 1; i < vec.size(); i++) {
    T key = vec[i];
    int j = i - 1;

    while (j >= 0 && vec[j] > key) {
      vec[j + 1] = vec[j];
      j = j - 1;
    }
    vec[j + 1] = key;
  }
}

namespace cpplab {
template <typename T> class vector {

public:
  vector() {
    this->msize = 0;
    this->capacity = 0;
    this->array = nullptr;
  }

  ~vector() {
    msize = 0;
    capacity = 0;
    delete[] array;
  }

  void push_back(T elem) {
    msize++;
    if (array == nullptr) {
      capacity = 2;
      array = new T[capacity];
    } else if (msize >= capacity) {
      capacity += 2;
      T *temp = new T[capacity];
      for (int i = 0; i < msize; i++) {
        temp[i] = array[i];
      }
      delete[] array;
      array = temp;
    }
    array[msize - 1] = elem;
  }

  const size_t size() { return msize; }

  using value_type = T;

  void pop() {
    if (msize == 0) {
      std::cout << "Cannot shrink array, size=0\n";
      return;
    }
    array[msize - 1] = 0;
    msize--;
    if (msize < capacity / 2) {
      capacity = capacity / 2;
      T *temp = new T[capacity];
      for (int i = 0; i < msize; i++) {
        temp[i] = array[i];
      }
      delete[] array;
      array = temp;
      std::cout << "Shrink\n";
    }
  }

  T &operator[](size_t i) {
    if (i >= msize) {
      exit(EXIT_FAILURE);
    }
    return array[i];
  }

private:
  size_t msize;
  size_t capacity;
  T *array;
};
} // namespace cpplab

template <typename T, typename G> auto operator*(T &lhs, G &rhs) {
  if (rhs.size() != lhs.size() || rhs.size() == 0 || lhs.size() == 0) {
    std::cout << "Different sizes or sizes are zero\n";
    return 0;
  }

  auto scalar_sum = rhs[0] * lhs[0];
  for (size_t i = 1; i < rhs.size(); i++) {
    scalar_sum += rhs[i] * lhs[i];
  }
  return scalar_sum;
}

int main() {
  std::cout << "Zadanie 1:\n";
  auto func = [](auto a, auto b) { return a > b ? a : b; };
  std::cout << my_max<int>(2, 10, func) << "\n";
  std::cout << my_max<char>('a', 'A', func) << "\n";
  std::cout << my_max<double>(1.2222, 1.9, func) << "\n";
  std::cout << "Zadanie 2:\n";
  std::vector vec = {20, 10, 90, 60, 30};
  std::cout << "Before sorting: ";
  for (auto &e : vec) {
    std::cout << e << ", ";
  }
  insertion_sort(vec);
  std::cout << "\nAfter sorting: ";
  for (auto &e : vec) {
    std::cout << e << ", ";
  }
  std::cout << "\n";

  std::cout << "Zadanie 3\n";
  cpplab::vector x = cpplab::vector<int>();
  x.push_back(1);
  x.push_back(2);
  x.push_back(3);
  x.push_back(5);
  cpplab::vector<int>::value_type y = 10;
  x.push_back(y);

  std::cout << "Scalar vector: " << x * vec << std::endl;
}
