#include "pitches.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define buttonC  22
#define buttonCS 24
#define buttonD  26
#define buttonDS 28
#define buttonE  30
#define buttonF  32
#define buttonFS 34
#define buttonG  36
#define buttonGS 38
#define buttonA  40
#define buttonAS 42
#define buttonB  44
#define buttonC2 46

bool screen = true;
bool halt = false;
bool pressed = false;
const int resetbutton = 2;
const int countbutton = 3;

const int buzzer = 10;
volatile int count = 0;

int fameBPM = 168;
int preludeBPM = 150;
int loveBPM = 160;

LiquidCrystal_I2C lcd(0x27, 20, 4);

int flamingo[] =
{
  //1ST loop
  NOTE_GS4, NOTE_AS4, NOTE_C5, NOTE_DS5,
  NOTE_F5,  NOTE_F5,  NOTE_G5, NOTE_F5,
  NOTE_DS5, NOTE_C5,  NOTE_F5, NOTE_DS5,

  NOTE_G4,
  NOTE_GS4, NOTE_AS4, NOTE_C5, NOTE_DS5,
  NOTE_F5,  NOTE_F5,  NOTE_G5, NOTE_F5,
  NOTE_DS5, NOTE_D5,  NOTE_AS4,

  NOTE_G4,  NOTE_C5,  NOTE_G4,  NOTE_C5, NOTE_AS4,

  NOTE_G4,  NOTE_FS4,
  NOTE_F4,  NOTE_GS4, NOTE_DS5,
  NOTE_F4,  NOTE_GS4, NOTE_DS5,
  NOTE_F4,  NOTE_DS5, NOTE_DS5,
  NOTE_F4,  NOTE_DS5, NOTE_F4,
  NOTE_G4,  NOTE_DS5, NOTE_G4, NOTE_AS4,

  //2ND LOOP
  NOTE_GS4, NOTE_AS4, NOTE_C5, NOTE_DS5,
  NOTE_F5,  NOTE_F5,  NOTE_G5, NOTE_F5,
  NOTE_DS5, NOTE_C5,  NOTE_F5, NOTE_DS5,

  NOTE_G4,
  NOTE_GS4, NOTE_AS4, NOTE_C5, NOTE_DS5,
  NOTE_F5,  NOTE_F5,  NOTE_G5, NOTE_F5,
  NOTE_DS5, NOTE_D5,  NOTE_AS4,

  NOTE_G4,  NOTE_C5,  NOTE_G4,  NOTE_C5, NOTE_AS4,

  NOTE_G4,  NOTE_FS4,
  NOTE_F4,  NOTE_GS4, NOTE_DS5,
  NOTE_F4,
  NOTE_C5,  NOTE_D5,  NOTE_DS5,
  0, 0
};

//notes in milliseconds
int tempo[]
{
  //1st measure
  169, 169, 169, 337,
  337, 84, 84,

  //2nd
  337, 337, 337, 337,

  //3rd
  505, 169, 169, 169, 169, 337,
  //4
  337, 84, 84, 337, 337,
  //5
  674, 505, 337,

  169, 169, 169, 505, 84, 84,

  169, 169, 169, 169, 169, 169, 169, 169,
  169, 169, 169, 169, 169, 169, 169, 169,

  //2nd loop 9th measure
  169, 169, 169, 337,
  337, 84, 84,

  337, 337, 337, 337,

  505, 169, 169, 169, 169, 337,

  337, 84, 84, 337, 337,

  647, 505, 337,

  169, 169, 169, 505, 84, 84,

  169, 169, 169, 169, 337, 337,

  674, 337, 337
};

int fame[]
{
  NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_G4,
  NOTE_AS4, NOTE_D4, NOTE_AS4, NOTE_G4,
  NOTE_AS4, NOTE_DS4, NOTE_DS5, NOTE_G4,
  NOTE_AS4, NOTE_DS4, NOTE_DS5, NOTE_AS4,

  NOTE_D5, NOTE_AS4, NOTE_DS5, NOTE_AS4,
  NOTE_F5, NOTE_AS4, NOTE_B4, NOTE_A4,
  NOTE_B4, NOTE_F4, NOTE_F5, NOTE_F4,
  NOTE_C5, NOTE_F4, NOTE_F5, NOTE_A4,

  NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_G4,
  NOTE_AS4, NOTE_D4, NOTE_AS4, NOTE_G4,
  NOTE_AS4, NOTE_DS4, NOTE_DS5, NOTE_G4,
  NOTE_AS4, NOTE_DS4, NOTE_DS5, NOTE_AS4,

  NOTE_D5, NOTE_AS4, NOTE_DS5, NOTE_AS4,
  NOTE_F5, NOTE_AS4, NOTE_C5, NOTE_A4,
  NOTE_C5, NOTE_F4, NOTE_F5, NOTE_F4,
  NOTE_C5, NOTE_F4, NOTE_F5, NOTE_A4
};

int fametempo[]
{
  16, 16, 16, 16,
  16, 16, 16, 16,
  16, 16, 16, 16,
  16, 16, 16, 16,

  16, 16, 16, 16,
  16, 16, 16, 16,
  16, 16, 16, 16,
  16, 16, 16, 16,

  16, 16, 16, 16,
  16, 16, 16, 16,
  16, 16, 16, 16,
  16, 16, 16, 16,

  16, 16, 16, 16,
  16, 16, 16, 16,
  16, 16, 16, 16,
  16, 16, 16, 16
};

int prelude[]
{
  NOTE_C3, NOTE_D3, NOTE_E3, NOTE_G3,
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_G4,
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_G5,
  NOTE_C6, NOTE_D6, NOTE_E6, NOTE_G6,
  NOTE_C7, 

  NOTE_G6, NOTE_E6, NOTE_D6, NOTE_C6,
  NOTE_G5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_G4, NOTE_E4, NOTE_D4, NOTE_C4,
  NOTE_G3, NOTE_E3, NOTE_D3, 

  NOTE_A2, NOTE_B2, NOTE_C2, NOTE_E2,
  NOTE_A3, NOTE_B3, NOTE_C3, NOTE_E3,
  NOTE_A4, NOTE_B4, NOTE_C4, NOTE_E4,
  NOTE_A5, NOTE_B5, NOTE_C5, NOTE_E5,
  NOTE_A6,

  NOTE_E5, NOTE_C5, NOTE_B5, NOTE_A5,
  NOTE_E4, NOTE_C4, NOTE_B4, NOTE_A4,
  NOTE_E3, NOTE_C3, NOTE_B3, NOTE_A3,
  NOTE_E2, NOTE_C2, NOTE_B2,
//2ND LOOP
  NOTE_C3, NOTE_D3, NOTE_E3, NOTE_G3,
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_G4,
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_G5,
  NOTE_C6, NOTE_D6, NOTE_E6, NOTE_G6,
  NOTE_C7, 

  NOTE_G6, NOTE_E6, NOTE_D6, NOTE_C6,
  NOTE_G5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_G4, NOTE_E4, NOTE_D4, NOTE_C4,
  NOTE_G3, NOTE_E3, NOTE_D3, 

  NOTE_A2, NOTE_B2, NOTE_C2, NOTE_E2,
  NOTE_A3, NOTE_B3, NOTE_C3, NOTE_E3,
  NOTE_A4, NOTE_B4, NOTE_C4, NOTE_E4,
  NOTE_A5, NOTE_B5, NOTE_C5, NOTE_E5,
  NOTE_A6,

  NOTE_E6, NOTE_C6, NOTE_B6, NOTE_A6,
  NOTE_E5, NOTE_C5, NOTE_B5, NOTE_A5,
  NOTE_E4, NOTE_C4, NOTE_B4, NOTE_A4,
  NOTE_E3, NOTE_C3, NOTE_B2, NOTE_A2,
//3rd - new section
  NOTE_C3, NOTE_F3, NOTE_G3, NOTE_A3,
  NOTE_C4, NOTE_F4, NOTE_G4, NOTE_A4,
  NOTE_C5, NOTE_F5, NOTE_G5, NOTE_A5,
  NOTE_C6, NOTE_F6, NOTE_G6, NOTE_A6,

  NOTE_G6, NOTE_F6, NOTE_C6, NOTE_A5,
  NOTE_G5, NOTE_F5, NOTE_C5, NOTE_A4,
  NOTE_G4, NOTE_F4, NOTE_C4, NOTE_A3,
  NOTE_G3, NOTE_F3, NOTE_C3, NOTE_B2,

  NOTE_D3, NOTE_G3, NOTE_A3, NOTE_B3,
  NOTE_D4, NOTE_G4, NOTE_A4, NOTE_B4,
  NOTE_D5, NOTE_G5, NOTE_A5, NOTE_B5,
  NOTE_D6, NOTE_G6, NOTE_A6, NOTE_B6,

  NOTE_A6, NOTE_G6, NOTE_D6, NOTE_B5,
  NOTE_A5, NOTE_G5, NOTE_D5, NOTE_B4,
  NOTE_A4, NOTE_G4, NOTE_D4, NOTE_B3,
  NOTE_A3, NOTE_G3, NOTE_D3, 
//13
  NOTE_GS2, NOTE_C3, NOTE_DS3, NOTE_G3,
  NOTE_GS3, NOTE_C4, NOTE_DS4, NOTE_G4,
  NOTE_GS4, NOTE_C5, NOTE_DS5, NOTE_G5,
  NOTE_GS5, NOTE_C6, NOTE_DS6, NOTE_G6,

  NOTE_DS6, NOTE_C6, NOTE_GS5, NOTE_G5,
  NOTE_DS5, NOTE_C5, NOTE_GS4, NOTE_G4,
  NOTE_DS4, NOTE_C4, NOTE_GS3, NOTE_G3,
  NOTE_DS3, NOTE_C3, NOTE_GS2,

  NOTE_D3, NOTE_F3, NOTE_A3, NOTE_AS3,
  NOTE_D4, NOTE_F4, NOTE_A4, NOTE_AS4,
  NOTE_D5, NOTE_F5, NOTE_A5, NOTE_AS5,
  NOTE_D6, NOTE_F6, NOTE_A6, NOTE_AS6,
   
  NOTE_A6, NOTE_F6, NOTE_D6, NOTE_AS5,
  NOTE_A5, NOTE_F5, NOTE_D5, NOTE_AS4,
  NOTE_A4, NOTE_F4, NOTE_D4, NOTE_AS3,
  NOTE_A3, NOTE_F3, NOTE_D3, NOTE_AS2
};

int preludetempo[]
{
  16,16,16,16,
  16,16,16,16,
  16,16,16,16,
  16,16,16,16,

  16,16,16,16,
  16,16,16,16,
  16,16,16,16,
  16,16,16,16,

  16,16,16,16,
  16,16,16,16,
  16,16,16,16,
  16,16,16,16,

  16,16,16,16,
  16,16,16,16,
  16,16,16,16,
  16,16,16,16,

  16,16,16,16,
  16,16,16,16,
  16,16,16,16,
  16,16,16,16,

  16,16,16,16,
  16,16,16,16,
  16,16,16,16,
  16,16,16,16,

  16,16,16,16,
  16,16,16,16,
  16,16,16,16,
  16,16,16,16,

  16,16,16,16,
  16,16,16,16,
  16,16,16,16,
  16,16,16,16,

  16,16,16,16,
  16,16,16,16,
  16,16,16,16,
  16,16,16,16,

  16,16,16,16,
  16,16,16,16,
  16,16,16,16,
  16,16,16,16,

  16,16,16,16,
  16,16,16,16,
  16,16,16,16,
  16,16,16,16,

  16,16,16,16,
  16,16,16,16,
  16,16,16,16,
  16,16,16,16,

  16,16,16,16,
  16,16,16,16,
  16,16,16,16,
  16,16,16,16,

  16,16,16,16,
  16,16,16,16,
  16,16,16,16,
  16,16,16,16,

  16,16,16,16,
  16,16,16,16,
  16,16,16,16,
  16,16,16,16,

  16,16,16,16,
  16,16,16,16,
  16,16,16,16,
  16,16,16
};

int love[]
{
  NOTE_G5, NOTE_FS5, NOTE_E5, NOTE_C5,
  NOTE_G5, NOTE_FS5, NOTE_E5, NOTE_C5,
  NOTE_G5, NOTE_FS5, NOTE_D5, NOTE_B4,
  NOTE_G5, NOTE_FS5, NOTE_D5, NOTE_B4,

  NOTE_G5,  NOTE_A5, NOTE_G5,  NOTE_A5,
  NOTE_FS5, NOTE_A5, NOTE_G5,  NOTE_A5,
  NOTE_FS5, NOTE_A5, NOTE_FS5, NOTE_C6, 
  NOTE_C6,  NOTE_C6, NOTE_B5,  NOTE_B5
};

int lovetempo []
{
  16,16,16,16,
  16,16,16,16,
  16,16,16,16,
  16,16,16,16,

  16,16,16,16,
  16,16,16,16,
  16,16,16,16,
  16,16,16,16,
};

void setup()
{
  Serial.begin(9600);
  Serial.print("count = ");
  Serial.println(count);
  pinMode(buttonC  , INPUT_PULLUP);
  pinMode(buttonCS , INPUT_PULLUP);
  pinMode(buttonD  , INPUT_PULLUP);
  pinMode(buttonDS , INPUT_PULLUP);
  pinMode(buttonE  , INPUT_PULLUP);
  pinMode(buttonF  , INPUT_PULLUP);
  pinMode(buttonFS , INPUT_PULLUP);
  pinMode(buttonG  , INPUT_PULLUP);
  pinMode(buttonGS , INPUT_PULLUP);
  pinMode(buttonA  , INPUT_PULLUP);
  pinMode(buttonAS , INPUT_PULLUP);
  pinMode(buttonB  , INPUT_PULLUP);
  pinMode(buttonC2 , INPUT_PULLUP);
  pinMode(resetbutton , INPUT_PULLUP);
  pinMode(countbutton , INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), plus, LOW);
  attachInterrupt(digitalPinToInterrupt(2), reset, LOW);
  lcd.init();
  lcd.backlight();
  lcd.begin(20,4);
  lcd.clear();
  lcd.setCursor(0,0);
}

void loop()
{
  if (count == 1)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Flamingo");
    lcd.setCursor(0, 1);
    lcd.print("By: Kero Kero Bonito");
    flamingosong();
  }

  if (count == 2)
  {   
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hall of Fame");
    lcd.setCursor(0, 1);
    lcd.print("By: The Script");
    famesong();
  }

  if (count == 3)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Prelude");
    lcd.setCursor(0, 1);
    lcd.print("From: FF7");
    preludesong();
  }

  if (count == 4)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Best Love Song");
    lcd.setCursor(0, 1);
    lcd.print("By: T-Pain");
    lovesong();
  }
  notes(); 
}

void plus()
{
  int reading = digitalRead(countbutton);

  if (reading == LOW && !pressed) // if button is pressed and was not pressed before
  {
    Serial.println(reading);
    count++;
    halt = true;
    Serial.print("count = ");
    Serial.println(count);

    pressed = true;
  }
  else if (reading == HIGH) {
    pressed = false;
  }
}

void reset()
{
  count = 0;
  halt = true;
  Serial.print("count = ");
  Serial.println(count);
}

void notes()
{
  while (digitalRead(buttonC) == LOW)
  {
    tone(buzzer, NOTE_C4);
    lcd.setCursor ( 0, 0 ); 
    lcd.print("C - 262 Hz");
  }
  while (digitalRead(buttonCS) == LOW)
  {
    tone(buzzer, NOTE_CS4);
    lcd.setCursor ( 0, 0 ); 
    lcd.print("C# - 277 Hz");
  }
  while (digitalRead(buttonD) == LOW)
  {
    tone(buzzer, NOTE_D4);
    lcd.setCursor ( 0, 0 ); 
    lcd.print("D - 294 Hz");
  }
  while (digitalRead(buttonDS) == LOW)
  {
    tone(buzzer, NOTE_DS4);
    lcd.setCursor ( 0, 0 ); 
    lcd.print("D# - 311 Hz");
  }
  while (digitalRead(buttonE) == LOW)
  {
    tone(buzzer, NOTE_E4);
    lcd.setCursor ( 0, 0 );
    lcd.print("E - 330 Hz");
  }
  while (digitalRead(buttonF) == LOW)
  {
    tone(buzzer, NOTE_F4);
    lcd.setCursor ( 0, 0 ); 
    lcd.print("F - 349 Hz");
  }
  while (digitalRead(buttonFS) == LOW)
  {
    tone(buzzer, NOTE_FS4);
    lcd.setCursor ( 0, 0 ); 
    lcd.print("F# - 370 Hz");
  }
  while (digitalRead(buttonG) == LOW)
  {
    tone(buzzer, NOTE_G4);
    lcd.setCursor ( 0, 0 ); 
    lcd.print("G - 392 Hz");
  }
  while (digitalRead(buttonGS) == LOW)
  {
    tone(buzzer, NOTE_GS4);
    lcd.setCursor ( 0, 0 ); 
    lcd.print("G# - 415 Hz");
  }
  while (digitalRead(buttonA) == LOW)
  {
    tone(buzzer, NOTE_A4);
    lcd.setCursor ( 0, 0 ); 
    lcd.print("A - 440 Hz");
  }
  while (digitalRead(buttonAS) == LOW)
  {
    tone(buzzer, NOTE_AS4);
    lcd.setCursor ( 0, 0 ); 
    lcd.print("A# - 466 Hz");
  }
  while (digitalRead(buttonB) == LOW)
  {
    tone(buzzer, NOTE_B4);
    lcd.setCursor ( 0, 0 ); 
    lcd.print("B - 494 Hz");
  }
  while (digitalRead(buttonC2) == LOW)
  {
    tone(buzzer, NOTE_C5);
    lcd.setCursor ( 0, 0 ); 
    lcd.print("C - 523 Hz");
  } 
  lcd.clear();
  noTone(buzzer);
}

void flamingosong()
{
  int size = sizeof(flamingo) / sizeof(int);
  for (int thisNote = 0; (thisNote < size && !halt); thisNote++)
  {
    int noteDuration = tempo[thisNote];

    tone(buzzer, flamingo[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1;
    delay(pauseBetweenNotes);
  }
  halt = false;
}

void famesong()
{
  int size = sizeof(fame) / sizeof(int);
  for (int thisNote = 0; (thisNote < size && !halt); thisNote++)
  {
    int noteDuration = (60000 / fameBPM) / (32 / fametempo[thisNote]);

    tone(buzzer, fame[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1;
    delay(pauseBetweenNotes);
  }
  halt = false;
}

void preludesong()
{
  int size = sizeof(prelude) / sizeof(int);
  for (int thisNote = 0; (thisNote < size && !halt); thisNote++)
  {
    int noteDuration = (60000 / preludeBPM) / (32 / preludetempo[thisNote]);

    tone(buzzer, prelude[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1;
    delay(pauseBetweenNotes);
  }
  halt = false;
}

void lovesong()
{
  int size = sizeof(love) / sizeof(int);
  for (int thisNote = 0; (thisNote < size && !halt); thisNote++)
  {
    int noteDuration = (60000 / loveBPM) / (32 / lovetempo[thisNote]);

    tone(buzzer, love[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1;
    delay(pauseBetweenNotes);
  }
  halt = false;
}
