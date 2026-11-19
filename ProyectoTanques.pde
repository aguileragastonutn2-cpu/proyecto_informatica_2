import processing.serial.*;
Tanque[] tanques = new Tanque[4];
Serial puerto;
String estadoSistema = "ESPERANDO DATOS";
void setup() {
  println(Serial.list());
    puerto = new Serial(this, "COM5", 9600);
  puerto.bufferUntil('\n');
  size(800, 500);

 tanques[0] = new Tanque(1, 70, 120);
tanques[1] = new Tanque(2, 250, 120);
tanques[2] = new Tanque(3, 430, 120);
tanques[3] = new Tanque(4, 610, 120);


}

void draw() {
  background(35, 40, 50);

  fill(255);
  textAlign(CENTER);
  textSize(26);
  text("SISTEMA DE CONTROL DE TANQUES", width/2, 50);

  for (int i = 0; i < 4; i++) {
    tanques[i].mostrar();
  }

  fill(100, 255, 100);
textSize(20);
textAlign(CENTER);
text("SISTEMA: " + estadoSistema, width/2, 440);

if (frameCount % 60 < 30) {
  ellipse(width/2, 465, 14, 14);
}
}
void mousePressed() {
  for (int i = 0; i < 4; i++) {
    boolean estabaDetenido = tanques[i].detenidoManual;

    tanques[i].presionar(mouseX, mouseY);

    if (puerto != null && estabaDetenido != tanques[i].detenidoManual) {
      if (tanques[i].detenidoManual) {
        puerto.write("DETENER," + (i + 1) + "\n");
      } else {
        puerto.write("REANUDAR," + (i + 1) + "\n");
      }
    }
  }
}
void serialEvent(Serial puertoActual) {
  String linea = puertoActual.readStringUntil('\n');

  if (linea != null) {
    linea = trim(linea);

    if (linea.startsWith("DATA,")) {
      String[] datos = split(linea, ',');

      if (datos.length == 6) {
        for (int i = 0; i < 4; i++) {
          float nivel = float(datos[i + 1]);
          tanques[i].actualizar(nivel);
        }

        int estado = int(datos[5]);

        switch (estado) {
          case 0:
            estadoSistema = "LLENANDO";
            break;
          case 1:
            estadoSistema = "LLENADO PARCIAL";
            break;
          case 2:
            estadoSistema = "COMPLETO";
            break;
          case 3:
            estadoSistema = "FALLA SENSOR";
            break;
        }
      }
    }
    else if (linea.startsWith("RECIBIDO,")) {
  println(linea);
}
  }
}
