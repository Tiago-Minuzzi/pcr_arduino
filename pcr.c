#include <OneWire.h> // inclusão de biblioteca
#include <DallasTemperature.h> // inclusão de biblioteca

#define DS18B20 7 // define o pino digital utilizado pelo sensor

OneWire ourWire(DS18B20); // configura uma instância onewire para se comunicar com o sensor
DallasTemperature sensors(&ourWire); // biblioteca DallasTemperature utiliza a OneWire

int RelePin1 = 2; // pino ao qual o Módulo Relé fan está conectado
int RelePin2 = 3; // pino ao qual o Módulo Relé aquecimento está conectado 
                    
// Numero de ciclos
int ciclos = 3;

// Setup de temperaturas
float temp_des = 94;
float temp_ane = 55;
float temp_ext = 72;
float temp_man = 4;
 
float tolerancia = 1;

// Setup de tempos para cada fase
int time_inicial = 20;
int time_des = 10;
int time_ane = 15;
int time_ext = 7;
int time_man = -1;

// NAO ALTERAR VALORES DAQUI EM DIANTE
// Setup do valor do ciclo inicial
int ci = 1;

// Inibidores de processo
bool halter0 = false;
bool halter_ciclo = false;


void setup() {
    Serial.begin(9600);
    sensors.begin(); //INICIA O SENSOR
    pinMode(RelePin1, OUTPUT); // seta o pino1 como saída
    pinMode(RelePin2, OUTPUT); // seta o pino2 como saída
    digitalWrite(RelePin1, HIGH); // seta o pino com nivel logico baixo
    digitalWrite(RelePin2, HIGH); 
}
 

int controller(int target_temp, int timef, int ciclo) {

    sensors.requestTemperatures();// solicita que a função informe a temperatura do sensor
    float temperature = sensors.getTempCByIndex(0)

    if (temperature < (target_temp - tolerancia)) {  
        digitalWrite(RelePin1, HIGH); // liga/deixa ligado o aquecedor
        digitalWrite(RelePin2, LOW); // deixa o fan desligado
        Serial.print("Aumentando temp. ");
        delay(1000);
    } else if (temperature > (target_temp + tolerancia)) {
        digitalWrite(RelePin1, LOW); // desligar o aquecimento
        digitalWrite(RelePin2, HIGH); // ligar o fan
        Serial.print("Diminuindo temp. ");
        delay (10000); 
    } else {
        int time0 = 1;

        if (timef == -1) {
            time0 = 0; 
        }

        digitalWrite(RelePin1, LOW); // desligar o aquecimento
        digitalWrite(RelePin2, LOW); // desligar o fan
        Serial.print("Mantendo: ");
        Serial.println(target_temp);

        do {
            Serial.print("Time");
            Serial.print(time0);
            if (time0 == timef) {
                return 1;
            }
            time0++;
            delay(1000);
        } while (time0 <= timef);
    }

    // Imprimindo no monitor serial
    Serial.print("- Ciclo: ");
    Serial.print(ciclo);
    Serial.print("\t");
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println("°C");
    delay(1000);

    return 0;
}

void loop() {
    if (halter0 == false) {
        int f0 = controller(temp_des, time_inicial, 0);
        if (f0 == 1) {
            halter0 = true;
        }
    } else if (halter_ciclo == false) {

        while(ci <= ciclos) {
            Serial.print(">>> Cycle");
            Serial.print(ci);

            Serial.print("--- Denaturation step ---");
            while(controller(temp_des, time_des, ci) == 0);

            Serial.print("--- Annealing step ---");
            while(controller(temp_ane, time_ane, ci) == 0);

            Serial.print("--- Extension step ---");
            while(controller(temp_ext, time_ext, ci) == 0);

            ci++;
    } 

        if ( ci > ciclos) {
            halter_ciclo = true;
            Serial.print("### Finalizando");
        }

    } else { 
        controller(temp_man, time_man, 0); 
    }
}
