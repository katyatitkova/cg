#pragma once

#include <thread>

inline void test(void (*test_case)())
{
   std::thread t1((*test_case));
   std::thread t2((*test_case));
   std::thread t3((*test_case));
   std::thread t4((*test_case));
   t1.join();
   t2.join();
   t3.join();
   t4.join();
}
