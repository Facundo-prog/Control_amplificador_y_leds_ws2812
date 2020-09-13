# Control de audio, amplificador y leds ws2812b
## Autor: Facundo Carroz

### Consta de dos librerias independientes, una para el control de un amplificador y otra para la lectura de audio. Tambien se incluye un paquete de librerias que contiene todos los efectos de luz. Diseñado para Arduino Uno, Mega y otros similares que funcionen a una frecuencia de 16Mhz. 

## Libreria AudioControl
- El codigo se encarga de analizar el audio
- Puede detectar la ausencia de audio 
- Permite setear diversos parametros de configuracion

## Libreria AmplifiedControl 
- Pude activar el pin mute/stand by de un amplificador
- Tambien puede controlar un ventilador para el amplificador
- Permite medir temperatura a travez de un sensor LM35
- Permite setear multiples parametros

## Paquete de librerias Effects
- Consta de 8 librerias que controlan los leds formando distintos efectos de luz
- Cada libreria puede controlar leds ws2812/ws2812b, adaptandose a la cantidad de leds y sincronizados con el audio
- Estan configuradas para un maximo de **500** leds por instancia
- Cada una se puede configurar de forma diferente 

## Dependencias
- El paquete Effects depende de la libreria **Adafruit_NeoPixel** para el control de los leds, la misma tiene que estar instalada en el equipo

## Algunos efectos de luz
![Imagen de tira led ws2812b](https://github.com/Facundo-prog/Control_Amplificador_con_Luces/blob/master/images/img_1.jpg)
![Imagen de tira led ws2812b](https://github.com/Facundo-prog/Control_Amplificador_con_Luces/blob/master/images/img_2.jpg)
![Imagen de tira led ws2812b](https://github.com/Facundo-prog/Control_Amplificador_con_Luces/blob/master/images/img_3.jpg)
