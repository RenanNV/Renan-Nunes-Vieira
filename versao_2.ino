#include <Servo.h> 

Servo ESC;
Servo BESC;

//Pino de controle do motor
int pino_motor = 10;
int pin = 11;

#define     sensor      2
#define     baud        9600

void setup()
{

    Serial.begin(baud);                               //Serial configurado para 9600 baud rate
    ESC.attach(pino_motor);
    BESC.attach(pin);
    Serial.begin(baud);

    delay(3000);
    
    ESC.writeMicroseconds(840);                       //Pulso mínimo para calibrar o ESC  
    delay(3000);
    
    ESC.writeMicroseconds(2000);                      //Pulso máximo para calibrar a ESC
    delay(3000);
    
    ESC.writeMicroseconds(840);
    
}

unsigned long w;
unsigned long z;
int a;

void loop() 
{
  ESC.writeMicroseconds(2000);
  BESC.writeMicroseconds(1000);
  //char digitado[4] = {' ', ' ', ' ', ' '};
  
  //while(!Serial.available());
  //Serial.readBytesUntil('\n', digitado, 4);
  //int largura  = atoi(digitado);
  //Serial.print("\nLargura de pulso: ");
  //Serial.println(largura);
  //ESC.writeMicroseconds(largura);
  //Recebimento de d

  }

  
