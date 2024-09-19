#include <LiquidCrystal.h>  // Incluir la biblioteca para el LCD

LiquidCrystal lcd(12, 11,5, 4, 3, 2);		// Inicializar la biblioteca con los números de los pines de la interfaz

// Pines de los botones
const int buttonInicio = 7;
const int buttonCaptura = 8;

int buttonInicioState = LOW; 
int lastButtonInicioState = LOW;
int buttonCapturaState = LOW;  // Estado inicial del botón de captura
int lastButtonCapturaState = LOW;  // Estado inicial previo del botón de captura
int analogPin = A0;
int val = 0;

// Variables globales
bool adquirirDatos = false;
bool capturandoDatos = false;	// Variable para controlar si estamos capturando datos

const int capacidadMaxima = 100; // Capacidad Máxima para almacear datos
float bufferVoltajes[capacidadMaxima]; // Buffer para almacenar los voltajes capturados
int indiceBuffer = 0; 

float frecuencia = 0.0;
float amplitud = 0.0;
float voltaje = 0.0;            // Variable para almacenar el voltaje
float voltajeMaximo = 0.0;      // Variable para almacenar el voltaje máximo
float voltajeMinimo = 5.0;      // Variable para almacenar el voltaje mínimo (inicialmente 5V para garantizar que cualquier lectura sea menor)
float voltajeAnterior = 0.0;
float tasaDeCambio = 0.0;

const int numLecturas = 10;   // Número de lecturas para analizar el patrón
float lecturasVoltaje[numLecturas]; // Buffer para almacenar lecturas
int indice = 0;
String tipoDeSenal = "";

// Punteros para las variables
float* pvoltaje = &voltaje;
float* pvoltajeMaximo = &voltajeMaximo;
float* pvoltajeMinimo = &voltajeMinimo;

unsigned long tiempoAnterior = 0;  // Inicializamos tiempoAnterior
unsigned long lastDebounceTime = 0;  // Tiempo para debounce
unsigned long debounceDelay = 50;    // Retraso para el debounce
unsigned long lastDebounceTimeCaptura = 0;
unsigned long debounceDelayCaptura = 50;
unsigned long lastDisplayUpdate = 0;
unsigned long displayInterval = 1000;  // Intervalo para actualizar la pantalla (1 segundo)


// Configurar pines
void setup() {
  
  // Configurar pines de botones
  pinMode(buttonInicio, INPUT_PULLUP);
  pinMode(buttonCaptura, INPUT_PULLUP);
    
  // Iniciar LCD
  lcd.begin(16, 2);
  lcd.print("Sistema listo");
  delay(1000);
 
  // Iniciar comunicación serie para depuración
  Serial.begin(9600);
}

void loop() {
	
	val = analogRead(analogPin); // Función para mostrar la señal
	Serial.println(val);
  
	handleButtonInicio();
	handleButtonCaptura();  
  
	if (adquirirDatos) {		// Si se está adquiriendo la señal, calcular sus características
		leerVoltaje(pvoltaje, pvoltajeMaximo, pvoltajeMinimo); 
		amplitud = calcularAmplitud();
		frecuencia = calcularFrecuencia();
		tipoDeSenal = identificarSenal();
		if (capturandoDatos){
			leerVoltajeYAlmacenar();
		}
	}
}
 
 // Verificar si el botón de inicio/detención fue presionado
void handleButtonInicio() {
	int reading = digitalRead(buttonInicio);
  
	if (reading != lastButtonInicioState) {
		lastDebounceTime = millis();  // Actualiza el tiempo si hay cambio
	}  
  
	if ((millis() - lastDebounceTime) > debounceDelay) {
		if (reading != buttonInicioState) {
			buttonInicioState = reading;
      
			if (buttonInicioState == LOW) {  // Cambiar el estado de adquisición de datos
				adquirirDatos = !adquirirDatos;
			
				if (adquirirDatos) {
					lcd.clear();
					lcd.setCursor(0, 0);
					lcd.print("Adquiriendo");
					lcd.setCursor(0, 1);
					lcd.print("Datos ...");
					          
					// Reiniciar valores máximo y mínimo para cada adquisición
					voltajeMaximo = 0.0;
					voltajeMinimo = 5.0;  // Reiniciamos el mínimo a 5V
          
					lastDisplayUpdate = millis();  // Actualizar el temporizador para la pantalla
				} 
				else {
					lcd.clear();
					lcd.setCursor(0, 0);
					lcd.print("Detenido");
					lastDisplayUpdate = millis();  // Actualizar el temporizador para la pantalla
				}
			}
		}
	}
	lastButtonInicioState = reading;
}

 // Verificar si el botón de captura fue presionado para alternar la visualización
void handleButtonCaptura() {
	int readingCaptura  = digitalRead(buttonCaptura);

	if (readingCaptura  != lastButtonCapturaState) {
		lastDebounceTimeCaptura = millis();  // Actualiza el tiempo si hay cambio en el botón de captura
		}
		
		if ((millis() - lastDebounceTimeCaptura) > debounceDelayCaptura) {
			if (readingCaptura != buttonCapturaState) {
				buttonCapturaState = readingCaptura;    
				
				if (buttonCapturaState == LOW) {  // Cambiar el estado de visualización en el LCD
				
					if (adquirirDatos) {
						capturandoDatos = !capturandoDatos;
					
						if (capturandoDatos) {            // Inicio de la captura
							lcd.clear();
							lcd.setCursor(0, 0);
							lcd.print("Capturando");
							lcd.setCursor(0, 1);
							lcd.print("Datos...");
												
							indiceBuffer = 0;	// Reiniciar el buffer y el índice de almacenamiento
						}

						else {            // Detención de la captura
							lcd.clear();
							lcd.setCursor(0, 0);
							lcd.print("Captura detenida");
							lcd.setCursor(0, 1);
							lcd.print("Procesando...");
							delay(1000);

							procesarDatosCapturados();		// Procesar los datos capturados
					
							int repeticiones = 0;  // Contador de repeticiones
							int maxRepeticiones = 3;  // Número máximo de repeticiones

							while (repeticiones < maxRepeticiones) {
								if (millis() - lastDisplayUpdate >= displayInterval) {
									lastDisplayUpdate = millis();
									mostrarDatos();  // Muestra los datos en el LCD
									repeticiones++;  // Incrementar el contador de repeticiones
								}
							}
							lcd.clear();
							lcd.print("Sistema listo");
						}
					} 
					else {          // Si no se ha iniciado la adquisición de datos, mostrar advertencia
						lcd.clear();
						lcd.setCursor(0, 0);
						lcd.print("Inicie primero");
						lcd.setCursor(0, 1);
						lcd.print("la captura");
						delay(2000);  // Mostrar advertencia por 2 segundos
						lcd.clear();
						lcd.print("Sistema listo");
					}
				}
			}
		}		
	lastButtonCapturaState = readingCaptura;
}

// Función para leer voltaje y almacenar
void leerVoltajeYAlmacenar() {
	// Leer el voltaje desde el pin analógico
	float voltajeActual = analogRead(analogPin) * (5.0 / 1023.0);	
	if (capturandoDatos && indiceBuffer < capacidadMaxima) {		// Almacenar el voltaje en el buffer si estamos capturando datos
		bufferVoltajes[indiceBuffer] = voltajeActual;
		indiceBuffer++;
	}
}

// Función para procesar datos capturados
void procesarDatosCapturados() {
	// Procesar los datos almacenados en el buffer
	if (indiceBuffer > 0) {
		float sumaVoltajes = 0.0;
		float maxVoltaje = 0.0;
		float minVoltaje = 5.0;
		for (int i = 0; i < indiceBuffer; i++) {
			sumaVoltajes += bufferVoltajes[i];
			if (bufferVoltajes[i] > maxVoltaje) {
				maxVoltaje = bufferVoltajes[i];
			}
			if (bufferVoltajes[i] < minVoltaje) {
				minVoltaje = bufferVoltajes[i];
			}
		}
	}
}

// Función para leer voltaje
void leerVoltaje(float* pvoltaje, float* pvoltajeMaximo, float* pvoltajeMinimo) {
	int valorAnalogico = analogRead(analogPin);
	*pvoltaje = ((valorAnalogico / 1023.0) * 5.0);
	// Actualizar buffer de lecturas
	lecturasVoltaje[indice] = *pvoltaje;
	indice = (indice + 1) % numLecturas;  // Incrementar índice y envolver
	if (*pvoltaje > *pvoltajeMaximo) {
		*pvoltajeMaximo = *pvoltaje;
	}
	if (*pvoltaje < *pvoltajeMinimo) {
		*pvoltajeMinimo = *pvoltaje;
	}
}

// Función para identificar tipo de señal
String identificarSenal() {
	float derivadas[numLecturas-1];
	// Calcular derivadas
	for (int i = 0; i < numLecturas - 1; i++) {
		derivadas[i] = lecturasVoltaje[(i + 1) % numLecturas] - lecturasVoltaje[i];
	}
	// Identificar señal cuadrada
	int cambiosBruscos = 0;
	for (int i = 0; i < numLecturas - 1; i++) {
		if (abs(derivadas[i]) > 1.0) {
			cambiosBruscos++;
		}
	}
	if (cambiosBruscos > (numLecturas / 2)) {
		return "Senal Cuadrada";
	}
	// Identificar señal senoidal
	bool cambioSuave = true;
	for (int i = 0; i < numLecturas - 1; i++) {
		if (abs(derivadas[i]) > 0.3) { // Ajusta el umbral según sea necesario
			cambioSuave = false;
			break;
		}
	}
	if (cambioSuave) {
		return "Senal Senoidal";
	}
	// Identificar señal triangular
	bool cambioConstante = true;
	for (int i = 1; i < numLecturas - 1; i++) {
		if (abs(derivadas[i] - derivadas[i - 1]) > 0.2) { // Ajusta el umbral según sea necesario
			cambioConstante = false;
			break;
		}
	}
	if (cambioConstante) {
		return "Señal Triangular";
	}
	return "No identificado";
}

// Función para calcular la amplitud
float calcularAmplitud() {
	return (voltajeMaximo - voltajeMinimo);
}

// Función para calcular la frecuencia
float calcularFrecuencia() {
	static int valorAnterior = 0;
	static unsigned long tiempoAnterior = 0;  // Tiempo del último cruce
	int valorActual = analogRead(analogPin);
	unsigned long tiempoActual = micros();  // Obtener el tiempo actual en microsegundos
  
	// Aplicar un filtro para evitar fluctuaciones por ruido
	int umbral = 511;  // Umbral de cruce en el punto medio (511 o 512)
  
	// Verificar si hay cruce por el umbral
	if ((valorAnterior > umbral && valorActual <= umbral) || (valorAnterior < umbral && valorActual >= umbral)) {
		float tiempoCiclo = (tiempoActual - tiempoAnterior) / 1000000.0;	// Calcular el tiempo de un ciclo completo (en segundos)
		tiempoAnterior = tiempoActual;		// Actualizar el tiempo del último cruce
		if (tiempoCiclo > 0) {		// Si el ciclo es válido (mayor a cero), calcular la frecuencia
			return 1.0 / tiempoCiclo;  // Frecuencia en Hz
		}
	}
	valorAnterior = valorActual;		// Actualizar el valor anterior
	return frecuencia;	// Retornar la última frecuencia calculada si no hay nuevo cruce
}

// Función para mostrar datos en LCD
void mostrarDatos() {
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Amplitud: ");
	lcd.setCursor(0, 1);
	lcd.print(amplitud);
	lcd.print(" V");
	delay(1000);

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Frecuencia: ");
	lcd.setCursor(0, 1);
	lcd.print(frecuencia);
	lcd.print(" Hz");
	delay(1000);

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Tipo: ");
	lcd.setCursor(0, 1);
	lcd.print(tipoDeSenal);
	delay(1000);  
}