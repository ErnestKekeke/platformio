#include <IRrecv.h>
#include <IRremoteESP8266.h>

 
// Define sensor pin
const int RECV_PIN = 4;
 
// Define IR Receiver and Results Objects
IRrecv irrecv(RECV_PIN);
decode_results results;
 
 
void setup(){
  Serial.begin(115200);

  irrecv.enableIRIn();  // Enable the IR Receiver

   Serial.println(" ****** IR is Ready ****** ");
}
 
void loop(){
  if (irrecv.decode(&results)){
    // Print Code in HEX
        Serial.println(results.value);  // 4294967295 means repeat code 
        Serial.println(results.value, HEX);   // FFFFFFFF means repeat code 
        Serial.print("decode_type: ");
        Serial.println(results.decode_type);
        Serial.print("bits: ");
        Serial.println(results.bits);
        Serial.print("address: ");
        Serial.println(results.address);
        Serial.print("rawlen: ");
        Serial.println(results.rawlen);
        Serial.print("overflow: ");
        Serial.println(results.overflow);
        Serial.print("repeat: ");
        Serial.println(results.repeat);
        Serial.print("command: ");
        Serial.println(results.command);
        delay(100);
        irrecv.resume();
        Serial.println("................ \n");
  }
}