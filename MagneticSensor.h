/*!
 * @file MagenticSensor.h
 * @brief DFRobot's Magentic Sensor
 * @n Header file for DFRobot's Magentic Sensor
 *
 * @copyright	[DFRobot](http://www.dfrobot.com), 2016
 * @copyright	GNU Lesser General Public License
 *
 * @author [carl](carl.xu@dfrobot.com)
 * @version  V1.0
 * @date  2016-07-11
 */


/* LSM303DLH Example Code
 
   LSM303 Breakout ---------- Arduino
         Vin                   5V
         GND                   GND
         SDA                   A4
         SCL                   A5
*/
#include <math.h>
#include <Arduino.h>
#include <Wire.h>

typedef enum
{
	SCALE = 2,  ///< accel full-scale, should be 2, 4, or 8.
	LSM303_MAG = 0x1E,  ///< assuming SA0 grounded
	LSM303_ACC = 0x18,  ///< assuming SA0 grounded
	/* LSM303 Register definitions */
	CTRL_REG1_A = 0x20,
	CTRL_REG2_A = 0x21,
	CTRL_REG3_A = 0x22,
	CTRL_REG4_A = 0x23,
	CTRL_REG5_A = 0x24,
	HP_FILTER_RESET_A = 0x25,
	REFERENCE_A = 0x26,
	STATUS_REG_A = 0x27,
	OUT_X_L_A = 0x28,
	OUT_X_H_A = 0x29,
	OUT_Y_L_A = 0x2A,
	OUT_Y_H_A = 0x2B,
	OUT_Z_L_A = 0x2C,
	OUT_Z_H_A = 0x2D,
	INT1_CFG_A = 0x30,
	INT1_SOURCE_A = 0x31,
	INT1_THS_A = 0x32,
	INT1_DURATION_A = 0x33,
	CRA_REG_M = 0x00,
	CRB_REG_M = 0x01,
	MR_REG_M = 0x02,
	OUT_X_H_M = 0x03,
	OUT_X_L_M = 0x04,
	OUT_Y_H_M = 0x05,
	OUT_Y_L_M = 0x06,
	OUT_Z_H_M = 0x07,
	OUT_Z_L_M = 0x08,
	SR_REG_M = 0x09,
	IRA_REG_M = 0x0A,
	IRB_REG_M = 0x0B,
	IRC_REG_M = 0x0C
}MagneticParameter;


class MagenticSensor {
 public:
	/*!
	*  @brief Constructor
	*/
	MagenticSensor();
  /*!
   *  @brief Destructor
   */
	~MagenticSensor();
	
	/*!
   *  @brief get angle value after be correct.
   *
   *  @return angle value.
   */
	
	float GetTiltHeading();
	
	
	/*!
   *  @brief Read the value of the register.
   *
   *  @param address Register address,
   *
   *  @return the value of the register to the address.
   */
	byte Read(byte address);
	
	/*!
   *  @brief write data into the sensor to the register address.
   *
   *  @param data  Register data
   *  @param address  Register address
   */
	
	void Write(byte data, byte address);
	
	/*!
   *  @brief init the sensor.
   *
   *  @param fs  Scanning mode.
   */
	
	void Init(int fs);
	
	/*!
   *  @brief get angle value befor be correct.
   *
   *  @return angle value.
   */
    float GetHeading();

 private:
	int accel[3];  ///< we'll store the raw acceleration values here.
	int mag[3];  ///< raw magnetometer values stored here.
	float realAccel[3];  ///< calculated acceleration values here.
	/*!
   *  @brief get magentic accel.
   */
	void GetMagenticAccel();
	/*!
   *  @brief get magentic mag.
   */
	void GetMagenticMag();

};














