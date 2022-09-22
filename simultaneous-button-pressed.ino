
const int ledPin = 13;      // the number of the LED pin
int ledState = LOW;         


const int buttonPin = 7;
const int buttonPin2 = 8;
const int buttonPin3 = 9;
    

int buttonState;             
int lastButtonState = 0;   

int buttonState2;             
int lastButtonState2 = 0;   

int buttonState3;             
int lastButtonState3 = 0;   


unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;   

unsigned long lastDebounceTime2 = 0;  
unsigned long debounceDelay2 = 50;   

unsigned long lastDebounceTime3 = 0;  
unsigned long debounceDelay3 = 50;   



void setup() {
  pinMode(buttonPin, OUTPUT);
  pinMode(buttonPin2, OUTPUT);
  pinMode(buttonPin3, OUTPUT);
  pinMode(ledPin, OUTPUT);

  
  digitalWrite(ledPin, ledState);
  Serial.begin(9600);
}




void loop() {
  int reading = digitalRead(buttonPin);
  int reading2 = digitalRead(buttonPin2);
  int reading3 = digitalRead(buttonPin3);


  //code cada boton
  if (reading != lastButtonState) {
  
    lastDebounceTime = millis();
  }
  
  if (reading2 != lastButtonState2) {
  
    lastDebounceTime2 = millis();
  }
  
  if (reading3 != lastButtonState3) {
  
    lastDebounceTime3 = millis();
  }



  if ((millis() - lastDebounceTime) > debounceDelay) {
  
    if (reading != buttonState) {
      buttonState = reading;

  
      if (buttonState == HIGH) {
        Serial.println("Red");
        ledState = !ledState;
      }
    }
  }



  if ((millis() - lastDebounceTime2) > debounceDelay2) {
  
    if (reading2 != buttonState2) {
      buttonState2 = reading2;

  
      if (buttonState2 == HIGH) {
        Serial.println("Blue");
        ledState = !ledState;
      }
    }
  }


  if ((millis() - lastDebounceTime3) > debounceDelay3) {
  
    if (reading3 != buttonState3) {
      buttonState3 = reading3;

  
      if (buttonState3 == HIGH) {
        Serial.println("Green!");
        ledState = !ledState;
      }
    }
  }

  
  digitalWrite(ledPin, ledState);

  
  lastButtonState = reading;
  lastButtonState2 = reading2;
  lastButtonState3 = reading3;
}
