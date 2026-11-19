#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Tanque.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

Tanque tanque1(2, 3, 10);
Tanque tanque2(4, 5, 11);
Tanque tanque3(6, 7, 12);
Tanque tanque4(8, 9, 13);

Tanque* tanques[4] = {
  &tanque1, &tanque2, &tanque3, &tanque4
};

const float DISTANCIA_VACIO = 20.0;
const float DISTANCIA_LLENO = 2.0;
const float UMBRAL = 90.0;

enum EstadoSistema {
  LLENANDO,
  LLENADO_PARCIAL,
  COMPLETO,
  FALLA_SENSOR
};

EstadoSistema estadoActual;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  pinMode(A0, OUTPUT);
  pinMode(A1, INPUT_PULLUP);

  for (int i = 0; i < 4; i++) {
    tanques[i]->iniciar();
  }
}

void loop() {
  if (digitalRead(A1) == LOW) {
    for (int i = 0; i < 4; i++) {
      tanques[i]->reiniciar();
    }
    delay(300);
  }

  int llenos = 0;
bool fallaSensor = false;
  for (int i = 0; i < 4; i++) {
    tanques[i]->medirNivel(
      DISTANCIA_VACIO, DISTANCIA_LLENO
    );

    tanques[i]->actualizarEstado(UMBRAL);

 if (tanques[i]->estaLleno()) {
  llenos++;
}

if (!tanques[i]->lecturaCorrecta()) {
  fallaSensor = true;
}
  }

  digitalWrite(A0, (!fallaSensor && llenos < 4) ? HIGH : LOW);

  if (fallaSensor) {
  estadoActual = FALLA_SENSOR;
} else if (llenos == 4) {
  estadoActual = COMPLETO;
} else if (llenos > 0) {
  estadoActual = LLENADO_PARCIAL;
} else {
  estadoActual = LLENANDO;
}

Serial.print("Estado del sistema: ");

switch (estadoActual) {
  case LLENANDO:
    Serial.println("LLENANDO");
    break;

  case LLENADO_PARCIAL:
    Serial.println("LLENADO PARCIAL");
    break;

  case COMPLETO:
    Serial.println("COMPLETO");
    break;

  case FALLA_SENSOR:
    Serial.println("FALLA SENSOR");
    break;
}

Serial.print("NIVELES,");

for (int i = 0; i < 4; i++) {
  Serial.print(tanques[i]->obtenerNivel());

  if (i < 3) {
    Serial.print(",");
  }
}

Serial.println();

  for (int i = 0; i < 4; i += 2) {
    lcd.clear();

    for (int j = 0; j < 2; j++) {
      int t = i + j;

      lcd.setCursor(0, j);
      lcd.print("T");
      lcd.print(t + 1);
      lcd.print(":");

      if (!tanques[t]->lecturaCorrecta()) {
        lcd.print(" ERROR");
      } else {
        lcd.print(tanques[t]->obtenerNivel(), 0);
        lcd.print("% ");
        lcd.print(tanques[t]->estaLleno()
                  ? "CERRADA" : "ABIERTA");
      }
    }

    delay(1200);
  }

  Serial.print("Tanques llenos: ");
  Serial.println(llenos);
}
