#include <gtest/gtest.h>

#include <Maths/Transformation.hpp>

#include "Maths/Vectors/Vector4d.hpp"

namespace EngineTest
{
  TEST(RotationTest, quatToAxis)
  {
    mtEngine::mtVec4f vec = {0.070535f, -0.277363f, 0.705345f, 0.648523f};
    mtEngine::quaternionToAxisAngle q;
    q = vec;

    EXPECT_EQ(q.x, 0.0926634967f);
    EXPECT_EQ(q.y, -0.364378363f);
    EXPECT_EQ(q.z, 0.926628411f);
    EXPECT_EQ(q.angle, 99.189621f);
  }
} // namespace EngineTest
