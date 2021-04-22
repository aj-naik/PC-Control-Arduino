const int trigPin1 = 11; 
const int echoPin1 = 10;      
const int trigPin2 = 6; 
const int echoPin2 = 5;  

long duration;                               
int distance1, distance2; 
float r;
unsigned long temp=0;
int temp1=0;
int l=0;


void find_distance (void);

// this function returns the value in cm.

void find_distance (void)                   
{ 
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration = pulseIn(echoPin1, HIGH, 5000);// here this pulsein function wont wait more then 5000us for the ultrasonic sound to came back. (due to this it wont measure more than 60cm)
                                           
 
  r = 3.4 * duration / 2;                  // calculation to get the measurement in cm using the time returned by the pulsein function.     
  distance1 = r / 100.00;

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration = pulseIn(echoPin2, HIGH, 5000);
  r = 3.4 * duration / 2;     
  distance2 = r / 100.00;
  delay(100);
}

void setup() 
{
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT); // initialize the trigger and echo pins of both the sensor as input and output:
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  delay (1000);
    
}

void loop()
{
  find_distance(); // this function will store the current distance measured by the ultrasonic sensor in the global variable "distance1 and distance2"
           
  
  if(distance2<=35 && distance2>=15)
  { 
    temp=millis();                   
    while(millis()<=(temp+300))      
    find_distance();
    if(distance2<=35 && distance2>=15) 
    {
     temp=distance2;                         
     while(distance2<=50 || distance2==0)    
     {
       find_distance();                      
       if((temp+6)<distance2)                // this condition becomes true if we move our hand away from the right sensor 
       {
       Serial.println("down");              
       }
       else if((temp-6)>distance2)           // this condition becomes true if we moves our hand closer to the right sensor.
       {
        Serial.println("up");                
       }
     }
    }
    else                                     // this condition becomes true, if we only swipe in front of the right sensor . 
    {
      Serial.println("next");                
    }
  }

  else if(distance1<=35 && distance1>=15)   
  { 
  
    temp=millis();                           
  
    while(millis()<=(temp+300))             
    {
       find_distance();
       if(distance2<=35 && distance2>=15)  
       {
         Serial.println("change");        
         l=1;                              
         break;                            
       }
    }
    
    if(l==0)                               // this condition will become true, only if we swipe our hand in front of left sensor.
    {
    Serial.println("previous");           
    while(distance1<=35 && distance1>=15) // this loop will rotate untill we removes our hand infront of the left sensor. this will avoid not to enter this if condition again.
    find_distance();                      
    }
    l=0;                                  // make l=0 for the next round.
   }
   
}
