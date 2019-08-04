# Humedad suelo
Medida de la humedad del suelo y envío a domoticz  

## Materiales
- 1 x ESP8266
- 1 X HD-38. Transcuctor capacitivo.
- 1 SIP 1A05. Relé reed

## Principales características
Mide la humedad del suelo mediante una sonda y envía los datos recogidos a domoticz en mini

Se monta sobre un dispositivo dotado de batería y placa solar. Es autónomo.  
Para ahorrar energía, el ESP entra en deep sleep una vez obtenida la muestra y enviado los datos.  
El transductor sólo se alimenta eléctricamente si el ESP está activo. La alimentación se hace mediante un relé reed (SIP 1A05) de bajo consumo.

De momento en prototipo
