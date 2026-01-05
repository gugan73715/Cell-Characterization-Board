#include <LiquidCrystal.h>


// Initialize the library with the numbers of the interface pins:
// rs, en, d4, d5, d6, d7
// These pin numbers are common, but adjust them if you wired the LCD differently.
const int rs = 13, en = 11, d4 = 7, d5 = 8, d6 = 9, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// --- Variables to hold the data you want to display ---
// You would replace these with sensor readings or user inputs in a real application.
int cellNumber = 1;
float capacityAh = 0;
float currentSettingA = 0.5;

void setup() {

  // External 2.5V Reference From DAC
  analogReference(EXTERNAL);

  // Set up the number of columns and rows on the LCD (16 columns, 2 rows)
  lcd.begin(16, 2);
  
  // Print a brief message at startup
  lcd.print("System Initializing");
  delay(2000); // Wait 2 seconds
  lcd.clear(); // Clear the screen after the initial message
}

void loop() {
  // --- Line 1: Cell Number and Capacity ---
  
  // Set the cursor to the first column (0) of the first row (0)
  lcd.setCursor(0, 0); 
  
  // Print "Cell no. :"
  lcd.print("Cellno.");
  
  // Move the cursor to where the value should go (column 10, row 0)
  lcd.setCursor(7, 0); 
  
  // Print the value of the cell number
  lcd.print(cellNumber); 
  lcd.print(" ");

  // Move the cursor a bit further to the right (column 12, row 0)
  lcd.setCursor(9, 0);
  
  // This is a space saver. If the cell number is single digit, we start Capacity on the same line.
  // Print "Cap:" (shortened from Capacity) on the same line
  lcd.print("I:"); 
  
  // Move the cursor to where the Capacity value should go (column 14, row 0)
  // NOTE: This leaves very little space. You may need to adjust layout.
  lcd.setCursor(11, 0);
  lcd.print(currentSettingA, 2);
  lcd.setCursor(15, 0);
  lcd.print("A");
  // lcd.print(capacityAh, 1); // Print the value with 1 decimal place

  // --- Line 2: Iset (Current Setting) ---
  
  // Set the cursor to the first column (0) of the second row (1)
  lcd.setCursor(0, 1); 
  
  // Print "Capacity :"
  lcd.print("Capacity :");
  
  // Move the cursor to where the Capacity value should go (column 10, row 1)
  lcd.setCursor(10, 1);
  
  // Print the Capacity value with 1 decimal place
  lcd.print(capacityAh, 1);
  
  // Move cursor to the space after Capacity
  lcd.setCursor(14, 1);
  
  // Print 'Ah' unit
  lcd.print("Ah");

  // Since we ran out of space, we'll use the available characters on the second line:
  
  // Clear the display for the next frame or use the space for Iset.
  // Since you need three items, we'll try to fit two on Line 1 and one on Line 2, or alternate.
  
  // --- Alternative Layout for Iset ---
  /*
  // Clear the display for the next frame
  delay(2000);
  lcd.clear();
  
  // Set the cursor to the first column (0) of the first row (0)
  lcd.setCursor(0, 0);
  lcd.print("Iset :");
  lcd.setCursor(6, 0);
  lcd.print(currentSettingA, 2); // Print the value with 2 decimal places
  lcd.print("A");
  */
  /*if (cellNumber < 10) 
  {
    cellNumber++;
  }

  else
  {
    cellNumber = 1;
  }
*/
  if (capacityAh < 5.0) 
  {
    capacityAh = capacityAh + 0.1;
  }

   else
  {
    capacityAh = 0.5;
  }
/*
  if (currentSettingA < 5) 
  {
    currentSettingA = currentSettingA + 0.5;
  }

   else
  {
    currentSettingA = 0.5;
  }
 */
  delay(1000); // Wait for 1 second before updating the display
  // In a real application, you might use an event-driven approach instead of delay().
}