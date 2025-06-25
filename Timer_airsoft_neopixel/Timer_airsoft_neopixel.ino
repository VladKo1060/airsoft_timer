#include <Servo.h>
#include "TM1637.h"
#include <Adafruit_NeoPixel.h>

#define CLK 2
#define DIO 3

#define but1_pin_timer_airsoft 4
#define but2_pin_timer_airsoft 5
#define but3_pin_timer_airsoft 6
#define but4_pin_timer_airsoft 7

#define buzzer_pin_timer_airsoft 8
#define servo_pin_timer_airsoft 9
#define password_strip_timer_airsoft 10

#define drebezg_timer_airsoft 500

#define tone_many_time_timer_airsoft 500
#define tone_few_time_timer_airsoft 750
#define time_tone2_activation_timer_airsoft 5

#define time_many_time_timer_airsoft 250
#define time_few_time_timer_airsoft 250

#define degrees_disconnect_contacts_timer_airsoft 130
#define degrees_connect_contacts_timer_airsoft 141
#define time_connect_contacts_timer_airsoft 1000
#define time_delay_boom_timer_airsoft 0

#define red_timer_airsoft 50
#define green_timer_airsoft 50
#define blue_timer_airsoft 50

#define light_timer_airsoft 50

unsigned long time_ = 0;
unsigned long time_boom = 10;

short int fuze_cod[4] = {0, 0, 0, 0};
short int defuze_cod[4] = {0, 0, 0, 0};
short int prozes_cod[4] = {0, 0, 0, 0};

bool flag_timer = 0;

short int ind_pass_prozes = 0;

TM1637 tm1637(CLK, DIO);
Servo boom;
Adafruit_NeoPixel strip (4, password_strip_timer_airsoft, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  
  boom.attach(servo_pin_timer_airsoft);
  boom.write(degrees_disconnect_contacts_timer_airsoft);
  
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;

  strip.begin();                     // инициализируем объект NeoPixel
  strip.show();                     // отключаем все пиксели на ленте
  strip.setBrightness(light_timer_airsoft);  // указываем яркость (максимум 255)

  pinMode(but1_pin_timer_airsoft, INPUT_PULLUP);
  pinMode(but2_pin_timer_airsoft, INPUT_PULLUP);
  pinMode(but3_pin_timer_airsoft, INPUT_PULLUP);
  pinMode(but4_pin_timer_airsoft, INPUT_PULLUP);


  print_disp(mili_to_int_minut(time_boom * 1000), 1);
  while (digitalRead(but2_pin_timer_airsoft)){
    if (!digitalRead(but1_pin_timer_airsoft)){
      time_boom += 1;
      print_disp(mili_to_int_minut(time_boom * 1000), 1);
      delay(drebezg_timer_airsoft);
    }
    else if (!digitalRead(but3_pin_timer_airsoft)){
      time_boom -= 1;
      print_disp(mili_to_int_minut(time_boom * 1000), 1);
      delay(drebezg_timer_airsoft);
    }
  }
  delay(drebezg_timer_airsoft);

  print_disp(mili_to_int_minut(time_boom * 1000), 0);


  
  short int i = 0;
  while (i < 4){
    if (!digitalRead(but1_pin_timer_airsoft)){
      fuze_cod[i] = 1;
      strip.setPixelColor(i, red_timer_airsoft, green_timer_airsoft, blue_timer_airsoft);
      strip.show();
      i += 1;
      delay(drebezg_timer_airsoft);
    }
    else if (!digitalRead(but2_pin_timer_airsoft)){
      fuze_cod[i] = 2;
      strip.setPixelColor(i, red_timer_airsoft, green_timer_airsoft, blue_timer_airsoft);
      strip.show();
      i += 1;
      delay(drebezg_timer_airsoft);
    }
    else if (!digitalRead(but3_pin_timer_airsoft)){
      fuze_cod[i] = 3;
      strip.setPixelColor(i, red_timer_airsoft, green_timer_airsoft, blue_timer_airsoft);
      strip.show();
      i += 1;
      delay(drebezg_timer_airsoft);
    }
    else if (!digitalRead(but4_pin_timer_airsoft)){
      fuze_cod[i] = 4;
      strip.setPixelColor(i, red_timer_airsoft, green_timer_airsoft, blue_timer_airsoft);
      strip.show();
      i += 1;
      delay(drebezg_timer_airsoft);
    }
  }
  Serial.println(fuze_cod[0]);
  Serial.println(fuze_cod[1]);
  Serial.println(fuze_cod[2]);
  Serial.println(fuze_cod[3]);
  Serial.println();
  for(i = 0;i < 4;i++) strip.setPixelColor(i, 0, 0, 0);
  strip.show();



  i = 0;
  while (i < 4){
    if (!digitalRead(but1_pin_timer_airsoft)){
      defuze_cod[i] = 1;
      strip.setPixelColor(i, red_timer_airsoft, green_timer_airsoft, blue_timer_airsoft);
      strip.show();
      i += 1;
      delay(drebezg_timer_airsoft);
    }
    else if (!digitalRead(but2_pin_timer_airsoft)){
      defuze_cod[i] = 2;
      strip.setPixelColor(i, red_timer_airsoft, green_timer_airsoft, blue_timer_airsoft);
      strip.show();
      i += 1;
      delay(drebezg_timer_airsoft);
    }
    else if (!digitalRead(but3_pin_timer_airsoft)){
      defuze_cod[i] = 3;
      strip.setPixelColor(i, red_timer_airsoft, green_timer_airsoft, blue_timer_airsoft);
      strip.show();
      i += 1;
      delay(drebezg_timer_airsoft);
    }
    else if (!digitalRead(but4_pin_timer_airsoft)){
      defuze_cod[i] = 4;
      strip.setPixelColor(i, red_timer_airsoft, green_timer_airsoft, blue_timer_airsoft);
      strip.show();
      i += 1;
      delay(drebezg_timer_airsoft);
    }
  }
  Serial.println(defuze_cod[0]);
  Serial.println(defuze_cod[1]);
  Serial.println(defuze_cod[2]);
  Serial.println(defuze_cod[3]);
  Serial.println();
  for(i = 0;i < 4;i++) strip.setPixelColor(i, 0, 0, 0);
  strip.show();
}

void loop() {
  if (flag_timer){
    if (time_boom > 0){
      if (millis() - time_ >= 1000){
        print_disp(mili_to_int_minut(time_boom * 1000), 1);
        tone(buzzer_pin_timer_airsoft, tone_many_time_timer_airsoft, time_many_time_timer_airsoft);
        time_ = millis();
        time_boom -= 1;
      }
      if (millis() - time_ >= 500){
        print_disp(mili_to_int_minut(time_boom * 1000), 0);
        if (time_boom < time_tone2_activation_timer_airsoft + 1) tone(buzzer_pin_timer_airsoft, tone_few_time_timer_airsoft, time_few_time_timer_airsoft);
        //time_ = millis();
      }
    }
    else {
      delay(time_delay_boom_timer_airsoft);
      boom.write(degrees_connect_contacts_timer_airsoft);
      delay(time_connect_contacts_timer_airsoft);
      boom.write(degrees_disconnect_contacts_timer_airsoft);
      for (;;){}
    }
  }



  if (!digitalRead(but1_pin_timer_airsoft)){
    prozes_cod[ind_pass_prozes] = 1;
    strip.setPixelColor(ind_pass_prozes, red_timer_airsoft, green_timer_airsoft, blue_timer_airsoft);
    strip.show();
    ind_pass_prozes += 1;
    delay(drebezg_timer_airsoft);
  }
  else if (!digitalRead(but2_pin_timer_airsoft)){
    prozes_cod[ind_pass_prozes] = 2;
    strip.setPixelColor(ind_pass_prozes, red_timer_airsoft, green_timer_airsoft, blue_timer_airsoft);
    strip.show();
    ind_pass_prozes += 1;
    delay(drebezg_timer_airsoft);
  }
  else if (!digitalRead(but3_pin_timer_airsoft)){
    prozes_cod[ind_pass_prozes] = 3;
    strip.setPixelColor(ind_pass_prozes, red_timer_airsoft, green_timer_airsoft, blue_timer_airsoft);
    strip.show();
    ind_pass_prozes += 1;
    delay(drebezg_timer_airsoft);
  }
  else if (!digitalRead(but4_pin_timer_airsoft)){
    prozes_cod[ind_pass_prozes] = 4;
    strip.setPixelColor(ind_pass_prozes, red_timer_airsoft, green_timer_airsoft, blue_timer_airsoft);
    strip.show();
    ind_pass_prozes += 1;
    delay(drebezg_timer_airsoft);
  }


  if (ind_pass_prozes == 4){
    if (flag_timer){
      if (paaword_richtig(prozes_cod, defuze_cod))flag_timer = 0;
      //prozes_cod = {0, 0, 0, 0};
    }
    else {
      if (paaword_richtig(prozes_cod, fuze_cod))flag_timer = 1;
      //prozes_cod = {0, 0, 0, 0};
    }
    ind_pass_prozes = 0;
    for(short int i = 0;i < 4;i++) strip.setPixelColor(i, 0, 0, 0);
    strip.show();
  }
  
}


void print_disp(int integ, bool point_on){
  tm1637.point(point_on);
  tm1637.display(3, integ % 10);
  integ = integ / 10;
  tm1637.display(2, integ % 10);
  integ = integ / 10;
  tm1637.display(1, integ % 10);
  integ = integ / 10;
  tm1637.display(0, integ % 10);
}

int mili_to_int_minut(unsigned long time_miles){
  unsigned int time_sec = time_miles / 1000;
  if (time_sec < 60) return time_sec;
  short int sec = time_sec % 60;
  int minut = time_sec / 60;
  return minut * 100 + sec;
}

bool paaword_richtig(short int pass_input[4], short int pass_richtig[4]){
  for(short int i = 0;i < 4;i++){
    if (pass_input[i] != pass_richtig[i]) return false;
  }
  return true;
}
