//------------------------------------------------------------------------------------------------------------
// INCLUDE - Hier werden Bibliotheken und andere Code-Module eingebunden (importiert)
//------------------------------------------------------------------------------------------------------------
/* Generelle Bibliothek für Arduino Progammierung */
#include <Arduino.h>
/* Für das 4-Zahlen Display
 * Das braucht die Bibliothek "TM1637 1.2.0" von Avishay Orpaz , siehe "Tools" -> "Bibliotheken verwalten" */
#include <TM1637Display.h>

//------------------------------------------------------------------------------------------------------------
// DEFINE - Hier werden Definitionen und Konstanten festgelegt
//------------------------------------------------------------------------------------------------------------
#define DISPL_4DIGIT_CLK_PIN  2
#define DISPL_4DIGIT_DIO_PIN  3
#define DISPL_4DIGIT_HELL     5
#define DISPL_4DIGIT_DUNKEL   1

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

// Die globale Variable "anzeige" mit der wir die 4-Zahlen Anzeige steuern können
TM1637Display     anzeige(DISPL_4DIGIT_CLK_PIN, DISPL_4DIGIT_DIO_PIN);

// ------------------------------------------------------------------------------------------------------------
// DIG_PINS_SETUP - Hier legen wir fest welche digital Pins als Eingang oder als Ausgang verwendet werden
// ------------------------------------------------------------------------------------------------------------
FUNKTION dig_pins_setup() {
  pinMode(DISPL_4DIGIT_CLK_PIN,   DIG_AUSGANG); 
  pinMode(DISPL_4DIGIT_DIO_PIN,   DIG_AUSGANG); 
  pinMode(LED_AUF_BORD,           DIG_AUSGANG); 

  // LED auf dem Bord aus machen
  digitalWrite(LED_AUF_BORD, AUS);
}

// #############################################################################################################
// #-----------------------------------------------------------------------------------------------------------#
// # HIER LEGEN WIR DIE FUNKTIONEN FÜR DIE NUTZUNG DER 4-DIGIT ANZEIGE FEST                                    #
// # An dieseer Stelle sind es aber nur Vorab-Deklarationen, die wirklichen Funktionen sind in einer Datei.    #
// # Siehe GameCube_B_4Digit_Anzeige.ino.                                                                      #
// # (INFO: Arduino nimmt die Ino-Dateien im Ordern in alphabetischer Reihenfolge und hängt sie aneinander...  #
// #-----------------------------------------------------------------------------------------------------------#
// #############################################################################################################

// ANZEIGE_SETUP - Hier legen wir fest wie die 4-Zahlen-Anzeige gestartet werden soll
FUNKTION anzeige_setup();

// ANZEIGE_SPIELSTAND - Damit können wir einen Spielstand anzeigen
FUNKTION anzeige_spielstand(ZAHL wert_links, ZAHL wert_rechts);

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
 // 3) Nun starten wir das 4-Zahlen Anzeige-Feld
 anzeige_setup();
 // 4) Zeige Spielstand 00:00
 anzeige_spielstand(0, 0);
}

// ############################################################################################################
// ------------------------------------------------------------------------------------------------------------
// LOOP - Diese Funktion wird vom Board immer wieder durchlaufen, so schnell es der Prozessor erlaubt.
// ------------------------------------------------------------------------------------------------------------
// ############################################################################################################
FUNKTION loop() {

  anzeige_spielstand(99,99);
  WARTE(1000);
  anzeige_spielstand(1,00);
  WARTE(1000);
  anzeige_spielstand(0,59);
  WARTE(1000);
  anzeige_spielstand(0,58);
  WARTE(1000);
  
}
