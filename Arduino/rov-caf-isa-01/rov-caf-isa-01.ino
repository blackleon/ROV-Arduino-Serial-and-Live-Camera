//rov-caf-isa-01
  
#include "DHT.h"

#include <Wire.h>
#include <LPS.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#define DHT1PIN A0
#define DHT2PIN A1
#define DHTTYPE DHT22

#define basincsifir 1035
#define derinlikK 1.0194

#define ONE_WIRE_BUS A2

DHT dht1(DHT1PIN, DHTTYPE);
DHT dht2(DHT2PIN, DHTTYPE);
LPS ps;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int onsaga = 10;
int onsagb = 11;
int onsola = 13;
int onsolb = 12;
int arkasaga = 6;
int arkasagb = 7;
int arkasola = 4;
int arkasolb = 5;
int ustona = 9;
int ustonb = 8;
int ustarkaa = 2;
int ustarkab = 3;

float sicaklik1;
float nem1;

float sicaklik2;
float nem2;

float basinc;
float derinlik;

float sicaklik;

char yon = '5';
int hiz = 3;
int dht1_timer;
int dht2_timer;
int serial_timer;
int derinlik_timer;
int sicaklik_timer;
void setup() 
{
  Serial.begin(19200);
  
  /*dht1.begin();
  dht2.begin();*/
  
  Wire.begin();
  ps.init();
  ps.enableDefault();

  sensors.begin();

  //debug
  
  dht1_timer = millis();
  dht2_timer = millis();
  serial_timer = millis();
  derinlik_timer = millis();
  sicaklik_timer = millis();

  pinMode(onsaga , OUTPUT);
  pinMode(onsagb , OUTPUT);
  pinMode(onsola , OUTPUT);
  pinMode(onsolb , OUTPUT);
  pinMode(arkasaga , OUTPUT);
  pinMode(arkasagb , OUTPUT);
  pinMode(arkasola , OUTPUT);
  pinMode(arkasolb , OUTPUT);
  pinMode(ustona , OUTPUT);
  pinMode(ustonb , OUTPUT);
  pinMode(ustarkaa , OUTPUT);
  pinMode(ustarkab , OUTPUT);
}

void loop() 
{
  int first = millis();

  /*if(millis()-dht1_timer>5000)
  {
    sicaklik1 = dht1.readTemperature();
    nem1 = dht1.readHumidity();
    dht1_timer = millis();
  }

  if(millis()-dht2_timer>5000)
  {
    sicaklik2 = dht2.readTemperature();
    nem2 = dht2.readHumidity();
    dht2_timer = millis();
  }*/
  
  if(millis()-derinlik_timer>200)
  {
    //basinc = 0.9 * basinc + 0.1 * ps.readPressureMillibars();
    basinc = ps.readPressureMillibars();
    sicaklik = ps.readTemperatureC();
    derinlik = (basinc-basincsifir) * derinlikK;
    if(derinlik<0)
    {
      derinlik = 0;
    }
    derinlik_timer = millis();
  }
  
  /*if(millis()-sicaklik_timer>200)
  {
    sensors.requestTemperatures();
    //sicaklik = sensors.getTempCByIndex(0);
    sicaklik = 0.9 * sicaklik + 0.1 * sensors.getTempCByIndex(0);
    sicaklik_timer = millis();
  }
  */
  switch (yon)
  {
    case '5'://5
      dur();
      break;
    case '2'://8
      ileri();
      break;
    case '8'://2
      geri();
      break;
    case '4'://6
      saga();
      break;
    case '6'://4
      sola();
      
      break;
    case '-'://+
      yukari();
      break;
    case '+'://-
      asagi();
      break;
    case '*':// *
      dikeydur();
      break;
    case '/':// /
      yataydur();
      break;
    case '0':// 0
      oneegil();
      break;
    case ',':// ,
      arkayaegil();
      break;
    default:
      break;
  }
  
  int second = millis() - first;
  
  //if(millis()-serial_timer>1000)
  //{
    Serial.print(derinlik);
    Serial.print(" ");
    Serial.print(sicaklik);
    Serial.print(" ");
    Serial.print(sicaklik1);
    Serial.print(" ");
    Serial.print(nem1);
    Serial.print(" ");
    Serial.print(sicaklik2);
    Serial.print(" ");
    Serial.print(nem2);
    Serial.print(" ");
    Serial.print(second);
    Serial.print(" ");
    Serial.println(yon);
    
    //serial_timer = millis();
  //}
}

void serialEvent()
{ 
  if(Serial.available()!=0)
  {
    yon = Serial.read();
  }
}

void ileri()
{
  analogWrite(onsagb, 255 * (hiz / 3));
  analogWrite(onsola, 255 * (hiz / 3));
  analogWrite(arkasagb, 255 * (hiz / 3));
  analogWrite(arkasolb, 255 * (hiz / 3));
  
  analogWrite(onsaga, 0);
  analogWrite(onsolb, 0);
  analogWrite(arkasaga, 0);
  analogWrite(arkasola, 0);
}

void geri()
{
  analogWrite(onsaga, 255 * (hiz / 3));
  analogWrite(onsolb, 255 * (hiz / 3));
  analogWrite(arkasaga, 255 * (hiz / 3));
  analogWrite(arkasola, 255 * (hiz / 3));
  
  analogWrite(onsagb, 0);
  analogWrite(onsola, 0);
  analogWrite(arkasagb, 0);
  analogWrite(arkasolb, 0);
}

void saga()
{
  analogWrite(onsaga, 255 * (hiz / 3));
  analogWrite(onsola, 255 * (hiz / 3));
  analogWrite(arkasaga, 255 * (hiz / 3));
  analogWrite(arkasolb, 255 * (hiz / 3));
  
  analogWrite(onsagb, 0);
  analogWrite(onsolb, 0);
  analogWrite(arkasagb, 0);
  analogWrite(arkasola, 0);
}

void sola()
{
  analogWrite(onsagb, 255 * (hiz / 3));
  analogWrite(onsolb, 255 * (hiz / 3));
  analogWrite(arkasagb, 255 * (hiz / 3));
  analogWrite(arkasola, 255 * (hiz / 3));
  
  analogWrite(onsaga, 0);
  analogWrite(onsola, 0);
  analogWrite(arkasaga, 0);
  analogWrite(arkasolb, 0);
}

void yukari()
{
  analogWrite(ustona, 255 * (hiz / 3));
  analogWrite(ustarkaa, 255 * (hiz / 3));

  analogWrite(ustonb, 0);
  analogWrite(ustarkab, 0);
}

void asagi()
{
  analogWrite(ustonb, 255 * (hiz / 3));
  analogWrite(ustarkab, 255 * (hiz / 3));

  analogWrite(ustona, 0);
  analogWrite(ustarkaa, 0);
}

void oneegil()
{
  analogWrite(ustonb, 255 * (hiz / 3));
  analogWrite(ustarkaa, 255 * (hiz / 3));

  analogWrite(ustona, 0);
  analogWrite(ustarkab, 0);
}

void arkayaegil()
{
  analogWrite(ustona, 255 * (hiz / 3));
  analogWrite(ustarkab, 255 * (hiz / 3));

  analogWrite(ustonb, 0);
  analogWrite(ustarkaa, 0);
}

void dur()
{
  analogWrite(onsaga, 0);
  analogWrite(onsagb, 0);
  analogWrite(onsola, 0);
  analogWrite(onsolb, 0);
  analogWrite(arkasaga, 0);
  analogWrite(arkasagb, 0);
  analogWrite(arkasola, 0);
  analogWrite(arkasolb, 0);
  analogWrite(ustona, 0);
  analogWrite(ustonb, 0);
  analogWrite(ustarkaa, 0);
  analogWrite(ustarkab, 0);
}

void dikeydur()
{
  analogWrite(ustona, 0);
  analogWrite(ustonb, 0);
  analogWrite(ustarkaa, 0);
  analogWrite(ustarkab, 0);
}


void yataydur()
{
  analogWrite(onsaga, 0);
  analogWrite(onsagb, 0);
  analogWrite(onsola, 0);
  analogWrite(onsolb, 0);
  analogWrite(arkasaga, 0);
  analogWrite(arkasagb, 0);
  analogWrite(arkasola, 0);
  analogWrite(arkasolb, 0);
}
