#include <Wire.h>
#define Addr 0x50
void setup()
{
  Serial.begin (9600);
  Wire.begin();
 
}
void loop()
{
/// at DAC vlaue 290 the current output will be around 4mA and 
///at DAC vlaue 1500 the current output will be around 20mA 
/// you can change these values to tune the 4-20mA output
  unsigned int data[2];
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Calling conversion result register, 0x00(0)
  Wire.write(0x00);
  // Stop I2C transmission
  Wire.endTransmission();
  
  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);
  
  // Read 2 bytes of data
  // raw_adc msb, raw_adc lsb
  if(Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }
  delay(300);
  // Convert the data to 12 bits
  int raw_adc = ((data[0] & 0x0F) * 256) + data[1];
  if (raw_adc > 290 && raw_adc < 1500)
  {
  Wire.beginTransmission(0x60 );
  Wire.write(64);  
  Wire.write(raw_adc >> 4);        // 8 MSB
  Wire.write((raw_adc & 15) << 4); //4 LSB
  delay(10);
  Serial.print("4-20mA current trnasmitter output ");
  Serial.println(raw_adc*0.013);
  Serial.print("\n");
  Wire.endTransmission();
  }
}
