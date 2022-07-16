#include <Arduino.h>

int botaoTempo = 8; // porta original 2;
int botaoNivelAgua = 4;
int botaoLIGARMAQUINA = 6; // ligar maquina manualmente para limpeza.
int botaoIniciar = 7;
int LEDMotorLigado = 11;
int LEDValvulaOFF = 19;
int LEDMotorDesligado = 10;
int LEDValvulaON = 12;
int LEDStandBy = 13;
int LEDAguaAlto = 18;
int LEDAguaMedio = 17;
int LED10min = 16;
int LED5min = 15;
int LEDEnergizado = 14;
int sensorAguaMedio;
int sensorAguaAlto;
int Motor;
int Solenoide;
int estadoBotaoTempo = 1;
int estadoBotaoAgua = 1;
int tempo;
int nivelAgua;

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
	pinMode(botaoNivelAgua, INPUT);
	pinMode(botaoTempo, INPUT);
	pinMode(botaoLIGARMAQUINA, INPUT);
	pinMode(Motor, OUTPUT);
	pinMode(sensorAguaAlto, INPUT);
	pinMode(sensorAguaMedio, INPUT);
}

void ligarMotor()
{
	digitalWrite(LEDMotorDesligado, LOW);
	digitalWrite(Motor, HIGH);
	digitalWrite(LEDMotorLigado, HIGH);
	digitalWrite(LEDMotorDesligado, HIGH);
	digitalWrite(Motor, LOW);
	digitalWrite(LEDMotorLigado, LOW);
}

void encherTanque(int nivelAgua)
{

	digitalWrite(LEDValvulaOFF, LOW);
	digitalWrite(LEDValvulaON, HIGH);
	delay(nivelAgua);
	digitalWrite(LEDValvulaOFF, HIGH);
	digitalWrite(LEDValvulaON, LOW);
}

void loop()

{
	if (digitalRead(botaoTempo) == HIGH)
	{
		delay(1);
		if (digitalRead(botaoTempo) == LOW)
		{
			digitalWrite(LED5min, estadoBotaoTempo);
			digitalWrite(LED10min, !estadoBotaoTempo);
			estadoBotaoTempo = !estadoBotaoTempo;
		}
	}

	if (estadoBotaoTempo == 1)
	{
		nivelAgua = 5;
	}
	if (estadoBotaoTempo == 0)
	{
		nivelAgua = 10;
	}

	if (digitalRead(botaoNivelAgua) == HIGH)
	{
		delay(1);
		if (digitalRead(botaoNivelAgua) == LOW)
		{
			digitalWrite(LEDAguaMedio, estadoBotaoAgua);
			digitalWrite(LEDAguaAlto, !estadoBotaoAgua);
			estadoBotaoAgua = !estadoBotaoAgua;
		}

	}
			
}
