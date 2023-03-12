#include <SPI.h>

#include <TFT_eSPI.h>       // LCD library
#include <ADS1115_WE.h>      // 16-bit ACD driver
#include <Wire.h>
#define I2C_ADDRESS 0x48

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library
ADS1115_WE adc = ADS1115_WE(I2C_ADDRESS);

void setup(void) {
  init_adc();
  
  tft.init();
  tft.invertDisplay( true ); // Binary inversion of colours
  tft.setRotation(3);

  tft.fillScreen(TFT_BLACK);
}

void loop() {
  tft.setCursor(0, 0, 4);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.println("OneWheel Charger");
  
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.println("v0.0.3");

  float voltage = 0.0;
  Serial.print("0: ");
  voltage = readChannel(ADS1115_COMP_0_GND);
  Serial.print(voltage);
  Serial.print(",   1: ");
  voltage = readChannel(ADS1115_COMP_1_GND);
  Serial.print(voltage);
  
  Serial.print(",   2: ");
  voltage = readChannel(ADS1115_COMP_2_GND);
  Serial.print(voltage);
  Serial.print(",   3: ");
  voltage = readChannel(ADS1115_COMP_3_GND);
  Serial.println(voltage);

  delay(100);
}

void init_adc() {
  Wire.begin();
  Serial.begin(115200);
  if(!adc.init()){
    Serial.println("ADS1115 not connected!");
  }
  adc.setVoltageRange_mV(ADS1115_RANGE_6144);
  Serial.println("ADS1115 Example Sketch - Single Shot Mode");
  Serial.println("Channel / Voltage [V]: ");
  Serial.println();
}

float readChannel(ADS1115_MUX channel) {
  float voltage = 0.0;
  adc.setCompareChannels(channel);
  adc.startSingleMeasurement();
  while(adc.isBusy()){}
  voltage = adc.getResult_V(); // alternative: getResult_mV for Millivolt
  return voltage;
}
