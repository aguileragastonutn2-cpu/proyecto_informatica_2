
#include "Tanque.h"

const int VALVULA_ABIERTA = 90;
const int VALVULA_CERRADA = 0;

Tanque::Tanque(int trig, int echo, int servo) {
  pinTrig = trig;
  pinEcho = echo;
  pinServo = servo;
  nivel = 0;
  lleno = false;
  lecturaValida = false;
}

void Tanque::iniciar() {
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);

  valvula.attach(pinServo);
  valvula.write(VALVULA_ABIERTA);
}

float Tanque::medirNivel(float distanciaVacio, float distanciaLleno) {
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);

  long tiempo = pulseIn(pinEcho, HIGH, 30000);

  if (tiempo == 0) {
    lecturaValida = false;
    nivel = -1;
    return nivel;
  }

  float distancia = tiempo * 0.0343 / 2;

  nivel = (distanciaVacio - distancia) /
          (distanciaVacio - distanciaLleno) * 100;

  nivel = constrain(nivel, 0, 100);
  lecturaValida = true;

  return nivel;
}

void Tanque::actualizarEstado(float umbral) {
  if (!lecturaValida) {
    valvula.write(VALVULA_CERRADA);
    return;
  }

  if (nivel >= umbral) {
    lleno = true;
    valvula.write(VALVULA_CERRADA);
  }
}

void Tanque::reiniciar() {
  lleno = false;
  nivel = 0;
  lecturaValida = false;
  valvula.write(VALVULA_ABIERTA);
}

float Tanque::obtenerNivel() {
  return nivel;
}

bool Tanque::estaLleno() {
  return lleno;
}

bool Tanque::lecturaCorrecta() {
  return lecturaValida;
}
