int Pin2 =  2;     

int Pin3 =  3;

int Pin4 =  4;

int Pin5 =  5;

int State2 = 0;

int State3 = 0;

int State4 = 0;

int State5 = 0;

void setup() {

 


 

Serial.begin(9600);

 

pinMode(Pin2, INPUT);  

pinMode(Pin3, INPUT);  

pinMode(Pin4, INPUT);  

pinMode(Pin5, INPUT);  

 

}

 

void loop(){

 

State2 = digitalRead(Pin2);

State3 = digitalRead(Pin3);

State4 = digitalRead(Pin4);

State5 = digitalRead(Pin5);

 

if (State2 == HIGH) {     

Serial.println("Signal DO");

} 

if (State3 == HIGH) {     

Serial.println("Signal D1");

} 

if (State4 == HIGH) {     

Serial.println("Signal D2");

} 

if (State5 == HIGH) {     

Serial.println("Signal D3");

} 

 

 

}


