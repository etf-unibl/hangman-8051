# hangman-8051
Hangman game implementation on 8051 uC device

SRPSKI


Potreban hardware:

	1. 3 x Easy8051 
	2. 2 x tastatura (PS/2 port)
	3. GLCD displej
	4. Protoboard
	5. Zice za povezivanje 
	6. 2 x PS/2 konektor
	
Potreban software:
	1. mikroC Pro for 8051
	2. 8051FLASH
	
---

Ploca 1:
	1. GLCD postaviti na mjesto na kojem pise GLCD 128x64, koje se nalazi u donjem desnom uglu ploce
	2. Prekidace 	SW0.0 - SW0.7
					SW1.1 i SW1.0
					SW3.1 i SW3.0
					SW7.7 
		postaviti u ON stanje
	3. Povezati zice sa pinova 3.1, 3.0, 1.1, 1.0 i GND sa protoboard-om
	    	
Ploce 2 i 3: 
	1. LCD postaviti na mjesto na kojem pise 2x16(lijeva strana ploce)
	2. Prekidace 	SW0.0 i SW0.1
					SW1.0 i SW1.1
					SW2.0 - SW2.5
		postaviti u ON stanje
	3. Povezati zice sa pinova 1.0, 1.1, GND na protoboard tako da zice sa 1.0/1.1/GND(ploca 2 i 3) 
	   bude u istoj liniji sa zicama sa pinova 3.1/3.0/GND(ploca 1)
	4. Povezati tastature na PORT0 ploca 1 i 2
	
Svaku plocu ukljuciti u PC pomocu USB2.0 A to B kabla. 
Nakon toga potrebno je programirati svaku plocu.

   Prvo pokrenuti mikroC Pro for 8051, a zatim importovati projekat u okruzenje (*.mcpav fajl) i 
   izvrsiti build projekta.

   Otvoriti 8051FLASH i u sekciji CODE pritisnuti LOAD. Otvorice se prozor unutar kojeg treba pronaci
   fajl master1.hex(ploca 1), slave_zadaje.hex(ploca 2) ili slave2.hex(ploca 3). 
   Na svaku plocu ucitati odgovarajuci fajl.
   Nakon sto se ucita fajl pritisnuti WRITE i sacekati da se zavrsi njegovo ucitavanje na plocu.

Da bi zapoceli igru potrebno je resetovati sve ploce, pri cemu ploca 1 treba da se resetuje poslednja.

IGRA MOZE DA POCNE!!!!

Napomena: 	Jedna ploca iskljucivo sluzi za zadavanje rijeci, a druga za pogadjanje.
			Ne postavljati ili uklanjati GLCD i/ili LCD dok je ploca ukljucena!



ENGLISH


Needed hardware:

	1. 3 x Easy8051 
	2. 2 x keyboard (PS/2 port)
	3. GLCD display
	4. Protoboard
	5. Wires 
	6. 2 x PS/2 conector
	
Needed software:
	1. mikroC Pro for 8051
	2. 8051FLASH
	
---

Easy8051 1:
	1. Set GLCD in up right corner of the board where writes GLCD 128x64.
	2. Set switches 	SW1.0 - SW1.7 (PORT 0)
						SW2.1 i SW2.0 (PORT 1)
						SW4.1 i SW4.0 (PORT 3)
						SW7.7 
		in ON state.
	3. Connect wires from pins 3.1, 3.0, 1.1, 1.0 and GND with protoboard.
    	
Easy8051 2 and 3: 
	1. Set LCD in left side of the board where writes 2x16.
	2. Set switches 	SW1.0 i SW1.1 (PORT 0)
						SW2.0 i SW2.1 (PORT 1)
						SW4.0 - SW4.5 (PORT 3)
						SW7.6
		ON state.
	3. Connect wires from pins 1.0, 1.1, GND with protoboard so that wires from  1.0/1.1/GND(Easy8051 2 - quessing board) 
	   be in same line with wires from pins 3.1/3.0/GND(Easy8051 1).
	4. Connect wires from pins 1.0, 1.1, GND on protoboard so that wires from 1.0/1.1/GND(Easy8051 3 - assigning)
	   be in same line with wires from pins 1.1/1.0/GND(Easy8051 1).
	5. Connesnt keyboards on PORT0 of the boards Easy8051 2 i 3.
	
Every board turn in PC using USB2.0 A to B cable. 
After that every board needs programming.

   First, we will start mikroC Pro for 8051a and then import project (*.mcpav file) and 
   build project.

   Open 8051FLASH and in section CODE cilck LOAD. Window will open in which you need to find folder
   whihc contains file master1.hex(Easy8051 1), slave_zadaje.hex(Easy8051 2) ili slave2.hex(Easy8051 3).
   After file is loaded click WRITE and wait for it to be written on board.

For starting the game all boards needs to be reseted, last one is board 1. 

GAME CAN START!!!!


NOTE: 	One board is for giving and the other one for quessing word.
		Don't set or remove GLCD and/or LCD while the board is turn on!!!
