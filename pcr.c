#include <Thermistor.h>

Thermistor temp(1); // termistor conectado na porta A1 (cria o objeto)

int RelePin1 = 2; // pino ao qual o Módulo Relé aquecimento está conectado
int RelePin2 = 3; // pino ao qual o Módulo Relé fan está conectado

int limiteDisparo1 = 48;
int limiteDisparo2 = 35;

//float temperature = temp.getTemp(); // calcula a temperatura

void setup() {
    Serial.begin(9600);
    pinMode(RelePin1, OUTPUT); // seta o pino1 como saída
    pinMode(RelePin2, OUTPUT); // seta o pino2 como saída
    digitalWrite(RelePin1, HIGH); // seta o pino com nivel logico baixo
    digitalWrite(RelePin2, HIGH); // seta o pino com nivel logico baixo
}

void step01() {
    float temperature = temp.getTemp(); // calcula a temperatura
    if (temperature < limiteDisparo1) {
        digitalWrite(RelePin2, LOW);
    } else {
        digitalWrite(RelePin2, HIGH);
    }
    delay(30000);

    // Imprimindo no monitor serial
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println("°C");

    delay(1000);
}

void step02() {
    float temperature = temp.getTemp(); // calcula a temperatura
    if (temperature > limiteDisparo2) {
        digitalWrite(RelePin1, LOW);
    } else {
        digitalWrite(RelePin1, HIGH);
    }
    delay(30000);

    // Imprimindo no monitor serial
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println("°C");

    delay(1000);
}

void loop() {
    step01();
    step02();
    delay(5000);
}
