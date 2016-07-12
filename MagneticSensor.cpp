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
#include "MagneticSensor.h"
MagenticSensor::MagenticSensor()
{
	Wire.begin();  // Start up I2C, required for MagenticSensor communication
}
MagenticSensor::~MagenticSensor()
{
	
}
void MagenticSensor::Init(int fs)
{
  Write(0x27, CTRL_REG1_A);  // 0x27 = normal power mode, all accel axes on
  if ((fs==8)||(fs==4))
    Write((0x00 | (fs-fs/2-1)<<4), CTRL_REG4_A);  // set full-scale
  else
    Write(0x00, CTRL_REG4_A);
  Write(0x14, CRA_REG_M);  // 0x14 = mag 30Hz output rate
  Write(0x00, MR_REG_M);  // 0x00 = continouous conversion mode
}
 

 
float MagenticSensor::GetHeading()
{
  GetMagenticAccel();
  while(!(Read(SR_REG_M) & 0x01))
    ;
  GetMagenticMag();
  for (int i=0; i<3; i++)
    realAccel[i] = accel[i] / pow(2, 15) * SCALE;  // calculate real acceleration values, in units of g 
  // see section 1.2 in app note AN3192
  float heading = 180*atan2(mag[1], mag[0])/PI;  // assume pitch, roll are 0  
  if (heading <0)
    heading += 360;
  return heading;
}
 
float MagenticSensor::GetTiltHeading()
{
  GetMagenticAccel();
  while(!(Read(SR_REG_M) & 0x01))
    ;
  GetMagenticMag();
  for (int i=0; i<3; i++)
    realAccel[i] = accel[i] / pow(2, 15) * SCALE;  // calculate real acceleration values, in units of g 
  // see appendix A in app note AN3192 
  float pitch = asin(-realAccel[0]);
  float roll = asin(realAccel[1]/cos(pitch));
   
  float xh = mag[0] * cos(pitch) + mag[2] * sin(pitch);
  float yh = mag[0] * sin(roll) * sin(pitch) + mag[1] * cos(roll) - mag[2] * sin(roll) * cos(pitch);
  float zh = -mag[0] * cos(roll) * sin(pitch) + mag[1] * sin(roll) + mag[2] * cos(roll) * cos(pitch);
 
  float heading = 180 * atan2(yh, xh)/PI;
  if (yh >= 0)
    return heading;
  else
    return (360 + heading);
}
 
void MagenticSensor::GetMagenticMag()
{
  Wire.beginTransmission(LSM303_MAG);
  Wire.write(OUT_X_H_M);
  Wire.endTransmission();
  Wire.requestFrom(LSM303_MAG, 6);
  for (int i=0; i<3; i++)
    mag[i] = (Wire.read() << 8) | Wire.read();
}
 
void MagenticSensor::GetMagenticAccel()
{
  accel[2] = ((int)Read(OUT_X_L_A) << 8) | (Read(OUT_X_H_A));
  accel[0] = ((int)Read(OUT_Y_L_A) << 8) | (Read(OUT_Y_H_A));
  accel[1] = ((int)Read(OUT_Z_L_A) << 8) | (Read(OUT_Z_H_A));  
  // had to swap those to right the data with the proper axis
}
 
byte MagenticSensor::Read(byte address)
{
  byte temp;
   
  if (address >= 0x20)
    Wire.beginTransmission(LSM303_ACC);
  else
    Wire.beginTransmission(LSM303_MAG);
     
  Wire.write(address);
   
  if (address >= 0x20)
    Wire.requestFrom(LSM303_ACC, 1);
  else
    Wire.requestFrom(LSM303_MAG, 1);
  while(!Wire.available())
    ;
  temp = Wire.read();
  Wire.endTransmission();
   
  return temp;
}
 
void MagenticSensor::Write(byte data, byte address)
{
  if (address >= 0x20)
    Wire.beginTransmission(LSM303_ACC);
  else
    Wire.beginTransmission(LSM303_MAG);
     
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();
}