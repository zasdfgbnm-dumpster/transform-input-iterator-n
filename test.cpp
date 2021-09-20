#include <cassert>
#include "transform_input_iterator.hpp"

struct Result {
    int64_t value;
    int64_t operator==(int64_t v) {
        return value == v;
    }
};

int main() {
    int64_t a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int64_t b[] = { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    int64_t c[] = { 0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };
    auto plus = [](int64_t a, int64_t b, int64_t c) -> Result { return {a + b + c}; };
    TransformInputIteratorN<Result, decltype(plus), ptrdiff_t, int64_t *, int64_t *, int64_t *> iter(a, b, c, plus);
    auto iter2 = iter;

    assert(*(iter++) == 0);
    assert(iter != iter2);
    assert((*iter).value == 111);
    assert(iter != iter2);
    assert(*(++iter) == 222);
    assert(iter != iter2);
    assert(*iter == 222);
    assert(iter != iter2);
    assert(*(iter += 2) == 444);
    assert(iter != iter2);
    assert(*iter == 444);
    assert(iter != iter2);
    assert(iter - iter2 == 4);
    assert(iter != iter2);
    assert(*(iter--) == 444);
    assert(iter != iter2);
    assert(*iter == 333);
    assert(iter != iter2);
    assert(*(--iter) == 222);
    assert(iter != iter2);
    assert(*iter == 222);
    assert(iter != iter2);
    assert(*(iter -= 2) == 0);
    assert(*iter == 0);
    assert(iter == iter2);
    assert(iter[1] == 111);
    assert(iter[2] == 222);
    assert(*(iter + 1) == 111);
    assert(*(iter + 2) == 222);
    iter += 2;
    assert(*(iter - 1) == 111);
    assert(*(iter - 2) == 0);
}
