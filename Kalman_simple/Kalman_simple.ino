#include <HX711.h>
#define DOUT_PIN  A1  // Pin de datos del módulo HX711
#define CLK_PIN   A0  // Pin de reloj del módulo HX711
HX711 scale;

const float R = 0.1;           // Varianza del ruido de medición
const float Q = 0.01;          // Varianza del ruido del proceso
const float sampleRate = 2000;  // Tasa de muestreo en Hz

float x_hat = 0.0;  // Estimación del estado
float P = 1.0;      // Covarianza de la estimación

void setup() {
  Serial.begin(9600);
  scale.begin(DOUT_PIN, CLK_PIN);
  scale.set_scale();
  scale.tare();
}

void loop() {
  // Leer el valor analógico
  float sensorValue = scale.get_units(10); // 10 lecturas para promediar

  // Convertir a voltaje
  float voltage = sensorValue * (5.0 / 1023.0);

  // Predicción del estado (modelo de sistema)
  float x_pred = x_hat;
  float P_pred = P + Q;

  // Actualización con la medición
  float K = P_pred / (P_pred + R);  // Ganancia de Kalman
  x_hat = x_pred + K * (voltage - x_pred);
  P = (1 - K) * P_pred;

  // Imprimir resultados
//  Serial.print("Raw Voltage: ");
//  Serial.print(voltage);
//  Serial.print("V, Filtered Voltage (Kalman): ");
  Serial.println(x_hat);
//  Serial.println("V");

  delay(1000 / sampleRate);
}
