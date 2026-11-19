class Tanque {
  int x, y;
  float nivel;
  boolean valvulaAbierta;
  boolean detenidoManual;
  int numero;

  Tanque(int n, int posX, int posY) {
    numero = n;
    x = posX;
    y = posY;
    nivel = 0;
    valvulaAbierta = true;
    detenidoManual = false;
  }

  void actualizar(float nuevoNivel) {
    nivel = constrain(nuevoNivel, 0, 100);
  }

  void mostrar() {
    fill(255);
    textAlign(CENTER);
    textSize(18);
    text("TANQUE " + numero, x + 50, y - 15);
   if (detenidoManual) {
  fill(255, 80, 80);
  text("VALVULA CERRADA", x + 50, y + 250);
} else if (valvulaAbierta) {
  if (frameCount % 60 < 30) {
    fill(100, 255, 100);
  } else {
    fill(40, 120, 60);
  }
  text("VALVULA ABIERTA", x + 50, y + 250);
} else {
  fill(255, 80, 80);
  text("VALVULA CERRADA", x + 50, y + 250);
}

    noFill();
    stroke(255);
    strokeWeight(2);
    rect(x, y, 100, 200);

    float altura = map(nivel, 0, 100, 0, 200);

    noStroke();
    fill(30, 150, 230);
    rect(x + 3, y + 200 - altura, 94, altura);

    fill(255);
    textSize(16);
    text(int(nivel) + "%", x + 50, y + 225);
    
    if (detenidoManual) {
  fill(180, 30, 30);
  text("REANUDAR", x + 50, y + 285);
} else {
  fill(220, 50, 50);
  text("DETENER", x + 50, y + 285);
}
  }
  void presionar(int mouseX, int mouseY) {
  if (mouseX >= x && mouseX <= x + 100 &&
      mouseY >= y + 265 && mouseY <= y + 300) {

    detenidoManual = !detenidoManual;
  }
}
}
