# Humedad suelo
Medida de la humedad del suelo y envío a domoticz  

## Materiales
- 1 x ESP8266
- 1 X YL-38. Transcuctor capacitivo.

## Principales características
Mide la humedad del suelo mediante una sonda y envía los datos recogidos a domoticz en mini.  
La medición de humedad es la media de las N medidas consecutivas. Se observa que las medidas individuales son muy variables. De hecho, variaciones muy grandes. Se toman 20 muestras y se calcula la media. Este valor es el que se envía.

Se monta sobre un dispositivo dotado de batería y placa solar. Es autónomo.  
Para ahorrar energía, el ESP entra en deep sleep una vez obtenida la muestra y enviado los datos.  
El transductor sólo se alimenta eléctricamente cuando vaya a tomar una muestra. Activo una salida digital que es la que alimenta dicho transductor.

De momento en prototipo

## Calibración
Se puede utilzar el sketch calibra/calibra.ino para obtner los valores de seco y mojado. Éste toma series de 1000 muestras y pinta los resultados.

### HD-38
No sé la razón pero, si actúo sobre el potenciometro de la placa afecta le valor analógico de salida.  
Para obtener los valores, situo el potenciómetro en un punto medio (más o menos).
Si lo sitúo a tope de sentido horario, la medida es siempre **1024**, en seco o mojado.  
Si lo sitúo a tope en sentido antihorario, la medida es siempre **3**, en seco o mojado.  
Teóricamente, solo debería afectar al valor de disparo de la salida digital. De hecho, el led que indica la salida digital siempre está encendido.

### YL-38
Este parece que funciona bien. La salida digital se activa dependiendo de la posición del potenciómetro y la salida analógica no varía actuando sobre el mismo. Decido emplear éste.

### Seco
Para seco, dejar la sonda al aire. El valor observado es de **Vseco = 1024**

### Mojado.
Para mojado, introducir la sonda en agua. El valor observado es de **Vmojado = 240**

### Valor en %
Supongo que el valor devuelto es lineal respecto al valor devuelto por la sonda.

factor = 100.0 / float(Vseco - Vmojado);  
valorPerc = round(float(Vseco - valor) * factor);
