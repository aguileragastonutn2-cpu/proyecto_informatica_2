#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trig[4] = {2, 4, 6, 8};
const int echo[4] = {3, 5, 7, 9};
const int pinServo[4] = {10, 11, 12, 13};

Servo valvulas[4];

const float distanciaVacio = 20.0;
const float distanciaLleno = 2.0;
const float umbral = 90.0;

const int ABIERTO = 90;
const int CERRADO = 0;

float niveles[4];
bool tanqueLleno[4] = {false, false, false, false};

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  pinMode(A0, OUTPUT);

pinMode(A1, INPUT_PULLUP);

  for (int i = 0; i < 4; i++) {
    pinMode(trig[i], OUTPUT);
    pinMode(echo[i], INPUT);

    valvulas[i].attach(pinServo[i]);
    valvulas[i].write(ABIERTO);
  }
}

void loop() {
  if (digitalRead(A1) == LOW) {
  for (int i = 0; i < 4; i++) {
    tanqueLleno[i] = false;
    valvulas[i].write(ABIERTO);
  }

  delay(300);
}
  int llenos = 0;

  for (int i = 0; i < 4; i++) {
    digitalWrite(trig[i], LOW);
    delayMicroseconds(2);
    digitalWrite(trig[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(trig[i], LOW);

    long tiempo = pulseIn(echo[i], HIGH, 30000);

    if (tiempo == 0) {
      niveles[i] = -1;
      valvulas[i].write(CERRADO);
    } else {
      float distancia = tiempo * 0.0343 / 2;

      niveles[i] = constrain(
        (distanciaVacio - distancia) /
        (distanciaVacio - distanciaLleno) * 100,
        0, 100
      );

      if (niveles[i] >= umbral) {
        tanqueLleno[i] = true;
        valvulas[i].write(CERRADO);
      }
    }

    if (tanqueLleno[i]) {
      llenos++;
    }
  }

digitalWrite(A0, llenos < 4 ? HIGH : LOW);



  for (int i = 0; i < 4; i += 2) {
    lcd.clear();

    for (int j = 0; j < 2; j++) {
      int t = i + j;

      lcd.setCursor(0, j);
      lcd.print("T");
      lcd.print(t + 1);
      lcd.print(":");

      if (niveles[t] < 0) {
        lcd.print(" ERROR");
      } else {
        lcd.print(niveles[t], 0);
        lcd.print("% ");
        lcd.print(tanqueLleno[t] ? "CERRADA" : "ABIERTA");
      }
    }

    delay(1200);
  }

  Serial.print("Tanques llenos: ");
  Serial.println(llenos);
}
