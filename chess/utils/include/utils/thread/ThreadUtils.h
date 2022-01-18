#ifndef UTILS_THREAD_THREADUTILS_H_
#define UTILS_THREAD_THREADUTILS_H_

//C system includes

//C++ system includes
#include <cstdint>

//Third-party includes

//Own includes

//Forward Declarations

class Threading {
public:
  Threading() = delete;

  static void sleepFor(int64_t microseconds);
};
#endif /* UTILS_THREAD_THREADUTILS_H_ */
