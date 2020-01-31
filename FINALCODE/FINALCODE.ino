#include <Keypad.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(5,6);
const byte ROWS = 4;
const byte COLS = 3;
byte datacount=0 ;
char data[5];
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {7,8,9,10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {11,12,13}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
long randNumber;
char buf[16];
void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
  randomSeed(analogRead(0));
  Serial.println("WELCOME!!!");
  Serial.println("ENTER YOUR PASSWORD");
}
void loop()
{
  char a;
  if (Serial.available()>0)
  {
     mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
     delay(3000);
  }
  
if (mySerial.available()>0)
   a = mySerial.read();
   if (a=='a')
   {
   Serial.println(a);
   random_number();
   
   }
   char key = keypad.getKey();
      if (key){
      data[datacount]=key;
      datacount++;
              } 
    if (datacount==4)
  {
    Serial.println(data);
    if(!strcmp(data,buf))
    {
      Serial.println("HI FRIEND COME IN!!!!!!");
      cleardata();
    }
    else
    {
      Serial.println("Not allowed");
      cleardata();
    }
  } 
}

void send_sms(long randNumber)
{
     mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     mySerial.println("AT+CMGS=\"+918903970069\"\r"); // Replace x with mobile number
     delay(1000);
     mySerial.println(String(randNumber));// The SMS text you want to send
     delay(100);
     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
  }

void cleardata()
{
  while (datacount != 0)
  { 
    data[datacount--] = 0; 
  }
  return;
}



void random_number()
{
  long randNumber;
  randNumber = random(1000,9999);
   Serial.println(randNumber);
   delay(2000);
  itoa(randNumber,buf,10);
  delay(1000);
  Serial.println(buf);
  send_sms(randNumber);
}
