//BIBLIOTECAS------------------------------------------------------------------------------

#include <LCD.h>                                      //Biblioteca do LCD
#include <LiquidCrystal.h>                            //Biblioteca do LCD
#include <LiquidCrystal_I2C.h>                        //Biblioteca do LCD
#include <Wire.h>                                     //Biblioteca do LCD

#include <EEPROM.h>                                   //Biblioteca da memória

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
#define     tecla9     0xFF5AA5                      //Tecla '9' do controle
#define     tecla0     0xFF4AB5                      //Tecla '0' do controle
#define     teclaAst   0xFF42BD                      //Tecla '*' do controle
#define     teclaS     0xFF52AD                      //Tecla '#' do controle
#define     teclaUp    0x511DBB                      //Tecla direcional para cima do controle
#define     teclaDown  0xA3C8EDDB                    //Tecla direcional para baixo do controle
#define     teclaLeft  0x52A3D41F                    //Tecla direcional para esquerda do controle
#define     teclaRight 0x20FE4DBB                    //Tecla direcional para direita do controle
#define     teclaOk    0xFF02FD                      //Tecla 'OK' do controle

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

float ae = 12.153;
float be = -10315;
float ae1 = 3.9047;
float be1 = -1180.9;


int pulso2000 = 1020;  //0 1           // TECLA 1
int pulso2250 = 1040;  //2 3           // TECLA 5
int pulso2500 = 1050;  //4 5           // TECLA 6
int pulso2750 = 1070;  //6 7           // TECLA 7
int pulso3000 = 1016;  //8 9           // TECLA 2
int pulso3250 = 1140;  //10 11         // TECLA 8
int pulso3500 = 1100;  //12 13         // TECLA 9
int pulso3750 = 1260;  //14 15         // TECLA 0
int pulso4000 = 1016;  //16 17         // TECLA 3
int pulso4250 = 1390;  //18 19         // TECLA #
int pulso4500 = 1450;  //20 21         // TECLA 4




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
/*
    EEPROM.write(0, pulso2000/256);
    EEPROM.write(1, pulso2000%256);

    EEPROM.write(2, pulso2250/256);
    EEPROM.write(3, pulso2250%256);

    EEPROM.write(4, pulso2500/256);
    EEPROM.write(5, pulso2500%256);

    EEPROM.write(6, pulso2750/256);
    EEPROM.write(7, pulso2750%256);

    EEPROM.write(8, pulso3000/256);
    EEPROM.write(9, pulso3000%256);

    EEPROM.write(10, pulso3250/256);
    EEPROM.write(11, pulso3250%256);

    EEPROM.write(12, pulso3500/256);
    EEPROM.write(13, pulso3500%256);

    EEPROM.write(14, pulso3750/256);
    EEPROM.write(15, pulso3750%256);

    EEPROM.write(16, pulso4000/256);
    EEPROM.write(17, pulso4000%256);

    EEPROM.write(18, pulso4250/256);
    EEPROM.write(19, pulso4250%256);

    EEPROM.write(20, pulso4500/256);
    EEPROM.write(21, pulso4500%256);
    /*
/*  
        int p2000 = (EEPROM.read(0)*256) + EEPROM.read(1);
        int p2500 = (EEPROM.read(2)*256) + EEPROM.read(3);
        int p3000 = (EEPROM.read(4)*256) + EEPROM.read(5);
        int p3500 = (EEPROM.read(6)*256) + EEPROM.read(7);
        int p4000 = (EEPROM.read(8)*256) + EEPROM.read(9);
        int p4500 = (EEPROM.read(10)*256) + EEPROM.read(11);
        Serial.println(p2000);
        Serial.println(p2500);
        Serial.println(p3000);
        Serial.println(p3500);
        Serial.println(p4000);
        Serial.println(p4500);

//        */
        
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
        lcd.print("1:2000 2:3000");
        lcd.setCursor(0, 2);
        lcd.print("3:4000 4:4500");
        escolha = 0;

        while (escolha == 0) {
          Serial.print("ESTOU NO SUBMENU");
          if (irrecv.decode(&results)) {
            switch (results.value)
            {
              case  tecla1: irrecv.resume(); Serial.print("Dopante 1"); escolha = 1;   pulso = (EEPROM.read(0)*256)  + EEPROM.read(1);   largura = 2000; temporot = 20; movimento(); break;
              case  tecla2: irrecv.resume(); Serial.print("Dopante 2"); escolha = 1;   pulso = (EEPROM.read(8)*256)  + EEPROM.read(9);   largura = 3000; temporot = 20; movimento(); break;
              case  tecla3: irrecv.resume(); Serial.print("Dopante 2"); escolha = 1;   pulso = (EEPROM.read(16)*256) + EEPROM.read(17);  largura = 4000; temporot = 20; movimento(); break;
              case  tecla4: irrecv.resume(); Serial.print("Dopante 3"); escolha = 1;   pulso = (EEPROM.read(20)*256) + EEPROM.read(21);  largura = 4500; temporot = 20; movimento(); break;
              case  tecla5: irrecv.resume(); Serial.print("Dopante 4"); escolha = 1;   pulso = (EEPROM.read(2)*256)  + EEPROM.read(3);   largura = 2250; temporot = 20; movimento(); break;
              case  tecla6: irrecv.resume(); Serial.print("Dopante 4"); escolha = 1;   pulso = (EEPROM.read(4)*256)  + EEPROM.read(5);   largura = 2500; temporot = 20; movimento(); break;
              case  tecla7: irrecv.resume(); Serial.print("Dopante 4"); escolha = 1;   pulso = (EEPROM.read(6)*256)  + EEPROM.read(7);   largura = 2750; temporot = 20; movimento(); break;
              case  tecla8: irrecv.resume(); Serial.print("Dopante 4"); escolha = 1;   pulso = (EEPROM.read(10)*256) + EEPROM.read(11);  largura = 3250; temporot = 20; movimento(); break;
              case  tecla9: irrecv.resume(); Serial.print("Dopante 4"); escolha = 1;   pulso = (EEPROM.read(12)*256) + EEPROM.read(13);  largura = 3500; temporot = 20; movimento(); break;
              case  tecla0: irrecv.resume(); Serial.print("Dopante 4"); escolha = 1;   pulso = (EEPROM.read(14)*256) + EEPROM.read(15);  largura = 3750; temporot = 20; movimento(); break;
              case  teclaS: irrecv.resume(); Serial.print("Dopante 4"); escolha = 1;   pulso = (EEPROM.read(18)*256) + EEPROM.read(19);  largura = 4250; temporot = 20; movimento(); break;    
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

                                                                       if(largura == 2000){
                                                                          pulso = (EEPROM.read(0)*256) + EEPROM.read(1);
                                                                       }
                                                                       
                                                                       if(largura == 2250){
                                                                          pulso = (EEPROM.read(2)*256) + EEPROM.read(3);
                                                                       }

                                                                       if(largura == 2500){
                                                                          pulso = (EEPROM.read(4)*256) + EEPROM.read(5);
                                                                       }

                                                                       if(largura == 2750){
                                                                          pulso = (EEPROM.read(6)*256) + EEPROM.read(7);
                                                                       }

                                                                       if(largura == 3000){
                                                                          pulso = (EEPROM.read(8)*256) + EEPROM.read(9);
                                                                       }

                                                                       if(largura == 3250){
                                                                          pulso = (EEPROM.read(10)*256) + EEPROM.read(11);
                                                                       }

                                                                       if(largura == 3500){
                                                                          pulso = (EEPROM.read(12)*256) + EEPROM.read(13);
                                                                       }

                                                                       if(largura == 3750){
                                                                          pulso = (EEPROM.read(14)*256) + EEPROM.read(15);
                                                                       }

                                                                       if(largura == 4000){
                                                                          pulso = (EEPROM.read(16)*256) + EEPROM.read(17);
                                                                       }

                                                                       if(largura == 4250){
                                                                          pulso = (EEPROM.read(18)*256) + EEPROM.read(19);
                                                                       }

                                                                       if(largura == 4500){
                                                                          pulso = (EEPROM.read(20)*256) + EEPROM.read(21);
                                                                       }
                                                                     
                                                                       else{
                                                                       if(largura > 2000 && largura < 3250){
                                                                          pulso = (largura - be) / ae;
                                                                       }

                                                                       if(largura > 3250 && largura < 4501){
                                                                          pulso = (largura - be1) / ae1;
                                                                       }
                                                                       }

                                                                        
                                                                       movimento();
                                                                       irrecv.resume();       //NOVA
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

  irrecv.resume();
  ESC.writeMicroseconds(pulso);
  lcd.noCursor();
  
  int repete = 0;
  
  unsigned long t = (millis() / 1000);
  unsigned long w = (millis() / 1000);
  unsigned long y = (millis() / 1000);
  unsigned long z = (millis() / 1000);
  
  int a = 0;
  int r = 0;
  int j = 0;
  int f = 0;
  
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
// ////////////////////////
        if(irrecv.decode(&results)){
       switch (results.value)
       {
       case  teclaAst:  ESC.writeMicroseconds(840);
                        irrecv.resume();
                          a = 2;
                          j = 2;
                          r = 2;
                          f = 1;
                        break;
       }
       irrecv.resume();
    }
//   ///////////////////////////////
    }
    Serial.print("Diferença: ");
    Serial.println(largura - conta);
    if ((abs(largura - conta)) <= 100){
      a = 2;
      Serial.println("AJUSTADO");

  if(largura == 2000){
    EEPROM.write(0, pulso/256);
    EEPROM.write(1, pulso%256);
  }

  if(largura == 2250){
    EEPROM.write(2, pulso/256);
    EEPROM.write(3, pulso%256);
  }

  if(largura == 2500){
    EEPROM.write(4, pulso/256);
    EEPROM.write(5, pulso%256);
  }

  if(largura == 2750){
    EEPROM.write(6, pulso/256);
    EEPROM.write(7, pulso%256);
  }

  if(largura == 3000){
    EEPROM.write(8, pulso/256);
    EEPROM.write(9, pulso%256);
  }

  if(largura == 3250){
    EEPROM.write(10, pulso/256);
    EEPROM.write(11, pulso%256);
  }

  if(largura == 3500){
    EEPROM.write(12, pulso/256);
    EEPROM.write(13, pulso%256);
  }

  if(largura == 3750){
    EEPROM.write(14, pulso/256);
    EEPROM.write(15, pulso%256);
  }

  if(largura == 4000){
    EEPROM.write(16, pulso/256);
    EEPROM.write(17, pulso%256);
  }

  if(largura == 4250){
    EEPROM.write(18, pulso/256);
    EEPROM.write(19, pulso%256);
  }

  if(largura == 4500){
    EEPROM.write(20, pulso/256);
    EEPROM.write(21, pulso%256);
  }

    }
    else{
    if((abs(largura - conta)) > 80){ 
     
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

  //

  //

  
    
  }


//----------CONFIRMAÇÃO----------------------------------------------------

  int confirmar = 1;
///// LINHA NOVA AQUI
  if(f == 0){  
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
        case teclaOk: confirmar = 0; break;
      }
      irrecv.resume(); 
    }
  }

///// LINHA NOVA AQUI
  }
  
}
//-------------------------------------------------------------------------

  lcd.clear();
  lcd.setCursor(0, 0);
  t = (millis() / 1000);
  w = (millis() / 1000);
  y = (millis() / 1000);
  z = (millis() / 1000);
  ESC.writeMicroseconds(pulso);
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

    lcd.print(w - t);
    tacometro();           
    lcd.setCursor(4,0);
    if((z-y) > 0){
      if((conta <= 9999) && (conta >= 0)){
        Serial.print(w-t);
        Serial.print(" RPM: ");
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
    if(irrecv.decode(&results)){
       switch (results.value)
       {
       case  teclaAst:  ESC.writeMicroseconds(840);
                        irrecv.resume();
                        r = 2;
                        break;
       }
       irrecv.resume();
    }
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
        case tecla1: repete = 0; if(f == 1){
                                    h = 1;
                                 }
                                 if(f == 0){
                                    h = 0;  
                                 }
                                 irrecv.resume(); 
                                 movimento(); 
                                 break;
               
        case tecla2: repete = 0; h = 1; irrecv.resume(); inicio(); break;
      }
      irrecv.resume(); 
    }
  }

//-----------------------------------------------------------------------
  
}

void tacometro(){
      int auxilio;
      unsigned long ohno = 0;
      conta = 0;                                    
      ohno = pulseIn(2, HIGH) + pulseIn(2, LOW);       
      conta = ((45000000)/ohno)/2;
      Serial.println(ohno);
      Serial.println(conta);
}
