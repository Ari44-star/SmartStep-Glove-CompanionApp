/* Proyecto: SmartStep - Guante Sensorial */
/* Autor: Ariatna Deloya Quiñones */
/* Descripción: Control de sensor HC-SR04 y motor vibrador */

int vibrador = 3;  // Pin D3 para el motor 
int echo = 11;     // Pin D11 para el cable azul
int trig = 12;     // Pin D12 para el cable amarillo

long duracion;     // Variable para el tiempo del pulso
int distancia;     // Variable para la distancia en cm

void setup() {
  pinMode(vibrador, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  
  // Iniciamos el monitor serie para ver los datos en la PC
  Serial.begin(9600); 
}

void loop() {
  // Limpiamos el pin del trigger
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  
  // Enviamos el pulso ultrasónico de 10 microsegundos
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  // Medimos cuánto tarda en regresar el eco
  duracion = pulseIn(echo, HIGH);
  
  // Calculamos la distancia en centímetros
  distancia = duracion / 58.2;

  // Imprimimos la distancia en el monitor serie para que la veas en la laptop
  Serial.print("Distancia detectada: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Lógica de vibración según tu diseño original
  if (distancia < 100 && distancia > 50) {
    // Vibración media (140 de fuerza) si está lejos
    analogWrite(vibrador, 140);
  }
  else if (distancia <= 50 && distancia > 0) {
    // Vibración máxima (255 de fuerza) si está muy cerca
    analogWrite(vibrador, 255);
  }
  else {
    // Apagado si no hay nada en el rango
    analogWrite(vibrador, 0);
  }

  delay(100); // Pausa para estabilidad
  }
}
