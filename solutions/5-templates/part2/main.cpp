#include "array.hpp"

void print(auto&& arr) {
    /* Helper function to print the contents of a FixedSizeArray */
    std::cout << "[ " << arr[0];
    for (int i = 1; i < arr.size(); ++i) {
        std::cout << ", " << arr[i];
    }
    std::cout << " ]" << std::endl;
}

int main() {
    // Initialise an empty fixed size array of 5 integers
    FixedSizeArray<int, 5> arr;
    std::cout << "Array size: " << arr.size() << std::endl;
    print(arr);

    // Use a for loop to set the array values. E.g. 1-5
    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = i + 1;
    }
    print(arr);

    // Call doubleInPlace() and print the new array
    arr.doubleInPlace();
    print(arr);

    // Initialise an empty fixed size array of 5 integers with the const specifier
    const FixedSizeArray<int, 5> constArr = arr;
    print(constArr);

    // Print the output of calling reduce()
    std::cout << constArr.reduce() << std::endl;

    // Check you get a compile time error if you try to set an element value in the
    // const array, or if you call doubleInPlace()
    // constArr[0] = 1;
    // constArr.doubleInPlace();

    // Initialise a fixed size array of strings with element values "Hello" and "World!"
    FixedSizeArray<std::string, 2> strArr;
    strArr[0] = "Hello";
    strArr[1] = "World!";
    std::cout << "strArr size: " << strArr.size() << std::endl;
    print(strArr);

    // Print the output of calling reduce() on strArr
    std::cout << "strArr reduction: " << strArr.reduce() << std::endl;

    // Call doubleInPlace(). What happens? Can you explain this?
    // EXTENSION: Can you change the behaviour of doubleInPlace for non numeric data types?
    // E.g. Just print an error and leave the array unchanged.
    // Hint: You may want to search for useful type traits, and look up 'if constexpr'.
    strArr.doubleInPlace();
    print(strArr);
}
