#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);//SDA->A4,SCL-->A5
//------------------------LCD-------------------------------------
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

// Define the keymap for the keypad
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins
byte rowPins[ROWS] = {9, 8, 7, 6}; 

// Connect keypad COL0, COL1, COL2 and COL3 to these Arduino pins
byte colPins[COLS] = {5, 4, 3, 2}; 

// Create the Keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
//------------------------keypad-------------------------------------
String inputPassword="";
String systemPassword="2580";
 
int Password_length=4;

int lock=10;
void setup() {
  lcd.init();         // Initialize the LCD
  lcd.backlight();    // Turn on the backlight
  lcd.setCursor(0,0); 
  Serial.print(9600);
  pinMode(lock,OUTPUT);
}
void loop() {
   
   lcd.clear();
   lcd.setCursor(1,0);
   lcd.print(":pass de mama:");
   delay(2000);
   int i=2;
   while(1){
   char key=keypad.getKey();
    if(key){
    if (inputPassword.length()<Password_length){
      inputPassword=inputPassword+key;
      lcd.clear();
      lcd.setCursor(i,1);
      lcd.print("#");
      i++;
    if (inputPassword.length()==Password_length){
      if(inputPassword==systemPassword){
      lcd.clear();
      lcd.setCursor(3,1);
      lcd.print("MILSE MAMA");
      digitalWrite(lock,HIGH);
      delay(5000);     
      inputPassword="";//Reset password
      break;
      
      }
      else{
      lcd.clear();
      lcd.setCursor(3,1);
      lcd.print("GHABLA!!");
      inputPassword="";//Reset password
      delay(2000);
      break;
      
      
      }
       }
  
    }
  }
  
    }
  digitalWrite(lock,LOW);
 
}

















