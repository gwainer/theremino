

/* 
 * Theremino - Theremin inspired Arduino.
 */
const int  c = 3830;    // 261 Hz 
const int  d = 3400;    // 294 Hz 
const int  e = 3038;    // 329 Hz 
const int  f = 2864;    // 349 Hz 
const int  g = 2550;    // 392 Hz 
const int  a = 2272;    // 440 Hz 
const int  b = 2028;    // 493 Hz 
// Define a special note, 'R', to represent a rest
const int  R = 0;

const int triggerPin = 2;
const int echoPin = 3;
const int speakerPin = 9;
const int tempo = 10000;
const int rest = 100;

void setup() {
   //inicializa porta serial
  Serial.begin(9600); 
}

void loop() {
 long duration, inches, cm;
 
 pinMode(triggerPin, OUTPUT);
 digitalWrite(triggerPin, LOW);
 delayMicroseconds(2);
 digitalWrite(triggerPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(triggerPin, LOW);

 pinMode(echoPin, INPUT);
 duration = pulseIn(echoPin, HIGH);
 inches = msToIn(duration);
 cm = msToCm(duration);
 playTone(cmToTone(cm));
 
 Serial.print(inches);
 Serial.print("in, ");
 Serial.print(cm);
 Serial.println("cm");
 Serial.print("Tone: ");
 Serial.println(cmToTone(cm));
 
 
 delay(100);
}

long msToIn(long ms) {
   return ms / 74 / 2;
}

long msToCm(long ms) {
   return ms / 29 / 2;
}

int cmToTone(long cm) {
  int tone = -1;
  pinMode(speakerPin, OUTPUT); 
  
  switch(cm) {
   case 1:
   case 2:
     tone = c;
     break;
   case 3:
   case 4:
     tone = d;
     break;
   case 5:
   case 6:
     tone = e;
     break;
   case 7:
   case 8:
     tone = f;
     break;
   case 9:
   case 10:
     tone = g;
     break;
   case 11:
   case 12:
     tone = a;
     break;
   default:
     tone = b;
     break;
  }
  return tone;
}  

int playTone(int tone) {
    long elapsed = 0;
    
    while (elapsed < 999999) {
      digitalWrite(speakerPin, HIGH);
      delayMicroseconds(tone / 2);
      
      digitalWrite(speakerPin, LOW);
      delayMicroseconds(tone / 2);
      
      elapsed += tone;
    }     
}
