int valueC;
int valueD;
int valueG;
int valueH;
int valueI;
int valueJ;
int valueK;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial.println("Test");
}

void loop() {

  while (Serial1.available() > 0)
  {
    String c = Serial1.readStringUntil('\n');
    Serial.println(c);
    int addressC = c.indexOf('C');
    int addressD = c.indexOf('D');
    int addressG = c.indexOf('G');
    int addressH = c.indexOf('H');
    int addressI = c.indexOf('I');
    int addressJ = c.indexOf('J');
    int addressK = c.indexOf('K');
    int addressEnd = c.indexOf(';');
    
    valueC = c.substring(addressC+1, addressD).toInt();
    valueD = c.substring(addressD+1, addressG).toInt();
    valueG = c.substring(addressG+1, addressH).toInt();
    valueH = c.substring(addressH+1, addressI).toInt();
    valueI = c.substring(addressI+1, addressJ).toInt();
    valueJ = c.substring(addressJ+1, addressK).toInt();
    valueK = c.substring(addressK+1, addressEnd).toInt();
    
    Serial.print(valueC);Serial.print(",");
    Serial.print(valueD);Serial.print(",");
    Serial.print(valueG);Serial.print(",");
    Serial.print(valueH);Serial.print(",");
    Serial.print(valueI);Serial.print(",");
    Serial.print(valueJ);Serial.print(",");
    Serial.print(valueK);Serial.println("");
    
    
    
  }



}
