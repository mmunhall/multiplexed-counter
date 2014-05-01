
#include "SevSeg.h"

//Create an instance of the object.
SevSeg sevseg;
const int D1_DOWN_BUTTON = 14;
const int D1_UP_BUTTON = 15;
const int D2_DOWN_BUTTON = 16;
const int D2_UP_BUTTON = 17;
const int D3_DOWN_BUTTON = 18;
const int D3_UP_BUTTON = 19;
boolean d1_up_current = LOW;
boolean d1_up_last = LOW;
boolean d1_down_current = LOW;
boolean d1_down_last = LOW;
boolean d2_up_current = LOW;
boolean d2_up_last = LOW;
boolean d2_down_current = LOW;
boolean d2_down_last = LOW;
boolean d3_up_current = LOW;
boolean d3_up_last = LOW;
boolean d3_down_current = LOW;
boolean d3_down_last = LOW;

int val = 0;

void setup() {
  pinMode(D1_UP_BUTTON, INPUT);
  pinMode(D1_DOWN_BUTTON, INPUT);
  pinMode(D2_UP_BUTTON, INPUT);
  pinMode(D2_DOWN_BUTTON, INPUT);
  pinMode(D3_UP_BUTTON, INPUT);
  pinMode(D3_DOWN_BUTTON, INPUT);
  
  // common anode display, with the digit pins connected
  //from 2-5 and the segment pins connected from 6-13
  sevseg.Begin(1,2,3,4,5,6,7,8,9,10,11,12,13);
  //Set the desired brightness (0 to 100);
  sevseg.Brightness(90);
  
  Serial.begin(9600);
}

void loop() {
  d1_up_current = debounce(D1_UP_BUTTON, d1_up_last);
  d1_down_current = debounce(D1_DOWN_BUTTON, d1_down_last);
  d2_up_current = debounce(D2_UP_BUTTON, d2_up_last);
  d2_down_current = debounce(D2_DOWN_BUTTON, d2_down_last);
  d3_up_current = debounce(D3_UP_BUTTON, d3_up_last);
  d3_down_current = debounce(D3_DOWN_BUTTON, d3_down_last);
  
  Serial.println(d2_down_current);
    
  if (d1_up_last == LOW && d1_up_current == HIGH) {
    Serial.println("D1 UP");
    int digit = getNthDigit(val, 3);
    if (digit == 9) {
      val -= 900; 
    } else {
      val += 100;
    }
    Serial.println(val);
  }
  d1_up_last = d1_up_current;
  
  if (d1_down_last == LOW && d1_down_current == HIGH) {
    Serial.println("D1 DOWN");
    int digit = getNthDigit(val, 3);
    if (digit == 0) {
      val += 900; 
    } else {
      val -= 100;
    }
    Serial.println(val);
  }
  d1_down_last = d1_down_current;
  
  if (d2_up_last == LOW && d2_up_current == HIGH) {
    Serial.println("D2 UP");
    int digit = getNthDigit(val, 2);
    if (digit == 9) {
       val -= 90; 
    } else {
      val += 10;
    }
    Serial.println(val);
  }
  d2_up_last = d2_up_current;
  
  
  if (d2_down_last == LOW && d2_down_current == HIGH) {
    Serial.println("D2 DOWN");
    int digit = getNthDigit(val, 2);
    if (digit == 0) {
       val += 90; 
    } else {
      val -= 10;
    }
    Serial.println(val);
  }
  d2_down_last = d2_down_current;  
  
  if (d3_up_last == LOW && d3_up_current == HIGH) {
    Serial.println("D3 UP");
    int digit = getNthDigit(val, 1);
    if (digit == 9) {
      val -= 9; 
    } else {
      val += 1;
    }
    Serial.println(val);
  }
  d3_up_last = d3_up_current;
  
  if (d3_down_last == LOW && d3_down_current == HIGH) {
    Serial.println("D3 DOWN");
    int digit = getNthDigit(val, 1);
    if (digit == 0) {
      val += 9; 
    } else {
      val -= 1;
    }
    Serial.println(val);
  }
  d3_down_last = d3_down_current;
  
  sevseg.NewNum(val, (byte) 3);
  sevseg.PrintOutput();
}

boolean debounce(boolean button, boolean last) {
  boolean current = digitalRead(button);
  if (last != current) {
    delay(2);
  }
  current = digitalRead(button);
  return current; 
} 

int getNthDigit(int number, int n) {    
  return (int) ((number / ((int) pow(10, n - 1))) % 10);
}








