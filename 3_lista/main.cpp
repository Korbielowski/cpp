#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

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

template <typename T> void as_sorted_view(std::vector<T> &vec) {
  std::vector<T *> vec_ptr;
  for (int i = 0; i < vec.size(); i++) {
    vec_ptr.push_back(&vec[i]);
  }

  std::sort(vec_ptr.begin(), vec_ptr.end(),
            [](const T *a, const T *b) { return *a < *b; });

  for (int i = 0; i < vec_ptr.size(); i++) {
    std::cout << *vec_ptr[i] << " ";
  }
  std::cout << std::endl;
}

template <typename T>
concept VectorLike = requires(T &a) {
  typename T::value_type;
  std::is_arithmetic_v<T>;
  a.size();
};

auto operator*(VectorLike auto &lhs, VectorLike auto &rhs) {
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

template <typename T> struct Node {
  Node(T val) : value(val), next(nullptr) {}

  T value;
  std::unique_ptr<Node> next;
};

template <typename T> class LinkedList {
public:
  LinkedList() : head(nullptr) {}

  void push(T val) {
    if (head == nullptr) {
      head = std::make_unique<Node<T>>(val);
      // std::cout << "Pushing val: " << val << std::endl;
    } else {
      Node<T> *current = head.get();
      while (current->next != nullptr) {
        current = current->next.get();
      }
      current->next = std::make_unique<Node<T>>(val);
      // std::cout << "Pushing val: " << val << std::endl;
    }
  }

  void print_list() {
    Node<T> *current = head.get();
    std::cout << "[ ";
    while (current != nullptr) {
      std::cout << current->value << " ";
      current = current->next.get();
    }
    std::cout << "]\n";
  }

  void reverse_list() {
    std::unique_ptr<Node<T>> previous = nullptr;
    std::unique_ptr<Node<T>> current = std::move(head);
    while (current != nullptr) {
      std::unique_ptr<Node<T>> next = std::move(current->next);
      current->next = std::move(previous);
      previous = std::move(current);
      current = std::move(next);
    }
    head = std::move(previous);
  }

private:
  std::unique_ptr<Node<T>> head;
};

int main() {
  std::vector vec1 = {1, 2, 3, 4};
  cpplab::vector x = cpplab::vector<int>();
  x.push_back(1);
  x.push_back(2);
  x.push_back(3);
  x.push_back(5);

  std::cout << "Mnozenie skalarne: " << x * vec1 << std::endl;
  // std::cout << "Mnozenie skalarne: " << 20.1f * vec1 << std::endl;
  // Tutaj kompilator pokaze blad, poniewaz mnozymy floata i vector

  LinkedList<int> ln;
  ln.push(20);
  ln.push(31231);
  ln.push(30);
  ln.push(40);

  std::cout << "Lista przed odwroceniem: ";
  ln.print_list();
  ln.reverse_list();
  std::cout << "Lista po odwroceniu: ";
  ln.print_list();

  std::vector vec2 = {9, 1, 3, 100, 21};
  std::cout << "vec2 przed posortowaniem: ";
  for (const int &elem : vec2) {
    std::cout << elem << " ";
  }
  std::cout << "\nvec2 As sorted view: ";
  as_sorted_view(vec2);
}
