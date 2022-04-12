class PIDController {
private:
  double kP = 0;
  double kI = 0;
  double kD = 0;

  double minOutput = 0;
  double maxOutput = 0;

  double minInput = 0;
  double maxInput = 0;

  double lastError = 0;
  double totalError = 0;

  double goal = 0;

public:
  // Set gains
  void configGains(double p, double i, double d);

  // Set the goal the target goal
  void setGoal(double target);

  // Configure max/min inputs
  void configInput(double minInput, double maxInput);

  // Configure saturation by setting the abs(maxOutput)
  void configSaturation(double minimumOutput, double maximumOutput);

  // Calculate output based on current input and dt
  double calculate(double current, double dt);

  double getGoal() { return goal; }
};
