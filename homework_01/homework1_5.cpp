// homework1_5.cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // sort, greater
#include <iterator>  // ostream_iterator, back_inserter
#include <functional>

int main() {
    std::cout << "----- Problem 1 -----\n";
    // Problem 1A: valid
    const std::string hello = "Hello";
    // hello + ", world" -> std::string, then + "!" -> std::string, valid
    const std::string messageA = hello + ", world" + "!";
    std::cout << "1A message: " << messageA << '\n';

    // Problem 1B: shown as given (invalid):
    // Sconst std::string exclaim = "!";
    // const std::string message = "Hello" + ", world" + exclaim;
    // Explanation: the expression "Hello" + ", world" is an attempt to add two C-style string pointers,
    // which is not defined. Operator+ is defined for std::string + const char* or const char* + std::string,
    // but not for two const char*.
    // Corrected forms:
    const std::string exclaim = "!";
    const std::string messageB_correct = std::string("Hello") + ", world" + exclaim;
    std::cout << "1B corrected message: " << messageB_correct << '\n';

    std::cout << "\n----- Problem 2 -----\n";
    // Problem 2: assignment associativity and behavior
    int a(0), b(1), c(2), d(3);
    // For the chain a = b = c = d; assignment must be right-associative:
    // equivalent to a = (b = (c = d));
    // Each assignment sets the left operand equal to the right operand.
    a = b = c = d;
    std::cout << "a b c d after chaining: " << a << " " << b << " " << c << " " << d << '\n';

    std::cout << "\n----- Problem 3 -----\n";
    // Problem 3A: incorrect method
    std::vector<int> u(10, 100); // 10 elements all 100
    std::vector<int> v;          // empty

    // std::copy(u.begin(), u.end(), v.begin());

    std::cout << "3A: Attempted incorrect std::copy from u to v (commented in code).\n";
    std::cout << "Reason: v.begin() is not a valid output range because v has size 0.\n";

    // Problem 3B correct way:

    // Direct copy assignment
    std::vector<int> v_fix = u;
    std::cout << "3B fix (direct assignment) v_fix size: " << v_fix.size() << ", elements: ";
    for (auto x : v_fix) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "\n----- Problem 4 -----\n";
    // Problem 4: iterate with iterator to print each element
    std::vector<int> temp = {1,2,3,4,5};
    std::cout << "Elements of temp using iterator: ";
    for (std::vector<int>::const_iterator it = temp.begin(); it != temp.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::cout << "\n----- Problem 5 -----\n";
    // Problem 5: sort integers from largest to smallest
    std::vector<int> sample = {4, 1, 9, 7, 3, 8, 2};
    std::cout << "Before sort (sample): ";
    for (auto x : sample) std::cout << x << " ";
    std::cout << "\n";

    // sort descending using std::greater<>
    std::sort(sample.begin(), sample.end(), std::greater<int>());

    std::cout << "After sort (descending): ";
    for (auto x : sample) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
