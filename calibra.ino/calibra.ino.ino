/*
 * Toma muestras del sensor de humedad
 * Està conectado a la entrada A0
 */

// YD-38 sensor de humedad
byte humidity_sensor_pin = A0;

#define NUM_MUESTRAS 100
unsigned long i = 0, valor, acum = 0, maxi = 0, mini = 10000;

void setup() {
  Serial.begin(115200);
}

void loop() {
  if(i == NUM_MUESTRAS){
    Serial.printf("Valor medio: %3d. Máx: %ld. Mín: %ld %\n", acum/i, maxi, mini);
    acum = 0; maxi = 0; mini = 10000; i = 0;
  }
  valor = analogRead(humidity_sensor_pin);
  acum += valor;
  if(valor > maxi) maxi = valor;
  if(valor < mini) mini = valor;
  i++;
  //Serial.printf("Muestra %03ld: %3ld - %3ld\n" , i, valor, acum/i);
  delay(500);
}
