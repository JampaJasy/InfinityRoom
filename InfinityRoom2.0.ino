// Alle Pin aangeven
const int redPin = 11;
const int greenPin = 10;
const int bluePin = 9;
const int blauwLeftPin = 5;
const int witLeftPin = 4;
const int blauwRightPin = 6;
const int witRightPin = 7;
// Functie
unsigned int rgbColour[3];

void setup() {
  // RGB LED moet uit beginnen.
  setColourRgb(0, 0, 0);
  pinMode(blauwLeftPin, OUTPUT);
  pinMode(witLeftPin, OUTPUT);
  pinMode(blauwRightPin, OUTPUT);
  pinMode(witRightPin, OUTPUT);
}

void loop() {

  DDRD = B11111110;  // Pin 1 tot 7 Als Outputs, pin 0 als input
  DDRD = DDRD | B11111100;  // Pin 2 tot 7 als Outputs
  // Hierdoor laat ik 0 en 1 met rust aangezien zij RX & TX zijn

  //Port manipulatie welke pins aan en uit gaan tussen 7,6,5 en 4
  PORTD = B11000000;
  delay(100);
  PORTD = B00110000;
  delay(100);
  PORTD = B11000000;
  delay(100);
  PORTD = B00000000;
  delay(100);
  PORTD = B11000000;
  delay(100);
  PORTD = B00110000;
  delay(100);
  PORTD = B11000000;
  delay(100);
  PORTD = B00000000;
  delay(100);

  // Start RGB LED met Red als kleur.
  rgbColour[0] = 255;
  rgbColour[1] = 0;
  rgbColour[2] = 0;

  // Increment & decrement tussen de kleuren.
  for (int decColour = 0; decColour < 3; decColour += 1) {
    int incColour = decColour == 2 ? 0 : decColour + 1;

    // cross-fade tussen de RGB kleuren.
    for (int i = 0; i < 255; i += 1) {
      rgbColour[decColour] -= 1;
      rgbColour[incColour] += 1;

      setColourRgb(rgbColour[0], rgbColour[1], rgbColour[2]);
      delay(5);
    }
  }

  //Het zetten van de Brightness voor elke pin.
  void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);
  }
