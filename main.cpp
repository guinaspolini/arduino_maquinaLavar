#include <Arduino.h>

int LEDMotorLigado = 2;
int LEDValvulaOFF = 3;
int LEDMotorDesligado = 4;
int botaoNivelAguaMedio = 5;
int LEDValvulaON = 6;
int LEDStandBy = 8;
int LEDAguaAlto = 9;
int LEDAguaMedio = 10;
int LED10min = 11;
int LED5min =12;
int LEDEnergizado = 13;
int botaoTempo10Min = 14;
int botaoLIGARMAQUINA = 15; // ligar maquina manualmente para limpeza.
int botaoTempo5Min = 16;
int botaoIniciar = 17;
int botaoNivelAguaAlto = 18;
int sensorAguaMedio = 19;
int sensorAguaAlto = 7;
int Motor = 20;
int Solenoide = 21;

void setup()
{
  pinMode(LED10min, OUTPUT);
  pinMode(LED5min, OUTPUT);
  pinMode(LEDAguaAlto, OUTPUT);
  pinMode(LEDAguaMedio, OUTPUT);
  pinMode(LEDValvulaOFF, OUTPUT);
  pinMode(LEDValvulaON, OUTPUT);
  pinMode(LEDEnergizado, OUTPUT);
  pinMode(LEDMotorDesligado, OUTPUT);
  pinMode(LEDMotorLigado, OUTPUT);
  pinMode(Solenoide, OUTPUT);
  pinMode(botaoIniciar, INPUT);
  pinMode(LEDStandBy, OUTPUT);
  pinMode(botaoNivelAguaAlto, INPUT);
  pinMode(botaoNivelAguaMedio, INPUT);
  pinMode(botaoTempo10Min, INPUT);
  pinMode(botaoTempo5Min, INPUT);
  pinMode(botaoLIGARMAQUINA, INPUT);
  pinMode(Motor, OUTPUT);
  pinMode(sensorAguaAlto, INPUT);
  pinMode(sensorAguaMedio, INPUT);
}

void ligarMotor ()
{

int tempoMotorLigado;

if(botaoTempo10Min== HIGH && botaoTempo5Min == LOW){
  tempoMotorLigado = 10000;
} else if(botaoTempo10Min==LOW && botaoTempo5Min==HIGH){
  tempoMotorLigado =5000;
}

  digitalWrite(LEDMotorDesligado, LOW);
  digitalWrite(Motor, HIGH);
  digitalWrite(LEDMotorLigado, HIGH);
  delay(tempoMotorLigado);
  digitalWrite(LEDMotorDesligado, HIGH);
  digitalWrite(Motor, LOW);
  digitalWrite(LEDMotorLigado, LOW);
}

void encherTanque()
{

  int nivelAgua;

if(botaoNivelAguaMedio== HIGH && botaoNivelAguaAlto == LOW){
  nivelAgua = sensorAguaMedio;
} else if(botaoNivelAguaMedio== LOW && botaoNivelAguaAlto == HIGH){
  nivelAgua = sensorAguaAlto;
}

  while (nivelAgua != LOW)
  {
    digitalWrite(LEDValvulaOFF, LOW);
    digitalWrite(LEDValvulaON, HIGH);
    nivelAgua = nivelAgua;
  }

  digitalWrite(LEDValvulaOFF, HIGH);
  digitalWrite(LEDValvulaON, LOW);
}


void loop()
{
// Maquina em StandBY
  digitalWrite(LEDEnergizado, HIGH);
  digitalWrite(LEDMotorDesligado, HIGH);
  digitalWrite(LEDValvulaOFF, HIGH);
  digitalWrite(LEDStandBy, HIGH);
  delay(250);
  digitalWrite(LEDStandBy, LOW);
  delay(250);

// inicializar máquina
  int estadoBotaoIniciar = digitalRead(botaoIniciar);

  if (estadoBotaoIniciar != LOW)
  {
    encherTanque();
    delay(1000);
    ligarMotor();
  }
}
