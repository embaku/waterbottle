#include <omp.h>
#include <vector>
#include <iostream>

using namespace std;

// Parallel reduction implementation of Min
int parallel_min(vector<int>& data) {
    int min_val = data[0];
    #pragma omp parallel for reduction(min: min_val)
    for (int i = 0; i < data.size(); i++) {
        if (data[i] < min_val) {
            min_val = data[i];
        }
    }
    return min_val;
}

// Parallel reduction implementation of Max
int parallel_max(vector<int>& data) {
    int max_val = data[0];
    #pragma omp parallel for reduction(max: max_val)
    for (int i = 0; i < data.size(); i++) {
        if (data[i] > max_val) {
            max_val = data[i];
        }
    }
    return max_val;
}

// Parallel reduction implementation of Sum
int parallel_sum(vector<int>& data) {
    int sum = 0;
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < data.size(); i++) {
        sum += data[i];
    }
    return sum;
}

// Parallel reduction implementation of Average
double parallel_average(vector<int>& data) {
    int sum = parallel_sum(data);
    return static_cast<double>(sum) / static_cast<double>(data.size());
}

// Example usage
int main() {
    vector<int> data = {5, 8, 1, 3, 9, 4, 6, 7, 5};
    
    // Compute the min value using parallel reduction
    int min_val = parallel_min(data);
    cout << "Min value: " << min_val << endl;
    
    // Compute the max value using parallel reduction
    int max_val = parallel_max(data);
    cout << "Max value: " << max_val << endl;
    
    // Compute the sum using parallel reduction
    int sum = parallel_sum(data);
    cout << "Sum: " << sum << endl;
    
    // Compute the average using parallel reduction
    double avg = parallel_average(data);
    cout << "Average: " << avg << endl;
    
    return 0;
}