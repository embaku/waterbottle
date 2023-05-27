#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

int main() {
    std::vector<int> array = {1, 5, 3, 8, 2, 7, 6, 4};
    int min_val, max_val, sum_val;

    // Parallel Min
    #pragma omp parallel for reduction(min: min_val)
    for (int i = 0; i < array.size(); ++i) {
        if (i == 0 || array[i] < min_val) {
            min_val = array[i];
        }
    }

    // Parallel Max
    #pragma omp parallel for reduction(max: max_val)
    for (int i = 0; i < array.size(); ++i) {
        if (i == 0 || array[i] > max_val) {
            max_val = array[i];
        }
    }

    // Parallel Sum
    #pragma omp parallel for reduction(+: sum_val)
    for (int i = 0; i < array.size(); ++i) {
        sum_val += array[i];
    }

    double avg_val = static_cast<double>(sum_val) / array.size();

    std::cout << "Parallel Min: " << min_val << std::endl;
    std::cout << "Parallel Max: " << max_val << std::endl;
    std::cout << "Parallel Sum: " << sum_val << std::endl;
    std::cout << "Parallel Average: " << avg_val << std::endl;

    return 0;
}