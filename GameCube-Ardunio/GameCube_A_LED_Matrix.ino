// ------------------------------------------------------------------------------------------------------------
// LED_MATRIX_SETUP - Hier legen wir fest wie die LED-Matrix gestartet werden soll
// ------------------------------------------------------------------------------------------------------------
FUNKTION led_matrix_setup() {
  // Erstmal starten
  ledMatrix.begin();
  
  // Dann machen wir einen Testlauf mit allen 3 Farben Grundfarben
  // 3 Durchläufe für die 3 Grundfarben...
  SCHLEIFE (ZAHL farbe = 0; farbe < 3; farbe++) { 

    // So viele Durchläufe wie wir LEDs haben...
    SCHLEIFE (ZAHL ledNr = 0; ledNr < LED_MATRIX_ANZAHL; ledNr++) {

      // Alle LEDs aus
      ledMatrix.clear();
      WENN (farbe IST 0) {
        ledMatrix.setPixelColor(ledNr, ledMatrix.Color(LED_HELLIGKEIT, 0, 0));
      }
      SONST WENN (farbe IST 1) {
        ledMatrix.setPixelColor(ledNr, ledMatrix.Color(0, LED_HELLIGKEIT, 0));
      }
      SONST WENN (farbe IST 2) {
        ledMatrix.setPixelColor(ledNr, ledMatrix.Color(0, 0, LED_HELLIGKEIT));
      }
      // ok - jetzt anzeigen!
      ledMatrix.show();  
      WARTE(2); // Mach 2 millisekunde Pause
    }    
  }
  // Anzeige löschen
  LED_MATRIX_AUS;  
}

// ------------------------------------------------------------------------------------------------------------
// LED_MATRIX_REIHE - mit dieser Funktion kann man eine Reihe einfärben. Es wird von unten von 1 bis 8 gezählt
// ------------------------------------------------------------------------------------------------------------
FUNKTION led_matrix_reihe(ZAHL reihe, ZAHL farbe) {

  // Zuerst mal überprüfen ob die Eingaben ok sind
  WENN (reihe < 1 ODER reihe > 8 ODER farbe < LED_FARBE_ROT ODER farbe > LED_FARBE_WEISS) {
    ABBRUCH;
  }

  // jetzt berechnen wir die Position der ersten LED in der Zeile
  ZAHL ersteLEDPosition = (reihe - 1) * 8;

  // Jetzt aktivieren wir je nach Farbe die LEDs, immer 8 Stück, beginnend von der ersten
  ZAHL ledNr = ersteLEDPosition;
  SCHLEIFE (ZAHL zaehler = 0; zaehler < 8; zaehler ++) { 
    
    ledNr = ersteLEDPosition + zaehler;
    WENN (farbe IST LED_FARBE_ROT) {
      ledMatrix.setPixelColor(ledNr, ledMatrix.Color(LED_HELLIGKEIT, 0, 0));
    }
    SONST WENN (farbe IST LED_FARBE_GRUEN) {
      ledMatrix.setPixelColor(ledNr, ledMatrix.Color(0, LED_HELLIGKEIT, 0));
    }
    SONST WENN (farbe IST LED_FARBE_BLAU) {
      ledMatrix.setPixelColor(ledNr, ledMatrix.Color(0, 0, LED_HELLIGKEIT));
    }
    SONST WENN (farbe IST LED_FARBE_ORANGE) {
      ledMatrix.setPixelColor(ledNr, ledMatrix.Color(LED_HELLIGKEIT, LED_HELLIGKEIT/2, 0));
    }
    SONST WENN (farbe IST LED_FARBE_SCHWARZ) {
      ledMatrix.setPixelColor(ledNr, ledMatrix.Color(0, 0, 0));
    }
    SONST WENN (farbe IST LED_FARBE_WEISS) {
      ledMatrix.setPixelColor(ledNr, ledMatrix.Color(LED_HELLIGKEIT, LED_HELLIGKEIT, LED_HELLIGKEIT));
    }
  }
  // ok - jetzt anzeigen!
  ledMatrix.show();
}


// ------------------------------------------------------------------------------------------------------------
// LED_MATRIX_SPALTE - mit dieser Funktion kann man eine Spalte einfärben. Es wird von links von 1 bis 8 gezählt
// ------------------------------------------------------------------------------------------------------------
FUNKTION led_matrix_spalte(ZAHL spalte, ZAHL farbe) {

  // Zuerst mal überprüfen ob die Eingaben ok sind
  WENN (spalte < 1 ODER spalte > 8 ODER farbe < LED_FARBE_ROT ODER farbe > LED_FARBE_WEISS) {
    ABBRUCH;
  }

  // jetzt berechnen wir die Position der ersten LED in der Spalte (unterste)
  ZAHL ersteLEDPosition = (9 - spalte) - 1;

  // Jetzt aktivieren wir je nach Farbe die LEDs, immer 8 Stück, beginnend von der untersten nach oben
  ZAHL ledNr = ersteLEDPosition;
  SCHLEIFE (ZAHL zaehler = 0; zaehler < 8; zaehler ++) { 
    
    ledNr = ersteLEDPosition + (zaehler * 8);
    WENN (farbe IST LED_FARBE_ROT) {
      ledMatrix.setPixelColor(ledNr, ledMatrix.Color(LED_HELLIGKEIT, 0, 0));
    }
    SONST WENN (farbe IST LED_FARBE_GRUEN) {
      ledMatrix.setPixelColor(ledNr, ledMatrix.Color(0, LED_HELLIGKEIT, 0));
    }
    SONST WENN (farbe IST LED_FARBE_BLAU) {
      ledMatrix.setPixelColor(ledNr, ledMatrix.Color(0, 0, LED_HELLIGKEIT));
    }
    SONST WENN (farbe IST LED_FARBE_ORANGE) {
      ledMatrix.setPixelColor(ledNr, ledMatrix.Color(LED_HELLIGKEIT, LED_HELLIGKEIT/2, 0));
    }
    SONST WENN (farbe IST LED_FARBE_SCHWARZ) {
      ledMatrix.setPixelColor(ledNr, ledMatrix.Color(0, 0, 0));
    }
    SONST WENN (farbe IST LED_FARBE_WEISS) {
      ledMatrix.setPixelColor(ledNr, ledMatrix.Color(LED_HELLIGKEIT, LED_HELLIGKEIT, LED_HELLIGKEIT));
    }
  }
  // ok - jetzt anzeigen!
  ledMatrix.show();
}

// ------------------------------------------------------------------------------------------------------------
// LED_MATRIX_PUNKT - mit dieser Funktion kann man einen Punkt einfärben. 
// Spalten werden von links von 1 bis 8 gezählt, Reihen von unten nach oben von 1 bis 8
// ------------------------------------------------------------------------------------------------------------
FUNKTION led_matrix_punkt(ZAHL reihe, ZAHL spalte, ZAHL farbe) {
  
  // Zuerst mal überprüfen ob die Eingaben ok sind
  WENN (reihe < 1 ODER reihe > 8 ODER spalte < 1 ODER spalte > 8 ODER farbe < LED_FARBE_ROT ODER farbe > LED_FARBE_WEISS) {
    ABBRUCH;
  }

  // jetzt berechnen wir die Position der LED 
  ZAHL ledNr = ((9 - spalte) - 1 ) + ((reihe - 1) * 8);

  WENN (farbe IST LED_FARBE_ROT) {
    ledMatrix.setPixelColor(ledNr, ledMatrix.Color(LED_HELLIGKEIT, 0, 0));
  }
  SONST WENN (farbe IST LED_FARBE_GRUEN) {
    ledMatrix.setPixelColor(ledNr, ledMatrix.Color(0, LED_HELLIGKEIT, 0));
  }
  SONST WENN (farbe IST LED_FARBE_BLAU) {
    ledMatrix.setPixelColor(ledNr, ledMatrix.Color(0, 0, LED_HELLIGKEIT));
  }
  SONST WENN (farbe IST LED_FARBE_ORANGE) {
    ledMatrix.setPixelColor(ledNr, ledMatrix.Color(LED_HELLIGKEIT, LED_HELLIGKEIT/2, 0));
  }
  SONST WENN (farbe IST LED_FARBE_SCHWARZ) {
      ledMatrix.setPixelColor(ledNr, ledMatrix.Color(0, 0, 0));
  }
  SONST WENN (farbe IST LED_FARBE_WEISS) {
    ledMatrix.setPixelColor(ledNr, ledMatrix.Color(LED_HELLIGKEIT, LED_HELLIGKEIT, LED_HELLIGKEIT));
  }
  // ok - jetzt anzeigen!
  ledMatrix.show();
}

// ------------------------------------------------------------------------------------------------------------
// led_matrix_zahl - Damit können wir eine Zahl im großen 8x8 LED Display anzeigen. 
// Der erste Parameter stellt die Zahl dar (0 - 16), der zweite die Farbe (LED_FARBE_ROT, LED_FARBE_GRUEN, LED_FARBE_BLAU)
// ------------------------------------------------------------------------------------------------------------
FUNKTION led_matrix_zahl(ZAHL zahl, ZAHL farbe) {

  // jetzt berechnen wir die Position der LED 
   
  // Überprüfe Eingabe und breche ab wenn nicht ok
  WENN (zahl < 0 ODER zahl > 16) {
    ABBRUCH;
  }

  // Erstmal die Anzeige löschen
  LED_MATRIX_AUS;

  WENN (zahl IST 0) {
    led_matrix_punkt(3, 4, farbe);
    led_matrix_punkt(3, 5, farbe);
    led_matrix_punkt(4, 3, farbe);
    led_matrix_punkt(4, 6, farbe);
    led_matrix_punkt(5, 4, farbe);
    led_matrix_punkt(5, 6, farbe);
    led_matrix_punkt(6, 4, farbe);
    led_matrix_punkt(6, 6, farbe);
    led_matrix_punkt(7, 4, farbe);
    led_matrix_punkt(7, 5, farbe);
  }
  SONST WENN (zahl IST 1) {
    led_matrix_punkt(3, 5, farbe);
    led_matrix_punkt(4, 5, farbe);
    led_matrix_punkt(5, 3, farbe);
    led_matrix_punkt(5, 5, farbe);
    led_matrix_punkt(6, 4, farbe);
    led_matrix_punkt(6, 5, farbe);
    led_matrix_punkt(7, 5, farbe);
  }
  SONST WENN (zahl IST 2) {
    led_matrix_punkt(3, 3, farbe);
    led_matrix_punkt(3, 4, farbe);
    led_matrix_punkt(3, 5, farbe);
    led_matrix_punkt(3, 6, farbe);
    led_matrix_punkt(4, 5, farbe);
    led_matrix_punkt(5, 6, farbe);
    led_matrix_punkt(6, 3, farbe);
    led_matrix_punkt(6, 6, farbe);
    led_matrix_punkt(7, 4, farbe);
    led_matrix_punkt(7, 5, farbe);
  }
  SONST WENN (zahl IST 3) {
    led_matrix_punkt(3, 4, farbe);
    led_matrix_punkt(3, 5, farbe);
    led_matrix_punkt(4, 6, farbe);
    led_matrix_punkt(5, 4, farbe);
    led_matrix_punkt(5, 5, farbe);
    led_matrix_punkt(6, 6, farbe);
    led_matrix_punkt(7, 4, farbe);
    led_matrix_punkt(7, 5, farbe);
  }
  SONST WENN (zahl IST 4) {
    led_matrix_punkt(3, 5, farbe);
    led_matrix_punkt(4, 5, farbe);
    led_matrix_punkt(5, 3, farbe);
    led_matrix_punkt(5, 4, farbe);
    led_matrix_punkt(5, 5, farbe);
    led_matrix_punkt(5, 6, farbe);
    led_matrix_punkt(6, 3, farbe);
    led_matrix_punkt(6, 5, farbe);
    led_matrix_punkt(7, 3, farbe); 
  }
  SONST WENN (zahl IST 5) {
    led_matrix_punkt(3, 3, farbe);
    led_matrix_punkt(3, 4, farbe);
    led_matrix_punkt(3, 5, farbe);
    led_matrix_punkt(4, 6, farbe);
    led_matrix_punkt(5, 3, farbe);
    led_matrix_punkt(5, 4, farbe);
    led_matrix_punkt(5, 5, farbe);
    led_matrix_punkt(6, 3, farbe);
    led_matrix_punkt(7, 3, farbe); 
    led_matrix_punkt(7, 4, farbe); 
    led_matrix_punkt(7, 5, farbe); 
    led_matrix_punkt(7, 6, farbe); 
  }
  SONST WENN (zahl IST 6) {
    led_matrix_punkt(3, 4, farbe);
    led_matrix_punkt(3, 5, farbe);
    led_matrix_punkt(4, 3, farbe);
    led_matrix_punkt(4, 6, farbe);
    led_matrix_punkt(5, 3, farbe);
    led_matrix_punkt(5, 4, farbe);
    led_matrix_punkt(5, 5, farbe);
    led_matrix_punkt(6, 3, farbe);
    led_matrix_punkt(7, 4, farbe); 
    led_matrix_punkt(7, 5, farbe); 
    led_matrix_punkt(7, 6, farbe); 
  }
  SONST WENN (zahl IST 7) {
    led_matrix_punkt(3, 3, farbe);
    led_matrix_punkt(4, 4, farbe);
    led_matrix_punkt(5, 5, farbe);
    led_matrix_punkt(6, 6, farbe);
    led_matrix_punkt(7, 3, farbe);
    led_matrix_punkt(7, 4, farbe);
    led_matrix_punkt(7, 5, farbe);
    led_matrix_punkt(7, 6, farbe);    
  }
  SONST WENN (zahl IST 8) {
    led_matrix_punkt(3, 4, farbe);
    led_matrix_punkt(3, 5, farbe);
    led_matrix_punkt(4, 3, farbe);
    led_matrix_punkt(4, 6, farbe);
    led_matrix_punkt(5, 4, farbe);
    led_matrix_punkt(5, 5, farbe);
    led_matrix_punkt(6, 3, farbe);
    led_matrix_punkt(6, 6, farbe); 
    led_matrix_punkt(7, 4, farbe);
    led_matrix_punkt(7, 5, farbe); 
  }
  SONST WENN (zahl IST 9) {
    led_matrix_punkt(3, 3, farbe);
    led_matrix_punkt(3, 4, farbe);
    led_matrix_punkt(3, 5, farbe);
    led_matrix_punkt(4, 6, farbe);
    led_matrix_punkt(5, 4, farbe);
    led_matrix_punkt(5, 5, farbe);
    led_matrix_punkt(5, 6, farbe);
    led_matrix_punkt(6, 3, farbe); 
    led_matrix_punkt(6, 6, farbe);
    led_matrix_punkt(7, 4, farbe); 
    led_matrix_punkt(7, 5, farbe); 
  }
  SONST WENN (zahl IST 10) {
    led_matrix_punkt(3, 3, farbe);
    led_matrix_punkt(4, 3, farbe);
    led_matrix_punkt(5, 3, farbe);
    led_matrix_punkt(6, 2, farbe);
    led_matrix_punkt(6, 3, farbe);
    led_matrix_punkt(7, 3, farbe);
    
    led_matrix_punkt(3, 6, farbe);
    led_matrix_punkt(4, 5, farbe);
    led_matrix_punkt(4, 7, farbe); 
    led_matrix_punkt(5, 5, farbe);
    led_matrix_punkt(5, 7, farbe); 
    led_matrix_punkt(6, 5, farbe);
    led_matrix_punkt(6, 7, farbe);
    led_matrix_punkt(7, 6, farbe);   
  }
  SONST WENN (zahl IST 11) {
    led_matrix_punkt(3, 3, farbe);
    led_matrix_punkt(4, 3, farbe);
    led_matrix_punkt(5, 3, farbe);
    led_matrix_punkt(6, 2, farbe);
    led_matrix_punkt(6, 3, farbe);
    led_matrix_punkt(7, 3, farbe);
    
    led_matrix_punkt(3, 6, farbe);
    led_matrix_punkt(4, 6, farbe);
    led_matrix_punkt(5, 6, farbe);
    led_matrix_punkt(6, 5, farbe);
    led_matrix_punkt(6, 6, farbe);
    led_matrix_punkt(7, 6, farbe); 
    
  }
  SONST WENN (zahl IST 12) {
    led_matrix_punkt(3, 3, farbe);
    led_matrix_punkt(4, 3, farbe);
    led_matrix_punkt(5, 3, farbe);
    led_matrix_punkt(6, 2, farbe);
    led_matrix_punkt(6, 3, farbe);
    led_matrix_punkt(7, 3, farbe);
    
    led_matrix_punkt(3, 5, farbe);
    led_matrix_punkt(3, 6, farbe);
    led_matrix_punkt(3, 7, farbe);
    led_matrix_punkt(4, 6, farbe);
    led_matrix_punkt(5, 7, farbe);
    led_matrix_punkt(6, 5, farbe); 
    led_matrix_punkt(6, 7, farbe); 
    led_matrix_punkt(7, 6, farbe);
  }
  SONST WENN (zahl IST 13) {
    led_matrix_punkt(3, 3, farbe);
    led_matrix_punkt(4, 3, farbe);
    led_matrix_punkt(5, 3, farbe);
    led_matrix_punkt(6, 2, farbe);
    led_matrix_punkt(6, 3, farbe);
    led_matrix_punkt(7, 3, farbe);
    
    led_matrix_punkt(3, 5, farbe);
    led_matrix_punkt(3, 6, farbe);
    led_matrix_punkt(4, 7, farbe);
    led_matrix_punkt(5, 5, farbe);
    led_matrix_punkt(5, 6, farbe);
    led_matrix_punkt(6, 7, farbe); 
    led_matrix_punkt(7, 5, farbe); 
    led_matrix_punkt(7, 6, farbe);   
  }
  SONST WENN (zahl IST 14) {
    led_matrix_punkt(3, 3, farbe);
    led_matrix_punkt(4, 3, farbe);
    led_matrix_punkt(5, 3, farbe);
    led_matrix_punkt(6, 2, farbe);
    led_matrix_punkt(6, 3, farbe);
    led_matrix_punkt(7, 3, farbe);
    
    led_matrix_punkt(3, 6, farbe);
    led_matrix_punkt(4, 6, farbe);
    led_matrix_punkt(5, 5, farbe);
    led_matrix_punkt(5, 6, farbe);
    led_matrix_punkt(5, 7, farbe); 
    led_matrix_punkt(6, 5, farbe); 
    led_matrix_punkt(7, 5, farbe); 
  }
  SONST WENN (zahl IST 15) {
    led_matrix_punkt(3, 3, farbe);
    led_matrix_punkt(4, 3, farbe);
    led_matrix_punkt(5, 3, farbe);
    led_matrix_punkt(6, 2, farbe);
    led_matrix_punkt(6, 3, farbe);
    led_matrix_punkt(7, 3, farbe);
    
    led_matrix_punkt(3, 5, farbe);
    led_matrix_punkt(3, 6, farbe);
    led_matrix_punkt(4, 7, farbe);
    led_matrix_punkt(5, 5, farbe);
    led_matrix_punkt(5, 6, farbe); 
    led_matrix_punkt(6, 5, farbe); 
    led_matrix_punkt(7, 5, farbe); 
    led_matrix_punkt(7, 6, farbe); 
    led_matrix_punkt(7, 7, farbe);    
  }
  SONST WENN (zahl IST 16) {
    led_matrix_punkt(3, 3, farbe);
    led_matrix_punkt(4, 3, farbe);
    led_matrix_punkt(5, 3, farbe);
    led_matrix_punkt(6, 2, farbe);
    led_matrix_punkt(6, 3, farbe);
    led_matrix_punkt(7, 3, farbe);
    
    led_matrix_punkt(3, 5, farbe);
    led_matrix_punkt(3, 6, farbe);
    led_matrix_punkt(3, 7, farbe);
    led_matrix_punkt(4, 5, farbe);
    led_matrix_punkt(4, 7, farbe); 
    led_matrix_punkt(5, 5, farbe); 
    led_matrix_punkt(5, 6, farbe); 
    led_matrix_punkt(5, 7, farbe); 
    led_matrix_punkt(6, 5, farbe);  
    led_matrix_punkt(7, 6, farbe);  
    led_matrix_punkt(7, 7, farbe);    
  }
}
