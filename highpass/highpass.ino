#include <HX711.h>

#define DOUT_PIN  A1  // Pin de datos del módulo HX711
#define CLK_PIN   A0  // Pin de reloj del módulo HX711
HX711 scale;

const int analogInputPin = A0;  // Pin de entrada analógica
const float R1 = 30.0;          // Valor de la resistencia en ohmios
const float C1 = 0.001;         // Valor del condensador en faradios
const float sampleRate = 100000;  // Tasa de muestreo en Hz

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

  // Aplicar el filtro pasaaltos
  float filteredVoltage = highPassFilter(voltage);

  // Imprimir resultados
//  Serial.print("Raw Voltage: ");
//  Serial.println(voltage);
//  Serial.print("V, Filtered Voltage: ");
  Serial.println(filteredVoltage);
//  Serial.println("V");

  delay(1000 / sampleRate);
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
