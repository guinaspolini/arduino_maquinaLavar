#include <Arduino.h>

int botaoIniciar = 2;
int botaoNivelAguaAlto = 3;
int botaoNivelAguaMedio = 4;
int botaoTempo10Min = 5;
int botaoTempo5Min = 6;
int sensorAguaMedio = 7;
int sensorAguaAlto = 8;
int LED5min = 9;
int LED10min = 10;
int LEDAguaMedio = 11;
int LEDAguaAlto = 12;
int botaoLIGARMAQUINA = 14; // ligar maquina manualmente para limpeza.
int LEDStandBy = 13;
int LEDValvulaOFF = 15;
int LEDValvulaON = 16;
int LEDEnergizado = 17;
int LEDMotorDesligado = 18;
int LEDMotorLigado = 19;
int Solenoide = 20;
int Motor = 21;

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
