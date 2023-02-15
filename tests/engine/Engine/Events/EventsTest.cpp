#include "EventsTest.hpp"

namespace EngineTest
{
  TEST_F(EventsTest, callback)
  {
    eventpp::CallbackList<void()> callback;
    callback.append([]() { std::cout << "Got callback 1." << std::endl; });

    callback();

    EXPECT_TRUE(true);
  }
} // namespace EngineTest
