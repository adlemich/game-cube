//------------------------------------------------------------------------------------------------------------
// INCLUDE - Hier werden Bibliotheken und andere Code-Module eingebunden (importiert)
//------------------------------------------------------------------------------------------------------------
/* Generelle Bibliothek für Arduino Progammierung */
#include <Arduino.h>
/* Für die 8x8 LED Matrix
 * Das braucht die Bibliothek "Adafruit NeoPixel 1.7.0", siehe "Tools" -> "Bibliotheken verwalten" */
#include <Adafruit_NeoPixel.h> 

//------------------------------------------------------------------------------------------------------------
// DEFINE - Hier werden Definitionen und Konstanten festgelegt
//------------------------------------------------------------------------------------------------------------
#define LED_MATRIX_PIN        6       // Dies ist der digitale Ausgang für das 8x8 LED Feld
#define LED_MATRIX_ANZAHL     64      // Anzahl der LED auf der 8x8 Matrix = 64
#define LED_MATRIX_AUS        ledMatrix.clear(); ledMatrix.show()  // Dieser Befehl löscht die LEDs 
#define LED_HELLIGKEIT        10 
#define LED_FARBE_ROT         0 
#define LED_FARBE_GRUEN       1
#define LED_FARBE_BLAU        2
#define LED_FARBE_ORANGE      3
#define LED_FARBE_WEISS       4

#define LED_AUF_BORD          13      // Dies ist der Kanel für rote die LED auf dem Board

#define AN                    HIGH    // Wert um einen digitalen Ausgang AN zu schalten
#define AUS                   LOW     // Wert um einen digitalen Ausgang AUS zu schalten
#define DIG_EINGANG           INPUT   // Wert um einen digitalen Pin als Eingang zu benutzen
#define DIG_AUSGANG           OUTPUT  // Wert um einen digitalen Pin als Ausgang zu benutzen
#define ABBRUCH               return  // Mit diesem Befehl wird eine Funktion abgebrochen
#define WENN                  if      // Mit diesem Wort kann man eine Überprüfung machen
#define IST                   ==      // Mit diesem Wort kann man eine Überprüfung machen
#define UNGLEICH              !=      // Mit diesem Wort kann man eine Überprüfung machen
#define SONST                 else    // Mit diesem Wort kann man eine Überprüfung machen (alternativen)
#define ODER                  ||      // Mit diesem Wort kann man eine Überprüfung machen
#define UND                   &&      // Mit diesem Wort kann man eine Überprüfung machen
#define SCHLEIFE              for     // Mit diesem Wort kann man eine Schleife (sich wiederholdende Befehle) starten
#define WARTE                 delay   // Mit diesem Befehl kann man für x Millisekunden warten bis es weiter geht
#define ZAHL                  int     // Dieses Wort legt fest, dass eine Variable eine Zahl sein soll
#define ZUSTAND               bool    // Dieses Wort legt fest, dass eine Variable ein Zustand (Ja/Nein) sein soll
#define FUNKTION              void    // Dieses Wort legt den Beginn einer Funktion fest
#define JA                    true    // Dieses Wort wird genutzt um den Zustand von Tasten und Schaltern zu prüfen
#define NEIN                  false   // Dieses Wort wird genutzt um den Zustand von Tasten und Schaltern zu prüfen
#define MODUS_SCHALTER_LINKS  true    // Dieses Wort drückt aus, dass der Spiel-Modus-Schalter links steht (Spiel 1)
#define MODUS_SCHALTER_RECHTS false   // Dieses Wort drückt aus, dass der Spiel-Modus-Schalter rechts steht (Spiel 2)         
#define ZUFALLSZAHL           random  // Dieses Wort wird genutzt um eine Zufallszahl zu erzeugen
 
//------------------------------------------------------------------------------------------------------------
// GLOABLE VARIABLEN - Hier legen wir Variablen, also Daten-Elemente an die wir im Programm nutzen
//------------------------------------------------------------------------------------------------------------

// Die globale Variable "ledMatrix" mit der wir die 8x8 LED Matrix steuern können
Adafruit_NeoPixel ledMatrix(LED_MATRIX_ANZAHL, LED_MATRIX_PIN, NEO_GRB + NEO_KHZ800);

// ------------------------------------------------------------------------------------------------------------
// DIG_PINS_SETUP - Hier legen wir fest welche digital Pins als Eingang oder als Ausgang verwendet werden
// ------------------------------------------------------------------------------------------------------------
FUNKTION dig_pins_setup() {
  pinMode(LED_MATRIX_PIN,         DIG_AUSGANG); 
  pinMode(LED_AUF_BORD,           DIG_AUSGANG); 

  // LED auf dem Bord aus machen
  digitalWrite(LED_AUF_BORD, AUS);
}

// #############################################################################################################
// #-----------------------------------------------------------------------------------------------------------#
// # HIER LEGEN WIR DIE FUNKTIONEN FÜR DIE NUTZUNG DER 8x8 LED-MATRIX FEST                                     #
// # An dieseer Stelle sind es aber nur Vorab-Deklarationen, die wirklichen Funktionen sind in einer Datei.    #
// # Siehe GameCube_A_LED_Matrix.ino.                                                                          #
// # (INFO: Arduino nimmt die Ino-Dateien im Ordern in alphabetischer Reihenfolge und hängt sie aneinander...  #
// #-----------------------------------------------------------------------------------------------------------#
// #############################################################################################################

// LED_MATRIX_SETUP - Hier legen wir fest wie die LED-Matrix gestartet werden soll
FUNKTION led_matrix_setup();

// LED_MATRIX_REIHE - mit dieser Funktion kann man eine Reihe einfärben. Es wird von unten von 1 bis 8 gezählt
FUNKTION led_matrix_reihe(ZAHL reihe, ZAHL farbe);

// LED_MATRIX_SPALTE - mit dieser Funktion kann man eine Spalte einfärben. Es wird von links von 1 bis 8 gezählt
FUNKTION led_matrix_spalte(ZAHL spalte, ZAHL farbe);

// LED_MATRIX_PUNKT - mit dieser Funktion kann man einen Punkt einfärben. 
// Spalten werden von links von 1 bis 8 gezählt, Reihen von unten nach oben von 1 bis 8
FUNKTION led_matrix_punkt(ZAHL reihe, ZAHL spalte, ZAHL farbe);

// led_matrix_zahl - Damit können wir eine Zahl im großen 8x8 LED Display anzeigen. 
// Der erste Parameter stellt die Zahl dar (0 - 16), der zweite die Farbe (LED_FARBE_ROT, LED_FARBE_GRUEN, LED_FARBE_BLAU)
FUNKTION led_matrix_zahl(ZAHL zahl, ZAHL farbe);


// ############################################################################################################
// ------------------------------------------------------------------------------------------------------------
// SETUP - Diese Funktion wird bei  Start des Arduino aufgerufen, hier werden alle Einrichtungen vorgenommen.
// ------------------------------------------------------------------------------------------------------------
// ############################################################################################################

FUNKTION setup() {

 // Wenn der analoge Eingangspin 0 nicht verbunden ist, wird zufälliges analoges
 // Rauschen mit randomSeed() benutzt, um verschiedene Zufalls-Zahlen bei jedem
 // Lauf des Sketches zu generieren.
 randomSeed(analogRead(0));  
  
 // 1) Zuerst legen wir für die digitalen Pins fest, ob sie als Ausgang oder Eingang dienen sollen
 dig_pins_setup(); 
 // 2) Nun starten wir das 8x8 LED Matrix Feld
 led_matrix_setup();
 
}

// ############################################################################################################
// ------------------------------------------------------------------------------------------------------------
// LOOP - Diese Funktion wird vom Board immer wieder durchlaufen, so schnell es der Prozessor erlaubt.
// ------------------------------------------------------------------------------------------------------------
// ############################################################################################################
FUNKTION loop() {

  led_matrix_reihe(1, LED_FARBE_ROT);
  WARTE(1000);
  led_matrix_spalte(3, LED_FARBE_GRUEN);
  WARTE(1000);
  led_matrix_punkt(4, 4, LED_FARBE_ORANGE);
  WARTE(1000);
  led_matrix_zahl(8, LED_FARBE_WEISS);  
  WARTE(1000);
}
