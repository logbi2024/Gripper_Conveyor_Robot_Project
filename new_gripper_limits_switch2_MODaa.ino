#include <SoftwareSerial.h> //Tx et RX 
#include <Servo.h>
#include <AccelStepper.h> 
#include <ContinuousStepper.h>
Servo myservo;

#define HALFSTEP 1
#define stepPin  4    //Base
#define dirPin  7     // Base
#define CstepPin  2     // IN1 on ULN2003 ==> Blue   on 28BYJ-48
#define CdirPin  5 
#define LstepPin  3 
#define LdirPin  6 
#define Enab  8    // IN3 on ULN2003 ==> Yellow on 28BYJ-48
#define LSC 9 // limit switch  X==Convoyer
#define LSL 10  // limit switch  Y==Loader
#define LSB 11 // limit switch  Z==BASE
char tosend;
char mode;
//#define motorPin4  11    // IN4 on ULN2003 ==> Orange on 28BYJ-48
int bluetoothTx = 0;
int bluetoothRx = 1;
// stepper robot base 
const int stepsPerRevolution = 100;
SoftwareSerial bluetooth(bluetoothTx,bluetoothRx);
AccelStepper Base(1, stepPin,dirPin);
AccelStepper Loader(1, LstepPin,LdirPin);
//ContinuousStepper<StepperDriver> Conveyor;
AccelStepper Conveyor(1, CstepPin,CdirPin);  
void setup() {
  pinMode(LSC, INPUT_PULLUP); // Convoyeur
  pinMode(LSL, INPUT_PULLUP); // Loader
  pinMode(LSB, INPUT_PULLUP); // Base

    
  // pinMode(Enab,OUTPUT); 
  // put your setup code here, to run once:
  myservo.attach(12);
  
  Serial.begin(115200);
  bluetooth.begin(115200);
  
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
  pinMode(CstepPin,OUTPUT);
  pinMode(CdirPin,OUTPUT);
  pinMode(LstepPin,OUTPUT);
  pinMode(LdirPin,OUTPUT);
  pinMode(Enab,OUTPUT); 
  pinMode(LSC ,INPUT_PULLUP);
  //pinMode(LSL , INPUT);
    // put your setup code here, to run once:
  Base.setMaxSpeed(400);
  Base.setAcceleration(100);
  Loader.setMaxSpeed(400);
  Loader.setAcceleration(100);
  Conveyor.setMaxSpeed(200);
  Conveyor.setAcceleration(50);
  //Conveyor
  //Conveyor.begin(CstepPin, CdirPin);
  //Conveyor.spin(800); // rotate at 200 steps per seconds
  //Conveyor.setAcceleration(100);
}

void loop() {

  // Vérification des fins de course
  if (digitalRead(LSC) == LOW) {
    // Stop convoyeur
    digitalWrite(CstepPin, LOW);
  }
  if (digitalRead(LSL) == LOW) {
    // Stop loader
    digitalWrite(LstepPin, LOW);
  }
  if (digitalRead(LSB) == LOW) {
    // Stop base
    digitalWrite(stepPin, LOW);
  }

   
  // put your main code here, to run repeatedly:
  while(bluetooth.available() > 0 )
      {
       
       tosend = bluetooth.read();
       
       Serial.println(tosend);
         
      } 
      
     if  (tosend =='O')
     {
      myservo.write(90);
     }

     if (tosend =='F')
     {
      myservo.write(0);
     }

     if (tosend =='G')
     {
        // put your main code here, to run repeatedly:
       Base.moveTo(-100);
       Base.runToPosition();
      // delay(1000);

     }

     if (tosend =='D')
     {
       Base.moveTo(100);
       Base.runToPosition();
       //delay(1000);
     }
     if (tosend =='P')
     {
         //Conveyor.begin(CstepPin, CdirPin);
         ///Conveyor.spin(800); // rotate at 200 steps per seconds
         ///Conveyor.setAcceleration(100);
         ///Conveyor.loop(); // Conveyor run
         Conveyor.setSpeed(200);
         Conveyor.runSpeed();
                
     }
     if (tosend =='S')
     {
       Conveyor.stop();// Conveyor Stop
      //Conveyor.powerOff();
     }

     //loader
     if (tosend =='L')
     {
       
       Loader.moveTo(100);
       Loader.runToPosition();
              
     }
     if (tosend =='R')
     {
      
       Loader.moveTo(-100);
       Loader.runToPosition();
              
     }
    // Auto mode  
    if (tosend =='A')
     {
       
      //Run Conveyor
     
      // Gripper open
      myservo.write(0);
      //delay(500);
      
      //base postion
      Base.moveTo(-100);
       Base.runToPosition();
       //delay(500);
       //loader loade
       Loader.moveTo(100);
       Loader.runToPosition();
       //delay(500);
       //loader reload
       Loader.moveTo(0);
       Loader.runToPosition();
       //delay(500);
       //Gripper close
        myservo.write(90);
        //delay(500);
       //base reverse poition
       Base.moveTo(100);
       Base.runToPosition();
       //delay(500);  
       myservo.write(0);
      //delay(500);   
      //Conveyor.setCurrentPosition(0);  
        
     }
  if (tosend =='H'){
     int closed = digitalRead(LSC);
        if(closed,LOW)
          {
          Conveyor.setSpeed(200);
         Conveyor.runSpeed();
           }
          else {
                Conveyor.stop();
               }
              
      
      
                 }
     
}
