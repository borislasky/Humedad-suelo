#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

                      
// Datos de conexión a WiFi
WiFiClient   InternetClient;
int status = WL_IDLE_STATUS;     // the starting Wifi radio's status
const char*  WIFI_SSID      = "AndroidAP";
const char*  WIFI_PASSWORD  = "boris123";

// Datos conexión http
HTTPClient http;
const char* urlNodeRedPre  = "http://192.168.43.212:1880/datosHumedad/?idsonda=0&valor=";
const char* urlDomoticzPre = "http://192.168.43.212:8084/json.htm?type=command&param=udevice&idx=";
const char* urlDomoticzSuf = "&svalue=0&nvalue=";

// YD-38 sensor de humedad
byte humidity_sensor_pin = A0;

const int NumMuestras = 25;
const unsigned long t = 15 * 60 * 1000 * 1000; //  Cada cuanto tomo muestra. en micro segundos 

// Valores leido cuando la sonda está seca y mojada
const int seco   = 550; // => 0%
const int mojado =  300; // => 100%
const float factor = 100.0 / float(seco - mojado);

char urlDomoticz[100];


void ini_WIFI() {
  int cont = 0;
  delay(100);
  Serial.print("Conectando a ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    cont++;
    if(cont==15){ // si no conecta pasados 15 intentos reboto
      Serial.println();
      Serial.print("No consigo conectar con ");
      Serial.print(WIFI_SSID);
      Serial.println(" Reboto");
      ESP.restart(); // si no consigo conectar reboto
    }
  }
  Serial.println("");
  Serial.print("WiFi conectada a ");
  Serial.print(WIFI_SSID);
  Serial.print(" - dirección IP: ");
  Serial.println(WiFi.localIP());
}

void llamaAPI(char* url){
  if (http.begin(url)) //Iniciar conexión
    Serial.println(url);
    for(int i=0; i<10; i++){ // pruebo hasta 10 veces
      int ret = http.GET(); // Realizar petición
      Serial.println(ret);
      if(ret == 200) break;
    }
}


int read_humidity_sensor() {
  int value = analogRead(humidity_sensor_pin);
  Serial.print(value);
  Serial.print(" - ");
  return round(float(seco - value) * factor);
}


void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Buenos días !");

  // Inicialización WiFi
  ini_WIFI();

    // tomo NumMuestras
  int n = 0;
  int humedad, Acum = 0;
  while(n < NumMuestras){
    humedad = read_humidity_sensor();
    Serial.println(humedad);
    Acum += humedad;
    n++;
    delay(50);
  }
  int humMedia = Acum / NumMuestras;
  
  // Llamada a domoticz
  Serial.println(humMedia);
  sprintf(urlDomoticz, "%s%d%s%d", urlDomoticzPre, 22, urlDomoticzSuf, humMedia);
  llamaAPI(urlDomoticz);

  Serial.println("Me voy a dormir");
  ESP.deepSleep(t, WAKE_RFCAL);

}

void loop() {

}
