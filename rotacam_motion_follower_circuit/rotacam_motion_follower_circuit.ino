#include <Servo.h> 

Servo myservohor,myservover;

const int Lin = 11, Rin = 13, Lout = 8, Rout = 12, upin = 4, dnin = 6, upout = 3, dnout = 5, serhor = 9, server = 10 ; //setting sensor pins and servo pin


long Rduration, Lduration, Rinches, Linches, uduration, dduration, uinches, dinches;

int threshold = 20; //Sensor threshold in inches

int anglehor = 90; //Initial angle

int anglever = 90; //Initial angle

void setup() {
  myservohor.attach(serhor); 
  myservover.attach(server);
  Serial.begin(9600);
}

void loop()
{
  
  pinMode(Rin, OUTPUT);
  digitalWrite(Rin, LOW);
  digitalWrite(Rin, HIGH);
  digitalWrite(Rin, LOW);
 
  Rduration = pulseIn(Rout, HIGH);
  
  pinMode(Lin, OUTPUT);
  digitalWrite(Lin, LOW);
  digitalWrite(Lin, HIGH);
  digitalWrite(Lin, LOW);
  
  Lduration = pulseIn(Lout, HIGH);
  
  pinMode(upin, OUTPUT);
  digitalWrite(upin, LOW);
  digitalWrite(upin, HIGH);
  digitalWrite(upin, LOW);

  uduration = pulseIn(upout, HIGH);
  
  pinMode(dnin, OUTPUT);
  digitalWrite(dnin, LOW);
  digitalWrite(dnin, HIGH);
  digitalWrite(dnin, LOW);
  
  dduration = pulseIn(dnout, HIGH);
  
  // convert the time into a distance
  Rinches = microsecondsToInches(Rduration);
  Linches = microsecondsToInches(Lduration);
  uinches = microsecondsToInches(uduration);
  dinches = microsecondsToInches(dduration);
  Serial.println("up=");
  Serial.println(uinches);
  Serial.println("down=");
  Serial.println(dinches);
  Serial.println("right=");
  Serial.println(Rinches);
  Serial.println("left=");
  Serial.println(Linches);
  follow();
  followupdn();
  
}

long microsecondsToInches(long microseconds)
{
  
  return microseconds / 74 / 2; //Formuae to convert time into distance for a ultrasonic dicstance sensor
}

void follow() 
{
  if (Linches < threshold || Rinches < threshold)
  {
    if (Linches + 2 < Rinches) //object close to right sensor
    {
      anglehor = anglehor - 20; //keeps rotating the cam right
    }
    else if (Rinches + 2 < Linches) //object close to left sensor
    {
      anglehor = anglehor + 20; //rotates the cam to left
    }
  }
  if (anglehor > 180)
  {
    anglehor = 180;
  }
  if (anglehor < 0)
  {
    anglehor = 0;
  }
  myservohor.write(anglehor);
  
}
void followupdn() 
{
  if (uinches < threshold || dinches < threshold)
  {
    if (uinches + 2 < dinches) // similar to horizontal axis servo
    {
      anglever = anglever + 20;
    }
    else if (dinches + 2 < uinches)
    {
      anglever = anglever - 20;
    }
  }
  if (anglever > 180)
  {
    anglever = 180;
  }
  if (anglever < 0)
  {
    anglever = 0;
  }
  myservover.write(anglever);
  
}
