template: titleslide

# C++ Threads - Basics
## James Richings, EPCC
### j.richings@epcc.ed.ac.uk

---

# Overview

- Introduction

- Creating and joining threads

- Passing arguments to threads

- Synchronisation

---
# C++11 threads

- API for multithreaded programming built in to C++11 standard
- Similar functionality to POSIX threads
  - but with a proper OO interface
  - based quite heavily on Boost threads library
- Portable
  - depends on C++11 support, available in most compilers today
- Threads are C++ objects
  - call a constructor to create a thread
- Synchronisation
  - mutex locks
  - condition variables
  - C++11 atomics
- Tasks
  - via async/futures/promises 

---
# Creating threads

- Threads are objects of the `std::thread` class
- Threads are created by calling the constructor for this class
- Pass as an argument what we want the thread to execute. This can be:
  - A function pointer
  - A function object / functor
  - A lambda expression

- Note: you cannot copy a thread
  
---
# Joining threads

The `join()` member function on a `std::thread` object causes the calling thread to wait for the thread object to finish executing its function/functor/lambda.

---
# Hello world – function pointer

```C++
#include <thread>
#include <iostream>
#include <vector>

void hello() {
  std::cout << "Hello from thread " << std::this_thread::get_id() << std::endl;
}

int main() {
  std::vector<std::thread> threads;
  for (int i = 0; i < 5; ++i) {
    threads.push_back(std::thread(hello));
  }

  for (auto& thread: threads) {
    thread.join();
  }
}
```

---
# Hello world – lambda function

```C++
#include <thread>
#include <iostream>
#include <vector>

int main() {
  std::vector<std::thread> threads;

  for(int i = 0; i < 5; ++i){
    threads.push_back(std::thread([] {
      std::cout << "Hello from thread " << std::this_thread::get_id() << std::endl;
    }));
  }

  for(auto& thread : threads){
    thread.join();
  }
}
```

---
# Thread IDs

- Can call `get_id()`on a thread
- Use `std::this_thread::get_id()` to call it on the executing thread
- Returns an arbitrary identifier
- Not much use! 
- If we want sequentially numbered threads, need to pass the number as an argument to the thread constructor.

---
# Passing arguments to threads

Arguments to the thread function are moved or copied by value

Passing simple arguments to threads is straightforward: 
```C++
void hello(int x, int y) {
  std::cout << "Hello " << x << " " << y << std::endl;
}

int main() {
  int a = 1;
  int b = 27;
  std::thread mythread(hello, a, b);
  mythread.join();
}
```

---
# Passing references to threads

Need to use a reference wrapper to avoid the argument to the thread constructor making a copy 
```C++
void hello(int& x) {
  x++;
}

int main() {
  int x = 9;
  std::thread mythread(hello, std::ref(x));
  mythread.join();
  std::cout << "x = " << x << std::endl; // x is 10 here
}
```

---
# Synchronisation

```C++
class Wallet
{
  int mMoney = 0;
public:
  Wallet() {}

  void addMoney(int money) {
    mMoney += money;
  }
};
```

If two threads call `addMoney()` on the same `Wallet` object, then we have a race condition.

---
# Mutex locks

- Can use a mutex lock to protect updates to shared variables
  - natural to declare a mutex inside the object whose data needs protecting

```C++
#include <mutex>
class Wallet
{
  int mMoney = 0;
  std::mutex mutex;
public:
  Wallet() {}

  void addMoney(int money) {
    mutex.lock();
    mMoney += money;
    mutex.unlock();
  }
};
```

---
# Guard objects

- Need to make sure a mutex is always unlocked
- Can be tricky in cases with complex control flow, or with exception handling. 
- The `std::lock_guard` class implements the RAII (resource allocation is initialization) pattern for mutexes
- Its constructor takes as an argument a mutex, which it then locks
- Its destructor unlocks the mutex 

---
# Guard objects

```C++
#include <mutex> 

class Wallet
{
  int mMoney = 0;
  std::mutex mutex;
public:
  Wallet() {}

  void addMoney(int money) {
    std::lock_guard<std::mutex> lockGuard(mutex);
    mMoney += money;
  } // mutex unlocked when lockGuard goes out of scope
};
```

---
# Atomics

- C++ provides an atomic template class `std::atomic`

- Efficient, lock-free operations supported for specialization to basic integer, boolean and character types

- Floating point support in C++20 standard only

---
# Atomics

```C++
#include <atomic>

class Wallet
{
  std::atomic<int> mMoney = 0;
public:
  Wallet() {}
  void addMoney(int money) {
    mMoney += money; //atomic increment
  }
  };
```

---
# Thread safe class design

- Possible to add a mutex data member to the class and make every member function that accesses any mutable state acquire and release the mutex (use a `lock_guard`)

- Good design, in the sense that multithreaded code can use the class without worrying about the synchronisation

- Can result in unacceptable overheads – lots of lock/unlocks, and synchronization when it’s not needed. 

- Need to think carefully about use cases in a given application.

---
# Reusing this material

.center[![CC-BY-NC-SA](https://mirrors.creativecommons.org/presskit/buttons/88x31/png/by-nc-sa.eu.png)]

This work is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

https://creativecommons.org/licenses/by-nc-sa/4.0/

.smaller[
This means you are free to copy and redistribute the material and adapt and build on the material under the following terms: You must give appropriate credit, provide a link to the license and indicate if changes were made. If you adapt or build on the material you must distribute your work under the same license as the original.

Acknowledge EPCC as follows: “© EPCC, The University of Edinburgh, www.epcc.ed.ac.uk”

Note that this presentation may contain images owned by others. Please seek their permission before reusing these images.
]
