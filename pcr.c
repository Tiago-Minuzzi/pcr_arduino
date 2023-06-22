#include <Thermistor.h>

Thermistor temp(1); // termistor conectado na porta A1 (cria o objeto)

int RelePin = 9; // pino ao qual o Módulo Relé está conectado
int RelePin1 = 2; // pino ao qual o Módulo Relé aquecimento está conectado
int RelePin2 = 3; // pino ao qual o Módulo Relé fan está conectado

int limiteDisparo1 = 45;
int limiteDisparo2 = 30;

float temperature = temp.getTemp(); // calcula a temperatura

void setup() {
    Serial.begin(9600);
    pinMode(RelePin1, OUTPUT); // seta o pino1 como saída
    pinMode(RelePin2, OUTPUT); // seta o pino2 como saída
    digitalWrite(RelePin1, LOW); // seta o pino com nivel logico baixo
}

void step01() {
    if (temperature < limiteDisparo1) {
        digitalWrite(RelePin1, HIGH);
    } else {
        digitalWrite(RelePin, LOW);
    }
    delay(30000);

    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println("°C");
}

void step02() {
    if (temperature > limiteDisparo2) {
        digitalWrite(RelePin1, HIGH);
    } else {
        digitalWrite(RelePin, LOW);
    }
    delay(30000);

    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println("°C");
}

int main() {
    setup();
    step01();
    step02();
    delay(5000);

    return 0;
}
