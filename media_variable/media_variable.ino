#include <HX711.h>

#define DOUT_PIN  A1  // Pin de datos del módulo HX711
#define CLK_PIN   A0  // Pin de reloj del módulo HX711
HX711 scale;

const int numSamples = 10;      // Número de muestras para el promedio móvil
int samples[numSamples];        // Almacenar las últimas muestras
int sampleIndex = 0;            // Índice para actualizar las muestras
const float sampleRate = 500;  // Tasa de muestreo en Hz

void setup() {
  Serial.begin(9600);
  scale.begin(DOUT_PIN, CLK_PIN);
  scale.set_scale();
  scale.tare();
}

void loop() {
  // Leer el valor analógico
  int sensorValue = scale.get_units(10);

  // Actualizar el arreglo de muestras
  updateSamples(sensorValue);

  // Calcular el promedio de las muestras
  float averagedVoltage = calculateAverage();

  // Imprimir resultados
//  Serial.print("Raw Voltage: ");
//  Serial.print(sensorValue * (5.0 / 1023.0));
//  Serial.print("V, Averaged Voltage: ");
  Serial.println(averagedVoltage);
//  Serial.println("V");

  delay(1000 / sampleRate);
}

void updateSamples(int sensorValue) {
  // Almacenar la última muestra en el arreglo
  samples[sampleIndex] = sensorValue;

  // Incrementar el índice y volver a cero si es necesario
  sampleIndex = (sampleIndex + 1) % numSamples;
}

float calculateAverage() {
  int sum = 0;
  // Sumar todas las muestras en el arreglo
  for (int i = 0; i < numSamples; ++i) {
    sum += samples[i];
  }
  // Calcular el promedio
  float average = static_cast<float>(sum) / numSamples;
  return average;
}