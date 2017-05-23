/*
  SD card test

  This example shows how use the utility libraries on which the'
  SD library is based in order to get info about your SD card.
  Very useful for testing a card when you're not sure whether its working or not.

  The circuit:
    SD card attached to SPI bus as follows:
 ** MOSI - pin 11 on Arduino Uno/Duemilanove/Diecimila
 ** MISO - pin 12 on Arduino Uno/Duemilanove/Diecimila
 ** CLK - pin 13 on Arduino Uno/Duemilanove/Diecimila
 ** CS - depends on your SD card shield or module.
        Pin 4 used here for consistency with other Arduino examples


  created  28 Mar 2011
  by Limor Fried
  modified 9 Apr 2012
  by Tom Igoe
*/


/*********************************************************************
  This is an example for our Monochrome OLEDs based on SSD1306 drivers

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
  // RTC.adjust(DateTime(__DATE__, __TIME__)); // Establece la fecha y hora (Comentar una vez establecida la hora)


  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  /*
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    // Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  */




  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  // display.display();
  // delay(2000);

  // Clear the buffer.
  display.clearDisplay();
  // text display tests 
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("0x"); 
  display.println(0xDEADBEEF, HEX);
  display.display();
 
  
  

}



void loop() {
  digitalClockDisplay();
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(1000);
}


void digitalClockDisplay() {


  DateTime now = RTC.now(); // Obtiene la fecha y hora del RTC

  /*
  Serial.print(now.year(), DEC); // Año
  Serial.print('/');
  Serial.print(now.month(), DEC); // Mes
  Serial.print('/');
  Serial.print(now.day(), DEC); // Dia
  Serial.print(' ');
  Serial.print(now.hour(), DEC); // Horas
  Serial.print(':');
  Serial.print(now.minute(), DEC); // Minutos
  Serial.print(':');
  Serial.print(now.second(), DEC); // Segundos
  Serial.println();
  */

  myFile = SD.open("test.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    myFile.print(now.hour());
    myFile.print(":");
    myFile.print(now.minute());
    myFile.print(":");
    myFile.println(now.second());

    // close the file:
    myFile.close();
    // Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }


  // Clear the buffer.
  display.clearDisplay();
  // text display tests 
  display.setTextSize(1);
  display.setCursor(0,0);
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

