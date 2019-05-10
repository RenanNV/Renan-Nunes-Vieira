//BIBLIOTECAS------------------------------------------------------------------------------

#include <LCD.h>                                      //Biblioteca do LCD
#include <LiquidCrystal.h>                            //Biblioteca do LCD
#include <LiquidCrystal_I2C.h>                        //Biblioteca do LCD
#include <Wire.h>                                     //Biblioteca do LCD

#include <Servo.h>                                    //Biblioteca do motor

#include <IRremote.h>                                 //Biblioteca do receptor infravermelho

//------------------------------------------------------------------------------------------

//DISPOSITIVOS------------------------------------------------------------------------------

#define     pino_motor  10
#define     RECV_PIN    11                           //Pino do receptor infravermelho
#define     sensor      2                           //Pino do sensor fotoreflexivo 
#define     baud        9600

//------------------------------------------------------------------------------------------

// --- Teclas do Controle ---
#define     tecla1     0xFF6897                      //Tecla '1' do controle
#define     tecla2     0xFF9867                      //Tecla '2' do controle
#define     tecla3     0xFFB04F                      //Tecla '3' do controle
#define     tecla4     0xFF30CF                      //Tecla '4' do controle
#define     tecla5     0xFF18E7                      //Tecla '5' do controle
#define     tecla6     0xFF7A85                      //Tecla '6' do controle
#define     tecla7     0xFF10EF                      //Tecla '7' do controle
#define     tecla8     0xFF38C7                      //Tecla '8' do controle
#define     tecla9     0xFF906F                       //Tecla '9' do controle
#define     tecla0     0xFF4AB5                      //Tecla '0' do controle
#define     teclaAst   0xFF42BD                      //Tecla '*' do controle
#define     teclaSus   0x3EC3FC1B                      //Tecla '#' do controle
#define     teclaUp    0x511DBB                        //Tecla direcional para cima do controle
#define     teclaDown  0xA3C8EDDB                      //Tecla direcional para baixo do controle
#define     teclaLeft  0x52A3D41F                      //Tecla direcional para esquerda do controle
#define     teclaRight 0x20FE4DBB                      //Tecla direcional para direita do controle
#define     teclaOk    0xFF02FD                        //Tecla 'OK' do controle

//--------------------------------------------------------------------------------------------------------------
 
//DECLARAÇÃO DE OBJETOS-----------------------------------------------------------------------------------------

IRrecv irrecv(RECV_PIN);                               //sensor infravermelho
decode_results results;                                //teclas recebidas
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
Servo ESC;

//--------------------------------------------------------------------------------------------------------------

//DECLARAÇÃO DE VARIÁVEIS GLOBAIS-----------------------------------------------------------

long conta = 0;
int rotacao[4] = {0, 0, 0, 0};
int segundos[2] = {0, 0};
int cont = -1;
int conttempo = -1;
int tempo = -1;
int escolha = 0;
int pulso;
int largura;
int temporot;
int controle = 1;
int h = 1;
unsigned int e = 990;
double o;
double oa;
double ob;
double oc;
double od;
double oe;
double of;
double og;

//----------------------------------------------------------------------------------------------


void setup() {
  
    Serial.begin(baud);                               //Serial configurado para 9600 baud rate
    ESC.attach(pino_motor);

    lcd.begin(16, 2);                                 //Inicializa LCD 16x2
    lcd.print("AGUARDE,");
    lcd.setCursor(0, 1);
    lcd.print("INICIANDO");
    delay(2000);
    
    ESC.writeMicroseconds(840);                       //Pulso mínimo para calibrar o ESC  
    lcd.print(".");
    delay(2000);
    
    ESC.writeMicroseconds(2000);                      //Pulso máximo para calibrar a ESC
    lcd.print("..");
    delay(3000);
    
    ESC.writeMicroseconds(840);
    lcd.print("...");
    
    lcd.clear();
    lcd.print("CALIBRADO");
    lcd.clear();
    
    irrecv.enableIRIn();
    inicio();
    
}

void inicio() {
  
  lcd.setCursor(0,0);
  lcd.print("1:MODO PADRAO");
  lcd.setCursor(0,1);
  lcd.print("2:MODO LIVRE");
  loop();
}

void loop() {
  if (irrecv.decode(&results)) {
    switch (results.value)
    {
      case  tecla1:  Serial.print("menu tecla 1");
        lcd.clear();
        irrecv.resume();
        lcd.print("1:FTR1   2:FTR2");
        lcd.setCursor(0, 2);
        lcd.print("3:DOP1   4:DOP2");
        escolha = 0;

        while (escolha == 0) {
          Serial.print("ESTOU NO SUBMENU");
          if (irrecv.decode(&results)) {
            switch (results.value)
            {
              case  tecla1: irrecv.resume(); Serial.print("Dopante 1"); escolha = 1;   pulso = 990; largura = 2000; temporot = 20; movimento(); break;
              case  tecla2: irrecv.resume(); Serial.print("Dopante 2"); escolha = 1;   pulso = 1020; largura = 2500; temporot = 20; movimento(); break;
              case  tecla3: irrecv.resume(); Serial.print("Dopante 2"); escolha = 1;   pulso = 1080; largura = 3000; temporot = 20; movimento(); break;
              case  tecla4: irrecv.resume(); Serial.print("Dopante 3"); escolha = 1;   pulso = 1170; largura = 3500; temporot = 20; movimento(); break;
              case  tecla5: irrecv.resume(); Serial.print("Dopante 4"); escolha = 1;   pulso = 1320; largura = 4000; temporot = 20; movimento(); break;
              case  tecla6: irrecv.resume(); Serial.print("Dopante 4"); escolha = 1;   pulso = 1450; largura = 4400; temporot = 20; movimento(); break;
            }
            irrecv.resume();
          }
        }
        break;

      case  tecla2:  Serial.print("menu tecla 2");
                     irrecv.resume();
                     lcd.clear();
                     lcd.print("DIGITE O RPM:");
                     lcd.setCursor(0, 1);
                     lcd.print("|    | [RPM]");
                     lcd.cursor();
                     lcd.setCursor(1, 1);
                     escolha = 0;

                     while (escolha == 0) {
                       if (irrecv.decode(&results)) {
                         switch (results.value)
                         {
                           case  tecla1:      cont = cont + 1; rotacao[cont] = 1; lcd.print("1"); break;
                           case  tecla2:      cont = cont + 1; rotacao[cont] = 2; lcd.print("2"); break;
                           case  tecla3:      cont = cont + 1; rotacao[cont] = 3; lcd.print("3"); break;
                           case  tecla4:      cont = cont + 1; rotacao[cont] = 4; lcd.print("4"); break;
                           case  tecla5:      cont = cont + 1; rotacao[cont] = 5; lcd.print("5"); break;
                           case  tecla6:      cont = cont + 1; rotacao[cont] = 6; lcd.print("6"); break;
                           case  tecla7:      cont = cont + 1; rotacao[cont] = 7; lcd.print("7"); break;
                           case  tecla8:      cont = cont + 1; rotacao[cont] = 8; lcd.print("8"); break;
                           case  tecla9:      cont = cont + 1; rotacao[cont] = 9; lcd.print("9"); break;
                           case  tecla0:      cont = cont + 1; rotacao[cont] = 0; lcd.print("0"); break;
                           case  teclaOk:     lcd.clear();
                                              lcd.setCursor(0,0);
                                              lcd.print("DIGITE O TEMPO:");
                                              lcd.setCursor(0,1);
                                              lcd.print("|  | [s]");
                                              lcd.cursor();
                                              lcd.setCursor(1,1);
                                              irrecv.resume();
                                              while (escolha == 0) {
                                                if(irrecv.decode(&results)){
                                                  switch (results.value)
                                                  {
                                                    case  tecla1:      conttempo = conttempo + 1; segundos[conttempo] = 1; lcd.print("1"); break;
                                                    case  tecla2:      conttempo = conttempo + 1; segundos[conttempo] = 2; lcd.print("2"); break;
                                                    case  tecla3:      conttempo = conttempo + 1; segundos[conttempo] = 3; lcd.print("3"); break;
                                                    case  tecla4:      conttempo = conttempo + 1; segundos[conttempo] = 4; lcd.print("4"); break;
                                                    case  tecla5:      conttempo = conttempo + 1; segundos[conttempo] = 5; lcd.print("5"); break;
                                                    case  tecla6:      conttempo = conttempo + 1; segundos[conttempo] = 6; lcd.print("6"); break;
                                                    case  tecla7:      conttempo = conttempo + 1; segundos[conttempo] = 7; lcd.print("7"); break;
                                                    case  tecla8:      conttempo = conttempo + 1; segundos[conttempo] = 8; lcd.print("8"); break;
                                                    case  tecla9:      conttempo = conttempo + 1; segundos[conttempo] = 9; lcd.print("9"); break;
                                                    case  tecla0:      conttempo = conttempo + 1; segundos[conttempo] = 0; lcd.print("0"); break;
                                                    case  teclaOk:     largura = rotacao[0] * 1000 + rotacao[1] * 100 + rotacao[2] * 10 + rotacao[3];
                                                                       temporot = segundos[0] * 10 + segundos[1];
                                                                       escolha = 1;

                                                                       lcd.clear();

                                                                       e = 990;
                                                                       o = (4 * pow(10,-12) * pow(e,6)) - (3 * pow(10,-8) * pow(e,5)) + (9 * pow(10,-5) * pow(e,4)) - (0.1373 * pow(e,3)) + (119.48 * pow(e,2)) - (55044 * e) + pow(10,7) - largura;
                                                                       oa = + (4 * pow(10,-12) * pow(e,6));
                                                                       ob = - (3 * pow(10,-8) * pow(e,5));
                                                                       oc = + (9 * pow(10,-5) * pow(e,4));
                                                                       od = - (0.1373 * pow(e,3));
                                                                       oe = + (119.48 * pow(e,2));
                                                                       of = (55044 * e);
                                                                       og = + pow(10,7);
                                                                       
                                                                       Serial.print("E: ");
                                                                       Serial.println(e);
                                                                       Serial.print("O: ");
                                                                       Serial.println(o);
                                                                       Serial.println(oa);
                                                                       Serial.println(ob);
                                                                       Serial.println(oc);
                                                                       Serial.println(od);
                                                                       Serial.println(oe);
                                                                       Serial.println(of);
                                                                       Serial.println(og);

                                                                       while(o != 0){
                                                                       e = e + 10;            
                                                                       o = (4 * pow(10,-12) * pow(e,6)) - (3 * pow(10,-8) * pow(e,5)) + (9 * pow(10,-5) * pow(e,4)) - (0.1373 * pow(e,3)) + (119.48 * pow(e,2)) - (55044 * e) + pow(10,7) - largura;
                                                                       Serial.print("E: ");
                                                                       Serial.println(e);
                                                                       Serial.print("O: ");
                                                                       Serial.println(o);
                                                                       e = e + 10;
                                                                       }

                                                                       pulso = e;
                                                                       
                                                                       movimento();
                                                                       break;
                                                  }
                                                  irrecv.resume();
                                                }
                                              }   
                         break;
                         }
            irrecv.resume();
        }
        }
        break;
    }
    irrecv.resume();
  }
}


void movimento() {

  lcd.noCursor();
  
  int repete = 0;
  
  unsigned long t = (millis() / 1000);
  unsigned long w = (millis() / 1000);
  unsigned long y = (millis() / 1000);
  unsigned long z = (millis() / 1000);
  
  int a = 0;
  int r = 0;
  int j = 0;
  
//----------ROTINA DE AJUSTE DE VELOCIDADE--------------------------------- 

if (h == 1){

    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("AJUSTANDO...");
    
    while(a != 2){
    ESC.writeMicroseconds(pulso);
    lcd.setCursor(0,0);
    lcd.print("RPM:    --");
    while(j != 2){  
    lcd.setCursor(10,0);
    lcd.print(largura);

    tacometro();
    lcd.setCursor(4,0);

    if((z-y) > 1){
      if((conta <= 9999) && (conta >= 0)){
        //Serial.print(w-t);
        //Serial.print("RPM: ");
        Serial.println(conta);
        lcd.print(conta);
        y = z;
      }
    }
    
    w = (millis() / 1000);
    z = (millis() / 1000);

    if ((w - t) == 10) {
      j = 2;
    }
    }
    Serial.print("Diferença: ");
    Serial.println(largura - conta);
    if ((abs(largura - conta)) <= 80){
      a = 2;
      Serial.println("AJUSTADO");
    }
    else{
    if((abs(largura - conta)) > 80){  //antes era >= 100
     
       if((largura - conta) > 80){
          pulso = pulso + 10;
          Serial.println("Aumentando"); 
          Serial.println(pulso);
       }

       if((largura - conta) < (-80)){
          pulso = pulso - 10;
          Serial.println("Diminuindo");
          Serial.println(pulso);
       }

       
          t = (millis() / 1000);
          w = (millis() / 1000);
          y = (millis() / 1000);
          z = (millis() / 1000);
          j = 0;
    }

    }

    
  }


//----------CONFIRMAÇÃO----------------------------------------------------

  int confirmar = 1;
  
  ESC.writeMicroseconds(840);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PRESSIONE 'OK'");
  lcd.setCursor(0, 1);
  lcd.print("PARA INICIAR");

  while (confirmar == 1) {
    if (irrecv.decode(&results)) {
      switch (results.value)
      {
        case teclaOk: confirmar = 0; ESC.writeMicroseconds(2000); break;
      }
      irrecv.resume(); 
    }
  }
}
//-------------------------------------------------------------------------

  lcd.clear();
  lcd.setCursor(0, 0);
  t = (millis() / 1000);
  w = (millis() / 1000);
  y = (millis() / 1000);
  z = (millis() / 1000);
  lcd.print("RPM:    --");
  lcd.setCursor(10, 0);
  lcd.print(largura);
  lcd.setCursor(0, 1);
  lcd.print("Tempo:  --");
  lcd.print(temporot);
  lcd.setCursor(5, 1);

  while (r != 2) {


    if ((w - t) >= 10) {
      lcd.setCursor(6, 1);
    }

    if ((w - t) < 10) {
      lcd.setCursor(6, 1);
      lcd.print("0");
      lcd.setCursor(7, 1);
    }

    if(irrecv.decode(&results)){
       switch (results.value)
       {
       case  teclaAst:  ESC.writeMicroseconds(840);
                        repete = 0; 
                        h = 1; 
                        irrecv.resume();
                        lcd.clear(); 
                        lcd.setCursor(0, 0);
                        lcd.print("DESACELERANDO...");
                        delay(3000);
                        lcd.clear(); 
                        inicio(); 
                        break;
       }
       irrecv.resume();
    }
    lcd.print(w - t);
    tacometro();           
    lcd.setCursor(4,0);
    if((z-y) > 0){
      if((conta <= 9999) && (conta >= 0)){
        Serial.print(w-t);
        Serial.print(" RPM: ");
        //Serial.println(conta);
        lcd.print(conta);
        y = z;
      }
    }
    //tacometro
    w = (millis() / 1000);
    z = (millis() / 1000);
    if ((w - t) == (temporot + 1)) {
      r = 2;
      Serial.println(r);
    }
    ESC.writeMicroseconds(pulso);
  }

  ESC.writeMicroseconds(840);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DESACELERANDO...");
  delay(3000);

//------MENU PARA REPETIR OU ENCERRAR A ROTAÇÃO--------------------------  
  
  repete = 1;
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1: REPETIR");
  lcd.setCursor(0, 1);
  lcd.print("2: MENU");

  while (repete == 1) {
    if (irrecv.decode(&results)) {
      switch (results.value)
      {
        case tecla1: repete = 0; h = 0; irrecv.resume(); movimento(); break;
        case tecla2: repete = 0; h = 1; irrecv.resume(); inicio(); break;
      }
      irrecv.resume(); 
    }
  }

//-----------------------------------------------------------------------
  
}

void tacometro(){
      int auxilio;
      int ohno = 0;
      conta = 0;                                    
      ohno = pulseIn(2, HIGH) + pulseIn(2, LOW);            
      conta = (45000000/ohno);
      Serial.println(conta);
}
