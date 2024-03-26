#include <iostream>
#include <vector>
#include <algorithm>
#include <future>

template<typename It, typename Func, size_t size = 25>
void parallel_for_each(It begin, It end, Func&& func) {
    size_t current_size = std::distance(begin, end);
    if (current_size <= size) {
        std::for_each(begin, end, func);
    }
    else {
        auto mid = std::next(begin, current_size / 2);
        auto ft = std::async(parallel_for_each<It, Func, size>, begin, mid, std::forward<Func>(func));
        parallel_for_each(mid, end, std::forward<Func>(func));
        ft.wait();
    }
}

int main() {
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    parallel_for_each(numbers.begin(), numbers.end(), [](int& num) {
        num *= 2;
        });

    std::cout << "After parallel for_each: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}