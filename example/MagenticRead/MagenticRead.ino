/*!
 * @file MagenticRead.ino
 * @brief DFRobot's Positioning ir camera
 * @n [Get the module here](http://www.dfrobot.com/index.php?route=product/product&product_id=640&search=LSM303&description=true)
 * @n This example get the four lightest positions of the IR sources.
 * @n [Connection and Diagram](http://www.dfrobot.com/wiki/index.php?title=LSM303_Tilt_Compensated_Compass(SEN0079))
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2016
 * @copyright	GNU Lesser General Public License
 *
 * @author [carl](carl.xu@dfrobot.com)
 * @version  V1.0
 * @date  2016-07-11
 */

#include <MagneticSensor.h>

/*!
 * @brief Library for DFRobot's Magetic Sensor
 * @author [carl](carl.xu@dfrobot.com)
 */

// Global variables
MagenticSensor mag = MagenticSensor();


void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  mag.Init(SCALE);
}

void loop() {
  Serial.print(mag.GetHeading(), 3);  // this only works if the sensor is level
  Serial.print("\t\t");
  Serial.println(mag.GetTiltHeading(), 3);
  delay(100);
}
