/*
The following example is based on Example sktch 15 of the SparkFun Inventor's Kit
*/

/*
SparkFun Inventor's Kit
Example sketch 15

LIQUID CRYSTAL DISPLAY (LCD)

  A Liquid Crystal Display (LCD) is a sophisticated module
  that can be used to display text or numeric data. The display
  included in your SIK features two lines of 16 characters, and
  a backlight so it can be used at night.

  If you've been using the Serial Monitor to output data,
  you'll find that a LCD provides many of the same benefits
  without needing to drag a large computer around.

  This sketch will show you how to connect an LCD to your Arduino
  and display any data you wish.

Hardware connections:

  The LCD has a 16-pin male header attached to it along the top
  edge. Pin 1 is the pin closest to the corner of the LCD.
  Pin 16 is the pin closest to the center of the LCD.

  Plug the LCD into your breadboard.

  As usual, you will want to connect the + and - power rails
  on the side of the breadboard to 5V and GND on your Arduino.

  Plug your 10K potentiometer into three unused rows on your
  breadboard. Connect one side of the potentiometer to 5V,
  and the other side to GND (it doesn't matter which). When you
  run this sketch, you'll use the potentiometer to adjust the
  contrast of the LCD so you can see the display.

  Now connect the LCD pins. Remember that pin 1 on the LCD
  is the one closest to the corner. Start there and work your
  way up.

  1 to GND
  2 to 5V
  3 to the center pin on the potentiometer
  4 to Arduino digital pin 12
  5 to GND
  6 to Arduino digital pin 11
  7 (no connection)
  8 (no connection)
  9 (no connection)
  10 (no connection)
  11 to Arduino digital pin 5
  12 to Arduino digital pin 4
  13 to Arduino digital pin 3
  14 to Arduino digital pin 2
  15 to 5V
  16 to GND

  Once everything is connected, load this sketch into the
  Arduino, and adjust the potentiometer until the display
  is clear.

Library

  The LCD has a chip built into it that controls all the
  individual dots that make up the display, and obeys commands
  sent to it by the the Arduino. The chip knows the dot patterns
  that make up all the text characters, saving you a lot of work.

  To communicate with this chip, we'll use the LiquidCrystal
  library, which is one of the standard libraries that comes
  with the Arduino. This library does most of the hard work
  of interfacing to the LCD; all you need to pick a location
  on the display and send your data!

Tips

  The LCD comes with a protective film over the display that
  you can peel off (but be careful of the display surface as
  it scratches easily).

  The LCD has a backlight that will light up when you turn on
  your Arduino. If the backlight doesn't turn on, check your
  connections.

  As we said above, the potentiometer adjusts the contrast of
  the display. If you can't see anything when you run the sketch,
  turn the potentiometer's knob until the text is clear.

This sketch was written by SparkFun Electronics,
with lots of help from the Arduino community.
This code is completely free for any use.
Visit http://learn.sparkfun.com/products/2 for SIK information.
Visit http://www.arduino.cc to learn about the Arduino.

Version 1.0 2/2013 MDG
*/

// Load the LiquidCrystal library, which will give us
// commands to interface to the LCD:

#include <LiquidCrystal.h>

// Initialize the library with the pins we're using.
// (Note that you can use different pins if needed.)
// See http://arduino.cc/en/Reference/LiquidCrystal
// for more information:

LiquidCrystal lcd(12,11,5,4,3,2);

const int temperaturePin = 0;//means A0

void setup()
{
    // In this sketch, we'll use the Arduino's serial port
  // to send text back to the main computer. For both sides to
  // communicate properly, they need to be set to the same speed.
  // We use the Serial.begin() function to initialize the port
  // and set the communications speed.

  // The speed is measured in bits per second, also known as
  // "baud rate". 9600 is a very commonly used baud rate,
  // and will transfer about 10 characters per second.
   Serial.begin(9600); //AS

  // The LiquidCrystal library can be used with many different
  // LCD sizes. We're using one that's 2 lines of 16 characters,
  // so we'll inform the library of that:

  lcd.begin(16, 2);

  // Data sent to the display will stay there until it's
  // overwritten or power is removed. This can be a problem
  // when you upload a new sketch to the Arduino but old data
  // remains on the display. Let's clear the LCD using the
  // clear() command from the LiquidCrystal library:

  lcd.clear();

  // Now we'll display a message on the LCD!

  // Just as with the Arduino IDE, there's a cursor that
  // determines where the data you type will appear. By default,
  // this cursor is invisible, though you can make it visible
  // with other library commands if you wish.

  // When the display powers up, the invisible cursor starts
  // on the top row and first column.

  lcd.print("Temperature is...");

  // Adjusting the contrast (IMPORTANT!)

  // When you run the sketch for the first time, there's a
  // very good chance you won't see anything on the LCD display.
  // This is because the contrast likely won't be set correctly.
  // Don't worry, it's easy to set, and once you set it you won't
  // need to change it again.

  // Run the sketch, then turn the potentiometer until you can
  // clearly see the "hello, world!" text. If you still can't
  // see anything, check all of your connections, and ensure that
  // the sketch was successfully uploaded to the Arduino.
}

void loop()
{
  //gather volatage readings
  float voltage, degreesC, degreesF;
  voltage = getVoltage(temperaturePin);
  degreesC = (voltage - 0.5) * 100.0;
  degreesF = degreesC * (9.0/5.0) + 32.0;

  // You can move the invisible cursor to any location on the
  // LCD before sending data. Counting starts from 0, so the top
  // line is line 0 and the bottom line is line 1. Columns range
  // from 0 on the left side, to 15 on the right.

  // In additon to the "hello, world!" printed above, let's
  // display a running count of the seconds since the Arduino
  // was last reset. Note that the data you send to the display
  // will stay there unless you erase it by overwriting it or
  // sending a lcd.clear() command.

  // Here we'll set the invisible cursor to the first column
  // (column 0) of the second line (line 1):

  lcd.setCursor(0,1);

  // Now we'll print the number of seconds (millis() / 1000)
  // since the Arduino last reset:

  lcd.print(degreesF);
  lcd.print("F");
  lcd.print("   ");
  lcd.print(degreesC);
  lcd.print("C");

  // TIP: Since the numeric data we're sending is always growing
  // in length, new values will always overwrite the previous ones.
  // However, if you want to display varying or decreasing numbers
  // like a countdown, you'll find that the display will leave
  // "orphan" characters when the new value is shorter than the
  // old one.

  // To prevent this, you'll need to erase the old number before
  // writing the new one. You can do this by overwriting the
  // last number with spaces. If you erase the old number and
  // immediately write the new one, the momentary erase won't
  // be noticeable. Here's a typical sequence of code:

  // lcd.setCursor(0,1);   // Set the cursor to the position
  // lcd.print("       "); // Erase the largest possible number
  // lcd.setCursor(0,1);   // Reset the cursor to the original position
  // lcd.print(millis()/1000); // Print our value

  // NEXT STEPS:

  // Now you know the basics of hooking up an LCD to the Arduino,
  // and sending text and numeric data to the display!

  // The LCD library has many commands for turning the
  // cursor on and off, scrolling the screen, etc. See:
  // http://arduino.cc/en/Reference/LiquidCrystal
  // for more information.

  // Arduino also comes with a number of built-in examples
  // showing off the features of the LiquidCrystal library.
  // These are locted in the file/examples/LiquidCrystal menu.

  // Have fun, and let us know what you create!
  // Your friends at SparkFun.

  delay(500); // repeat once per 1/2 second (change as you wish!)
}

/*
The following gets the readings from the temperature sensor
 */
float getVoltage(int pin)
{
  // This function has one input parameter, the analog pin number
  // to read. You might notice that this function does not have
  // "void" in front of it; this is because it returns a floating-
  // point value, which is the true voltage on that pin (0 to 5V).

  // You can write your own functions that take in parameters
  // and return values. Here's how:

    // To take in parameters, put their type and name in the
    // parenthesis after the function name (see above). You can
    // have multiple parameters, separated with commas.

    // To return a value, put the type BEFORE the function name
    // (see "float", above), and use a return() statement in your code
    // to actually return the value (see below).

    // If you don't need to get any parameters, you can just put
    // "()" after the function name.

    // If you don't need to return a value, just write "void" before
    // the function name.

  // Here's the return statement for this function. We're doing
  // all the math we need to do within this statement:

  return (analogRead(pin) * 0.004882814);

  // This equation converts the 0 to 1023 value that analogRead()
  // returns, into a 0.0 to 5.0 value that is the true voltage
  // being read at that pin.
}

