#define F true
#define BACK false

void setup() {
  Serial.begin(9600);
  
  for(int i=5; i<13; i++){
   pinMode(i,OUTPUT);
  }

   for(int i=5;i<13;i++){
   digitalWrite(i,LOW);
  }

  motorON(true);
}

void loop() {
  if(Serial.available()){
    int s1[8];
    for (int i; i < 8; i++){
      s1[i]  = Serial.read();
    }
    int Lvel, Rvel;
    char Ldirection, Rdirection;
    Ldirection = (char)(s1[0]);
    Rdirection = (char)(s1[4]);
    Lvel = s1[1]*100 + s1[2]*10 + s1[3] - 48 * 111;
    Rvel = s1[5]*100 + s1[6]*10 + s1[7] - 48 * 111;
    LeftMotorControl(Lvel, Ldirection);
  }
}

void LeftMotorControl(int Lvel, char Ldirection){
  if(Ldirection == "F"){
    digitalWrite(5,LOW);
    analogWrite(6,Lvel);
  }
  else{
    digitalWrite(6,LOW);
    analogWrite(5,Lvel);
  }
}

void RightMotorControl(int Rvel, char Rdirection){
  if(Rdirection == "F"){
    digitalWrite(10,LOW);
    analogWrite(9,Rvel);
  }
  else{
    digitalWrite(9,LOW);
    analogWrite(10,Rvel);
  }
}

void motorON(boolean a){
  if(a == true)
  {
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(12,HIGH);
  }
  else
  {
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
  }

}
