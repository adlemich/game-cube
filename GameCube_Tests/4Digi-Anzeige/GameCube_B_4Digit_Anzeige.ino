
// ------------------------------------------------------------------------------------------------------------
// ANZEIGE_SETUP - Hier legen wir fest wie die 4-Zahlen-Anzeige gestartet werden soll
// ------------------------------------------------------------------------------------------------------------
FUNKTION anzeige_setup() {
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  
  // Wir wollen die Anzeige auf "Dunkel" einstellen 
  anzeige.setBrightness(DISPL_4DIGIT_DUNKEL);

  // Wir testen die Anzeige indem wir die Zahlen von 0 bis 9 einmal durchlaufen
  SCHLEIFE (ZAHL zahl = 0; zahl < 10; zahl ++) {
    data[0] = anzeige.encodeDigit(zahl);
    data[1] = anzeige.encodeDigit(zahl);
    data[2] = anzeige.encodeDigit(zahl);
    data[3] = anzeige.encodeDigit(zahl);
    anzeige.setSegments(data);
    WARTE(20); // Mach 20 Millisekunden Pause
  }
  // Jetzt noch den Doppelpunkt testen
  anzeige.showNumberDecEx(0, (0x80 >> 1), true);
  WARTE(20); // Mach 20 Millisekunden Pause
  // Und Anzeige löschen
  anzeige.clear(); 
}

// ------------------------------------------------------------------------------------------------------------
// ANZEIGE_SPIELSTAND - Damit können wir einen Spielstand anzeigen
// ------------------------------------------------------------------------------------------------------------
FUNKTION anzeige_spielstand(ZAHL wert_links, ZAHL wert_rechts) {

  // Überprüfe Eingabe und breche ab wenn nicht ok
  WENN (wert_links < 0 ODER wert_links > 99 ODER wert_rechts < 0 ODER wert_rechts > 99) {
    ABBRUCH;
  }
   
  // Eingabe ist ok, berechne Gesamtwert
  ZAHL anzeigeWert = (wert_links * 100) + wert_rechts;
  // Jetzt den Wert auf der Anzeige ausgeben
  anzeige.showNumberDecEx(anzeigeWert, (0x80 >> 1), true);
}
