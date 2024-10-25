//Initiallizing - constants
const int sensorPin = 8;
const int ledPin = 13;
const int learningPeriod =30*1000; // it takes 30s fot the PIR sensor to adapt to its enviroment
const int buzz=12;

//Initalizing - variable
int learningCompleted = 0;

void setup() 
{
Serial.begin(115200);
 //Inputs
pinMode(sensorPin, INPUT); //PIR sensor
 //Outputs
pinMode(ledPin, OUTPUT); //LED 
pinMode (buzz, OUTPUT); //Piezo
Serial.println("Learning enivroment");

}

void loop() {
 
if(millis()<learningPeriod){// If statement- the time elapsed is less then the learning period int:  
delay(20); //20ms delay
return; 
}
if(learningCompleted == 0) { //If statement- if the int "LearningCompleted" is equal to 0;
learningCompleted = 1; // int "LearningCompleted is eual to 1;
Serial.println("Completed"); //Print "Completed" to the Serial Monitor
}

if(digitalRead(sensorPin) == HIGH) { //If statement -PIR sensor detects movement, the following happens: 
Serial.println("Movement"); //Printing "Movement on the Serial Monitor
digitalWrite(ledPin,HIGH); //LED is turned on  
tone(buzz, 1000); //Piezo alarm is turned on at a frequency of 1000Hz
} 
     
  else { // If no movement is detected by the PIR then;
Serial.println("No movement"); // No movement is printed on the Serial Monitor
digitalWrite(ledPin,LOW); // LED is off
digitalWrite(buzz, LOW); // Piezo is also off
}
  
delay(1000); //A 1s delay between loops
}
