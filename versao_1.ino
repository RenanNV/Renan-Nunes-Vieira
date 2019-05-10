#include <Servo.h> 
 
Servo ESC;

//Pino do potenciometro
int pino_pot = A0;

//Pino de controle do motor
int pino_motor = 9;

//Valores utilizados para o Potenciometro e o Motor
int valor = 0;
int valorms = 700;

void setup()
{
  //Inicia Serial
  Serial.begin(9600);

  //Inicia ESC
  ESC.attach(pino_motor);
  ESC.writeMicroseconds(0);

  //Aguarde 5 segundos para começar
  Serial.println("Aguardando 5 segundos...");
}

void loop()
{
  //Lê o valor do potenciômetro
  valor = analogRead(pino_pot);

  //Converte o valor para uma faixa entre 1000 e 2000
  valorms = map(valor, 0, 1023, 840, 2000);

  //Mostra os valores do potenciômetro no monitor serial
  Serial.print("Potenciometro: ");
  Serial.print(valorms);
  Serial.print("    ");
  Serial.println(valor);

  //Envia o valor convertido para o ESC
  ESC.writeMicroseconds(valorms);
}
