/** @file main.cpp
 *  @brief Runs PID controller in forloop (2 iterations) and prints.
 *
 *  @author Sherif Shazly (sshazly)
 *  @copyright (2017) Sherif Shazly
 *  @bug No known bugs.
 */


#include <PID.hpp>

int main() {
  double kp = 0;
  double ki = 0;
  double kd = 0;
  double target = 0;
  double val = 0;
  double dt = 0.1;
  cout << "Please input Kp, Ki, Kd for PID control (seperated by a space)" << endl;
  cin >> kp >> ki >> kd;
  cout << "Please input setpoint, initial velocity, delta time (seperated by a space)" << endl;
  cin >> target >> val >> dt;
  class PID pid; 	 	/// Declare pid as class PID
  pid.setGain(kp,ki,kd); 	/// Set gain values (pointless, not used in calculation)
  pid.initialize(dt);
  for (int i = 0; i < 100; i++) {
				/// Calculate increment
        double inc = pid.calculate(target, val); 
				/// Print values to console
        printf("velocity:% 7.3f     increment:% 7.3f\n", val, inc); 
        val += inc; 		/// add increment to dynamic value
  }
  return 0;
}
