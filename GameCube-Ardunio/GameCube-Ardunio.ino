//------------------------------------------------------------------------------------------------------------
// INCLUDE - Hier werden Bibliotheken und andere Code-Module eingebunden (importiert)
//------------------------------------------------------------------------------------------------------------
/* Generelle Bibliothek für Arduino Progammierung */
#include <Arduino.h>
/* Für die 8x8 LED Matrix
 * Das braucht die Bibliothek "Adafruit NeoPixel 1.7.0", siehe "Tools" -> "Bibliotheken verwalten" */
#include <Adafruit_NeoPixel.h> 
/* Für das 4-Zahlen Displa
 * Das braucht die Bibliothek "TM1637 1.2.0" von Avishay Orpaz , siehe "Tools" -> "Bibliotheken verwalten" */
#include <TM1637Display.h>

//------------------------------------------------------------------------------------------------------------
// DEFINE - Hier werden Definitionen und Konstanten festgelegt
//------------------------------------------------------------------------------------------------------------
#define DISPL_4DIGIT_CLK_PIN  2
#define DISPL_4DIGIT_DIO_PIN  3
#define DISPL_4DIGIT_HELL     5
#define DISPL_4DIGIT_DUNKEL   1

#define LED_MATRIX_PIN        6       // Dies ist der digitale Ausgang für das 8x8 LED Feld
#define LED_MATRIX_ANZAHL     64      // Anzahl der LED auf der 8x8 Matrix = 64
#define LED_MATRIX_AUS        ledMatrix.clear(); ledMatrix.show()  // Dieser Befehl löscht die LEDs 
#define LED_HELLIGKEIT        10 
#define LED_FARBE_ROT         0 
#define LED_FARBE_GRUEN       1
#define LED_FARBE_BLAU        2
#define LED_FARBE_ORANGE      3
#define LED_FARBE_WEISS       4

#define SCHALTER_MODUS_PIN     8      // Dies ist der Kanal für den Modus-Schalter
#define TASTER_GRUEN_UNTEN_PIN 9      // Dies ist der Kanal für den grünen, unteren Taster
#define TASTER_GRUEN_OBEN_PIN 10      // Dies ist der Kanal für den grünen, oberen Taster
#define TASTER_ROT_UNTEN_PIN  11      // Dies ist der Kanal für den roten, unteren Taster
#define TASTER_ROT_OBEN_PIN   12      // Dies ist der Kanal für den roten, oberen Taster

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

#define SPIELER_ROT           1       // Dieses Wort bezeichnet den Spieler Rot / Links
#define SPIELER_GRUEN         2       // Dieses Wort bezeichnet den Spieler Grüen / Rechts
 
//------------------------------------------------------------------------------------------------------------
// GLOABLE VARIABLEN - Hier legen wir Variablen, also Daten-Elemente an die wir im Programm nutzen
//------------------------------------------------------------------------------------------------------------

// Die globale Variable "ledMatrix" mit der wir die 8x8 LED Matrix steuern können
Adafruit_NeoPixel ledMatrix(LED_MATRIX_ANZAHL, LED_MATRIX_PIN, NEO_GRB + NEO_KHZ800);
// Die globale Variable "anzeige" mit der wir die 4-Zahlen Anzeige steuern können
TM1637Display     anzeige(DISPL_4DIGIT_CLK_PIN, DISPL_4DIGIT_DIO_PIN);

// Die globale Variable "schalterModusLetzterZustand" merkt sich den letzten Zustand des Schalters für den Spielmodus (
ZUSTAND schalterModusLetzterZustand = MODUS_SCHALTER_LINKS;
// Die globale Variable "tasterRotObenLetzterZustand" merkt sich den letzten Zustand des Tasters
ZUSTAND tasterRotObenLetzterZustand = NEIN;
// Die globale Variable "tasterRotUntenLetzterZustand" merkt sich den letzten Zustand des Tasters
ZUSTAND tasterRotUntenLetzterZustand = NEIN;
// Die globale Variable "tasterGruenObenLetzterZustand" merkt sich den letzten Zustand des Tasters
ZUSTAND tasterGruenObenLetzterZustand = NEIN;
// Die globale Variable "tasterGruenUntenLetzterZustand" merkt sich den letzten Zustand des Tasters
ZUSTAND tasterGruenUntenLetzterZustand = NEIN;

// ------------------------------------------------------------------------------------------------------------
// DIG_PINS_SETUP - Hier legen wir fest welche digital Pins als Eingang oder als Ausgang verwendet werden
// ------------------------------------------------------------------------------------------------------------
FUNKTION dig_pins_setup() {
  pinMode(1,                      DIG_AUSGANG); 
  pinMode(DISPL_4DIGIT_CLK_PIN,   DIG_AUSGANG); 
  pinMode(DISPL_4DIGIT_DIO_PIN,   DIG_AUSGANG); 
  pinMode(4,                      DIG_AUSGANG); 
  pinMode(5,                      DIG_AUSGANG); 
  pinMode(LED_MATRIX_PIN,         DIG_AUSGANG); 
  pinMode(7,                      DIG_AUSGANG); 
  pinMode(SCHALTER_MODUS_PIN,     DIG_EINGANG); 
  pinMode(TASTER_GRUEN_UNTEN_PIN, DIG_EINGANG); 
  pinMode(TASTER_GRUEN_OBEN_PIN,  DIG_EINGANG); 
  pinMode(TASTER_ROT_UNTEN_PIN,   DIG_EINGANG); 
  pinMode(TASTER_ROT_OBEN_PIN,    DIG_EINGANG); 
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

// #############################################################################################################
// #-----------------------------------------------------------------------------------------------------------#
// # HIER LEGEN WIR DIE FUNKTIONEN FÜR DIE NUTZUNG DER TASTER UND SCHALTER                                     #
// # An dieseer Stelle sind es aber nur Vorab-Deklarationen, die wirklichen Funktionen sind in einer Datei.    #
// # Siehe GameCube_C_TasterSchalter.ino.                                                                      #
// # (INFO: Arduino nimmt die Ino-Dateien im Ordern in alphabetischer Reihenfolge und hängt sie aneinander...  #
// #-----------------------------------------------------------------------------------------------------------#
// #############################################################################################################

// WURDE_TASTER_GEDRUECKT - Überprüft einen Taster und gibt JA oder NEIN zurück
ZUSTAND wurde_taster_gedrueckt(ZAHL taster);

// modus_schalter_geschaltet - Überprüft ob der Schalter für den Modus umgeschaltet wurde. Gibt JA oder NEIN zurück
ZUSTAND modus_schalter_geschaltet();

// #############################################################################################################
// #-----------------------------------------------------------------------------------------------------------#
// # HIER LEGEN WIR DIE FUNKTIONEN FÜR SPIEL 1 UND SPIEL 2 FEST                                                #
// # An dieseer Stelle sind es aber nur Vorab-Deklarationen, die wirklichen Funktionen sind in Dateien.        #
// # Siehe Spiel1.ino und Spiel2.ino                                                                           #
// # (INFO: Arduino nimmt die Ino-Dateien im Ordern in alphabetischer Reihenfolge und hängt sie aneinander...  #
// #-----------------------------------------------------------------------------------------------------------#
// #############################################################################################################
FUNKTION spiel_1_start();
FUNKTION spiel_1_taster_gruen_oben();
FUNKTION spiel_1_taster_gruen_unten();
FUNKTION spiel_1_taster_rot_oben();
FUNKTION spiel_1_taster_rot_unten();
FUNKTION spiel_1_loop();

FUNKTION spiel_2_start();
FUNKTION spiel_2_taster_gruen_oben();
FUNKTION spiel_2_taster_gruen_unten();
FUNKTION spiel_2_taster_rot_oben();
FUNKTION spiel_2_taster_rot_unten();
FUNKTION spiel_2_loop();


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
 // 3) Nun starten wir das 4-Zahlen Anzeige-Feld
 anzeige_setup();
 // 4) Zeige Spielstand 00:00
 anzeige_spielstand(0, 0);
 // 5) Starte Spiel je nachdem wie der Modus-Schalter steht
 modus_schalter_geschaltet();
 WENN (schalterModusLetzterZustand IST MODUS_SCHALTER_LINKS) {
  // Schalter steht links, Spiel 1 starten
   spiel_1_start();
 }
 SONST {
  // Schalter steht rechts, Spiel 2 starten
   spiel_2_start();
 }
}

// ############################################################################################################
// ------------------------------------------------------------------------------------------------------------
// LOOP - Diese Funktion wird vom Board immer wieder durchlaufen, so schnell es der Prozessor erlaubt.
// ------------------------------------------------------------------------------------------------------------
// ############################################################################################################
FUNKTION loop() {

  // SPIEL-MODUS SCHALTER PRÜFEN UND SPIELE STARTEN WENN GEÄNDERT
  WENN (modus_schalter_geschaltet() IST JA) {
    // Zuerst setzen wir die Anzeigen zurück
    anzeige_spielstand(0, 0);
    LED_MATRIX_AUS;
  
    // Ok,der schalter wurde geändert, nun das richtige Spiel starten
    WENN (schalterModusLetzterZustand IST MODUS_SCHALTER_LINKS) {
       // Zeige eine 1 und warte 1 Sekunde
       led_matrix_zahl(1, LED_FARBE_ORANGE);
       WARTE(1000);
       LED_MATRIX_AUS;
       // Schalter steht links, Spiel 1 starten
       spiel_1_start();
    }
    SONST {
       // Zeige eine 2 und warte 1 Sekunde
       led_matrix_zahl(2, LED_FARBE_ORANGE);
       WARTE(1000);
       LED_MATRIX_AUS;
      // Schalter steht rechts, Spiel 2 starten
       spiel_2_start();
    }
  }
  SONST {

    // TASTER PRÜFEN UND AKTION AUSFÜHREN WENN GEDRÜCKT
    WENN (wurde_taster_gedrueckt(TASTER_ROT_OBEN_PIN) IST JA) {
      // Taster-Aktion nun starten 
      WENN (schalterModusLetzterZustand IST MODUS_SCHALTER_LINKS) {
      // Schalter steht links, Spiel 1 
       spiel_1_taster_rot_oben();
      }
      SONST {
        // Schalter steht rechts, Spiel 2 
        spiel_2_taster_rot_oben();
      }
    }
    
    WENN (wurde_taster_gedrueckt(TASTER_ROT_UNTEN_PIN) IST JA) {
      // Taster-Aktion nun starten 
      WENN (schalterModusLetzterZustand IST MODUS_SCHALTER_LINKS) {
      // Schalter steht links, Spiel 1 
         spiel_1_taster_rot_unten();
      }
      SONST {
        // Schalter steht rechts, Spiel 2 
         spiel_2_taster_rot_unten();
      }
    }
    
    WENN (wurde_taster_gedrueckt(TASTER_GRUEN_OBEN_PIN) IST JA) {
      // Taster-Aktion nun starten 
      WENN (schalterModusLetzterZustand IST MODUS_SCHALTER_LINKS) {
         // Schalter steht links, Spiel 1 
         spiel_1_taster_gruen_oben();
      }
      SONST {
        // Schalter steht rechts, Spiel 2 
         spiel_2_taster_gruen_oben();
      }
    }
    
    WENN (wurde_taster_gedrueckt(TASTER_GRUEN_UNTEN_PIN) IST JA) {
      // Taster-Aktion nun starten 
      WENN (schalterModusLetzterZustand IST MODUS_SCHALTER_LINKS) {
         // Schalter steht links, Spiel 1 
         spiel_1_taster_gruen_unten();
      }
      SONST {
        // Schalter steht rechts, Spiel 2 
         spiel_2_taster_gruen_unten();
      }
    }
  
    // Alle Taster geprüft, nun rufen wir den Loop des Spiels auf
    WENN (schalterModusLetzterZustand IST MODUS_SCHALTER_LINKS) {
      // Schalter steht links, Spiel 1 loop
       spiel_1_loop();
    }
    SONST {
      // Schalter steht rechts, Spiel 2 loop
       spiel_2_loop();
    }
  }
}
