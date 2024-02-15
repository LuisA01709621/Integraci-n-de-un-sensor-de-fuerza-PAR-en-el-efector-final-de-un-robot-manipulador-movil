#include <HX711.h>

#define DOUT_PIN  A1  // Pin de datos del módulo HX711
#define CLK_PIN   A0  // Pin de reloj del módulo HX711

HX711 scale;

void setup() {
  Serial.begin(9600);
  scale.begin(DOUT_PIN, CLK_PIN);
  scale.set_scale();
  scale.tare();
}

void loop() {
  float weight = scale.get_units(10); // 10 lecturas para promediar
  //Serial.print("Peso: ");
  Serial.println(weight);
//  Serial.println(abs(weight));
  //Serial.println(" kg");
  delay(100); // Espera un segundo antes de leer nuevamente
}


