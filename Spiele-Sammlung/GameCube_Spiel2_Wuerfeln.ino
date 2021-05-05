/*
 * WÜRFEL SPIEL
 * 
 * Ein einfaches Würfelspiel, kann auch genutzt werden um für ein Brettspiel etc den physischen Würfel zu ersetzen.
 * Funktion: 
 * 
 * Mit den unteren beiden Tastern kann man einstellen wieviele "Seiten" der Würfel haben soll. Also in welchem
 * Bereich 1...X der Würfel würfeln soll. 2 bis 16. 
 * Der unterere rote Taster reduziert die Anzahl der Würfelseiten, der untere grüne Taster erhöht die Anzahl der 
 * Würfelseiten. Die entsprechende Zahl wird in blau angezeigt.
 * 
 * Mit den oberen beiden Tastern wird gewürfelt. Wenn rot gedrückt wird, wird eine Rote Zahl gewürfelt. Bei grün
 * eine grüne Zahl. Das wird immer abwechselnd gemacht. Wer in einer Runde die höhere Zahl würfelt bekommt einen Punkt.
 * Rot beginnt. Wenn der Spieler drückt, der grade nicht dran ist, wird ein Farbbalken angezeigt.
 */

//------------------------------------------------------------------------------------------------------------
// GLOABLE VARIABLEN - Hier legen wir Variablen, also Daten-Elemente an die wir im Spiel nutzen
//------------------------------------------------------------------------------------------------------------
ZAHL wuerfelSeiten    = 6;            // Anzahl der Würfelseiten (zwischen 2 und 16 erlaubt)
ZAHL aktuellerSpieler = SPIELER_ROT;  // Startspieler ist Rot
ZAHL letzteZahlRot    = 0;
ZAHL letzteZahlGruen  = 0;
ZAHL punkteRot        = 0;
ZAHL punkteGruen      = 0;

// ------------------------------------------------------------------------------------------------------------
// spiel_2_start - Legt fest was passiert wenn das Spiel gestartet wird
// Hier zeigen wir an wie die aktuelle Einstellung des Würfels ist und zeigen einen roten Balken um
// zu zeigen, dass Rot beginnt.
// ------------------------------------------------------------------------------------------------------------
FUNKTION spiel_2_start() { 
  // Zeige in blau die aktuelle Würfel-Einstellung an
  led_matrix_zahl(wuerfelSeiten, LED_FARBE_BLAU);
  // Zeige einen Roten Balken links um zu signalisieren dass Rot an der Reihe ist
  led_matrix_spalte(1, LED_FARBE_ROT);
}

// ------------------------------------------------------------------------------------------------------------
// spiel_2_taster_gruen_oben - Legt fest was passiert wenn der grüne, obere Taster gedrückt wird
// Wenn der grüne Spieler dran ist, dann wird eine grüne Zahl gewürfelt und das Ergebnis berechnet.
// ------------------------------------------------------------------------------------------------------------
FUNKTION spiel_2_taster_gruen_oben() { 

  // Wenn Grün dran ist, generiere eine grüne Zufallszahl
  WENN (aktuellerSpieler IST SPIELER_GRUEN) {
    ZAHL wuerfelergebnis = 0;
    // Werfe 10 Mal und nimm das letzte Ergebnis
    SCHLEIFE (ZAHL durchlauf = 0; durchlauf < 10; durchlauf ++) {
      // Achtung, die Funktion ZUFALLSZAHL gibt eine Zahl von 0 bis "wuerfelSeiten - 1" zurück, daher müssen wir noch 1 addieren.
      wuerfelergebnis = ZUFALLSZAHL(wuerfelSeiten) + 1;
      // Das Ergebnis auf der LED Matrix zeigen
      led_matrix_zahl(wuerfelergebnis, LED_FARBE_GRUEN);
      // Ein wenig warten (50 Milisekunden)
      WARTE(50);
    }
    // Ergebnis merken und Spieler wechseln
    letzteZahlGruen = wuerfelergebnis;
    aktuellerSpieler = SPIELER_ROT;

    // Da Gruen immer der zweite Spieler ist, können wir nun prüfen wer diese Runde das bessere Würfelergebnis hatte
    WENN (letzteZahlGruen > letzteZahlRot) {
      punkteGruen = punkteGruen + 1;
    }
    SONST WENN (letzteZahlRot > letzteZahlGruen) {
      punkteRot = punkteRot + 1;
    }

    // Jetzt noch den neuen Spielstand anzeigen
    anzeige_spielstand(punkteRot, punkteGruen);
  }
  SONST {
    // zeige den Balken an um zu zeigen dass der andere dran ist
    led_matrix_spalte(1, LED_FARBE_ROT);
  }
}

// ------------------------------------------------------------------------------------------------------------
// spiel_2_taster_gruen_unten - Legt fest was passiert wenn der grüne, untere Taster gedrückt wird
// Erhöht die Siten des Würfels um 1.
// ------------------------------------------------------------------------------------------------------------
FUNKTION spiel_2_taster_gruen_unten() { 
  // Zeige in blau die aktuelle Würfel-Einstellung an
  led_matrix_zahl(wuerfelSeiten, LED_FARBE_BLAU);
  // Erhöhe um 1, maximal auf 16
  WENN (wuerfelSeiten < 16) {
    wuerfelSeiten = wuerfelSeiten + 1;
  }
  // Zeige in blau die aktuelle Würfel-Einstellung an
  led_matrix_zahl(wuerfelSeiten, LED_FARBE_BLAU);
}

// ------------------------------------------------------------------------------------------------------------
// spiel_2_taster_rot_oben - Legt fest was passiert wenn der rote, obere Taster gedrückt wird
// Wenn der rote Spieler dran ist, dann wird eine rote Zahl gewürfelt
// ------------------------------------------------------------------------------------------------------------
FUNKTION spiel_2_taster_rot_oben() { 
  // Wenn Rot dran ist, geniere eine Rote Zufallszahl
  WENN (aktuellerSpieler IST SPIELER_ROT) {
    ZAHL wuerfelergebnis = 0;
    // Werfe 10 Mal und nimm das letzte Ergebnis
    SCHLEIFE (ZAHL durchlauf = 0; durchlauf < 10; durchlauf ++) {
      wuerfelergebnis = ZUFALLSZAHL(wuerfelSeiten) + 1;
      led_matrix_zahl(wuerfelergebnis, LED_FARBE_ROT);
      WARTE(50);
    }
    letzteZahlRot = wuerfelergebnis;
    aktuellerSpieler = SPIELER_GRUEN;
  }
  SONST {
    // zeige den Balken an um zu zeigen dass der andere dran ist
    led_matrix_spalte(8, LED_FARBE_GRUEN);
  }
}

// ------------------------------------------------------------------------------------------------------------
// spiel_2_taster_rot_unten - Legt fest was passiert wenn der rote, untere Taster gedrückt wird
// Reduziert die Zahl der Würfelseiten um 1
// ------------------------------------------------------------------------------------------------------------
FUNKTION spiel_2_taster_rot_unten() {
  // Zeige in blau die aktuelle Würfel-Einstellung an
  led_matrix_zahl(wuerfelSeiten, LED_FARBE_BLAU);
  // Reduziere um 1, maximal auf 2
  WENN (wuerfelSeiten > 2) {
    wuerfelSeiten = wuerfelSeiten - 1;
  } 
  // Zeige in blau die aktuelle Würfel-Einstellung an
  led_matrix_zahl(wuerfelSeiten, LED_FARBE_BLAU);
}

// ------------------------------------------------------------------------------------------------------------
// spiel_2_loop - Diese Funktion wird immer dann aufgerufen wenn kein Taster gedrückt wurde, hier läuft die Hauptroutine
// ------------------------------------------------------------------------------------------------------------
FUNKTION spiel_2_loop() { 
  // hier passiert nix. Wir pausieren nur für 1 Millisekunde um den Prozessor zu entlasten
  WARTE(1);
}
