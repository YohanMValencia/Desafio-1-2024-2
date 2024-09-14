#include <LiquidCrystal.h>  // Incluir la biblioteca para el LCD

// Inicializar la biblioteca con los números de los pines de la interfaz
LiquidCrystal lcd(12, 11,5, 4, 3, 2);

// Pines de los botones
const int buttonInicio = 8;
const int buttonCaptura = 7;

int buttonState;
int lastButtonState = LOW; 
int analogPin = A0;
int val = 0;

// Variables globales
bool adquirirDatos = false;
float frecuencia = 0.0;
float amplitud = 0.0;
float voltajeMaximo = 0.0;
float voltajeMinimo = 5.0;


unsigned long tiempoAnterior = 0;  // Inicializamos tiempoAnterior
int valorAnalogico = 0;
//float tiempoCiclo = 0;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;  

// Configurar pines
void setup() {
  

  // Configurar pines de botones
  pinMode(buttonInicio, INPUT);
  pinMode(buttonCaptura, INPUT);
  
  
  // Iniciar LCD
  lcd.begin(16, 2);
  lcd.print("Sistema listo");
  delay(1000);
 

  // Iniciar comunicación serie para depuración
  Serial.begin(9600);
}

void loop() {
  
  // Función para mostrar los señal
  val = analogRead(analogPin);
  Serial.println(val);

  
  // Verificar si el botón de inicio/detención fue presionado
    int reading = digitalRead(buttonInicio);
   	if (reading != lastButtonState) {
    lastDebounceTime = millis();

    adquirirDatos = !adquirirDatos;
    
    if (adquirirDatos) {
      lcd.clear();
      lcd.print("Adquiriendo...");
  	  delay(1000);
      Serial.println("Adquiriendo datos...");
  
    } else {
      lcd.clear();
      lcd.print("Detenido");
      delay(1000);
      Serial.println("Adquisición detenida");
    }
  }
    
  
  // Si se está adquiriendo la señal, calcular sus características
  if (adquirirDatos) {
    // Leer la señal desde el pin analógico (A0)
    int valorSenal = analogRead(A0);
    leerVoltaje(valorAnalogico);
    frecuencia = calcularFrecuencia(valorSenal);

    // Opcional: mostrar en serie para verificar
    Serial.print("Amplitud: ");
    Serial.print(amplitud);
    Serial.print(" V - Frecuencia: ");
    Serial.print(frecuencia);
    Serial.println(" Hz");
  }
  
  // Verificar si el botón de captura fue presionado para mostrar los datos
  if (digitalRead(buttonCaptura) == LOW) {
    delay(300);  // Anti-rebote
    mostrarDatos();
  }
}

// Función para leer la señal y actualizar los valores de voltaje máximo y mínimo
void leerVoltaje(int valorAnalogico) {
  // Convertir el valor analógico (0-1023) a voltaje (0-5V)
  float voltaje = ((valorAnalogico * 5.0) / 1023.0);

  // Actualizar voltaje máximo
  if (voltaje > voltajeMaximo) {
    voltajeMaximo = voltaje;
  }

  // Actualizar voltaje mínimo
  if (voltaje < voltajeMinimo) {
    voltajeMinimo = voltaje;
  }
}
// Función para calcular la amplitud
float calcularAmplitud() {
  return (voltajeMaximo - voltajeMinimo);  // Amplitud = Voltaje máximo - Voltaje mínimo
}


// Función para calcular la frecuencia (simplificación)
float calcularFrecuencia(int valorAnalogico) {
  unsigned long tiempoActual = millis();
  float tiempoCiclo = ((tiempoActual - tiempoAnterior) / 1000.0);  // Tiempo en segundos
  tiempoAnterior = tiempoActual;

  // Proteger de división por cero
  if (tiempoCiclo == 0) {
    return 0;  // Evitar cálculo incorrecto
  }

  return (1.0 / tiempoCiclo);  // Frecuencia (f = 1/T)
}
// Función para mostrar los datos en el LCD
void mostrarDatos() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Amp: ");
  lcd.print(amplitud);
  lcd.print(" V");
  
  lcd.setCursor(0, 1);
  lcd.print("Freq: ");
  lcd.print(frecuencia);
  lcd.print(" Hz");
}
