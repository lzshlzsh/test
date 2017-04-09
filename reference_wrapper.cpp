#include <algorithm>
#include <list>
#include <vector>
#include <iostream>
#include <numeric>
#include <random>
#include <functional>
 
template <class T>
class reference_wrapper_test {
public:
  // types
  typedef T type;
 
  // construct/copy/destroy
  reference_wrapper_test(T& ref) noexcept : _ptr(std::addressof(ref)) {}
  reference_wrapper_test(T&&) = delete;
  reference_wrapper_test(const reference_wrapper_test&) noexcept = default;
 
  // assignment
  reference_wrapper_test& operator=(const reference_wrapper_test& x) noexcept = default;
 
  // access
  operator T& () const noexcept { return *_ptr; }
  T& get() const noexcept { return *_ptr; }
 
private:
  T* _ptr;
};

int main()
{
    std::list<int> l(10);
    std::iota(l.begin(), l.end(), -4);
 
    std::vector<std::reference_wrapper<int>> v(l.begin(), l.end());
    // can't use shuffle on a list (requires random access), but can use it on a vector
    std::shuffle(v.begin(), v.end(), std::mt19937{std::random_device{}()});
 
    std::cout << "Contents of the list: ";
    for (int n : l) std::cout << n << ' '; std::cout << '\n';
 
    std::cout << "Contents of the list, as seen through a shuffled vector: ";
    for (int i : v) std::cout << i << ' '; std::cout << '\n';
 
    std::cout << "Doubling the values in the initial list...\n";
    for (int& i : l) {
        i *= 2;
    }
 
    std::cout << "Contents of the list, as seen through a shuffled vector: ";
    for (int i : v) std::cout << i << ' '; std::cout << '\n';
}
