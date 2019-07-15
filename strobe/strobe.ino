
#define LED_PIN     12

#define BRIGHTNESS  255
#define STROBE_TOL  50
#define VALVE_TOL  25



int strobePotPin = 2;    // select the input pin for the potentiometer
int valvePotPin = 3; 
int valvePin = 3;    // select the input pin for the potentiometer
int valveFq = 0; 
int tempValveFq = 0; 
int strobeFq = 0;
int valvePWM = 0;// variable to store the value coming from the sensor



void setup() {
  // put your setup code here, to run once:
  
  delay(3000); // sanity delay
  Serial.begin(9600);      // open the serial port at 9600 bps: 
  pinMode(valvePin, OUTPUT);
  //int valvePWM = map((valveFq*2),0,490,0,255);
  //analogWrite(valvePin,valvePWM);   
}

unsigned long ms = 0; 
unsigned long pms = 0;
int is_up = 0; 
void loop() {
  // put your main code here, to run repeatedly:
  strobeFq = analogRead(strobePotPin)/STROBE_TOL;
  tempValveFq = analogRead(valvePotPin);///VALVE_TOL;// read the value from the sensor
  //Serial.println(tempValveFq);
  if(valveFq != tempValveFq){
    valveFq = tempValveFq;
    valvePWM = map(valveFq,0,1021,0,255);
    analogWrite(valvePin,valvePWM);  
    //Serial.println(valvePWM);
  }

  ms = millis();

  unsigned long delta = ms-pms; 

  if (delta>strobeFq){
    Serial.println(strobeFq);
    Serial.println(delta); 
    if (is_up){
      digitalWrite(LED_PIN, LOW);
    }
    else {
      digitalWrite(LED_PIN, HIGH);
    }
    is_up = 1-is_up; 
   pms = ms; 
  }
}
