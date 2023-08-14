// RPM Measurement using Interrupts

// Define variables
float value = 0;
float rev = 0;
int rpm = 0;
int oldTime = 0;
int currentTime;

// Interrupt service routine
void isr()
{
  rev++; // Increment revolution count
}

void setup()
{
  Serial.begin(9600); // Initialize serial communication
  attachInterrupt(0, isr, RISING); // Attach interrupt to rising edge of signal
}

void loop()
{
  delay(1000); // Wait for 1 second
  detachInterrupt(0); // Detach the interrupt to prevent interference
  currentTime = millis() - oldTime; // Calculate elapsed time since last loop
  rpm = (rev / currentTime) * 60000 / 2; // Calculate RPM for blades (divide by 2 for one interrupt per revolution)
  oldTime = millis(); // Update the old time for the next loop
  rev = 0; // Reset revolution count

  // Print RPM value to serial monitor
  Serial.print(rpm);
  Serial.println(" RPM");

  attachInterrupt(0, isr, RISING); // Reattach the interrupt for the next loop
}
