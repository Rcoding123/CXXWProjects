#include <cstddef>
#include <cstdint>
#include <iostream>

enum class Side : std::int8_t { BUY, SELL };

struct alignas(32) Order {
  std::int64_t orderId;
  std::int64_t price;
  std::int32_t size;
  Side side;
};

template <typename T, std::size_t N> class RawBuffer {
private:
  T *data;
  std::size_t *freelist;
  std::size_t top;

public:
  RawBuffer() : data(new T[N]), freelist(new std::size_t[N]), top(N) {
    for (std::size_t i{}; i < N; i++) {
      freelist[i] = i;
    }
  };

  // --- The O(1) Allocation ---
  T *acquire() {
    // If top is 0, we have no available indices left in the stack
    if (top == 0) {
      return nullptr;
    }

    // Decrement top FIRST. If top was 1000, it becomes 999
    --top;

    // Read the available index from the top of the stack
    std::size_t available_index = freelist[top];

    // Hand back the memory address at that index
    return &data[available_index];
  }

  // --- The O(1) Deallocation ---
  void release(T *item) {
    // Find the index by calculating the physical memory distance
    // between the item's pointer and the start of the data array
    std::size_t index = item - data;

    // Put the index back on the top of the stack
    freelist[top] = index;

    // Increment the top so we know we have one more item available
    ++top;
  }

  // Clean up memory when the pool shuts down
  ~RawBuffer() {
    delete[] data;
    delete[] freelist;
  }
};

int main() {
  auto myBuffer{RawBuffer<int, 100>()};
  auto ptr1 = myBuffer.acquire();
  std::cout << ptr1 << '\n';

  auto ptr2 = myBuffer.acquire();
  std::cout << ptr2 << '\n';

  auto ptr3 = myBuffer.acquire();
  std::cout << ptr3 << '\n';

  myBuffer.release(ptr2);

  auto ptr4 = myBuffer.acquire();
  std::cout << ptr4 << '\n';
}
