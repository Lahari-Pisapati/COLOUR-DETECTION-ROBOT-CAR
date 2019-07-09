#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7,8); 
const byte address[6] = "00001";
char msg = 's';

String userinput;
int userinput1 = 0;


void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

}

void loop() {

  if(Serial.available()>0)
  {
    userinput = Serial.read();
    Serial.flush();
    userinput1 = userinput.toInt();
    userinput1 = userinput1-48;

    Serial.print("this is arduino data: ");
    Serial.println(userinput1);

    if(userinput1 == 3)
    msg = 'f';

    else if(userinput1 == 2)
    msg = 'r';
    
    else if(userinput1 == 1)
    msg = 'l';
    
    else 
    msg = 's';
    
    delay(1);
    radio.write(&msg,sizeof(msg));
  }

}
