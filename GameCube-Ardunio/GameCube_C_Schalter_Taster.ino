// ------------------------------------------------------------------------------------------------------------
// modus_schalter_geschaltet - Überprüft ob der Schalter für den Modus umgeschaltet wurde. Gibt JA oder NEIN zurück
// ------------------------------------------------------------------------------------------------------------
ZUSTAND modus_schalter_geschaltet() {
  
  // Jetzt den Wert am Digital Eingang ablesen
  ZUSTAND schalter_jetzt = digitalRead(SCHALTER_MODUS_PIN);
  ZUSTAND ergebnis = NEIN;

  WENN (schalter_jetzt UNGLEICH schalterModusLetzterZustand)
  {
    // Der Zustand des Schalters hat sich geändert. Jetzt muss was passieren
    ergebnis = JA;
  }
  schalterModusLetzterZustand = schalter_jetzt;

  ABBRUCH ergebnis; 
}

// ------------------------------------------------------------------------------------------------------------
// WURDE_TASTER_GEDRUECKT - Überprüft einen Taster und gibt JA oder NEIN zurück
// ------------------------------------------------------------------------------------------------------------
ZUSTAND wurde_taster_gedrueckt(ZAHL taster) {

  // Jetzt den Wert am Digital Eingang ablesen
  ZUSTAND taster_jetzt = digitalRead(taster);
  ZUSTAND ergebnis = NEIN;
    
  // Jeder Taster wird gesondert untersucht
  // GRÜN UNTEN
  WENN (taster IST TASTER_GRUEN_UNTEN_PIN) {
    WENN (taster_jetzt UNGLEICH tasterGruenUntenLetzterZustand UND taster_jetzt IST JA)
    {
      // Der Zustand des Tasters hat sich von NEIN auf JA geändert. Jetzt muss was passieren
      ergebnis = JA;
    }
    tasterGruenUntenLetzterZustand = taster_jetzt;
  }
  // GRÜN OBEN
  SONST WENN (taster IST TASTER_GRUEN_OBEN_PIN) {
    WENN (taster_jetzt UNGLEICH tasterGruenObenLetzterZustand UND taster_jetzt IST JA)
    {
      // Der Zustand des Tasters hat sich von NEIN auf JA geändert. Jetzt muss was passieren
      ergebnis = JA;
    }
    tasterGruenObenLetzterZustand = taster_jetzt;
  }
  // ROT UNTEN
  SONST WENN (taster IST TASTER_ROT_UNTEN_PIN) {
    WENN (taster_jetzt UNGLEICH tasterRotUntenLetzterZustand UND taster_jetzt IST JA)
    {
      // Der Zustand des Tasters hat sich von NEIN auf JA geändert. Jetzt muss was passieren
      ergebnis = JA;
    }
    tasterRotUntenLetzterZustand = taster_jetzt;
  }
  // ROT OBEN
  SONST WENN (taster IST TASTER_ROT_OBEN_PIN) {
    WENN (taster_jetzt UNGLEICH tasterRotObenLetzterZustand UND taster_jetzt IST JA)
    {
      // Der Zustand des Tasters hat sich von NEIN auf JA geändert. Jetzt muss was passieren
      ergebnis = JA;
    }
    tasterRotObenLetzterZustand = taster_jetzt;
  }
 
  ABBRUCH ergebnis; 
}
