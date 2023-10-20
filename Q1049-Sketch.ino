#include <EEPROM.h>

int matrizFios[] = { 0, 0, 0, 0, 0, 0 };
unsigned long delaySetup;
bool configura;
byte matriz;

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);

  pinMode(A0, INPUT_PULLUP);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(A1, OUTPUT);

  //Testa botão apertado para entrar no setup da matriz dos fios.
  digitalWrite(A1, LOW);
  delaySetup = millis();
  configura = false;
  while (!digitalRead(A0)) {

    if ((millis() - delaySetup) > 2000) {
      configura = true;
      break;
    }
    //delay(10);
  }

  //Entra no setup da matriz dos fios a testar
  if (configura) {
    matrizFios[0] = !digitalRead(2);
    matrizFios[1] = !digitalRead(3);
    matrizFios[2] = !digitalRead(4);
    matrizFios[3] = !digitalRead(5);
    matrizFios[4] = !digitalRead(6);
    matrizFios[5] = !digitalRead(7);

    matriz = 0;
    bitWrite(matriz, 0, matrizFios[0]);
    bitWrite(matriz, 1, matrizFios[1]);
    bitWrite(matriz, 2, matrizFios[2]);
    bitWrite(matriz, 3, matrizFios[3]);
    bitWrite(matriz, 4, matrizFios[4]);
    bitWrite(matriz, 5, matrizFios[5]);

    EEPROM.update(420, matriz);
  } else {
    matriz = EEPROM.read(420);
    matrizFios[0] = bitRead(matriz, 0);
    matrizFios[1] = bitRead(matriz, 1);
    matrizFios[2] = bitRead(matriz, 2);
    matrizFios[3] = bitRead(matriz, 3);
    matrizFios[4] = bitRead(matriz, 4);
    matrizFios[5] = bitRead(matriz, 5);
  }

  //Mostra que o setup terminou acendendo o LED verde
  digitalWrite(A1, HIGH);
  while (!digitalRead(A0));
}

void loop() {
  unsigned long delayTeste;
  unsigned long delayPisca;
  bool par = 1;
  bool teste[5];

  if (!digitalRead(A0)) {

    digitalWrite(A1, LOW);
    teste[0] = LOW;
    teste[1] = LOW;
    teste[2] = LOW;
    teste[3] = LOW;
    teste[4] = LOW;
    teste[5] = LOW;

    delayTeste = millis();
    while ((millis() - delayTeste) < 4000) {

      if ((millis() - delayPisca) > 100) {
        delayPisca = millis();
        if (par) {
          digitalWrite(8, HIGH);
          digitalWrite(9, LOW);
          digitalWrite(10, LOW);
          digitalWrite(11, HIGH);
          digitalWrite(12, HIGH);
          digitalWrite(13, LOW);
          par = 0;
        } else {
          digitalWrite(8, LOW);
          digitalWrite(9, HIGH);
          digitalWrite(10, HIGH);
          digitalWrite(11, LOW);
          digitalWrite(12, LOW);
          digitalWrite(13, HIGH);
          par = 1;
        }
      }

      if (digitalRead(2)) teste[0] = HIGH;
      if (digitalRead(3)) teste[1] = HIGH;
      if (digitalRead(4)) teste[2] = HIGH;
      if (digitalRead(5)) teste[3] = HIGH;
      if (digitalRead(6)) teste[4] = HIGH;
      if (digitalRead(7)) teste[5] = HIGH;
      //delay(10);
    }

    digitalWrite(8, teste[0] && matrizFios[0]);
    digitalWrite(9, teste[1] && matrizFios[1]);
    digitalWrite(10, teste[2] && matrizFios[2]);
    digitalWrite(11, teste[3] && matrizFios[3]);
    digitalWrite(12, teste[4] && matrizFios[4]);
    digitalWrite(13, teste[5] && matrizFios[5]);

    digitalWrite(A1, !(teste[0] && matrizFios[0]) && !(teste[1] && matrizFios[1]) && !(teste[2] && matrizFios[2]) && !(teste[3] && matrizFios[3]) && !(teste[4] && matrizFios[4]) && !(teste[5] && matrizFios[5]));
  }

  //delay(10);
}
