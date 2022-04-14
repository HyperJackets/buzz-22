#include "pid_controller.h"
#include "gtest/gtest.h"

TEST(PIDController, SetGoal) {
  PIDController controller;
  controller.setGoal(10);
  // We expect to see 0 because we haven't configured our min/max inputs
  EXPECT_EQ(controller.getGoal(), 0);
}

TEST(PIDController, ConfigInputGoal) {
  PIDController controller;
  controller.configInput(-10, 10);
  controller.setGoal(5);
  EXPECT_EQ(controller.getGoal(), 5);
}

TEST(PIDController, ConfigSaturation) {
  PIDController controller;
  controller.configInput(-100, 100);
  controller.setGoal(100);
  controller.configGains(100, 0, 0);
  // 100 * 100 would be theoretical output
  // We should expect only 1 if that is our max
  controller.configSaturation(-1, 1);
  // 1 * 100 > 1, we should cap at 1
  EXPECT_EQ(controller.calculate(1, 0.2), 1);
}

TEST(PIDController, calculate) {
  PIDController controller;
  controller.configInput(-1, 1);
  controller.setGoal(1);
  controller.configGains(0.1, 0, 0.001);
  controller.configSaturation(-1, 1);
  EXPECT_NEAR(controller.calculate(0, 0.2), 0.105, 0.0001);

  controller.configSaturation(-10, 10);
  EXPECT_NEAR(controller.calculate(0, 0.2), 0.1, 0.0001);
}
