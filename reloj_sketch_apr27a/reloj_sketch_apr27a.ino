/*********************************************************************
  SD card 
  
 ** SD card e bus SPI:
 ** MOSI  - pin 11  Arduino Uno/Duemilanove/Diecimila
 ** MISO  - pin 12  Arduino Uno/Duemilanove/Diecimila
 ** CLK   - pin 13  Arduino Uno/Duemilanove/Diecimila
 ** CS    - variable dependiendo del shield
        Usamos Pin 4 

  created  28 Mar 2011 by Limor Fried
  modified 9 Apr 2012 by Tom Igoe
  
 
  Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

  This example is for a 128x32 size display using I2C to communicate
  3 pins are required to interface (2 I2C and one reset)

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada  for Adafruit Industries.
  BSD license, check license.txt for more information
  All text above, and the splash screen must be included in any redistribution


  RTC (reloj)

  // Establece la fecha y hora (Comentar una vez establecida la hora) 
  RTC.adjust(DateTime(__DATE__, __TIME__)); 

  
*********************************************************************/


#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


RTC_DS1307 RTC;
File myFile;


// pantalla lcd oled 0.91
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


void setup() {
  Wire.begin();
  Serial.begin(115200);
  // while (!Serial); // Solo para el Leonardo

  pinMode(LED_BUILTIN, OUTPUT);
  RTC.begin(); // Inicia la comunicación con el RTC

  if (!SD.begin(4)) {
    Serial.println("Error al iniciar SD!");
    return;
  }
  Serial.println("SD Iniciada");
  
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  // initialize with the I2C addr 0x3C (for the 128x32)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);   
  display.clearDisplay(); // Clear the buffer.

}



void loop() {
  digitalClockDisplay();
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(1000);
}


void digitalClockDisplay() {

  DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC
  imprimirDateTime(now);
  
  myFile = SD.open("test.txt", FILE_WRITE);  
  if (myFile) {
    myFile.print(now.hour());
    myFile.print(":");
    myFile.print(now.minute());
    myFile.print(":");
    myFile.println(now.second());
    myFile.close();
  } else {
    Serial.println("error abriendo test.txt");
  }


  // Clear the buffer.
  display.clearDisplay();
  // text display tests
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(now.year(), DEC); // Año
  display.print('/');
  display.print(now.month(), DEC); // Mes
  display.print('/');
  display.println(now.day(), DEC); // Dia

  // display.setTextSize(2);
  display.setTextSize(1);
  display.print(now.hour(), DEC); // Horas
  display.print(':');
  display.print(now.minute(), DEC); // Minutos
  display.print(':');
  display.println(now.second(), DEC); // Segundos

  display.setTextSize(1);
  display.println("jajajaja");
  display.print("arduiiiiiiino");
  display.display();


}

