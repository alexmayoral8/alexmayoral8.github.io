#include <Stepper.h>

int stepsPerRevolution = 2048;  // Ajusta según tu motor
int motSpeed = 15;
int flexiones = 3250;

int botonPin = 2;  // Pin donde conectas el botón
bool botonPrevio = HIGH; // Estado previo del botón (INPUT_PULLUP)
unsigned long ultimoTiempo = 0;
unsigned long debounce = 200; // 200 ms de anti-rebote

Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11); //(steps,IN1,IN3,IN2,IN4)

void setup() {
  Serial.begin(9600);
  pinMode(botonPin, INPUT_PULLUP);  // Botón conectado a GND
  myStepper.setSpeed(motSpeed);
  Serial.println("Presiona el botón para iniciar la secuencia...");
}

void loop() {
  bool botonActual = digitalRead(botonPin);

  // Detecta flanco descendente con anti-rebote
  if (botonPrevio == HIGH && botonActual == LOW && (millis() - ultimoTiempo) > debounce) {
    ultimoTiempo = millis(); // Actualiza tiempo para anti-rebote
    Serial.println("Iniciando secuencia...");

    myStepper.step(200); 
    delay(100);
    
    for (int i = 0; i < flexiones; i++) {
      Serial.print("Flexión número: ");
      Serial.println(i + 1);
      myStepper.step(-400);   // Aproximadamente 30 grados adelante 
      delay(100);            // Pausa opcional
      myStepper.step(400);  // Aproximadamente 30 grados atrás 
      delay(100);            // Pausa opcional
    }

    Serial.println("Secuencia completada. Presiona el botón para repetir.");
  }

  botonPrevio = botonActual; // Guarda el estado actual para la próxima lectura
}
