# Humedad suelo
Medida de la humedad del suelo y envío a domoticz  

## Materiales
- 1 x ESP8266
- 1 X HD-38. Transcuctor capacitivo.
- 1 SIP 1A05. Relé reed

## Principales características
Mide la humedad del suelo mediante una sonda y envía los datos recogidos a domoticz en mini.  
La medición de humedad es la media de las N medidas consecutivas. Se observa que las medidas individuales son muy variables. De hecho, variaciones muy grandes. Se toman 20 muestras y se calcula la media. Este valor es el que se envía.

Para la calibración de la sonda se siguen los siguientes pasos:  
1.- Tomar n muestras con la sonda al aire. Esto marcará el valor de 0% humedad.  
2.- Tomar n muestras con la sonda sumergida en agua. Esto marcará el valor 100%.  

Se monta sobre un dispositivo dotado de batería y placa solar. Es autónomo.  
Para ahorrar energía, el ESP entra en deep sleep una vez obtenida la muestra y enviado los datos.  
El transductor sólo se alimenta eléctricamente si el ESP está activo. La alimentación se hace mediante un relé reed (SIP 1A05) de bajo consumo.

De momento en prototipo

## Calibración
Se puede utilzar el scketch calib
