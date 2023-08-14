#include <HX711.h>

// Pin definitions for HX711 module
#define DT  4
#define SCK  3

// Initialize HX711
HX711 scale(DT, SCK);
float calibration_factor = +435700;  // Calibration factor for conversion to weight units

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  scale.set_scale();   // Initialize the scale
  long zero_factor = scale.read_average();  // Get zero factor (not used here)
}

void loop() {
  scale.set_scale(calibration_factor);  // Apply the calibration factor

  Serial.print(scale.get_units(), 3);   // Print weight in specified format
  Serial.print(" kg");  // Display weight in kilograms
  
  Serial.println();  // Move to the next line
  delay(100);  // Delay for stability

  if (Serial.available()) {
    char temp = Serial.read();
    // Adjust calibration factor based on user input
    if (temp == '+' || temp == 'a')
      calibration_factor += 10;
    else if (temp == '-' || temp == 'z')
      calibration_factor -= 10;
    else if (temp == 's')
      calibration_factor += 100;
    else if (temp == 'x')
      calibration_factor -= 100;
    else if (temp == 'd')
      calibration_factor += 1000;
    else if (temp == 'c')
      calibration_factor -= 1000;
    else if (temp == 'f')
      calibration_factor += 10000;
    else if (temp == 'v')
      calibration_factor -= 10000;
    else if (temp == 't')
      scale.tare();  // Reset the scale to zero
  }
}
