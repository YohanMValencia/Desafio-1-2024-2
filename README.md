![image](https://github.com/user-attachments/assets/8e0c8146-adc0-45d2-9c20-57b245a8ee5a)
# Desafio-1-2024-2
### Semestre 2024 – 2, Desafío 1, Septiembre 9 de 2024

## Consideraciones Iniciales
Una señal se caracteriza por su forma de onda, frecuencia, amplitud, entre otras. Según la aplicación, cada una de estas características tiene un uso específico, por ejemplo, la frecuencia de una señal corresponde a la cantidad de ciclos por segundo y se mide en Hertz (Hz). Estimar adecuadamente la frecuencia de una señal, es fundamental, por ejemplo, en sistemas que requieren sincronización. La Figura 1 muestra una señal senoidal de amplitud 1 y frecuencia 5 Hz.

![image](https://github.com/user-attachments/assets/321a972d-82f9-4bc2-b0fd-d8ba8661c1d1)                          
Figura 1

Además de la forma de onda senoidal, se pueden encontrar señales triangulares, cuadradas, diente de sierra, tren de impulso y muchas más.

Estas señales, por lo general, se generan de forma artificial, pero también corresponden con la respuesta de algunos sistemas de la naturaleza.

La Figura 2, muestra la configuración para conectar un generador de señales a una de las entradas analógicas de un Arduino UNO. En este caso se está generando una señal senoidal de amplitud pico-pico de 1 y frecuencia 1. 

El generador de señales permite variar en tiempo de simulación las características de la señal generada.

![image](https://github.com/user-attachments/assets/4199bd91-6830-47b6-9aaa-51e4498e7416)
Figura 2

En la Figura 3 se puede observar la visualización de los datos de adquisición de una señal senoidal a través del monitor serie. De igual forma, se muestra el código fuente utilizado para la simulación.

![image](https://github.com/user-attachments/assets/49f6cfa0-8b2a-4b90-bb0e-2f69936b7e73)
Figura 3

## Objetivos
• Desarrollar la capacidad de solución de problemas en los estudiantes, enfrentándolos a problemáticas de la vida cotidiana.

• Identificar si el estudiante adquirió las destrezas y conocimientos fundamentales de la programación con C++, en donde resaltamos estructuras de programación (iterativas, secuenciales y decisión), tipos de datos, apuntadores, arreglos, memoria dinámica y funciones.

• Evaluar la capacidad de incorporar la plataforma Arduino dentro de la solución a un problema cotidiano.

El objetivo principal de esta actividad es poner a prueba sus destrezas en análisis de problemas y manejo del lenguaje C++. Si usted ha llevado un proceso disciplinado de aprendizaje a lo largo del semestre, esta es una oportunidad de demostrarlo. Podrá plantear una solución viable y su resultado será satisfactorio. En caso contrario, podrá identificar sus debilidades y deberá tomar medidas con el fin de poder ser apto para enfrentar situaciones como las que se plantean en la sección Contexto.

Trate en lo posible de valorar muy bien la verdadera complejidad del problema planteado, no se rinda antes de intentarlo o de plantear los posibles escenarios de solución. Se dará cuenta de que, aunque al principio le puede parecer difícil, ya ha podido enfrentarse a problemas similares. Si se toma el tiempo adecuado para analizar, el proceso de codificación no le tomará mucho tiempo.

Esperamos que disfrute del desafío propuesto. Le recomendamos que lea primero todo el documento antes de comenzar y asegúrese de entender muy bien las instrucciones antes de desarrollar esta actividad evaluativa.

## Especificaciones
La empresa Informa2 tiene la necesidad de que, dada una señal analógica, se deban identificar sus características principales y visualizar los resultados de acuerdo con lo siguiente:
• El comienzo de la adquisición de datos se hará mediante la activación de un pulsador.

• Una vez iniciada la adquisición, en cualquier momento se puede solicitar la información de la señal capturada. Esta petición se hará mediante la activación de un pulsador. Mientras se procesa la información, la adquisición de datos puede ser suspendida (alternativa: detenerse). Una vez se termine de procesar la información (y se entreguen las salidas,) la adquisición se debe reanudar.

• El valor de las características de la señal capturada se debe visualizar a través de una pantalla LCD. Las características a visualizar se especifican en los numerales dos y tres a continuación.

De acuerdo con lo anterior, entre otras cosas, usted deberá:
1. [15%] Realizar el montaje en Tinkercad que permita realizar la simulación del sistema de adquisición y visualización de la información de la señal capturada. Puede utilizar la librería Adafruit_LiquidCrystal.h. Se puede apoyar en el Starter de Arduino del LCD incluido en Tinkercad. En este ítem, es obligatorio utilizar el generador de señales incluido en Tinkercad.
2. [20%] Implementar un algoritmo que permita medir la frecuencia en Hertz y la amplitud, en Voltios, de la señal de entrada.
3. [65%] Implementar un algoritmo que permita identificar la forma de onda de la señal de entrada. Las formas de onda a identificar corresponden a las incluidas en el generador de señales del Tinkercad. Si la entrada no corresponde con ninguna de las formas de onda especificadas, debe tener el estado de señal desconocida.

## Requisitos mínimos
A continuación, se describen los requisitos que se deben cumplir. El incumplimiento de cualquiera de ellos implica que su nota sea cero.
1. Genere un informe en donde se detalle el desarrollo del proyecto, explique entre otras cosas:

      a. Análisis del problema y consideraciones para la alternativa de solución propuesta.

      b. Esquema donde describa las tareas que usted definió en el desarrollo de los algoritmos.

      c. Algoritmos implementados.

      d. Problemas de desarrollo que afrontó.

      e. Evolución de la solución y consideraciones para tener en cuenta en la implementación.

3. La solución debe ser implementada en lenguaje C++.
   
5. La implementación debe incluir el uso de punteros, arreglos y memoria dinámica.
   
7. Se debe crear un repositorio público en el cual se van a poder cargar todos los archivos relacionados a la solución planteada por usted (informe, código fuente y otros anexos).
   
9. Una vez cumplida la fecha de entrega no se podrá hacer modificación alguna al repositorio.
    
11. Se deben hacer commits de forma regular (al menos uno al día) de tal forma que se evidencie la evolución de la propuesta de solución y su implementación.
    
13. Se debe adjuntar un enlace de youtube a un video que debe incluir lo siguiente:
    
      a. Presentación de la solución planteada. Análisis realizado y explicación de la arquitectura del sistema (3 minutos máximo).
  
      b. Demostración de funcionamiento del sistema. Explicar cómo funciona: ejemplos demostrativos (3 minutos máximo).
  
      c. Explicación del código fuente. Tenga en cuenta que debe justificar la elección de las variables y estructuras de control usados. Por qué eligió uno u otro tipo de variable o estructura de control en cada caso     particular y que ventaja ofrecen estos en comparación de otras que también podrían haber sido usados (5 minutos máximo).
  
      d. La duración total del video no debe exceder 11 minutos ni ser inferior a 5 minutos.
  
      e. Asegúrese que el video tenga buen sonido y que se puede visualizar con resolución suficiente para apreciar bien los componentes presentados.
  
15. El plazo de entrega se divide en dos momentos:
    
      a. El día 14 de Septiembre para adjuntar la evidencia del proceso de análisis y diseño de la solución.
  
      b. El día 17 de Septiembre para adjuntar la evidencia del proceso de implementación.
  
17. En Ude@ se deben adjuntar dos enlaces: uno al repositorio y otro al video, nada más.
    
19. Para la evaluación del desafío se realizará una sustentación oral en un horario concertado con el profesor. La asistencia a la sustentación es obligatoria.

### Fue revisado por los profesores Aníbal Guerra y Augusto Salazar.
