#include<thread>

void f() {
  std::this_thread::sleep_for(std::chrono::seconds(3));
}

int main() {
  std::thread t(f);
  t.join();
}
