#include "PIDController.h"
#include <algorithm>
#include <math.h>

void PIDController::setGoal(double target) {
  goal = ::std::max(minInput, ::std::min(maxInput, target));
}

void PIDController::configGains(double p, double i, double d) {
  kP = p;
  kI = i;
  kD = d;
}

void PIDController::configInput(double minimumInput, double maximumInput) {
  minInput = minimumInput;
  maxInput = maximumInput;
}

void PIDController::configSaturation(double minimumOutput,
                                     double maximumOutput) {
  minOutput = minimumOutput;
  maxOutput = maximumOutput;
}

double PIDController::calculate(double current, double dt) {
  double error = goal - current;
  totalError += error;

  double vel = (error - lastError) / dt;

  double output = kP * error + kI * totalError + kD * vel;

  output = ::std::max(minOutput, ::std::min(output, maxOutput));

  lastError = error;

  return output;
}
