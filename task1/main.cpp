#include <iostream>
#include <vector>
#include <future>

template<typename T>
std::pair<T, size_t> find_min(const std::vector<T>& vec, size_t start) {
    auto min_iter = std::min_element(vec.begin() + start, vec.end());
    size_t min_index = std::distance(vec.begin(), min_iter);
    return std::make_pair(*min_iter, min_index);
}

template<typename T>
std::vector<T> selection_sort(const std::vector<T>& vec) {
    std::vector<T> sorted_vec(vec);
    size_t n = sorted_vec.size();

    for (size_t i = 0; i < n; ++i) {
        auto min_future = std::async(find_min<T>, std::cref(sorted_vec), i);
        auto min_pair = min_future.get();
        std::swap(sorted_vec[i], sorted_vec[min_pair.second]);
    }

    return sorted_vec;
}

int main() {
    
    std::vector<int> unsorted_vec = { 64, 25, 12, 22, 110 };
    std::vector<int> sorted_vec = selection_sort(unsorted_vec);

    std::cout << "Unsorted array: ";
    for (const auto& element : unsorted_vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    std::cout << "Sorted array: ";
    for (const auto& element : sorted_vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}