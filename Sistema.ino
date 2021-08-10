//Inclui as bibliotecas
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc; //Objeto rtc da classe DS1307

#define entradaDigital 10
#define entradaAnalogica 0 //umidade
bool dSensor;//sensor de umidade
int aSensor;//sensor de umidade

const int sensorPin = A2; //PINO ANALÓGICO UTILIZADO PELO SENSOR de temperatura
float temperatura = 0; //VARIÁVEL DO TIPO FLOAT

int pinoLed = 13;
int pinoSensorLuz = A3; //luz
int valorLuz = 0;

const int ledVermelho = 12;
const int ledAzul = 11;//leds do sensor de temperatura
const int ledVerde = 10;

int Buzzer = 7;
char diasDaSemana[7][12] = {"Domingo", "Segunda", "Terca", "Quarta", "Quinta", "Sexta",
"Sabado"}; //Dias da semana

void setup(){
    Serial.begin(9600); //INICIALIZAÇÃO DA SERIAL
    pinMode(Buzzer,OUTPUT);//buzzer
    pinMode(pinoLed,OUTPUT);
    pinMode(entradaDigital, INPUT);
    pinMode (ledVermelho, OUTPUT);
    pinMode (ledAzul, OUTPUT);//leds do sensor de temp
    pinMode (ledVerde, OUTPUT);

    Serial.begin(9600); //Inicializa a comunicacao serial
    if (! rtc.begin()) { //Se o RTC nao for inicializado, faz
    Serial.println("RTC NAO INICIALIZADO"); //Imprime o texto
    while (1); } //Trava o programa
    
    rtc.adjust(DateTime(2021, 8, 3, 15, 24, 00));//Ajusta o tempo do RTC para a data e hora
    //definida pelo usuario. OLHAR DEPOIS
    delay(100); // 100 Milissegundos
}


void loop(){
    FRelogio();
}

void FTemperatura(){ //funçao da temperatura
//sensor de temperatura
    temperatura = (analogRead(sensorPin) * 0.0048828125/ 0.1); //VARIÁVEL RECEBE A
    //TEMPERATURA MEDIDA
    Serial.print("Temperatura = "); //IMPRIME O TEXTO NA SERIAL
    Serial.print(temperatura); //IMPRIME NA SERIAL A TEMPERATURA MEDIDA
    Serial.println(" C"); //IMPRIME O TEXTO NA SERIAL
  if(temperatura <10){
    tone(Buzzer,392);// Liga o buzzer
    delay(200); // Espera um tempo para Desativar
    noTone;//Desativa o buzzer
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledAzul, LOW);
    digitalWrite(ledVerde, LOW);
    } else if(temperatura >= 10 && temperatura <= 28){
        tone(Buzzer,392);// Liga o buzzer
        delay(200); // Espera um tempo para Desativar
        noTone;//Desativa o buzzer
        digitalWrite(ledAzul, HIGH);
        digitalWrite(ledVermelho, LOW);
        digitalWrite(ledVerde, LOW);
        } else if(temperatura >28){
            tone(Buzzer,392);// Liga o buzzer
            delay(200); // Espera um tempo para Desativar
            //Desativa o buzzer
            noTone;
            digitalWrite(ledVerde, HIGH);
            digitalWrite(ledAzul, LOW);
            digitalWrite(ledVermelho, LOW);
            }
}

void FLuminosidade(){
    //sensor de luminosidade
    valorLuz = analogRead(pinoSensorLuz);
    if(valorLuz>600){
        digitalWrite(pinoLed,LOW);
        Serial.print("Luz Okay"); //IMPRIME O TEXTO NA SERIAL
        Serial.println();
        }
        else
        {
            digitalWrite(pinoLed,HIGH);
            Serial.print("Luz Baixa"); //IMPRIME O TEXTO NA SERIAL
            Serial.println();
            }
}

void FUmidade(){
    //sensor de umidade
    dSensor = digitalRead(entradaDigital);
    aSensor = analogRead(entradaAnalogica);
    // Serial.print("Leitura entrada digital: ");
    //Serial.println(dSensor);
    // Serial.print("Leitura entrada analogica: ");
    // Serial.println(aSensor);
    //Serial.println();
    if (aSensor > 0 && aSensor < 400)
    {
        Serial.println("Status: Solo umido");
        }
        if (aSensor > 400 && aSensor <801)
        {
          Serial.println("Status: Umidade moderada");
          }
          else (aSensor > 800 && aSensor < 1024); {
              Serial.println("Status: Solo seco");
              }
}

void FRelogio(){
    //reogio
    DateTime agora = rtc.now(); // Faz a leitura de dados de data e hora
    Serial.print("Data: ");
    Serial.print(agora.day(), DEC); //Imprime dia
    Serial.print('/'); //Imprime barra
    Serial.print(agora.month(), DEC); //Imprime mes
    Serial.print('/'); //Imprime barra
    Serial.print(agora.year(), DEC); //Imprime ano
    Serial.print(" / Dia da semana: "); //Imprime texto
    Serial.print(diasDaSemana[agora.dayOfTheWeek()]); //Imprime dia da semana
    Serial.print(" / Horas: "); //Imprime texto
    Serial.print(agora.hour(), DEC); //Imprime hora
    Serial.print(':'); //Imprime dois pontos
    Serial.print(agora.minute(), DEC); //Imprime os minutos
    Serial.print(':'); //Imprime dois pontos
    Serial.print(agora.second(), DEC); //Imprime os segundos
    delay(1000); // 1 Segundo
    Serial.println(); //Quebra de linha
  
    if(agora.hour()== 8){
        FTemperatura();
        FLuminosidade();
        FUmidade();
        Serial.println(); //Quebra de linha
        Serial.println(); //Quebra de linha
        }
         else if(agora.hour()== 15){
            FTemperatura();
            FLuminosidade();
            FUmidade();
            Serial.println(); //Quebra de linha
            Serial.println(); //Quebra de linha
            }
         else if (agora.hour()== 17){
                FTemperatura();
                FLuminosidade();
                FUmidade();
                Serial.println(); //Quebra de linha
                Serial.println(); //Quebra de linha
                }
                
}
