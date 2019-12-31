#include <DigiUSB.h>

void run_hello_seq(int delay_ms) {
  digitalWrite(0, HIGH);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  DigiUSB.delay(delay_ms);
  digitalWrite(0, LOW);
  digitalWrite(1, HIGH);
  digitalWrite(2, LOW);
  DigiUSB.delay(delay_ms);
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, HIGH);
  DigiUSB.delay(delay_ms); 
}

void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);  
  DigiUSB.begin();

  run_hello_seq(100);
  run_hello_seq(100);
  run_hello_seq(100);
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
}

void set_led(int lastPort, int lastState) {
  if (lastPort == 0) {
    if (lastState == '0') {
      digitalWrite(0, LOW);
    }
    if (lastState == '1') {
      digitalWrite(0, HIGH);
    }  
  }
  if (lastPort == 1) {
    if (lastState == '0') {
      digitalWrite(1, LOW);
    }
    if (lastState == '1') {
      digitalWrite(1, HIGH);
    }  
  }
  if (lastPort == 2) {
    if (lastState == '0') {
      digitalWrite(2, LOW);
    }
    if (lastState == '1') {
      digitalWrite(2, HIGH);
    }  
  }
}

void process_input() {

  int Port0State;
  int Port1State;
  int Port2State;
  int Timeout;
  int Delimiter;
  
  while (true) {
    if (DigiUSB.available()) {
      // read 3 symbols
      Port0State = DigiUSB.read();
      DigiUSB.delay(10);
      Port1State = DigiUSB.read();
      DigiUSB.delay(10);
      Port2State = DigiUSB.read(); 
      DigiUSB.delay(10);
      Timeout = DigiUSB.read(); 
      DigiUSB.delay(10);
      Delimiter = DigiUSB.read();  
      DigiUSB.delay(10);
      
      if (Port0State == '\n') {
        break;  
      }    
      if (Delimiter != '-') {
        DigiUSB.write("err");
        DigiUSB.write('\n');
        break;  
      }
      
      set_led(0,Port0State);      
      set_led(1,Port1State);
      set_led(2,Port2State); 
      if (Timeout=='1') {
        DigiUSB.delay(50);
      }
      if (Timeout=='2') {
        DigiUSB.delay(100);
      }
      if (Timeout=='3') {
        DigiUSB.delay(300);
      }
      if (Timeout=='4') {
        DigiUSB.delay(500);
      }
      if (Timeout=='5') {
        DigiUSB.delay(1000);
      }
    }

    DigiUSB.delay(10);
  }
}

void loop() {
  process_input();
}
