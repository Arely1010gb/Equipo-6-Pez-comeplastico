#include <Servo.h>

// Pines sensores ultrasónicos
#define trigFront 2
#define echoFront 3
#define trigLeft 6
#define echoLeft 7
#define trigRight 8
#define echoRight 9
#define trigBack 4
#define echoBack 5
#define trigMouth 10
#define echoMouth 11

// Pines motores
#define motorLeft A0   // motor izquierdo
#define motorRight A1  // motor derecho
#define motorFront A2  // motor frontal/reversa

// Servo 
Servo mouthServo;
#define servoPin 12

// Variables 
int distFront, distLeft, distRight, distBack, distMouth;
bool bocaCerrando = false;
unsigned long tiempoInicioBoca = 0;

// Función para medir distancia (HC-SR04)
int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 25000); // timeout 25 ms
  int distance = duration * 0.034 / 2;
  if (distance == 0 || distance > 200) distance = 200; // filtrar lecturas falsas
  return distance;
}

// Acciones (enciende/apaga motores)
void moveForward() {
  digitalWrite(motorFront, LOW);   // apagar reversa
  digitalWrite(motorLeft, HIGH);
  digitalWrite(motorRight, HIGH);
}
void turnLeft() {
  digitalWrite(motorFront, LOW);
  digitalWrite(motorLeft, LOW);
  digitalWrite(motorRight, HIGH);  // empuja a la izquierda
}
void turnRight() {
  digitalWrite(motorFront, LOW);
  digitalWrite(motorLeft, HIGH);   // empuja a la derecha
  digitalWrite(motorRight, LOW);
}
void moveBackward() {
  digitalWrite(motorLeft, LOW);
  digitalWrite(motorRight, LOW);
  digitalWrite(motorFront, HIGH);  // retrocede
}
void stopAll() {
  digitalWrite(motorLeft, LOW);
  digitalWrite(motorRight, LOW);
  digitalWrite(motorFront, LOW);
}

// ---------- Setup ----------
void setup() {
  Serial.begin(9600);

  // Sensores
  pinMode(trigFront, OUTPUT); pinMode(echoFront, INPUT);
  pinMode(trigLeft, OUTPUT);  pinMode(echoLeft, INPUT);
  pinMode(trigRight, OUTPUT); pinMode(echoRight, INPUT);
  pinMode(trigBack, OUTPUT);  pinMode(echoBack, INPUT);
  pinMode(trigMouth, OUTPUT); pinMode(echoMouth, INPUT);

  // Motores
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
  pinMode(motorFront, OUTPUT);

  // Servo
  mouthServo.attach(servoPin);
  mouthServo.write(90); // boca abierta por defecto
}

// ---------- Loop ----------
void loop() {
  const int UMBRAL = 10; // umbral de distancia en cm

  // Leer sensores
  distFront = getDistance(trigFront, echoFront);
  distLeft  = getDistance(trigLeft, echoLeft);
  distRight = getDistance(trigRight, echoRight);
  distBack  = getDistance(trigBack, echoBack);
  distMouth = getDistance(trigMouth, echoMouth);

  Serial.print("F:"); Serial.print(distFront);
  Serial.print(" L:"); Serial.print(distLeft);
  Serial.print(" R:"); Serial.print(distRight);
  Serial.print(" Bk:"); Serial.print(distBack);
  Serial.print(" M:"); Serial.println(distMouth);

  // Movimiento
  if (distFront < UMBRAL) {
    stopAll();
    delay(50);

    if (distLeft < UMBRAL && distRight < UMBRAL) {
      if (distBack > UMBRAL) {
        moveBackward();
        delay(700);
      } else {
        stopAll();
        delay(300);
      }
    } else {
      if (distRight < UMBRAL) {
        turnLeft();
        delay(500);
      } else if (distLeft < UMBRAL) {
        turnRight();
        delay(500);
      } else {
        turnRight();
        delay(400);
      }
    }
  } else if (distBack < UMBRAL) {
    moveForward();
  } else {
    moveForward();
  }

  // --- Control no bloqueante del servo (boca) ---
  unsigned long ahora = millis();
  if (distMouth < 5 && !bocaCerrando) {
    mouthServo.write(0);          // cierra boca
    bocaCerrando = true;
    tiempoInicioBoca = ahora;
  }
  if (bocaCerrando && (ahora - tiempoInicioBoca > 700)) {
    mouthServo.write(90);         // abre boca
    bocaCerrando = false;
  }

  delay(100);
}

