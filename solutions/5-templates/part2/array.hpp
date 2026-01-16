#ifndef CPPEX_ARRAY_HPP
#define CPPEX_ARRAY_HPP

#include <iostream>

// Add template parameters to set the data type and array size at compile time
template <typename T, unsigned int N>
class FixedSizeArray {

private:
    T data[N];

public:

    FixedSizeArray() {
        for (int i = 0; i < N; ++i) {
            data[i] = T();  // Initialise values by calling type's default constructor
        }
    }

    // Overload the [] operator to provide access to the array elements
    T& operator[](int index) {
        return data[index];
    }

    const T& operator[](int index) const {
        return data[index];
    }

    // Create function size() that returns the size of the array
    unsigned int size() const { return N; }

    // Create function reduce() that sums all elements of the array
    T reduce() const {
        T result = data[0];
        for (int i = 1; i < N; ++i) {
            result += data[i];
        }
        return result;
    }

    // Create function doubleInPlace() that doubles each element of the array
    void doubleInPlace() {
        if constexpr (std::is_arithmetic<T>()) {
            for (int i = 0; i < N; ++i) {
                data[i] *= 2;
            }
        } else {
            std::cout << "ERROR: Cannot double array values. Data type is not arithmetic" << std::endl;
        }
    }
};

#endif
