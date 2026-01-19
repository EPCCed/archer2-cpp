#ifndef CPPEX_ARRAY_HPP
#define CPPEX_ARRAY_HPP

// TODO: Add template parameters to set the data type and array size at compile time
class FixedSizeArray {

private:
    int data[10];

public:

    FixedSizeArray() {
        for (int i = 0; i < 10; ++i) {
            data[i] = 0;  // Does this work for all data types?
        }
    }

    // TODO: Overload the [] operator to provide access to the array elements

    // TODO: Create function size() that returns the size of the array

    // TODO: Create function reduce() that sums all elements of the array

    // TODO: Create function doubleInPlace() that doubles each element of the array
};

#endif
