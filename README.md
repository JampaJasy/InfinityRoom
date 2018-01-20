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

In dit geval gebruikte ik Port D aangezien op de Port D al mijn led lichtjes op aangesloten zijn. Port D maps alle digitale pins van 0 tot 7 op de Arduino. De DDR die je doorgeeft kan een 1 of 0 zijn, waarin de 1 voor HIGH staat en 0 voor LOW.

Volledige code valt terug te vinden in het .ino bestand als er behoefte is aan code inzage. 

Voor procesonderbouwing verwijs ik u naar het .pdf document. 
