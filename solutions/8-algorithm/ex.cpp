#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

void print_vec(std::vector<int> &vec) {
  for (auto &el : vec) {
    std::cout << el << " ";
  }
  std::cout << std::endl << std::endl;
}

int main(int argc, char* argv[]) {
  // First, a warmup of basic algorithm usage
  auto nums = std::vector<int>(50);

  // let's initalize our vector with some random numbers
  for (int i = 0; i < 50; ++i) {
    nums[i] = std::rand() % 100;
  }

  // Bonus: can we do this using the algorithms library? Hint - std::generate
  // and use the following lambda
  auto gen = []() { return std::rand() % 100; };

  // Your code here....
  std::generate(begin(nums), end(nums), gen);

  // Now, sort nums.

  // Your code here....
  std::sort(nums.begin(), nums.end());

  std::cout << "Sorted nums: ";
  print_vec(nums);
  // Reverse sort nums, using (a) sort on its own and (b) using sort and another
  // algorithm function

  // Your code here....
  std::sort(nums.begin(), nums.end(), std::greater<int>());

  std::cout << "Reverse sorted nums (a): ";
  print_vec(nums);

  // Your code here....
  std::sort(nums.begin(), nums.end());
  std::reverse(nums.begin(), nums.end());

  std::cout << "Reverse sorted nums (b): ";
  print_vec(nums);

  // Now, lets look at a more involved example. We'll be working through Project
  // Euler No.2 (https://projecteuler.net/problem=2) "By considering the terms in
  // the Fibonacci sequence whose values do not exceed four million, find the sum
  // of the even-valued terms"

  // First lets get the fist 47 fibonacci numbers
  // BONUS: use std::transform

  auto fibs = std::vector<int>(47);

  // Your code here....
  fibs[0] = 0;
  fibs[1] = 1;

  std::transform(fibs.begin(), fibs.end() - 2, fibs.begin() + 1,
                 fibs.begin() + 2, std::plus<int>());

  print_vec(fibs);

  // Next, get all that are less than or equal to 4 million, and store them in
  // fibs_less HINT: use std::copy_if and std::back_inserter

  auto fibs_less = std::vector<int>();

  // Your code here....
  std::copy_if(fibs.begin(), fibs.end(), std::back_inserter(fibs_less),
               [](int x) { return x <= 4000000; });

  std::cout << "fibs <= 4000000: ";
  print_vec(fibs_less);

  // Now, get the evens. Use the same approach as above
  auto evens = std::vector<int>();

  // Your code here....

  std::copy_if(fibs_less.begin(), fibs_less.end(), std::back_inserter(evens),
               [](int x) { return !(x % 2); });

  std::cout << "Evens: ";
  print_vec(evens);

  // Finally, let's sum them (hint: std::accumulate)

  int sum = std::accumulate(evens.begin(), evens.end(), 0);

  std::cout << "Sum of even fibonacci numbers not greater than 4 million: "
            << sum << std::endl;

  return 0;
}
