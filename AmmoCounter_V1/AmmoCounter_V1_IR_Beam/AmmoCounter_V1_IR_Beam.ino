// AmmoCounter V1 with IR Beam 
// Updated 10/3/2016
// Created by: Nathaniel Deal
// More Info: www.ammocounter.com 

// Include Libraries
#include <Button.h>
#include <AmmoCounter.h>

// Setup Toggle/Counter Variables
int toggleArray[] = {35,25,22,18,15,12,10,6}; // Setup array of magazine sizes
int toggleCount = (sizeof(toggleArray)/sizeof(int))-1; // Find size of array
int togglePosition = toggleCount; // Start at max capacity.
int count = toggleArray[toggleCount];  // Set intial count to highest capacity.
AmmoCounter counter = AmmoCounter(); // Setup AmmoCounter instance

// IR Beam Setup
int irSensorPin = A2;
int idleValue = 1;
int fireValue = 3;
boolean hasCleared = false;  // Check for cleared dart
 
// Toggle/Reset Setup
Button toggleBtn = Button (4, PULLDOWN);   // Use digital pin 4 for the toggle pin
Button resetBtn = Button (5, PULLDOWN);    // Use digital pin 5 for the reset pin

void setup() {
  
  // Show Initial Count
  counter.displayNumber(count);

  // Serial.begin(9600); // Uncomment for testing
}               

void loop(){
  
  // Monitor IR Beam
  //----------------------------------------------------//

    int sensorValue = analogRead(irSensorPin); // Read the analog in value
    int outputValue = map(sensorValue, 0, 1023, 0, 10);  // Map it to the range of the analog output

    // Check to see if dart has fired
    if (outputValue > fireValue)
    {
      if (hasCleared == true) // If barrel is clear and beam is broken then countdown 
      {
        counter.displayNumber(--count); 
        hasCleared = false;

        // Print the results to the serial monitor for testing
        // Serial.print("\t output = ");      
        // Serial.println(outputValue);
      }
    }

    // Check to see if dart has cleared
    if (outputValue <= idleValue)
    {
      hasCleared = true;
    }
  
  // Monitor Toggle Button
  //----------------------------------------------------//
  
    // Check if the togglebutton is pressed.
    if (toggleBtn.uniquePress()) {       
        
      // Toggle the display
      if (togglePosition == 0) {
        togglePosition = toggleCount; //Reset to max.
      } else {
        togglePosition--; //Deincrement capacity one step 
      } 
      
      count = toggleArray[togglePosition];
      counter.displayNumber(count); //Send to display      
    }
  
  // Monitor Reset Button
  //----------------------------------------------------//
  
    // Check if resetbutton is pressed.
    if (resetBtn.uniquePress()) {  
      
      count = toggleArray[togglePosition];
      counter.displayNumber(count); //Send to display  
    }

  // Auto-Reset
  //----------------------------------------------------//

    // Check if count has finished
    if (count == 0) {
      count = toggleArray[togglePosition];  
      counter.displayNumber(count); //Send to display
    }
}

