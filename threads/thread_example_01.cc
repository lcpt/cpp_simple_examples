#include <iostream>
#include <thread>

void task(int id)
  {
    std::cout << "Hello from thread: " << id << std::endl;
  }

int main()
  {
    std::thread t1(task, 1); // Creates a thread that calls function task(1)
    std::thread t2(task, 2); // Creates another thread.

    // ... more code ...

    t1.join(); // Espera a que t1 termine
    t2.join(); // Espera a que t2 termine
    return 0;
  }
