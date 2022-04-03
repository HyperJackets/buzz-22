
class PIDController {
private:
  double kP;
  double kI;
  double kD;

  double minOutput;
  double maxOutput;

  double minInput;
  double maxInput;

  double lastError;
  double totalError;

  double goal;

public:
  // Set the goal the target goal
  void setGoal(double target);

  // Configure max/min inputs
  void configInput(double minInput, double maxInput);

  // Configure saturation by setting the abs(maxOutput)
  void configSaturation(double minimumOutput, double maximumOutput);

  // Calculate output based on current input and dt
  double calculate(double current, double dt);
}
