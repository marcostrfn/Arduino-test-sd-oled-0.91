
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
void imprimirDateTime(DateTime now) {

  char str[20];
  sprintf(str, "%i/%i/%i ::: %i:%i:%i", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
  Serial.println(str);
  /*
    Serial.print(now.year(), DEC);    // Año
    Serial.print('/');
    Serial.print(now.month(), DEC);   // Mes
    Serial.print('/');
    Serial.print(now.day(), DEC);     // Dia
    Serial.print(' ');
    Serial.print(now.hour(), DEC);    // Horas
    Serial.print(':');
    Serial.print(now.minute(), DEC);  // Minutos
    Serial.print(':');
    Serial.print(now.second(), DEC);  // Segundos
    Serial.println();
  */
}
