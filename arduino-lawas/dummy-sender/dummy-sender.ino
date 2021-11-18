unsigned long sendDataPrevMillis = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  
}

void loop() {

  if ((millis() - sendDataPrevMillis > 5000 * 1 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    Serial.print("C");Serial.print(1); //do
  Serial.print("D");Serial.print(2); //ec
  Serial.print("G");Serial.print(3); //orp
  Serial.print("H");Serial.print(4); //ph
  Serial.print("I");Serial.print(5); //tds
  Serial.print("J");Serial.print(6); //temp
  Serial.print("K");Serial.print(7);Serial.println(";");//wc       
  }
    

  
  
  
}
