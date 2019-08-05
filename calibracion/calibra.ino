/*
 * Toma muestras del sensor de humedad
 * Està conectado a la entrada A0
 */

// YL-38 sensor de humedad
byte SensorSalidaAnalogica = A0;
byte AlimentacionSensor    = 5;      //D1

#define NUM_MUESTRAS 100
unsigned long i = 0, valor, acum = 0, maxi = 0, mini = 10000;

unsigned int leeSensor(){
  digitalWrite(AlimentacionSensor, HIGH);
  delay(100); // Espero un poquito
  valor = analogRead(SensorSalidaAnalogica);
  digitalWrite(AlimentacionSensor, LOW);
  return valor;
}

void setup() {
  Serial.begin(115200);
  pinMode(AlimentacionSensor, OUTPUT);
}

void loop() {
  if(i == NUM_MUESTRAS){
    Serial.printf("Valor medio: %3d. Máx: %ld. Mín: %ld %\n", acum/i, maxi, mini);
    acum = 0; maxi = 0; mini = 10000; i = 0;
  }
  valor = leeSensor();
  acum += valor;
  if(valor > maxi) maxi = valor;
  if(valor < mini) mini = valor;
  i++;
  Serial.printf("Muestra %03ld: %ld\n" , i, valor);
  delay(400);
}
