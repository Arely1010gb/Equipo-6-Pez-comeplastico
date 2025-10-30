# Proyecto Pez Comeplástico con Arduino

#### 📘 Descripción del proyecto
El Pez Comeplástico es un robot educativo inspirado en la idea de un pez que detecta y “come” desechos plásticos mediante sensores ultrasónicos y un servo que simula la boca.

Su objetivo es concientizar sobre la contaminación marina y demostrar el uso de sensores, servos y controladores en un proyecto de robótica con Arduino.

Este proyecto detecta obstáculos y objetos cercanos, se mueve de forma autónoma evitando colisiones, y activa un servo para simular que “mastica” cuando un objeto se aproxima a su boca.

#### ⚙️ Requisitos e instalación
##### 🧩 Hardware necesario
- 1 × Arduino UNO (o Nano)
- 5 × Sensores ultrasónicos HC-SR04
- Frontal, Izquierdo, Derecho, Trasero y Boca
- 3 × Motores DC
- 1 × Módulo de control de motores (puede ser puente H o transistores)
- 1 × Servo motor SG90 (para la boca)
- Protoboard y cables Dupont
- Fuente de alimentación de 5V (baterías o adaptador)

##### 💻 Software necesario
- Arduino IDE (versión 1.8 o superior)
- Librería estándar Servo.h (ya incluida en el IDE)
- Cable USB-B para subir el código

##### 🔧 Instalación
1. Descarga o clona este repositorio:
   
 ```bash  
 git clone https://github.com/Arely1010gb/Equipo-6-Pez-comeplastico.git
 ```

1. Abre el archivo pez_comeplastico.ino en el Arduino IDE.
1. Selecciona tu placa y puerto:
1. Placa: Arduino UNO
1. Puerto: COMx (dependiendo de tu sistema)
1. Carga el código en el Arduino con el botón Subir (Upload).
1. Conecta los sensores y motores según el diagrama de pines mostrado abajo.

##### ▶️ Cómo usarlo
1. Coloca el robot en una superficie libre de obstáculos.
1. Enciende la alimentación del Arduino y los motores.
1. El pez comenzará a moverse hacia adelante evitando obstáculos:
1. Si detecta un objeto al frente, gira o retrocede.
1. Si detecta algo cerca de su “boca” (sensor frontal pequeño), cerrará la boca (servo) durante unos segundos simulando que “come”.
1. Puedes observar los valores de los sensores abriendo el Monitor Serial

##### 🧠 Comportamientos principales

Sensor  | Función | Acción
------------- | ------------- | -------------
Frontal  | Detecta obstáculos frontales | Detiene o gira
Izquierdo/Derecho  | Evita choques laterales | Gira al lado opuesto
Trasero  | Evita retrocesos peligrosos | Avanza
Boca | Detecta objetos pequeños cercanos | Activa servo (masticar)

##### 📁 Estructura del proyecto
pez-comeplastico/ 

│ 

├── README.md # Documentación del proyecto 

├── main.ino # Código fuente principal 

├── /diagramas # Diagramas de arquitectura y flujo

│    ├── esquematico1.png 

|    |── esquematico2.png

│    └── diagrama-bloques.png 


##### 🧩 Arquitectura del sistema
El sistema del Pez Comeplástico está conformado por tres módulos principales: sensores, unidad de control y actuadores.

###### Módulo de sensores:
Está compuesto por cinco sensores ultrasónicos HC-SR04 colocados alrededor del robot (frontal, izquierdo, derecho, trasero y boca).
Su función es medir la distancia con los objetos cercanos y enviar esta información al Arduino en forma de señales digitales.

###### Módulo de control (Arduino UNO):
Es el cerebro del sistema. Recibe las lecturas de los sensores, analiza la información y decide las acciones que debe realizar el robot.
A partir de la lógica del programa, el Arduino determina si debe avanzar, girar, retroceder o detenerse.
Además, controla el movimiento del servo para abrir o cerrar la boca cuando detecta un objeto muy cerca.

###### Módulo de actuadores:
Incluye tres motores DC que permiten el movimiento del robot (adelante, atrás, izquierda o derecha) y un servo motor SG90 encargado de simular la apertura y cierre de la boca.
Los motores están conectados a pines analógicos (A0, A1, A2) y se controlan con señales digitales.
El servo se conecta al pin 12 y se maneja mediante la librería Servo.h.

###### En conjunto, el flujo de funcionamiento es el siguiente: 
Los sensores detectan distancias → el Arduino procesa la información y toma decisiones → los motores y el servo ejecutan las acciones correspondientes.
De esta forma, el robot puede desplazarse de manera autónoma y reaccionar ante los objetos que se acercan, imitando el comportamiento de un pez que “come” plástico.

##### 🔄 Diagrama de secuencia (boca)
Objeto detectado → Sensor Boca → Arduino → Servo → Cierra boca → Espera → Abre boca

##### 🧠 Resumen técnico del sistema
- Control principal con Arduino UNO.
- 5 sensores ultrasónicos miden distancias.
- Motores controlados por pines digitales (A0–A2).
- Servo controlado con la librería Servo.h.
- Lógica de movimiento basada en umbrales de distancia (UMBRAL = 10 cm).
- Evita bloqueos con un control no bloqueante (millis()) para el servo.

##### 🪜 Guía paso a paso de instalación
1. Conecta todos los sensores según el código (trig y echo por pin).
1. Conecta los motores DC a los pines A0, A1, A2.
1. Conecta el servo al pin 12.
1. Sube el programa al Arduino.
1. Alimenta el sistema con una fuente estable de 5 V.
1. Observa el comportamiento en el monitor serial (opcional).

##### ❓ FAQ
1. ######  ¿Qué pasa si el pez no se mueve?
Verifica las conexiones de los motores y asegúrate de tener una fuente suficiente.

1. ###### El servo no se mueve.
Revisa la conexión al pin 12 y que el servo no esté dañado o atascado.

1. ###### Los sensores marcan “200 cm” siempre.
Esto indica que no están recibiendo eco (mal conectados o dañados). 

1.  ###### ¿Puedo agregar más funciones?
Sí. Puedes integrar sensores de color o cámaras para detectar plásticos reales.
