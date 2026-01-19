#include "array.hpp"
#include <iostream>

void print(auto&& arr) {
    /* Helper function to print the contents of a FixedSizeArray */
    std::cout << "[ " << arr[0];
    std::cout << "[ " << arr[0];
    for (int i = 1; i < arr.size(); ++i) {
        std::cout << ", " << arr[i];
    }
    std::cout << " ]" << std::endl;
}

int main() {
    // TODO: Initialise an empty fixed size array of 5 integers
    std::cout << "Array size: " << arr.size() << std::endl;
    print(arr);

    // TODO: Use a for loop to set the array values. E.g. 1-5
    print(arr);

    // TODO: Call doubleInPlace() and print the new array
    arr.doubleInPlace();
    print(arr);

    // TODO: Initialise an empty fixed size array of 5 integers with the const specifier
    print(constArr);

    // TODO: Print the output of calling reduce()

    // TODO: Check you get a compile time error if you try to set an element value in the
    // const array, or if you call doubleInPlace()

    // TODO: Initialise a fixed size array of strings with element values "Hello" and "World!"
    print(strArr);

    // TODO: Print the output of calling reduce() on strArr

    // TODO: Call doubleInPlace(). What happens? Can you explain this?
    // EXTENSION: Can you change the behaviour of doubleInPlace for non numeric data types?
    // E.g. Just print an error and leave the array unchanged.
    // Hint: You may want to search for useful type traits, and look up 'if constexpr'.
    print(strArr);
}
