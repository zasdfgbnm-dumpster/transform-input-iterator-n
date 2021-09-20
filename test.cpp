#include "transform_input_iterator.hpp"

int main() {
    double a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    double b[] = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 };
    double c[] = { 0.01, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09 };
    auto plus = [](double a, double b, double c) {
        std::cout << a << std::endl;
        return a + b + c;
    };
    TransformInputIteratorN<double, decltype(plus), ptrdiff_t, double *, double *, double *> iter(a, b, c, plus);
    std::cout << *iter << std::endl;
}
