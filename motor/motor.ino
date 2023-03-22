
void setup() {
  Serial.begin(9600);
  
  for(int i=2; i<5; i++){
   pinMode(i,OUTPUT);
  }
  for(int i=22; i<25; i++){
   pinMode(i,OUTPUT);
  }

   for(int i=2;i<5;i++){
   digitalWrite(i,LOW);
  }
  for(int i=22;i<25;i++){
   digitalWrite(i,LOW);
  }
  motorON(true);
}

void loop() {
  if(Serial.available() > 0){
    String cmd = Serial.readString();
    Serial.println(cmd);
    
    int Lvel, Rvel;
    String Ldirection, Rdirection;
    Ldirection = (String)(cmd[0]);
    Rdirection = (String)(cmd[4]);
    Lvel = (int)(cmd[1])*100 + (int)(cmd[2])*10 + (int)(cmd[3]) - 48 * 111;
    Rvel = (int)(cmd[5])*100 + (int)(cmd[6])*10 + (int)(cmd[7]) - 48 * 111;
    LeftMotorControl(Lvel, Ldirection);
    RightMotorControl(Rvel, Rdirection);
  }
}

void LeftMotorControl(int Lvel, String Ldirection){
  if(Ldirection == "F"){
    digitalWrite(2,LOW);
    analogWrite(3,Lvel);
  }
  else{
    digitalWrite(3,LOW);
    analogWrite(2,Lvel);
  }
}

void RightMotorControl(int Rvel, String Rdirection){
  if(Rdirection == "F"){
    digitalWrite(5,LOW);
    analogWrite(4,Rvel);
  }
  else{
    digitalWrite(4,LOW);
    analogWrite(5,Rvel);
  }
}

void motorON(boolean a){
  if(a == true)
  {
    for(int i=22;i<25;i++){
   digitalWrite(i,HIGH);
  }
  }
  else
  {
    for(int i=22;i<25;i++){
   digitalWrite(i,LOW);
  }
  }
}
