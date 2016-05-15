#include <Keyboard.h>

//#define debug yes

const int NSIPIN    =  1; // pin for dial pulses
const int NSAPIN    =  0; // pin for rst btn
const int ledPin    = 13; // pin for indicator led

int dialCntr        =  0; // count dial pulses
int currNSIPINState =  0; // current pulse state
int currNSAPINState =  0; // current rst btn state
int lastNSIPINState =  0; // last pulse btn state
int lastNSAPINState =  1; // last rst btn state


void setup() {
  #ifdef debug
  // set up serial
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  #endif
  
  pinMode(NSIPIN, INPUT_PULLUP);
  pinMode(NSAPIN, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  #ifdef debug
  Serial.println( "Starting dialCounter... " );
  #endif
}

void loop() {
  currNSAPINState = digitalRead( NSAPIN );
  currNSIPINState = digitalRead( NSIPIN );

  if( currNSAPINState != lastNSAPINState ) {
    if( lastNSAPINState == LOW ) {
      #ifdef debug
      Serial.println( dialCntr % 10 );
      #endif
      Keyboard.print( dialCntr % 10 );
      dialCntr = 0;
    }
  }
  
  if( currNSIPINState != lastNSIPINState ) {
    if( currNSIPINState == HIGH ) {
      dialCntr++;
    }
  }

  delay( 31 );
  
  lastNSAPINState = currNSAPINState;
  lastNSIPINState = currNSIPINState;
}
