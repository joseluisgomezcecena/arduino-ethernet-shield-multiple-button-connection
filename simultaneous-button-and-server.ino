
#include <SPI.h>
#include <Ethernet.h>


void(* resetFunc) (void) = 0;//reset function is built-in

//Shield code.

byte mac[] = { 0xDE, 0xAD, 0xDB, 0xEF, 0xFE, 0xFD };


IPAddress server(192,168,1,141); 
//char server[] = "http://mxmtsvrandon1"; 


//IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 8, 54);
IPAddress myDns(192, 168, 0, 1);

EthernetClient client;


// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true; 


//end shield code.



const int ledPin = 13;      // the number of the LED pin
int ledState = LOW;         


const int buttonPin = 7; //rojo
const int buttonPin2 = 8;//azul
const int buttonPin3 = 9;//verde
    

//rojo
int buttonState;             
int lastButtonState = 0;
int counter = 0;   

//azul
int buttonState2;             
int lastButtonState2 = 0;   
int counter2 = 0;

//verde
int buttonState3;             
int lastButtonState3 = 0;
int counter3 = 0;   


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

  Serial.println("Start...");

  //Shield Code.
  Ethernet.init(10);  // Most Arduino shields

  Serial.println("Initialize Ethernet with DHCP:");

    
   if (Ethernet.begin(mac) == 0) 
   {
        Serial.println("Failed to configure Ethernet using DHCP");
        // Check for Ethernet hardware present
        if (Ethernet.hardwareStatus() == EthernetNoHardware) 
        {
            Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
            while (true) {
                delay(1); // do nothing, no point running without Ethernet hardware
            }
        }
        if (Ethernet.linkStatus() == LinkOFF) 
        {
            Serial.println("Ethernet cable is not connected.");
        }
        // try to congifure using IP address instead of DHCP:
        Ethernet.begin(mac, ip, myDns);
    } 
    else 
    {
        Serial.print("  DHCP assigned IP ");
        Serial.println(Ethernet.localIP());
    }
    
    // give the Ethernet shield a second to initialize:
    delay(1000);
    Serial.print("connecting to ");
    Serial.print(server);
    Serial.println("...");

 //end shield code.

  
  
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

        counter++;
        delay(10);
        Serial.println(counter);

        if(counter >= 10)
        {
          Serial.println("regresar a 0");
          //shield code
        
            digitalWrite(LED_BUILTIN, HIGH);
            delay(50);
      
            // if you get a connection, report back via serial:
            if (client.connect(server, 80)== 1) 
            {
                Serial.print("connected to ");
                Serial.println(client.remoteIP());
                // Make a HTTP request:
                client.println("GET /production-tracker-medcomp/Api/v1/insert.php?site=1037&value=10 HTTP/1.1");
                client.println("Host: 192.168.1.141");
                client.println("Connection: close");
                client.println();
            } 
            else 
            {
                // if you didn't get a connection to the server:
                Serial.println("connection failed");
                delay(1000);
                Serial.println("Trying to reconnect...");
                delay(1000);
    
                resetFunc();
            }
            beginMicros = micros();
            // if there are incoming bytes available
            // from the server, read them and print them:
            int len = client.available();
            if (len > 0) 
            {
                byte buffer[80];
                if (len > 80) len = 80;
                client.read(buffer, len);
                if (printWebData) {
                    Serial.write(buffer, len); // show in the serial monitor (slows some boards)
                }
                byteCount = byteCount + len;
            }
    
            // if the server's disconnected, stop the client:
            if (!client.connected()) 
            {
                endMicros = micros();
                Serial.println();
                Serial.println("disconnecting.");
                client.stop();
                Serial.print("Received ");
                Serial.print(byteCount);
                Serial.print(" bytes in ");
                float seconds = (float)(endMicros - beginMicros) / 1000000.0;
                Serial.print(seconds, 4);
                float rate = (float)byteCount / seconds / 1000.0;
                Serial.print(", rate = ");
                Serial.print(rate);
                Serial.print(" kbytes/second");
                Serial.println();
    
                setup();
    
                // do nothing forevermore:
                while (true) 
                {
                    delay(1000);
                }
            }
    
            
           //shield code
           
           counter = 0;
        }//if counter
      }
    }
  }



  if ((millis() - lastDebounceTime2) > debounceDelay2) {
  
    if (reading2 != buttonState2) {
      buttonState2 = reading2;

  
      if (buttonState2 == HIGH) {
        Serial.println("Blue");
        ledState = !ledState;

        counter2++;
        //code
        delay(10);
        Serial.println(counter);

        if(counter2 >= 10)
        {
            Serial.println("Regresando a 0 azul.");
            //shield code
            
            digitalWrite(LED_BUILTIN, HIGH);
            delay(50);
      
            // if you get a connection, report back via serial:
            if (client.connect(server, 80)== 1) 
            {
                Serial.print("connected to ");
                Serial.println(client.remoteIP());
                // Make a HTTP request:
                client.println("GET /production-tracker-medcomp/Api/v1/insert_b.php?site=1038&value=10 HTTP/1.1");
                client.println("Host: 192.168.1.141");
                client.println("Connection: close");
                client.println();
    
           
    
    
            } 
            else 
            {
                // if you didn't get a connection to the server:
                Serial.println("connection failed");
                delay(1000);
                Serial.println("Trying to reconnect...");
                delay(1000);
    
                resetFunc();
            }
            beginMicros = micros();
            // if there are incoming bytes available
            // from the server, read them and print them:
            int len = client.available();
            if (len > 0) 
            {
                byte buffer[80];
                if (len > 80) len = 80;
                client.read(buffer, len);
                if (printWebData) {
                    Serial.write(buffer, len); // show in the serial monitor (slows some boards)
                }
                byteCount = byteCount + len;
            }
    
            // if the server's disconnected, stop the client:
            if (!client.connected()) 
            {
                endMicros = micros();
                Serial.println();
                Serial.println("disconnecting.");
                client.stop();
                Serial.print("Received ");
                Serial.print(byteCount);
                Serial.print(" bytes in ");
                float seconds = (float)(endMicros - beginMicros) / 1000000.0;
                Serial.print(seconds, 4);
                float rate = (float)byteCount / seconds / 1000.0;
                Serial.print(", rate = ");
                Serial.print(rate);
                Serial.print(" kbytes/second");
                Serial.println();
    
                setup();
    
                // do nothing forevermore:
                while (true) 
                {
                    delay(1000);
                }
            }
    
            
           //shield code
          counter2 = 0;
        }




        //code end
        
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
