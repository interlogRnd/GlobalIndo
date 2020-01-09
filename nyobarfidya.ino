//use arduino 1.6.4 IDE and boards maneger esp6288 2.3.0
#undef DEBUG_ESP_WIFI
#undef DEBUG_ESP_PORT
#undef DEBUG_WIFI

#include<ESP8266WiFi.h>
#include<SPI.h>
#include"MFRC522.h"`
/* wiring the MFRC522 to ESP8266 (ESP-12)
  RST      = GPIO5
  SDA (SS) = GPIO4
  MOSI     = GPIO13
  MISO     = GPIO12
  SCK      = GPIO14
  GND      = GND
  3.3v     = 3.3v
*/

#define RST_PIN 5 // RST-PIN to RC522 RFID - SPI Module GPIO5
#define SS_PIN	4 // SDA-PIN to RC522 RFID - SPI Module GPIPO4
#define LED 16  // control low and high (2 led in 1 i/o) HIGH to RED, LOW to GREEN
//#define LGREEN 9
#define LBLUE 2 // LED 2

bool rfid_tag_present_prev = false;
bool rfid_tag_present = false;
int _rfid_error_counter = 0;
bool _tag_found = false;
boolean detekartu, ss;
const int analogInPin = A0;
int sensorValue = 0;
int outputValue = 0;
boolean exc = false;

const char* ssid = "najibganteng"; // change according to your Network
const char* pass = "1234567890"; // change according to yout Network
const char* php  = " /transaksi.php";
const char* host = "10.3.141.1";
const uint16_t port = 8080;
String perangkat = "9001";
String mystring,mystring_present,mystring_prev;
String mystring1;
boolean GoodCard;
WiFiClient client;

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
//void (* resetFunc)(void) = 0;
void setup() {
  pinMode(LED,OUTPUT);
  pinMode(LBLUE,OUTPUT);
  digitalWrite(LBLUE,HIGH);
  Serial.begin(9600);
  SPI.begin(); //Init SPI bus
  mfrc522.PCD_Init();

  WiFi.begin(ssid, pass);

  int retries = 0; // connect until 10 time counter
  while ((WiFi.status() != WL_CONNECTED) )
  {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() ==  WL_CONNECTED)
  {
    Serial.println(F("WiFi connected"));
    digitalWrite(LED,LOW);
  }
  Serial.println(F("Ready!"));
  Serial.println(F("======================================================"));
  Serial.println(F("Scan for Card and print UID:"));
}

void loop() {
  sensorValue = analogRead(analogInPin);
  
  outputValue = map(sensorValue,0,1024,LOW,HIGH); // 1 untuk hitam ada kartu dan 0 untuk terang untuk tidak ada kartu
  //Serial.println(outputValue);
  if(WiFi.status() != WL_CONNECTED) 
  {
    digitalWrite(LED,LOW);
  }
  else 
  {
    digitalWrite(LED,HIGH);
  }
//if (ss == 0)
//{
    detectcardd();
    delay(1000);
//}
//  delay(100);
//  if (ss == 1)
//  {
//    dariweb();      
//  }
  

//  MFRC522::MIFARE_Key key;
//  for (byte i = 0; i < 6; i++) {
//    key.keyByte[i] = 0xFF;
//  }
//
//  byte block;
//  byte len;
//  MFRC522::StatusCode status;
//  
//  // Look for new cards
//  if ( ! mfrc522.PICC_IsNewCardPresent()) {
//    return;
//  }
//  // Select one of the cards
//  if ( ! mfrc522.PICC_ReadCardSerial()) {
//    return;
//  }
//  
//  byte buffer2[8];
//  block = 1;
//  len = 18;
//
//  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid)); //line 834
//  if (status != MFRC522::STATUS_OK) {
//    //Serial.print(F("Authentication failed: "));
//    //Serial.println(mfrc522.GetStatusCodeName(status));   
//    //return 0;
//  }
//
//  status = mfrc522.MIFARE_Read(block, buffer2, &len);
//  if (status != MFRC522::STATUS_OK) {
//    //Serial.print(F("Reading failed: "));
//    //Serial.println(mfrc522.GetStatusCodeName(status));
//    //return 0;
//    GoodCard = LOW; //tap kartu masuk sini 
//  }
//
//  else {
//    GoodCard = HIGH;// pertama masuk sini 
//    
//  }
//  if(GoodCard ==  LOW)
//  {
//    digitalWrite(LBLUE,LOW);
//    delay(200);
//    digitalWrite(LBLUE,HIGH);
//    delay(200); 
//     
//  }
//  else if(GoodCard == HIGH)
//  {
//    digitalWrite(LBLUE,HIGH);
//
//  }else {}
//  
//  //PRINT LAST NAME
//  for (uint8_t i = 0; i < 6; i++) {
//    //Serial.write(buffer2[i]);
//    //mystring = String((char*)buffer2[i]); // data berantakan hexa
//    mystring += (char)buffer2[i];
//    mystring1 = mystring;
//  }  
//    mystring ="";


//  if (!client.connect(host, port)) {
//    Serial.println("connection failed");
//    delay(5000);
//    return;
//  }
//  if (client.connected())
//  {
//    String url;
//    String mood;
//    url += php;
//    url += "?mood=";
//    url += mystring; // send data to server
//    url += "~";
//    url += perangkat;
//    url += "~";
//    url += outputValue;// tidak bisa karena jarak RFID harus dekat baru 0 dikirim 
//    //url += "HALLO"; // send data to server
//    client.print("GET");
//    client.print(url);
//    client.println(" HTTP/1.1");
//    client.print("Host: ");
//    client.println(host);
//    client.println("Connection: close");
//    client.println();
//    Serial.println(mystring);
//    //delay(3000);
//  }


//  if (client.connected()){
//
//    String url;
//    String mood;
//    url += php;
//    url += "?mood=";
//    url += mystring;
//    url += "~";
//    url += perangkat;
//    url += "~";
//    url += detekartu; 
// 
// 
//    //Serial.println(url);
//    //Serial.println(outputValue);
//    //Serial.println(exc);
////    client.print("GET"); 
////    client.print(url);
////    client.println(" HTTP/1.1");
////    client.print("Host: ");
////    client.println(host);
////    client.println("Connection: close");
////    client.println();
////    Serial.println(url);
//
//    if(detekartu == LOW && exc == false){
//      client.print("GET"); 
//      client.print(url);
//      client.println(" HTTP/1.1");
//      client.print("Host: ");
//      client.println(host);
//      client.println("Connection: close");
//      client.println();
//      Serial.println(mystring);
//      Serial.println("kartu disimpan");
//      exc = true;
//    } 
//     if(detekartu == HIGH && exc == true){
//      client.print("GET");
//      client.print(url);
//      client.println(" HTTP/1.1");
//      client.print("Host: ");
//      client.println(host);
//      client.println("Connection: close");
//      client.println();
//      Serial.println(mystring);
//      Serial.println("kartu dilepas");
//      exc = false;
//   }
//  }
}

void detectcardd()
{ 
  rfid_tag_present_prev = rfid_tag_present;
  mystring_prev = mystring_present;
   _rfid_error_counter += 1;
  if(_rfid_error_counter > 5){ //kondisi lepas kartu
    _tag_found = false;
    detekartu=0;
//    Serial.println("tagfalse");
  }
    Serial.println(detekartu);
    Serial.println(mystring_present);
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }
  if (client.connected()){

    String url;
    String mood;
    url += php;
    url += "?mood=";
    url += mystring_present;
    url += "~";
    url += perangkat;
    url += "~";
    url += detekartu; 

     if(detekartu == 0 && exc == true){
      client.print("GET");
      client.print(url);
      client.println(" HTTP/1.1");
      client.print("Host: ");
      client.println(host);
      client.println("Connection: close");
      client.println();
      Serial.println(mystring);
      Serial.println("kartu dilepas");
      exc = false;
   }
  }
    
  byte buffer2[8];
  byte block = 1;
  byte len = 18;

  MFRC522::StatusCode status;
  MFRC522::MIFARE_Key key;
    for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  //  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid)); //line 834
  if (status != MFRC522::STATUS_OK) {
  }
  if(_rfid_error_counter > 5){
    _tag_found = false;
  }
  status = mfrc522.MIFARE_Read(block, buffer2, &len);
  if (status != MFRC522::STATUS_OK) {
    GoodCard = LOW; //tap kartu masuk sini 
        _rfid_error_counter = 0;
    _tag_found = true; 
  }
  rfid_tag_present = _tag_found;
  // rising edge
//  if (rfid_tag_present && !rfid_tag_present_prev){
  if (_tag_found == true){
//    Serial.println("Tag found");
    detekartu = 1;
  }
//    Serial.println(detekartu);
  for (uint8_t i = 0; i < 6; i++) {
    mystring += (char)buffer2[i];
    mystring1 = mystring;
  }  

  mystring_present = mystring;
   if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }
  if (client.connected()){

    String url;
    String mood;
    url += php;
    url += "?mood=";
    url += mystring_present;
    url += "~";
    url += perangkat;
    url += "~";
    url += detekartu; 

    if(detekartu == 1 && exc == false){
      client.print("GET"); 
      client.print(url);
      client.println(" HTTP/1.1");
      client.print("Host: ");
      client.println(host);
      client.println("Connection: close");
      client.println();
      Serial.println(mystring);
      Serial.println("kartu disimpan");
      exc = true;
    } 
  }
  
  mystring ="";
//  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  delay(100);
  ss = 1;
}

