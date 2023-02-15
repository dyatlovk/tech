#pragma once

#include <gtest/gtest.h>
#include <third_party/eventpp/callbacklist.h>

namespace EngineTest
{
  class EventsTest : public ::testing::Test
  {
  protected:
    EventsTest() = default;
    ~EventsTest() override = default;

    void SetUp() override {}
  };
} // namespace EngineTest
