#include <Arduino.h>

int botaoNivelAguaMedio = 2;
int botaoTempo10Min = 3;
int botaoTempo5Min = 4;
int sensorAguaMedio = 5;
int sensorAguaAlto = 6;
int botaoNivelAguaAlto = 7;
int LED5min = 21;
int LED10min = 8;
int LEDAguaMedio = 9;
int botaoIniciar = 10;
int botaoLIGARMAQUINA = 11; // ligar maquina manualmente para limpeza.
int LEDValvulaOFF = 12;
int LEDStandBy = 13;
int LEDValvulaON = 14;
int LEDEnergizado = 15;
int LEDMotorDesligado = 16;
int LEDMotorLigado = 17;
int Solenoide = 18;
int Motor = 19;
int LEDAguaAlto = 20;

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

void ligarMotor()
{

	int tempoMotorLigado;

	if (botaoTempo10Min != HIGH && botaoTempo5Min != LOW)
	{
		tempoMotorLigado = 5000;
	}
	else if (botaoTempo10Min != LOW && botaoTempo5Min != HIGH)
	{
		tempoMotorLigado = 10000;
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

	if (botaoNivelAguaMedio == HIGH && botaoNivelAguaAlto == LOW)
	{
		nivelAgua = sensorAguaMedio;
	}
	else if (botaoNivelAguaMedio == LOW && botaoNivelAguaAlto == HIGH)
	{
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

	//Ligar Maquina Manualmente
	{
		int estadoMaquina = digitalRead(botaoLIGARMAQUINA);
		while (estadoMaquina != LOW && Motor != HIGH && Solenoide != HIGH)
		{
			digitalWrite(LEDStandBy,LOW);
			digitalWrite(Motor, HIGH);
			digitalWrite(LEDMotorDesligado, LOW);
			digitalWrite(LEDMotorLigado, HIGH);
			estadoMaquina = estadoMaquina;
		}
	}
	// inicializar máquina
	{
		int estadoBotaoIniciar = digitalRead(botaoIniciar);

		if (estadoBotaoIniciar != LOW)
		{
			encherTanque();
			delay(100);
			ligarMotor();
		}
	}
}
