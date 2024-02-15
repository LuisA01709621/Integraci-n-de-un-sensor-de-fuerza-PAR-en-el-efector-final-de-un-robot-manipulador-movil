// Un filtro pasa banda se puede entender como un filtro pasaaltas y un pasabajas en serie.
#include <HX711.h>

#define DOUT_PIN  A1  // Pin de datos del módulo HX711
#define CLK_PIN   A0  // Pin de reloj del módulo HX711
HX711 scale;

const int analogInputPin = A0;  // Pin de entrada analógica
const float R1 = 10.0;          // Valor de la resistencia en ohmios
const float C1 = 0.001;         // Valor del condensador en faradios
const float R2 = 2.0;          // Otra resistencia para el segundo filtro
const float C2 = 0.001;         // Otro condensador para el segundo filtro
const float sampleRate = 1000;  // Tasa de muestreo en Hz

void setup() {
  Serial.begin(9600);
  scale.begin(DOUT_PIN, CLK_PIN);
  scale.set_scale();
  scale.tare();
}
void loop() {
  float sensorValue = scale.get_units(10); // 10 lecturas para promediar
  // Calcular el voltaje
  float voltage = sensorValue * (5.0 / 1023.0);

  // Aplicar el filtro de banda
  float bandFilteredVoltage = bandPassFilter(voltage);

  // Imprimir resultados
//  Serial.print("Raw Voltage: ");
//  Serial.print(voltage);
//  Serial.print("V, Band-Filtered Voltage: ");
  Serial.println(bandFilteredVoltage);
//  Serial.println("V");

  delay(1000 / sampleRate);
}

float bandPassFilter(float inputVoltage) {
  // Aplicar el filtro pasaaltos
  float highPassFilteredVoltage = highPassFilter(inputVoltage);

  // Aplicar el filtro pasabajas al resultado del filtro pasaaltos
  float bandFilteredVoltage = lowPassFilter(highPassFilteredVoltage);

  return bandFilteredVoltage;
}

float highPassFilter(float inputVoltage) {
  static float prevFilteredVoltage = 0.0;
  float alpha = 1 / (1 + (R1 * C1 * 2 * 3.14159265358979323846 * sampleRate));

  // Aplicar el filtro pasaaltos
  float filteredVoltage = alpha * (prevFilteredVoltage + inputVoltage - prevFilteredVoltage);

  // Actualizar el valor filtrado anterior
  prevFilteredVoltage = filteredVoltage;

  return filteredVoltage;
}

float lowPassFilter(float inputVoltage) {
  static float prevFilteredVoltage = 0.0;
  float alpha = 1 / (1 + (R2 * C2 * 2 * 3.14159265358979323846 * sampleRate));

  // Aplicar el filtro pasabajas
  float filteredVoltage = alpha * inputVoltage + (1 - alpha) * prevFilteredVoltage;

  // Actualizar el valor filtrado anterior
  prevFilteredVoltage = filteredVoltage;

  return filteredVoltage;
}
