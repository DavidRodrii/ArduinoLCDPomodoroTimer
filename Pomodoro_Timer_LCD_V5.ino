/*
    Arduino Pomodoro Countdown Timer

WARNING: This code is fully functional for your Pomodoro needs,
but be aware it's just very ugly.

Created by: Tutorial45
http://tutorial45.com/building-an-arduino-countdown-timer/

and by: Randy Sarafan
http://www.instructables.com/id/Arduino-Countdown-Timer/?ALLSTEPS

Collaborated by: David Rodriguez
http://drodrii.me/

*/
#include <LiquidCrystal.h> 
 
int S = 59; // count seconds 
int M = 24; // count minutes

// TEST VALUES
//int S = 10; // count seconds 
//int M = 0; // count minutes


// The number of the pushbutton pin
const int buttonPin = 12;     

// Variables for the current and the previous reading from the pushbutton pin
int buttonState;             
int lastButtonState = 0; 

// Additional variable to keep track of the previous button press state.
// This one only keeps track of the state of the button when there is a 
// debounce delay event.
int previousState;

// Tracks the last time the output pin was toggled
long lastDebounceTime = 0;  

 // The debounce time; increase if the button is registering a single press more than once
long debounceDelay = 20;   

// Variable for counting the number of times the button has been pressed.
int buttonPushCounter;

// This variable gets toggled either high or low each time the button is pressed. 
// In other words, this variable changes states with each button press.
bool pressed = true;

int buttonpress;


//initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2,3,4,5,6,7); // pins connected to LCD
 
void setup(){
 lcd.begin(16,2);//set up the LCD's number of columns and rows

// Set buzzer output
 pinMode(11, OUTPUT);
  
// Set pushbutton input
 pinMode(buttonPin, INPUT);
 
}


void loop(){
// lcd.setCursor(0,0);
// lcd.print("                ");
// lcd.setCursor(4,0); 
// lcd.print ("Pomodoro");
 lcd.setCursor(6,1);
 lcd.print(" ");
 lcd.setCursor(7,1);
 lcd.print(":");
 lcd.setCursor(8,1);
 lcd.print(" ");
 
 S--;
  
 if(S<0)
 {
  M--;
  S=59;
 }
 
 if(M>9)
 {
  lcd.setCursor(4,1);
  lcd.print(M);
 }
 else
 {
  lcd.setCursor(4,1);
  lcd.print("0"); 
  lcd.setCursor(5,1);
  lcd.print(M);
 }

  
 if(S>9)
 {
  lcd.setCursor(9,1);
  lcd.print(S);
 }
 else
 {
  lcd.setCursor(9,1);
  lcd.print("0"); 
  lcd.setCursor(10,1);
  lcd.print(S);
 }


// WE WILL TRY TO INSERT THE BUTTON CHECK CODE HERE
// the (y < 50) relation originally used in the old code is delaying
// the count down sequence so I decided to use (y < 36) as the closest
// calibration to seconds, but just in case you wanna see for yourself
// I have it commented out below
//  for (int y = 0; y < 50; y){

// THIS IS THE CLOSEST CALIBRATION TO SECONDS
 for (int y = 0; y < 36; y){
 // Take a button reading
  int reading = digitalRead(buttonPin);
        
 // check to see if you just pressed the button
 // (i.e. the input went from LOW to HIGH),  and you've waited
 // long enough since the last press to ignore any noise:  
        
 // If the state of the the switch has changed, due to being 
 // pressed or a false contact, then reset the debounce timer
  if (reading != lastButtonState){
    lastDebounceTime = millis();
  } 
        
 // If the current reading is beyond the debounce delay
 // set the button state to the current reading
  if ((millis() - lastDebounceTime) > debounceDelay){
    buttonState = reading;
  }
        
        
 // If the current state and the previous state do not match
 // and the current state indicates that the button is being pressed
 // then flip the state of the "pressed" variable (to true or false)
 // and increase the button push counter
  if (buttonState != previousState){
    if(buttonState == 1){
      pressed = !pressed;
      buttonPushCounter++;
    }
  }


 // If the state of the button press is true
 // then the display is paused and it stops counting
  if (pressed == true){
    lcd.setCursor(0,0);
    lcd.print("                "); 
    lcd.setCursor(2,0); 
    lcd.print ("Timer Paused");
  // Displays the left digit
    if(M>9){
      lcd.setCursor(4,1);
      lcd.print(M);
    }
    else{
      lcd.setCursor(4,1);
      lcd.print(" "); 
      lcd.setCursor(5,1);
      lcd.print(M);
    }
    delay(10);
            
  // Displays the right digit
    if(S>9){
      lcd.setCursor(9,1);
      lcd.print(S);
    }
    else{
      lcd.setCursor(9,1);
      lcd.print(" "); 
      lcd.setCursor(10,1);
      lcd.print(S);
    }
    delay(10);
  }
          
 // Otherwise, if the state is not true
 // the display resumes displaying the countdown
  else{
    // lcd.setCursor(1,0); 
    // lcd.print ("25 Minute Timer");
    // lcd.setCursor(0,0);
    // lcd.print("                ");
    lcd.setCursor(1,0); 
    lcd.print ("Pomodoro Timer");
    if(M>9){
      lcd.setCursor(4,1);
      lcd.print(M);
    }
    else{
      lcd.setCursor(4,1);
      lcd.print("0"); 
      lcd.setCursor(5,1);
      lcd.print(M);
    }
    delay(10);

    if(S>9){
      lcd.setCursor(9,1);
      lcd.print(S);
    }
    else{
      lcd.setCursor(9,1);
      lcd.print("0"); 
      lcd.setCursor(10,1);
      lcd.print(S);
    }
    delay(10);
    y = y + 1;
  }
            
           
 // Update the previousState variable for the next loop
  previousState = buttonState; 
         
 // Update the lastButtonState variable for the next loop
  lastButtonState = reading; 


// THIS IS WHERE THE FUNCTION RESTARTS

  while (M == 0 && S == 0){
    timesUp();
  }

// If the button is pressed 3 times in under a second
// reset the program
  if (buttonPushCounter > 2){
    buttonPushCounter = 0;
    return;
  }

 }

 buttonPushCounter = 0;

// END OF VOID LOOP() 
}


// This function runs over and over when the time runs out
// Only pressing the red button makes this stop
void timesUp(){
  
  // Beep on
  // 4 short Beeps followed by 1 long beep
  analogWrite(11, 20);
  delay(50);
  analogWrite(11, 0);
  delay(50);
  analogWrite(11, 20);
  delay(50);
  analogWrite(11, 0);
  delay(50);
  analogWrite(11, 20);
  delay(50);
  analogWrite(11, 0);
  delay(50);
  analogWrite(11, 20);
  delay(50);
  analogWrite(11, 0);
  delay(50);
  analogWrite(11, 20);
  delay(200);
  analogWrite(11, 0);
  delay(100);
  
  // Display "00" 1/2 second
  for (int z = 0; z < 25; z++){
    lcd.setCursor(4, 1);
    lcd.print("0");
    lcd.setCursor(9, 1);
    lcd.print("0");
    // digitalWrite(9, 1);
    // digitalWrite(10, 0);
    // lightUpDigit(0);
    delay(10);
            
    lcd.setCursor(5, 1);
    lcd.print("0");
    lcd.setCursor(10, 1);
    lcd.print("0");
    delay(10);
    
    // Reset the counter if the button is pressed
    // and disable the display and beep
    if(digitalRead(buttonPin) == 1){
      pressed = true;
      S = 59;
      M = 24;
      analogWrite(11, 0);
      lcd.setCursor(4, 1);
      lcd.print(M);
      lcd.setCursor(9, 1);
      lcd.print(S);
      delay(2000);
      return;
    } 
  }
   
  // Beep off
  analogWrite(11, 0);
   
  // Display off 1/2 second
   for (int z = 0; z < 25; z++){
    lcd.setCursor(4, 1);
    lcd.print(" ");
    lcd.setCursor(9, 1);
    lcd.print(" ");
    delay(10);
            
    lcd.setCursor(5, 1);
    lcd.print(" ");
    lcd.setCursor(10, 1);
    lcd.print(" ");
    delay(10);
    
    // Reset the counter if the button is pressed
    if(digitalRead(buttonPin) == 1){
      pressed = true;
      S = 59;
      M = 24;
      delay(2000);
      return;
    } 
  } 
}


