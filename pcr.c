#include <Thermistor.h>

Thermistor temp(1); // termistor conectado na porta A1 (cria o objeto)

int RelePin1 = 2; // pino ao qual o Módulo Relé fan está conectado
int RelePin2 = 3; // pino ao qual o Módulo Relé aquecimento está conectado 
                    //
int limiteDisparo1 = 38;
int tempManutencao = 33
int limiteDisparo2 = 25;
int tolerancia = 1;


void setup() {
    Serial.begin(9600);
    pinMode(RelePin1, OUTPUT); // seta o pino1 como saída
    pinMode(RelePin2, OUTPUT); // seta o pino2 como saída
    digitalWrite(RelePin1, HIGH); // seta o pino com nivel logico baixo
    digitalWrite(RelePin2, HIGH); //
}
 

void loop() {
    float temperature = temp.getTemp(); // calcula a temperatura
    int contador = 0;

    if (temperature < limiteDisparo1) {
        digitalWrite(RelePin1, HIGH);
        digitalWrite(RelePin2, LOW);
        Serial.print("Aumentando a temp");
        delay(1000);
    } else if (temperature < (limiteDisparo1 + tolerancia ) && temperature > tempManutencao) {  
        digitalWrite(RelePin2, LOW); // desligar o fan
        digitalWrite(RelePin1, LOW); // desligar o aquecimento
        Serial.print("Mantendo");
        contador++;
        Serial.print(contador);      
        delay(1000);  
    } else if (temperature > (limiteDisparo1 + tolerancia)) {
        digitalWrite(RelePin2, HIGH); // ligar o fan
        digitalWrite(RelePin1, LOW); // desligar o aquecimento
        Serial.print("Diminuindo a temp");
        delay (10000); 
    }

    // Imprimindo no monitor serial
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println("°C");
    delay(1000);
}
