#ifndef CPPEX_MY_ARRAY_HPP
#define CPPEX_MY_ARRAY_HPP

#include <iomanip>
#include <iostream>

class my_array {

public:

  /*
  Typically these should be private.
  Making them public so we can easily test the implementation
  */
  std::string const name = "default";
  unsigned size = 0;
  double* data = nullptr;

/* PART 1 - START HERE */

  // Default constructor
  my_array() = default;

  // Constructor
  explicit my_array(std::string name, unsigned n) {
    log("Constructing");
    // TODO: Implement constructor
  }

  // Destructor
  ~my_array() {
    log("Destroying");
    // TODO: Implement destructor
  }

/* PART 2 */

/* UNCOMMENT TO COMPLETE PART 2

  // Copy constructor
  // NOTE: Name should copy from other, but append "_cp"
  my_array(my_array const& other) {
    log("Copy constructing");
    // TODO: Implement copy constructor
  }

  // Copy assignment operator
  // NOTE: Name should not change
  my_array& operator=(my_array const& other) {
    log("Destroying");
    // TODO: Implement copy assignment operator
    log("Copy assigning");
  }

REMOVE THIS LINE TO COMPLETE PART 2 */

/* PART 3 */

/* UNCOMMENT TO COMPLETE PART 3

  // Move constructor
  // NOTE: Name should copy from other, but append "_mv"
  my_array(my_array&& other) noexcept {
    log("Move construct");
    // TODO: Implement move constructor
  }

  // Move assignment operator
  // NOTE: Name should not change
  my_array& operator=(my_array&& other) noexcept {
    // TODO: Implement move assignment operator
    log("Move assign");
  }

REMOVE THIS LINE TO COMPLETE PART 3 */

/* END */

  double& operator[](unsigned i) const {
    return data[i];
  }

private:
  void log(std::string label) {
    /* Helper method to log current status of the object */
    #ifndef MY_ARRAY_NO_LOGGING
      std::cout << std::setw(17) << label << ": " << std::setw(9) << data << " [" << name << "] " << std::endl;
    #endif
  }

};

#endif