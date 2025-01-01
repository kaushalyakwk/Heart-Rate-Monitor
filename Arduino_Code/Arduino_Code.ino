#include <LiquidCrystal_I2C.h> #include <Wire.h>

//buttons
int upButton = 13; int downButton = 11; int selectButton = 12;

boolean up = false; boolean down = false; boolean middle = false;



//menu
int menuitem = 1;
 
int frame = 1; int page = 1;
int lastMenuItem = 1;


String menuItem1 = "Pulse rate"; String menuItem2 = "Temperature"; String menuItem3 = "Battery level";



//thermistor variables
#define analogPin A0 //the thermistor attach to #define beta 3950 //the beta of the thermistor
#define resistance 10 //the value of the pull-up resistor




//pulse rate sensor variables
int data = A1; //pulse rate sensor input int count = 0;
int start=12;
unsigned long temp = 0;


LiquidCrystal_I2C lcd(0x27, 16, 2);


byte customChar1[8] = {0b00000,0b00000,0b00011,0b00111,0b01111,0b01111,0b01111,0b01111}; byte customChar2[8] = {0b00000,0b11000,0b11100,0b11110,0b11111,0b11111,0b11111,0b11111}; byte customChar3[8] = {0b00000,0b00011,0b00111,0b01111,0b11111,0b11111,0b11111,0b11111}; byte customChar4[8] = {0b00000,0b10000,0b11000,0b11100,0b11110,0b11110,0b11110,0b11110}; byte customChar5[8] = {0b00111,0b00011,0b00001,0b00000,0b00000,0b00000,0b00000,0b00000}; byte customChar6[8] = {0b11111,0b11111,0b11111,0b11111,0b01111,0b00111,0b00011,0b00001}; byte customChar7[8] = {0b11111,0b11111,0b11111,0b11111,0b11110,0b11100,0b11000,0b10000};
 
byte customChar8[8] = {0b11100,0b11000,0b10000,0b00000,0b00000,0b00000,0b00000,0b00000};


void setup() { pinMode(data,INPUT);
pinMode(upButton, INPUT_PULLUP); pinMode(downButton, INPUT_PULLUP); pinMode(selectButton, INPUT_PULLUP); lcd.init();
lcd.backlight(); lcd.clear();
lcd.createChar(1, customChar1); lcd.createChar(2, customChar2); lcd.createChar(3, customChar3); lcd.createChar(4, customChar4); lcd.createChar(5, customChar5); lcd.createChar(6, customChar6); lcd.createChar(7, customChar7); lcd.createChar(8, customChar8); lcd.setCursor(0,0); lcd.print("Heart monitor"); delay(1000);
lcd.setCursor(0,1); lcd.print(" Main Menu "); delay(3000);
}


void loop() { drawMenu();
if (!digitalRead(downButton)){ down = true;
 
while (!digitalRead(downButton));
}
if (!digitalRead(upButton)){ up = true;
while(!digitalRead(upButton));
}
if (!digitalRead(selectButton)){ middle = true;
while (!digitalRead(selectButton));
}


if (up && page == 1 ) {


up = false;
if(menuitem==2 && frame ==2)
{
frame--;
}
lastMenuItem = menuitem; menuitem--;
if (menuitem==0)
{
menuitem=1;
}
}
if (down && page == 1)
{


down = false;
if(menuitem==2 && lastMenuItem == 1)
 
{
frame ++;
}else if(menuitem==3 && lastMenuItem == 2)
{
frame ++;
}
lastMenuItem = menuitem; menuitem++;
if (menuitem==4)
{
menuitem--;
}
}
if (middle) //Middle Button is Pressed
{
middle = false;


if(page == 1 && menuitem == 1)// Reset
{
pulse_sensor_val();
}


else if (page == 1 && menuitem == 2)
{
thermistor_val();
}
else if (page == 1 && menuitem == 3)
{
battery_level();
}
 
}
}




void drawMenu()
{


if (page==1)
{


if(menuitem==1 && frame ==1)
{
lcd.setCursor(0,0); lcd.print("  "); lcd.setCursor(0,1); lcd.print(" ");
displayMenuItem(menuItem1, 0,true); displayMenuItem(menuItem2, 1,false);
}
else if(menuitem == 2 && frame == 1)
{
lcd.setCursor(0,0); lcd.print(" "); lcd.setCursor(0,1); lcd.print(" ");
displayMenuItem(menuItem1, 0,false); displayMenuItem(menuItem2, 1,true);
}
else if(menuitem == 2 && frame == 2)
{
 
lcd.setCursor(0,0); lcd.print(" "); lcd.setCursor(0,1); lcd.print(" ");
displayMenuItem(menuItem2, 0,true); displayMenuItem(menuItem3, 1,false);
}


else if(menuitem == 3 && frame == 2)
{
lcd.setCursor(0,0);
lcd.print(" "); lcd.setCursor(0,1); lcd.print(" ");
displayMenuItem(menuItem2, 0,false); displayMenuItem(menuItem3, 1,true);
}


}
}




void displayMenuItem(String item, int position, boolean selected)
{
if(selected)
{
//display.setTextColor(WHITE, BLACK); lcd.setCursor(0, position); lcd.print("X"+item);
}else
 
{
//display.setTextColor(BLACK, WHITE); lcd.setCursor(0, position); lcd.print(">"+item);
}


}


void pulse_sensor_val(){ lcd.setCursor(0, 0); lcd.print("Place The Finger"); lcd.setCursor(0, 1); lcd.print("And Press Start");

while(digitalRead(start)>0);


lcd.clear(); temp=millis();

while(millis()<(temp+10000))
{
if(analogRead(data)>=500)
{
count=count+1;


lcd.setCursor(6, 0); lcd.write(byte(1)); lcd.setCursor(7, 0); lcd.write(byte(2)); lcd.setCursor(8, 0);
 
lcd.write(byte(3)); lcd.setCursor(9, 0); lcd.write(byte(4));

lcd.setCursor(6, 1); lcd.write(byte(5)); lcd.setCursor(7, 1); lcd.write(byte(6)); lcd.setCursor(8, 1); lcd.write(byte(7)); lcd.setCursor(9, 1); lcd.write(byte(8));

while(analogRead(data)>=500);


lcd.clear();
}
}


lcd.clear(); lcd.setCursor(0, 0); count=count*6; lcd.setCursor(2, 0); lcd.write(byte(1)); lcd.setCursor(3, 0); lcd.write(byte(2)); lcd.setCursor(4, 0); lcd.write(byte(3)); lcd.setCursor(5, 0); lcd.write(byte(4));
 

lcd.setCursor(2, 1); lcd.write(byte(5)); lcd.setCursor(3, 1); lcd.write(byte(6)); lcd.setCursor(4, 1); lcd.write(byte(7)); lcd.setCursor(5, 1); lcd.write(byte(8)); lcd.setCursor(7, 1);

lcd.print(count); lcd.print(" BPM"); delay(1000); temp=0;
}


void thermistor_val(){ while(!middle){

if (!digitalRead(selectButton)){ middle = true;
while (!digitalRead(selectButton));
}


long a =1023 - analogRead(analogPin); //read thermistor value Serial.print("Raw reading ");
Serial.println(a);
//the calculating formula of temperature
float tempC = beta /(log((1025.0 * 10 / a - 10) / 10) + beta / 298.0) - 273.0;
 
float tempF = 1.8*tempC + 32.0; Serial.print("Centigrade "); Serial.println(tempC); Serial.print("Fahrenheit "); Serial.println(tempF); Serial.println("");

// Print a message of "Temp: "to the LCD. lcd.setCursor(0, 0);// set the cursor to column 0, line 0
lcd.print("Temp: "); // Print a message of "Temp: "to the LCD. lcd.print(tempC); // Print a centigrade temperature to the LCD.
// Print the unit of the centigrade temperature to the LCD. lcd.write(char(223));
lcd.print("C");//print the unit" ℃ "
lcd.setCursor(0, 1);// set the cursor to column 0, line 1 lcd.print("Fahr: ");
lcd.print(tempF);// Print a Fahrenheit temperature to the LCD. lcd.write(char(223)); // Print the unit of the Fahrenheit temperature to the LCD. lcd.print(" F");//print the unit"°F"
delay(200); //wait for 100 milliseconds
}


middle = false;
}


void battery_level(){ while(!middle){

if (!digitalRead(selectButton)){ middle = true;
 
while (!digitalRead(selectButton));
}


int battery = analogRead(A2);
float battery_level = map(battery,0,1023,2,3.7);
float battery_percentage = ((battery_level-2)/1.7)*100; lcd.clear();
lcd.print("Battery level:"); lcd.setCursor(0, 1); lcd.print(battery_percentage);
}
middle=false;
}
