#define sw 13
#define light 12

uint32_t m1, m2;

void setup() {
  pinMode(sw, INPUT_PULLUP);
  pinMode(light, OUTPUT);
  Serial.begin(9600);
  m1=m2=millis();
}

void loop() {
  m2 = millis();
  if(m2-m1 > 500){
    m1 = m2;
    digitalWrite(light, !digitalRead(light));
  }
  int r = button_read();
  if (r != 0) Serial.println(r);
}

int button_read() {
  int cl = 0;
p:  int t = 0;
  if (digitalRead(sw) == 0) {
    digitalWrite(light, HIGH);
    while (digitalRead(sw) == 0) {
      delay(1); t++;
    }
    digitalWrite(light, LOW);
    if (t > 15) {
      t = 0; cl++;
      while (digitalRead(sw) == HIGH) {
        delay(1); t++;
        if (t > 1000) return cl;
      }
      goto p;
    }
  }
  return cl;
}