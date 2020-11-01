//Firstly we have to define the pinouts
int data = 5;
int clk = 6;
int enable = 7;

//first we are going to declare a five sized array to hold the digits
byte digits[5];

void write_MC14489(byte digitData) {

  int i=0;
  int pinState;

  digitalWrite(data, 0);
  digitalWrite(clk, 0);

  for (i=7; i>=0; i--)  {
    digitalWrite(clk, 0);
    if ( digitData & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }

    digitalWrite(data, pinState);
    digitalWrite(clk, 1);
    digitalWrite(data, 0);
  }

  digitalWrite(clk, 0);
}

void writeDigits(byte digits[5]){
  digitalWrite(enable, LOW); 
   write_MC14489(  (0xff << 4) | digits[3]  ); // D23~D16
   write_MC14489(  (digits[4] << 4) | digits[2]); // D15~D8
   write_MC14489(  (digits[1] << 4) | digits[0] ); // D7~D0
   digitalWrite(enable, HIGH);
}

 
void second_counter()
{
  for(int i=0; i<100000; i++){
    
      digits[0] = i % 100000 /10000;
      digits[1] = i % 10000  /1000;
      digits[2] = i % 1000   /100;
      digits[3] = i % 100   / 10 ;
      digits[4] = i % 10     ;
      
      writeDigits(digits);
      delay(1000);
  }
  
  delay(10);
}




void setup()
{  
   pinMode(data, OUTPUT);
   pinMode(enable, OUTPUT);
   pinMode(clk, OUTPUT);

   //Start the MC14489
   digitalWrite(enable, LOW);
   write_MC14489( 0x01 );
   digitalWrite(enable, HIGH);
   delay(10);
}

void loop()
{
   second_counter();
}
