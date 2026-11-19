
#ifndef TANQUE_H
#define TANQUE_H

#include <Arduino.h>
#include <Servo.h>

class Tanque {
  private:
    int pinTrig;
    int pinEcho;
    int pinServo;

    Servo valvula;
    float nivel;
    bool lleno;
    bool lecturaValida;

  public:
    Tanque(int trig, int echo, int servo);

    void iniciar();
    float medirNivel(float distanciaVacio, float distanciaLleno);
    void actualizarEstado(float umbral);
    void reiniciar();

    float obtenerNivel();
    bool estaLleno();
    bool lecturaCorrecta();
};

#endif
