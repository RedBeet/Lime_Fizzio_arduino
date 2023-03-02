
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
    digitalWrite(5,LOW);
    analogWrite(6,Lvel);
  }
  else{
    digitalWrite(6,LOW);
    analogWrite(5,Lvel);
  }
}

void RightMotorControl(int Rvel, String Rdirection){
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
