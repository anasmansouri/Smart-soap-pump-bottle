
#include <Arduino_FreeRTOS.h>
#include <Servo.h>

//define arduino pins numbers 
const int trigPin = 9;
const int echoPin = 10;

// defines variables
Servo myservo ;
long duration;
int distance;


void setup() {
myservo.attach(8);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication

// Creating Task
xTaskCreate(tach_1,NULL,configMINIMAL_STACK_SIZE,NULL,1,NULL);
   vTaskStartScheduler();
}
// Empty loop
void loop()
{
  // Empty. Things are done in Tasks.
}

// task function 
void tach_1(void)
{
    while(1){   
            // Clears the trigPin
            digitalWrite(trigPin, LOW);
            delayMicroseconds(2);
            // Sets the trigPin on HIGH state for 10 micro seconds
            digitalWrite(trigPin, HIGH);
            delayMicroseconds(10);
            digitalWrite(trigPin, LOW);
            // Reads the echoPin, returns the sound wave travel time in microseconds
            duration = pulseIn(echoPin, HIGH);
            // Calculating the distance
            distance= duration*0.034/2;
            // Prints the distance on the Serial Monitor
            Serial.print("Distance: ");
            Serial.println(distance);
            if(distance <10){
            
              myservo.write(map(180,0,180,0,180));
            }else{
              myservo.write(map(0,0,180,0,180));
            }
    }
}
