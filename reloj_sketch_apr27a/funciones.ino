
/*
    Escribir en un fichero de la tarjeta SD
*/
void testSdWrite() {
  myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile) {
    Serial.print("Escribiendo a test.txt.");
    myFile.println("test 1, 2, 3.");
    myFile.close();
  } else {
    Serial.println("error abriendo test.txt");
  }
}

/*
   Leer un fichero de la tarjeta SD
*/
void testSdRead() {
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close();
  } else {
    Serial.println("error abriendo test.txt");
  }
}

/*
   Imprimir en OLED
*/
void imprimirEnOled() {
  display.clearDisplay(); // Clear the buffer.
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("0x");
  display.println(0xDEADBEEF, HEX);
  display.display();
}


/*
   Imprime fecha y hora por puerto de serie
*/
void imprimirDateTime() {

  snprintf(str, 20, "%4i/%02i/%02i %02i:%02i:%02i", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
  Serial.println(str);

  //  Serial.print(now.year(), DEC);    // Año
  //  Serial.print('/');
  //  Serial.print(now.month(), DEC);   // Mes
  //  Serial.print('/');
  //  Serial.print(now.day(), DEC);     // Dia
  //  Serial.print(' ');
  //  Serial.print(now.hour(), DEC);    // Horas
  //  Serial.print(':');
  //  Serial.print(now.minute(), DEC);  // Minutos
  //  Serial.print(':');
  //  Serial.print(now.second(), DEC);  // Segundos
  //  Serial.println();

}

void imprimirDisplay() {
  // Clear the buffer.
  display.clearDisplay();
  // text display tests
  display.setTextSize(1);
  display.setCursor(0, 0);
  snprintf(str, 20, "%4i/%02i/%02i %02i:%02i:%02i", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
  display.println(str);

  display.setTextSize(2);
  display.setCursor(10, 10);
  display.print(c);
  display.display();
}


void grabarFecha() {
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
}


void parsearOrden(char b) {
  
  if (b == '.' or cIncoming == BUFFER_SIZE) {
    char *p = inComing;
    snprintf(str, BUFFER_SIZE+1, "%s", p);
    Serial.println(str);

    memset(inComing, '\0', sizeof(char)*BUFFER_SIZE);
    cIncoming = 0;
    if (b=='.') return;
  } 
  inComing[cIncoming++] = b;
  
}

