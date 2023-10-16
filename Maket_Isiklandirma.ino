/**
Uzaktan kumanda tuşları

1 -> Parklar Aç/Kapa (Kapatırken kısa ve uzun açıksa onlarda kapanır.)
2 -> Kısalar Aç/Kapa (Kapatırken uzunlar da açıksa uzunlar da kapanır.)
3 -> Uzunlar Aç/Kapa
4 -> Sol sinyaller Aç/Kapa (Açarken sağ sinyaller açıksa onlar kapanır.)
5 -> Sağ sinyaller Aç/Kapa (Açarken sol sinyaller açıksa onlar kapanır.)
6 -> Fren lambası Aç/Kapa
7 -> Dörtlüler Aç/Kapa
8 -> Geri vites lambası Aç/Kapa
OK -> Sistemi Aç/Kapa (Açınca kısa bir demo yapar.)
*/

#define DECODE_NEC
#include <Arduino.h>
#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp>
#define LEDon  LOW
#define LEDoff !LEDon

#define PARK_LED 3
#define KISA_LED 4
#define UZUN_LED 5
#define STOP_LED 6
#define SOL_LED 7
#define SAG_LED 8
#define PLAKA_LED 9
#define FREN_LED 10
#define GERI_LED 11
#define IC_LED 12
#define short1 A0
#define short2 A1
#define short3 A2
#define short4 A3
#define short5 A4

bool parkLedDurum = false;
bool kisaLedDurum = false;
bool uzunLedDurum = false;
bool stopLedDurum = false;
bool solLedDurum = false;
bool solLedState = LOW;
unsigned long solLedEskiZaman = 0;
bool sagLedState = LOW;
bool sagLedDurum = false;
unsigned long sagLedEskiZaman = 0;
bool plakaLedDurum = false;
bool frenLedDurum = false;
bool geriLedDurum = false;
bool icLedDurum = false;
bool dortluLedDurum = false;
bool dortluLedState = LOW;
unsigned long dortluLedEskiZaman = 0;

bool systemState = false;

void setup() {
  Serial.begin(115200);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  pinMode(PARK_LED, OUTPUT);
  pinMode(KISA_LED, OUTPUT);
  pinMode(UZUN_LED, OUTPUT);
  pinMode(STOP_LED, OUTPUT);
  pinMode(SOL_LED, OUTPUT);
  pinMode(SAG_LED, OUTPUT);
  pinMode(PLAKA_LED, OUTPUT);
  pinMode(FREN_LED, OUTPUT);
  pinMode(GERI_LED, OUTPUT);
  pinMode(IC_LED, OUTPUT);
  pinMode(short1, INPUT_PULLUP); 
  pinMode(short2, INPUT_PULLUP); 
  pinMode(short3, INPUT_PULLUP); 
  pinMode(short4, INPUT_PULLUP); 
  pinMode(short5, INPUT_PULLUP); 
}

unsigned long inMuteMs = 0;

void loop() {
  if(systemState == true){
    checkShortCircuits();
  }

  if ( millis() - inMuteMs > 1000 && inMuteMs != 0 ) {
    // abandon old mute attempt
    inMuteMs = 0 ;
  }

  if(parkLedDurum == true && systemState == true){
    digitalWrite(STOP_LED, HIGH);
    digitalWrite(IC_LED, HIGH);
    digitalWrite(PLAKA_LED, HIGH);
  }else{
    digitalWrite(STOP_LED, LOW);
    digitalWrite(IC_LED, LOW);
    digitalWrite(PLAKA_LED, LOW);
  }

  if(solLedDurum == true && (millis() - solLedEskiZaman > 500) && systemState == true){
    solLedState = !solLedState;
    digitalWrite(SOL_LED, solLedState);
    solLedEskiZaman = millis();
  }

  if(sagLedDurum == true && (millis() - sagLedEskiZaman > 500) && systemState == true){
    sagLedState = !sagLedState;
    digitalWrite(SAG_LED, sagLedState);
    sagLedEskiZaman = millis();
  }

  if(dortluLedDurum == true && (millis() - dortluLedEskiZaman > 500) && systemState == true){
    dortluLedState = !dortluLedState;
    digitalWrite(SAG_LED, dortluLedState);
    digitalWrite(SOL_LED, dortluLedState);
    dortluLedEskiZaman = millis();
  }

  if (IrReceiver.decode()) {
    // Kısa farları aç/kapa
    if (IrReceiver.decodedIRData.command == 0x45 && (millis() - inMuteMs > 150) && systemState == true){
      // Serial.println("Button 1");
      parkLedDurum = !parkLedDurum;

      // Kısa ve Uzunları kapat
      if(parkLedDurum == false){
        kisaLedDurum = false;
        uzunLedDurum = false;
        digitalWrite(KISA_LED, LOW);
        digitalWrite(UZUN_LED, LOW);
      }

      digitalWrite(PARK_LED, parkLedDurum);
      inMuteMs = millis() ;
    } else if (IrReceiver.decodedIRData.command == 0x46 && (millis() - inMuteMs > 150) && systemState == true){
      // Serial.println("Button 2");
      kisaLedDurum = !kisaLedDurum;

      // Uzunları kapat
      if(kisaLedDurum == false){
        uzunLedDurum = false;
        digitalWrite(UZUN_LED, LOW);
      }else{
        parkLedDurum = true;
        digitalWrite(PARK_LED, HIGH);
      }

      digitalWrite(KISA_LED, kisaLedDurum);

      inMuteMs = millis() ;
    } else if (IrReceiver.decodedIRData.command == 0x47 && (millis() - inMuteMs > 150) && systemState == true){
      // Serial.println("Button 3");

      uzunLedDurum = !uzunLedDurum;

      if(uzunLedDurum == true){
        parkLedDurum = true;
        kisaLedDurum = true;
        digitalWrite(PARK_LED, HIGH);
        digitalWrite(KISA_LED, HIGH);
      }

      digitalWrite(UZUN_LED, uzunLedDurum);

      inMuteMs = millis() ;
    } else if (IrReceiver.decodedIRData.command == 0x44 && (millis() - inMuteMs > 150) && systemState == true){
      // Serial.println("Button 4");
      if(sagLedDurum == true){
        sagLedDurum = false;
        digitalWrite(SAG_LED, LOW);
        sagLedState = LOW;
        sagLedEskiZaman = 0;
      }

      if(dortluLedDurum == true){
        dortluLedDurum = false;
        digitalWrite(SAG_LED, LOW);
        digitalWrite(SOL_LED, LOW);
        dortluLedState = LOW;
        dortluLedEskiZaman = 0;
      }

      solLedDurum = !solLedDurum;
      inMuteMs = millis();
      if(solLedDurum == false){
        digitalWrite(SOL_LED, LOW);
        solLedState = LOW;
        solLedEskiZaman = 0;
      }
    } else if (IrReceiver.decodedIRData.command == 0x40 && (millis() - inMuteMs > 150) && systemState == true){
      // Serial.println("Button 5");
      if(solLedDurum == true){
        solLedDurum = false;
        digitalWrite(SOL_LED, LOW);
        solLedState = LOW;
        solLedEskiZaman = 0;
      }

      if(dortluLedDurum == true){
        dortluLedDurum = false;
        digitalWrite(SAG_LED, LOW);
        digitalWrite(SOL_LED, LOW);
        dortluLedState = LOW;
        dortluLedEskiZaman = 0;
      }

      sagLedDurum = !sagLedDurum;
      inMuteMs = millis();
      if(sagLedDurum == false){
        digitalWrite(SAG_LED, LOW);
        sagLedState = LOW;
        sagLedEskiZaman = 0;
      }
    } else if (IrReceiver.decodedIRData.command == 0x43 && (millis() - inMuteMs > 150) && systemState == true){
      // Serial.println("Button 6");
      frenLedDurum = !frenLedDurum;
      digitalWrite(FREN_LED, frenLedDurum);
      inMuteMs = millis() ;
    } else if (IrReceiver.decodedIRData.command == 0x7 && (millis() - inMuteMs > 150) && systemState == true){
      // Serial.println("Button 7");
      if(solLedDurum == true){
        solLedDurum = false;
        solLedState = LOW;
        solLedEskiZaman = 0;
        digitalWrite(SOL_LED, LOW);
      }

      if(sagLedDurum == true){
        sagLedDurum = false;
        sagLedState = LOW;
        sagLedEskiZaman = 0;
        digitalWrite(SAG_LED, LOW);
      }

      dortluLedDurum = !dortluLedDurum;            
      inMuteMs = millis();

      if(dortluLedDurum == false){
        sagLedState = LOW;
        sagLedEskiZaman = 0;
        solLedState = LOW;
        solLedEskiZaman = 0;
        digitalWrite(SAG_LED, LOW);
        digitalWrite(SOL_LED, LOW);
      }
    } else if (IrReceiver.decodedIRData.command == 0x15 && (millis() - inMuteMs > 150) && systemState == true){
      // Serial.println("Button 8");
      geriLedDurum = !geriLedDurum;
      digitalWrite(GERI_LED, geriLedDurum);
      inMuteMs = millis() ;
    } else if (IrReceiver.decodedIRData.command == 0x9){
      // Serial.println("Button 9");
    } else if (IrReceiver.decodedIRData.command == 0x19){
      // Serial.println("Button 0");
    } else if (IrReceiver.decodedIRData.command == 0x16){
      // Serial.println("Button *");
    } else if (IrReceiver.decodedIRData.command == 0xD){
      // Serial.println("Button #");
    } else if (IrReceiver.decodedIRData.command == 0x18){
      // Serial.println("Button Up");
    } else if (IrReceiver.decodedIRData.command == 0x8){
      // Serial.println("Button Left");
      if(sagLedDurum == true){
        sagLedDurum = false;
        digitalWrite(SAG_LED, LOW);
        sagLedState = LOW;
        sagLedEskiZaman = 0;
      }

      if(dortluLedDurum == true){
        dortluLedDurum = false;
        digitalWrite(SAG_LED, LOW);
        digitalWrite(SOL_LED, LOW);
        dortluLedState = LOW;
        dortluLedEskiZaman = 0;
      }

      solLedDurum = !solLedDurum;
      inMuteMs = millis();
      if(solLedDurum == false){
        digitalWrite(SOL_LED, LOW);
        solLedState = LOW;
        solLedEskiZaman = 0;
      }
    } else if (IrReceiver.decodedIRData.command == 0x5A){
      // Serial.println("Button Right");
      if(solLedDurum == true){
        solLedDurum = false;
        digitalWrite(SOL_LED, LOW);
        solLedState = LOW;
        solLedEskiZaman = 0;
      }

      if(dortluLedDurum == true){
        dortluLedDurum = false;
        digitalWrite(SAG_LED, LOW);
        digitalWrite(SOL_LED, LOW);
        dortluLedState = LOW;
        dortluLedEskiZaman = 0;
      }

      sagLedDurum = !sagLedDurum;
      inMuteMs = millis();
      if(sagLedDurum == false){
        digitalWrite(SAG_LED, LOW);
        sagLedState = LOW;
        sagLedEskiZaman = 0;
      }
    } else if (IrReceiver.decodedIRData.command == 0x1C && (millis() - inMuteMs > 150)){
      demo();
      inMuteMs = millis();
    } else if (IrReceiver.decodedIRData.command == 0x52){
      // Serial.println("Button Down");
      inMuteMs = millis();
    }

    IrReceiver.resume(); 
  }
}

void demo(){
  if(systemState == false){
    digitalWrite(PARK_LED, HIGH);
    digitalWrite(STOP_LED, HIGH);
    digitalWrite(PLAKA_LED, HIGH);
    digitalWrite(IC_LED, HIGH);
    digitalWrite(KISA_LED, HIGH);
    delay(50);
    digitalWrite(PARK_LED, LOW);
    digitalWrite(STOP_LED, LOW);
    digitalWrite(PLAKA_LED, LOW);
    digitalWrite(IC_LED, LOW);
    digitalWrite(KISA_LED, LOW);
    delay(50);
    digitalWrite(PARK_LED, HIGH);
    digitalWrite(STOP_LED, HIGH);
    digitalWrite(PLAKA_LED, HIGH);
    digitalWrite(IC_LED, HIGH);
    digitalWrite(KISA_LED, HIGH);
    delay(50);
    digitalWrite(PARK_LED, LOW);
    digitalWrite(STOP_LED, LOW);
    digitalWrite(PLAKA_LED, LOW);
    digitalWrite(IC_LED, LOW);
    digitalWrite(KISA_LED, LOW);
    delay(50);
    digitalWrite(PARK_LED, HIGH);
    digitalWrite(STOP_LED, HIGH);
    digitalWrite(PLAKA_LED, HIGH);
    digitalWrite(IC_LED, HIGH);
    digitalWrite(KISA_LED, HIGH);
    delay(50);
    digitalWrite(PARK_LED, LOW);
    digitalWrite(STOP_LED, LOW);
    digitalWrite(PLAKA_LED, LOW);
    digitalWrite(IC_LED, LOW);
    digitalWrite(KISA_LED, LOW);
    delay(50);
    digitalWrite(PARK_LED, HIGH);
    digitalWrite(STOP_LED, HIGH);
    digitalWrite(PLAKA_LED, HIGH);
    digitalWrite(IC_LED, HIGH);
    digitalWrite(KISA_LED, HIGH);
    delay(50);
    digitalWrite(PARK_LED, LOW);
    digitalWrite(STOP_LED, LOW);
    digitalWrite(PLAKA_LED, LOW);
    digitalWrite(IC_LED, LOW);
    digitalWrite(KISA_LED, LOW);
    delay(50);

    digitalWrite(SOL_LED, HIGH);
    delay(50);
    digitalWrite(SOL_LED, LOW);
    delay(50);
    digitalWrite(SOL_LED, HIGH);
    delay(50);
    digitalWrite(SOL_LED, LOW);
    delay(50);
    digitalWrite(SOL_LED, HIGH);
    delay(50);
    digitalWrite(SOL_LED, LOW);
    delay(50);
    digitalWrite(SOL_LED, HIGH);
    delay(50);
    digitalWrite(SOL_LED, LOW);
    delay(50);

    digitalWrite(SAG_LED, HIGH);
    delay(50);
    digitalWrite(SAG_LED, LOW);
    delay(50);
    digitalWrite(SAG_LED, HIGH);
    delay(50);
    digitalWrite(SAG_LED, LOW);
    delay(50);
    digitalWrite(SAG_LED, HIGH);
    delay(50);
    digitalWrite(SAG_LED, LOW);
    delay(50);
    digitalWrite(SAG_LED, HIGH);
    delay(50);
    digitalWrite(SAG_LED, LOW);
    delay(50);

    digitalWrite(SOL_LED, HIGH);
    delay(50);
    digitalWrite(SOL_LED, LOW);
    delay(50);
    digitalWrite(SOL_LED, HIGH);
    delay(50);
    digitalWrite(SOL_LED, LOW);
    delay(50);
    digitalWrite(SOL_LED, HIGH);
    delay(50);
    digitalWrite(SOL_LED, LOW);
    delay(50);
    digitalWrite(SOL_LED, HIGH);
    delay(50);
    digitalWrite(SOL_LED, LOW);
    delay(50);

    digitalWrite(SAG_LED, HIGH);
    delay(50);
    digitalWrite(SAG_LED, LOW);
    delay(50);
    digitalWrite(SAG_LED, HIGH);
    delay(50);
    digitalWrite(SAG_LED, LOW);
    delay(50);
    digitalWrite(SAG_LED, HIGH);
    delay(50);
    digitalWrite(SAG_LED, LOW);
    delay(50);
    digitalWrite(SAG_LED, HIGH);
    delay(50);
    digitalWrite(SAG_LED, LOW);
    delay(50);

    systemState = true;
  }else{
    parkLedDurum = false;
    kisaLedDurum = false;
    uzunLedDurum = false;
    stopLedDurum = false;
    solLedDurum = false;
    solLedState = LOW;
    solLedEskiZaman = 0;
    sagLedState = LOW;
    sagLedDurum = false;
    sagLedEskiZaman = 0;
    plakaLedDurum = false;
    frenLedDurum = false;
    geriLedDurum = false;
    icLedDurum = false;
    dortluLedDurum = false;
    dortluLedState = LOW;
    dortluLedEskiZaman = 0;
    digitalWrite(PARK_LED, LOW);
    digitalWrite(KISA_LED, LOW);
    digitalWrite(UZUN_LED, LOW);
    digitalWrite(STOP_LED, LOW);
    digitalWrite(SOL_LED, LOW);
    digitalWrite(SAG_LED, LOW);
    digitalWrite(PLAKA_LED, LOW);
    digitalWrite(FREN_LED, LOW);
    digitalWrite(GERI_LED, LOW);
    digitalWrite(IC_LED, LOW);

    digitalWrite(KISA_LED, HIGH);
    digitalWrite(UZUN_LED, HIGH);
    digitalWrite(STOP_LED, HIGH);
    delay(500);
    digitalWrite(KISA_LED, LOW);
    digitalWrite(UZUN_LED, LOW);
    digitalWrite(STOP_LED, LOW);

    systemState = false;
  }
}

void checkShortCircuits(){
  if(digitalRead(short1) == HIGH || digitalRead(short2) == HIGH || digitalRead(short3) == HIGH || digitalRead(short4) == HIGH || digitalRead(short5) == HIGH){
    if(parkLedDurum == false){
      digitalWrite(IC_LED, HIGH);
    }
  }else{
    if(parkLedDurum == false){
      digitalWrite(IC_LED, LOW);
    }
  }
}
