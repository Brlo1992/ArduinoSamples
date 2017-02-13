#include <OneWire.h>
#include <Wire.h> 
#include <DallasTemperature.h>      
#include <LiquidCrystal_I2C.h>
int buzz=13;
int red=7;
int green=8;
int blue=9;
int buzzerBeepCount = 0;
bool alert = false;
#define ONE_WIRE_BUS 10 //szyna danych termometr
#define TEMPERATURE_PRECISION 9 // dokładność pomiaru 

// LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

int numberOfDevices; // Number of temperature devices found

DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address

void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library");
 
  // dioda RGB
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  digitalWrite(blue, LOW);
 
  // LCD
  lcd.begin(20,4);
  
  // MRUGNIĘCIA
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight(); //podświetlenie włączone
  
  lcd.setCursor(0,0); 
  lcd.print("Witaj!");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("Odczyt temperatur.."); 
  lcd.setCursor(0,3);
  lcd.print("Wersja: 1.1 by GM");
  lcd.setCursor(0,2);
  
  loadTemps();
  

  //Buzzer
  pinMode(13, OUTPUT);

  // Start up the library
  sensors.begin();
  
  // Grab a count of devices on the wire
  numberOfDevices = sensors.getDeviceCount();
  
  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  Serial.print(numberOfDevices, DEC);
  Serial.println(" devices.");

  // report parasite power requirements
  Serial.print("Parasite power is: "); 
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");
  
  // Loop through each device, print out address
  for(int i=0;i<numberOfDevices; i++)
  {
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i))
	{
		Serial.print("Found device ");
		Serial.print(i, DEC);
		Serial.print(" with address: ");
		printAddress(tempDeviceAddress);
		Serial.println();
		
		Serial.print("Setting resolution to ");
		Serial.println(TEMPERATURE_PRECISION, DEC);
		
		// set the resolution to TEMPERATURE_PRECISION bit (Each Dallas/Maxim device is capable of several different resolutions)
		sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);
		
		Serial.print("Resolution actually set to: ");
		Serial.print(sensors.getResolution(tempDeviceAddress), DEC); 
		Serial.println();
	}else{
		Serial.print("Found ghost device at ");
		Serial.print(i, DEC);
		Serial.print(" but could not detect address. Check power and cabling");
	}
  }
  digitalWrite(green, LOW);
  digitalWrite(blue, HIGH);
}

// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
  // method 1 - slower
  //Serial.print("Temp C: ");
  //Serial.print(sensors.getTempC(deviceAddress));
  //Serial.print(" Temp F: ");
  //Serial.print(sensors.getTempF(deviceAddress)); // Makes a second call to getTempC and then converts to Fahrenheit

  // method 2 - faster
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Temp F: ");
  Serial.println(DallasTemperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit
}


void loop(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  

  // Loop through each device, print out temperature data
  for(int i=0;i<numberOfDevices; i++)
  {
    // Search the wire for address
    if(sensors.getAddress(tempDeviceAddress, i))
	{
		// Output the device ID
		Serial.print("Temperature for device: ");
		Serial.println(i,DEC);
		
		// It responds almost immediately. Let's print out the data
		printTemperature(tempDeviceAddress); // Use a simple function to print out the data
	} 
	//else ghost device! Check your power requirements and cabling
	
  }
      
      
      //LCD//
  
  float tempPiec = sensors.getTempCByIndex(1);
  lcd.setCursor(0,0); 
  lcd.print(" Piec: ");
  
  if(tempPiec >= 80) // temp. alarmu
  {
         if(alert == false)
         {
             digitalWrite(red, LOW);
             digitalWrite(green, HIGH);
             digitalWrite(blue, HIGH);
             alert = true;
         }
         if(buzzerBeepCount < 5)
         {
            // buzzerBeepCount = buzzerBeepCount + 1
            // buzzerBeepCount += 1;
             buzzerBeepCount ++;
             tone (buzz, 3000, 1000); 
         }

   }
   else{
         if(alert == true)
         {
             digitalWrite(red, HIGH);
             digitalWrite(green, LOW);
             digitalWrite(blue, HIGH);  
             alert = false;
         }
         if(buzzerBeepCount > 0)
         {
             buzzerBeepCount = 0; 
         }
  }

  printOwenTempOnScreen(tempPiec);
  printTermaOnScreen(1, "Terma: ",0);
  printOtherTempsOnScreen(2, "T.Wew: ",3);
  printOtherTempsOnScreen(3, "T.Zew: ",2);
  
  //lcd.setCursor(0,1);
  //lcd.print("Terma: ");
  //lcd.print(sensors.getTempCByIndex(0)+5);
  //lcd.setCursor(11,1);
  //lcd.print(" 'C");

  //T. WEW
  //lcd.setCursor(0,2);
  //lcd.print("T.Wew: ");
  //lcd.print(sensors.getTempCByIndex(3));
  //lcd.setCursor(11,2);
  //lcd.print(" 'C");

  //T. ZEW
  //lcd.setCursor(0,3);
  //lcd.print("T.Zew: ");
  //lcd.print(sensors.getTempCByIndex(2));
  //lcd.setCursor(11,3);
  //lcd.print(" 'C");
  
  lcd.setCursor(0,0);
  delay(3000);
}

void loadTemps()
{
     delay(300);  
     for(int index = 0; index < 20; index ++)
     {
          lcd.print(">");
          delay(300);
     }
     lcd.clear(); 
}


void printOwenTempOnScreen(float tempPiec)
{
     lcd.print(tempPiec);
     lcd.setCursor(11,0);
     lcd.print(" 'C");   
}
void printTermaOnScreen(int cursorPosition, String nameToDisplay, int sensorIndex)
{
     lcd.setCursor(0,cursorPosition);
     lcd.print(nameToDisplay);
     lcd.print(sensors.getTempCByIndex(sensorIndex) + 1);
     lcd.setCursor(11,cursorPosition);
     lcd.print(" 'C");  
}
void printOtherTempsOnScreen(int cursorPosition, String nameToDisplay, int sensorIndex)
{
     lcd.setCursor(0,cursorPosition);
     lcd.print(nameToDisplay);
     lcd.print(sensors.getTempCByIndex(sensorIndex));
     lcd.setCursor(11,cursorPosition);
     lcd.print(" 'C");  
}
// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
     for (uint8_t i = 0; i < 8; i++)
     {
        if (deviceAddress[i] < 16) Serial.print("0");
        Serial.print(deviceAddress[i], HEX);
     }
}


