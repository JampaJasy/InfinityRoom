# InfinityRoom
Vrije Project Infinity Room 2.0

PROCES 
Code
Omdat ik dus iets met lichten en geluid wilde doen was het tijd om de code in te duiken en te kijken wat ik het beste kon doen met lichten. Ik ben samen met Geert op het idee gekomen om lichten aan te sturen aan de hand van een sequens. In eerste instantie wilde ik lichtjes apart sturen, alleen zou dit voor teveel regels code zorgen als ik elk lampje individueel een opdracht gaf. Op dit gebied kwam Geert met de oplossing om ‘Port Manipulatie’ te gebruiken op de Arduino. Port manipulatie zorgt ervoor dat je niet elk lampje hoeft aan te sturen maar dat je gewoon een gehele Port kan aansturen. 
Port Registers maken een lagere en snellere manipulatie van de i/o pinnen van de Arduino mogelijk. De chips die op het Arduino-bord worden gebruikt, hebben drie poorten:
•	Port B (digital pin 8 to 13)
•	Port C (analog input pins)
•	Port D (digital pins 0 to 7)
Elke Port wordt bestuurd door 3 register die als variabelen in de Arduino te vinden zijn. Het DDR-register bepaalt of de pin een INPUT of OUTPUT is. Het Port-register bepaalt of de pin HIGH of LOW  is en het Pin-register leest de toestand van INPUT-pinnen ingesteld op invoer met de standaard pinMode() code. 
In dit geval gebruikte ik Port D aangezien op de Port D al mijn led lichtjes op aangesloten zijn. Port D maps alle digitale pins van 0 tot 7 op de Arduino. De DDR die je doorgeeft kan een 1 of 0 zijn, waarin de 1 voor HIGH staat en 0 voor LOW. Zonder Port manipulatie zou de code er zo uitzien om een lichtje aan te krijgen: 
1.	digitalWrite(blauwLeftPin, HIGH);  
2.	  delay(100);  
3.	  //digitalWrite(whiteBlueleftPin, LOW);  
4.	  //delay(100);  
 

Dit zou echter voor een veel te lange code geven als er een sequens gebouwd moet worden van meerdere lampjes. Met behulp van Port D & DDR wordt het zo gedaan: 
1.	DDRD = B11111110;  // sets Arduino pins 1 to 7 as outputs, pin 0 as input  
2.	DDRD = DDRD | B11111100;  // this is safer as it sets pins 2 to 7 as outputs  
3.	                    // without changing the value of pins 0 & 1, which are RX & TX   
4.	  
5.	PORTD = B11000000;   
6.	  delay(100);  
7.	PORTD = B00000000;   
8.	  delay(100);    
9.	  PORTD = B11000000;   
10.	  delay(100);  
11.	PORTD = B00000000;   
12.	  delay(100);  
13.	  PORTD = B11000000;   
14.	  delay(100);  
15.	PORTD = B00000000;   
16.	  delay(100);  
17.	  PORTD = B11000000;   
18.	  delay(100);  
19.	PORTD = B00000000;   
20.	  delay(100);  
Met behulp van Port D kan ik de gehele analoge rij aansturen met een regel code welke wel op HIGH moeten worden gezet en welke niet. Hiervan kan meerdere sequensen achter elkaar zetten waardoor een hele grote sequens krijgt. Dit is qua code veel voordeliger en netjes aangezien het niet veel ruimte meer inneemt. 
Naast dat er lichtjes worden aangestuurd heb ik ook een centrale RGB LED die voor sfeer kan zorgen in de infinity room. Deze wordt niet aangestuurd via Port D maar wel via red, green en blue pins. Zie hier de volledige code:
1.	const int redPin = 11;  
2.	const int greenPin = 10;  
3.	const int bluePin = 9;  
4.	const int blauwLeftPin = 13;  
5.	const int witLeftPin = 12;  
6.	const int blauwRightPin = 6;  
7.	const int witRightPin = 7;  
8.	  
9.	byte myPorts[] = "B01000000"  
10.	"B11000000"  
11.	"B10000000"  
12.	"B00000000";  
13.	  
14.	  
15.	void setup() {  
16.	  // LED off.  
17.	  setColourRgb(0,0,0);    
18.	  pinMode(blauwLeftPin,OUTPUT);  
19.	  pinMode(witLeftPin,OUTPUT);  
20.	  pinMode(blauwRightPin,OUTPUT);  
21.	  pinMode(witRightPin,OUTPUT);  
22.	}  
23.	  
24.	void loop() {  
25.	  
26.	DDRD = B11111110;  // sets Arduino pins 1 to 7 as outputs, pin 0 as input  
27.	DDRD = DDRD | B11111100;  // this is safer as it sets pins 2 to 7 as outputs  
28.	                    // without changing the value of pins 0 & 1, which are RX & TX   
29.	  
30.	PORTD = B11000000;   
31.	  delay(100);  
32.	PORTD = B00000000;   
33.	  delay(100);    
34.	  PORTD = B11000000;   
35.	  delay(100);  
36.	PORTD = B00000000;   
37.	  delay(100);  
38.	  PORTD = B11000000;   
39.	  delay(100);  
40.	PORTD = B00000000;   
41.	  delay(100);  
42.	  PORTD = B11000000;   
43.	  delay(100);  
44.	PORTD = B00000000;   
45.	  delay(100);  
46.	    
47.	  unsigned int rgbColour[3];  
48.	  
49.	  // Begin met Red.  
50.	  rgbColour[0] = 255;  
51.	  rgbColour[1] = 0;  
52.	  rgbColour[2] = 0;    
53.	  
54.	  // Increment & decrement.  
55.	  for (int decColour = 0; decColour < 3; decColour += 1) {  
56.	    int incColour = decColour == 2 ? 0 : decColour + 1;  
57.	  
58.	    // cross-fade.  
59.	    for(int i = 0; i < 255; i += 1) {  
60.	      rgbColour[decColour] -= 1;  
61.	      rgbColour[incColour] += 1;  
62.	        
63.	      setColourRgb(rgbColour[0], rgbColour[1], rgbColour[2]);  
64.	      delay(5);  
65.	    }  
66.	  }  
67.	  
68.	  //digitalWrite(blauwLeftPin, HIGH);  
69.	  //delay(100);  
70.	  //digitalWrite(whiteBlueleftPin, LOW);  
71.	  //delay(100);  
72.	  
73.	  //digitalWrite(witLeftPin, HIGH);  
74.	  //delay(100);  
75.	  //digitalWrite(whiteBluerightPin, LOW);  
76.	  //delay(100);  
77.	  
78.	            
79.	  
80.	    
81.	}  
82.	  
83.	void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {  
84.	  analogWrite(redPin, red);  
85.	  analogWrite(greenPin, green);  
86.	  analogWrite(bluePin, blue);  
87.	 }  
Deze volledige code is vervolgens opgeschoond en onnodige regels zijn eruit gehaald. Verder heb ik comments erbij gezet waar nodig was om beetje uitleg te geven wat er staat. 
1.	// Alle Pin aangeven  
2.	const int redPin = 11;  
3.	const int greenPin = 10;  
4.	const int bluePin = 9;  
5.	const int blauwLeftPin = 5;  
6.	const int witLeftPin = 4;  
7.	const int blauwRightPin = 6;  
8.	const int witRightPin = 7;  
9.	// Functie  
10.	unsigned int rgbColour[3];  
11.	  
12.	void setup() {  
13.	  // RGB LED moet uit beginnen.  
14.	  setColourRgb(0, 0, 0);  
15.	  pinMode(blauwLeftPin, OUTPUT);  
16.	  pinMode(witLeftPin, OUTPUT);  
17.	  pinMode(blauwRightPin, OUTPUT);  
18.	  pinMode(witRightPin, OUTPUT);  
19.	}  
20.	  
21.	void loop() {  
22.	  
23.	  DDRD = B11111110;  // Pin 1 tot 7 Als Outputs, pin 0 als input  
24.	  DDRD = DDRD | B11111100;  // Pin 2 tot 7 als Outputs  
25.	  // Hierdoor laat ik 0 en 1 met rust aangezien zij RX & TX zijn  
26.	  
27.	  //Port manipulatie welke pins aan en uit gaan tussen 7,6,5 en 4  
28.	  PORTD = B11000000;  
29.	  delay(100);  
30.	  PORTD = B00110000;  
31.	  delay(100);  
32.	  PORTD = B11000000;  
33.	  delay(100);  
34.	  PORTD = B00000000;  
35.	  delay(100);  
36.	  PORTD = B11000000;  
37.	  delay(100);  
38.	  PORTD = B00110000;  
39.	  delay(100);  
40.	  PORTD = B11000000;  
41.	  delay(100);  
42.	  PORTD = B00000000;  
43.	  delay(100);  
44.	  
45.	  // Start RGB LED met Red als kleur.  
46.	  rgbColour[0] = 255;  
47.	  rgbColour[1] = 0;  
48.	  rgbColour[2] = 0;  
49.	  
50.	  // Increment & decrement tussen de kleuren.  
51.	  for (int decColour = 0; decColour < 3; decColour += 1) {  
52.	    int incColour = decColour == 2 ? 0 : decColour + 1;  
53.	  
54.	    // cross-fade tussen de RGB kleuren.  
55.	    for (int i = 0; i < 255; i += 1) {  
56.	      rgbColour[decColour] -= 1;  
57.	      rgbColour[incColour] += 1;  
58.	  
59.	      setColourRgb(rgbColour[0], rgbColour[1], rgbColour[2]);  
60.	      delay(5);  
61.	    }  
62.	  }  
63.	  
64.	  //Het zetten van de Brightness voor elke pin.  
65.	  void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {  
66.	    analogWrite(redPin, red);  
67.	    analogWrite(greenPin, green);  
68.	    analogWrite(bluePin, blue);  
69.	  }  
