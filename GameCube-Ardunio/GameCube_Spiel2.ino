/*
 * GAME CUBE - PONG
 * Die ist eine einfache Variante des Klassikers PONG, ein Spiel bei dem zwei Spieler einen Ball 
 * mit ihren Balken abwehren müssen und so verhindern dass der Gegner Punkte macht. Verpasst ein 
 * Spieler den Ball, bekommt der Gegner einen Punkt.
 * 
 * Mit den beiden Tastern kann ein Spieler seinen Balken nach rechts oder links bewegen. Pro Tastendruck
 * bewegt sich der Balken um eine Position. Der Balken ist 3 Punkte breit und kann sich von ganz oben bis 
 * ganz unten bewegen. Referenzpunkt ist der mittlere Punkt eines Balken.
 * 
 * Der Ball bewegt sich mit wachsenender Geschwindigkeit. Er prallt von den Wänden oben und unten ab (im 
 * gleichen Winkel). Wenn der Ball auf einen Balken trifft, dann wird er mit einem zufälligen Winkel wieder
 * zurückprallen und somit die Flugbahn etwas interessanter gestalten. Trifft der Ball auf das Ende des Spielfelds
 * (am Balken vorbei), so wird das als Tor gewertet. Bei 10 Punkten endet ein Spiel.
 */

//------------------------------------------------------------------------------------------------------------
// GLOABLE VARIABLEN - Hier legen wir Variablen, also Daten-Elemente an die wir im Spiel nutzen
//------------------------------------------------------------------------------------------------------------
#define POSITION_BALKEN_MIN        0 // Die Position ganz unten
#define POSITION_BALKEN_MAX        9 // Die Position ganz oben
#define BALL_GESCHWIND_MAX    150000 // Die maximale Geschwindigkeit des Balls
#define BALL_GESCHWIND_START   10000 // Die Start-Geschwindigkeit des Balls
#define BALL_BESCHLEUNIGUNG     3000 // Die Beschleunigung des Balls (in Prozent) pro Sekunde == 1000 Zyklen. 
#define BALL_VERT_GESCHW_MAX   10000 // Die vertikale Geschwindigkeit des Balls (max)
#define ZYKLUS_BASIS         1000000 // Unsere Basis zur Aktivierung der zyklischen Prozesse

ZAHL punkte_Spieler_1 = 0;  // Spieler 1 ist links / rot
ZAHL punkte_Spieler_2 = 0;  // Spieler 2 ist rechts / grün

// Die Postion der Balken entlang der vertikalen Spalten - 1 ist ganz unten, 8 ganz oben.
ZAHL position_Balken_1 = 4; // Der linke Balken started auf Position 4 (von unten gezählt) 
ZAHL position_Balken_2 = 5; // Der rechte Balken started auf Position 5 (von unten gezählt)

ZAHL position_Ball_Hori        = 4; // Die Position des Balls - horizontal - 1 ist ganz links, 8 ganz rechts
ZAHL geschwindigkeit_Ball_Hori = BALL_GESCHWIND_START; // Die aktuelle horizontale Geschwindigkeit des Balls in Prozent. Hier die Startgeschwindigkeit
ZUSTAND richtung_Ball_rechts   = JA; // Der Ball düst erstmal nach rechts.
ZAHL position_Ball_Vert        = 4; // Die Position des Balls - vertikal - 1 ist ganz unten, 8 ganz oben
ZAHL geschwindigkeit_Ball_Vert = 1; // Die aktuelle vertikale  Geschwindigkeit des Balls in Prozent. Hier die Startgeschwindigkeit
ZUSTAND richtung_Ball_hoch     = JA; // Der Ball düst erstmal nach oben

ZAHL zyklusZaehler = 1; // Ein Zähler, der die 1ms- Zyklen zählt

// ------------------------------------------------------------------------------------------------------------
// Diese Funktion malt den roten Balken, 3 Punkte um den Referenzpunkt
// ------------------------------------------------------------------------------------------------------------
FUNKTION spiel_2_male_balken_rot() { 
  
  // Zuerst malen wir die ganze linke Spalte schwarz aus
  led_matrix_spalte(1, LED_FARBE_SCHWARZ);
  // Jetzt den Balken mit 3 Punkten um die Position herum
  led_matrix_punkt(position_Balken_1 - 1, 1, LED_FARBE_ROT);
  led_matrix_punkt(position_Balken_1,     1, LED_FARBE_ROT);
  led_matrix_punkt(position_Balken_1 + 1, 1, LED_FARBE_ROT);
}

// ------------------------------------------------------------------------------------------------------------
// Diese Funktion malt den grünen Balken, 3 Punkte um den Referenzpunkt
// ------------------------------------------------------------------------------------------------------------
FUNKTION spiel_2_male_balken_gruen() { 

    // Zuerst malen wir die ganze rechte Spalte schwarz aus
  led_matrix_spalte(8, LED_FARBE_SCHWARZ);
  // Jetzt den Balken mit 3 Punkten um die Position herum
  led_matrix_punkt(position_Balken_2 - 1, 8, LED_FARBE_GRUEN);
  led_matrix_punkt(position_Balken_2,     8, LED_FARBE_GRUEN);
  led_matrix_punkt(position_Balken_2 + 1, 8, LED_FARBE_GRUEN);
  
}

// ------------------------------------------------------------------------------------------------------------
// Diese Funktion malt den Ball
// ------------------------------------------------------------------------------------------------------------
FUNKTION spiel_2_male_ball() { 

  led_matrix_punkt(position_Ball_Vert, position_Ball_Hori, LED_FARBE_WEISS);    
}
// ------------------------------------------------------------------------------------------------------------
// Diese Funktion entfernt den Ball
// ------------------------------------------------------------------------------------------------------------
FUNKTION spiel_2_entferne_ball() { 

  led_matrix_punkt(position_Ball_Vert, position_Ball_Hori, LED_FARBE_SCHWARZ);    
}


// ------------------------------------------------------------------------------------------------------------
// spiel_2_start - Legt fest was passiert wenn das Spiel gestartet wird
//  
// ------------------------------------------------------------------------------------------------------------
FUNKTION spiel_2_start() { 

  // Werte setzten
  position_Balken_1 = 4; // Der linke Balken started auf Position 4 (von unten gezählt) 
  position_Balken_2 = 5; // Der rechte Balken started auf Position 5 (von unten gezählt)

  position_Ball_Hori        = 4; // Die Position des Balls - horizontal - 1 ist ganz links, 8 ganz rechts
  geschwindigkeit_Ball_Hori = BALL_GESCHWIND_START; // Die aktuelle horizontale Geschwindigkeit des Balls in Prozent. Hier die Startgeschwindigkeit
  richtung_Ball_rechts      = JA; // Der Ball düst erstmal nach rechts.
  position_Ball_Vert        = 4; // Die Position des Balls - vertikal - 1 ist ganz unten, 8 ganz oben
  geschwindigkeit_Ball_Vert = 1; // Die aktuelle vertikale  Geschwindigkeit des Balls in Prozent. Hier die Startgeschwindigkeit

  zyklusZaehler = 1; // Ein Zähler, der die 1ms- Zyklen zählt

  // Malen wir die obere Wand
  led_matrix_reihe(8, LED_FARBE_BLAU);
  // Malen wir die untere Wand
  led_matrix_reihe(1, LED_FARBE_BLAU);

  // Malen wir die Balken
  spiel_2_male_balken_rot();
  spiel_2_male_balken_gruen();

  // Malen wir den Ball
  spiel_2_male_ball();

  // Spiel-Stands-Anzeige zurücksetzen
  anzeige_spielstand(punkte_Spieler_1, punkte_Spieler_2);
  
}

// ------------------------------------------------------------------------------------------------------------
// spiel_2_taster_gruen_oben - Legt fest was passiert wenn der grüne, obere Taster gedrückt wird
// 
// ------------------------------------------------------------------------------------------------------------
FUNKTION spiel_2_taster_gruen_oben() { 

  // Überprüfen ob max erreicht
  WENN (position_Balken_2 < POSITION_BALKEN_MAX) {
    // Balken von Spieler 2 um eine Position hoch
    position_Balken_2 = position_Balken_2 + 1;  
    // Jetzt neu malen
    spiel_2_male_balken_gruen();
  }
}

// ------------------------------------------------------------------------------------------------------------
// spiel_2_taster_gruen_unten - Legt fest was passiert wenn der grüne, untere Taster gedrückt wird
// 
// ------------------------------------------------------------------------------------------------------------
FUNKTION spiel_2_taster_gruen_unten() { 

  // Überprüfen ob min erreicht
  WENN (position_Balken_2 > POSITION_BALKEN_MIN) {
    // Balken von Spieler 2 um eine Position runter
    position_Balken_2 = position_Balken_2 - 1;  
    // Jetzt neu malen
    spiel_2_male_balken_gruen();
  }
   
}

// ------------------------------------------------------------------------------------------------------------
// spiel_2_taster_rot_oben - Legt fest was passiert wenn der rote, obere Taster gedrückt wird
// 
// ------------------------------------------------------------------------------------------------------------
FUNKTION spiel_2_taster_rot_oben() { 

  // Überprüfen ob max erreicht
  WENN (position_Balken_1 < POSITION_BALKEN_MAX) {
    // Balken von Spieler 1 um eine Position hoch
    position_Balken_1 = position_Balken_1 + 1;  
    // Jetzt neu malen
    spiel_2_male_balken_rot();
  }
}

// ------------------------------------------------------------------------------------------------------------
// spiel_2_taster_rot_unten - Legt fest was passiert wenn der rote, untere Taster gedrückt wird
// 
// ------------------------------------------------------------------------------------------------------------
FUNKTION spiel_2_taster_rot_unten() {

  // Überprüfen ob min erreicht
  WENN (position_Balken_1 > POSITION_BALKEN_MIN) {
    // Balken von Spieler 1 um eine Position runter
    position_Balken_1 = position_Balken_1 - 1;  
    // Jetzt neu malen
    spiel_2_male_balken_rot();
  }
}


// ------------------------------------------------------------------------------------------------------------
// spiel_2_bewege_Ball - Berechnet die neue Position des Balls und setzt den Punkt auf der LED Matrix
// ------------------------------------------------------------------------------------------------------------
FUNKTION spiel_2_bewege_Ball() {

  // Bei jedem 1000. Zyklus, also grob nach einer Sekunde erhöhen wir die Geschwindigkeit
  WENN (zyklusZaehler % 1000 IST 0) {
    // WIr erhöhen die Ballgeschwindigkeit Horizonztal
    // Auf MAX begrenzen
    WENN (geschwindigkeit_Ball_Hori < BALL_GESCHWIND_MAX) {
      geschwindigkeit_Ball_Hori = geschwindigkeit_Ball_Hori + BALL_BESCHLEUNIGUNG;  
    }
  }

  // Bevor wir den Ball bewegen müssen wir den alten entfernen
  spiel_2_entferne_ball();

  // Der Ball geht horizontal ein Feld weiter, entsprechend seiner Geschwindigkeit
  // Hier verwenden wir die Modulo Funktion - sie gibt uns den Rest einer Division zurück
  WENN ( (zyklusZaehler % (ZYKLUS_BASIS / geschwindigkeit_Ball_Hori)) IST 0) {
    WENN (richtung_Ball_rechts IST JA) {
      position_Ball_Hori = position_Ball_Hori + 1;
    }
    SONST {
      position_Ball_Hori = position_Ball_Hori - 1;
    }
  }

  // Der Ball geht vertikal ein Feld weiter, entsprechend seiner Geschwindigkeit
  // Hier verwenden wir die Modulo Funktion - sie gibt uns den Rest einer Division zurück
  WENN ( (zyklusZaehler % (ZYKLUS_BASIS / geschwindigkeit_Ball_Vert)) IST 0) {
    WENN (richtung_Ball_hoch IST JA) {
      position_Ball_Vert = position_Ball_Vert + 1;
    }
    SONST {
      position_Ball_Vert = position_Ball_Vert - 1;
    }
  }

  // Malen wir den Ball
  spiel_2_male_ball();
}

// ------------------------------------------------------------------------------------------------------------
// spiel_2_teste_Wand - Überprüft ob der Ball oben oder unten angesossen ist. Dreht dann die vertikale Geschwindikeit um
// ------------------------------------------------------------------------------------------------------------
FUNKTION spiel_2_teste_Wand() {

 // UNTEN
 WENN (position_Ball_Vert IST 2) {
  // wir schicken den Ball wieder nach oben
  richtung_Ball_hoch = JA;
 }

 // OBEN
 WENN (position_Ball_Vert IST 7) {
  // wir schicken den Ball wieder nach oben
  richtung_Ball_hoch = NEIN;
 }
}

// ------------------------------------------------------------------------------------------------------------
// spiel_2_teste_Balken - Überprüft ob der Ball einen der Spielerbalken berührt, und der Ball damit zurück fliegt
// ------------------------------------------------------------------------------------------------------------
FUNKTION spiel_2_teste_Balken() {

  // Wenn der Ball links auf LED 2 ist - LINKE Position
  WENN (position_Ball_Hori IST 2) {
    // Jetzt gucken wir ob der Balken vertikal neben dem Ball ist, der Balken dehnt sich nach oben und unten um 1 aus
    WENN (position_Ball_Vert IST position_Balken_1 ODER
          position_Ball_Vert IST position_Balken_1 + 1 ODER
          position_Ball_Vert IST position_Balken_1 - 1) {

      // Treffer! Jetzt schicken wir den Ball wieder nach rechts ...
      richtung_Ball_rechts = JA;
      // ... und geben ihm eine zufällige vertikale Geschwindigkeit
      geschwindigkeit_Ball_Vert = ZUFALLSZAHL(1, BALL_VERT_GESCHW_MAX);
    }          
  }

  // Wenn der Ball links auf LED 7 ist - RECHTE Position
  WENN (position_Ball_Hori IST 7) {
    // Jetzt gucken wir ob der Balken vertikal neben dem Ball ist, der Balken dehnt sich nach oben und unten um 1 aus
    WENN (position_Ball_Vert IST position_Balken_2 ODER
          position_Ball_Vert IST position_Balken_2 + 1 ODER
          position_Ball_Vert IST position_Balken_2 - 1) {

      // Treffer! Jetzt schicken wir den Ball wieder nach links
      richtung_Ball_rechts = NEIN;
      // ... und geben ihm eine zufällige vertikale Geschwindigkeit
      geschwindigkeit_Ball_Vert = ZUFALLSZAHL(1, BALL_VERT_GESCHW_MAX);
    }          
  }
}

// ------------------------------------------------------------------------------------------------------------
// spiel_2_teste_Tor - Überprüft ob der Ball ein Tor gemacht hat
// ------------------------------------------------------------------------------------------------------------
FUNKTION spiel_2_teste_Tor() {
 
 ZUSTAND tor_gefallen = NEIN;
 
 // Wenn der Ball links hinter LED 1 ist - LINKE Position
 WENN (position_Ball_Hori IST 0) {
    // TOOOOOR für Spieler 2
    punkte_Spieler_2 = punkte_Spieler_2 + 1;
    tor_gefallen = JA;
  }

 // Wenn der Ball links hinter LED 8 ist - RECHTE Position
 WENN (position_Ball_Hori IST 9) {
    // TOOOOOR für Spieler 1
    punkte_Spieler_1 = punkte_Spieler_1 + 1;
    tor_gefallen = JA;
  }

 // Wenn ein Tor gefallen ist
 WENN (tor_gefallen IST JA) {

  // Eine kleine Animiation einspielen
  LED_MATRIX_AUS;
  SCHLEIFE (ZAHL reihe = 1; reihe < 9; reihe++) {
    led_matrix_reihe(reihe, LED_FARBE_BLAU); 
    WARTE(50);
    led_matrix_reihe(reihe, LED_FARBE_SCHWARZ);     
  }
  SCHLEIFE (ZAHL reihe = 8; reihe > 0; reihe--) {
    led_matrix_reihe(reihe, LED_FARBE_ORANGE); 
    WARTE(50);
    led_matrix_reihe(reihe, LED_FARBE_SCHWARZ);     
  }
  LED_MATRIX_AUS;
  
  // Alles auf Anfang
  spiel_2_start();
 }  
}
// ------------------------------------------------------------------------------------------------------------
// spiel_2_loop - Diese Funktion wird immer dann aufgerufen wenn kein Taster gedrückt wurde, hier läuft die Hauptroutine
// ------------------------------------------------------------------------------------------------------------
FUNKTION spiel_2_loop() { 

  // Die Taster-Aktionen werden im Hauptprogramm bereits behandelt
  // Als erstes berechnen wir die neue Ball-Position und zeichnen den Ball neu
  spiel_2_bewege_Ball();

  // Jetzt testen wir ob der Ball oben oder unten angestossen ist
  spiel_2_teste_Wand();

  // Jetzt testen wir ob der Ball an einen der Spielerbalken anstösst
  spiel_2_teste_Balken();

  // Jetzt testen wir ob der Ball ein Tor gemacht hat
  spiel_2_teste_Tor();

  // Zyklus eins hoch zählen bis maximal ZYKLUS_BASIS
  zyklusZaehler = zyklusZaehler + 1;
  WENN (zyklusZaehler > ZYKLUS_BASIS) {
    zyklusZaehler = 1;
  }
  
  // hier passiert nix. Wir pausieren nur für 1 Millisekunde um den Prozessor zu entlasten
  WARTE(1);
}
