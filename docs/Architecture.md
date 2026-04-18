# NGEngineGames — Architecture

**Version:** 0.1  
**Author:** Bart4223 (Nils Grimmer)  
**Stand:** 2026-04-13

---

## 1. Projekttyp

NGEngineGames ist eine **Arduino C++ Library** für retro-artige Spiele auf Arduino-Mikrocontrollern mit RGB-LED-Matrix oder OLED-Display. Die Library ist nach dem Standard-Arduino-Library-Format aufgebaut (`library.properties`, `src/`, `examples/`).

| Eigenschaft | Wert |
| --- | --- |
| Name | NGEngineGames |
| Version | 0.1 |
| Kategorie | Display |
| Architekturen | `*` (alle Arduino-Plattformen) |
| GitHub | <https://github.com/bart4223/NGEngineGames.git> |

---

## 2. Einbettung in das NGEngine-Ökosystem

NGEngineGames ist die oberste Schicht des NGEngine-Stacks und baut vollständig auf den beiden Basis-Libraries auf:

```text
[NGEngineGames]        — Spiele, Sprites, visuelle Effekte, Hardware-Projekte
        │
        ▼
[NGEngineControl]      — Konkrete Treiber, Unit-Controller, Hardware-Abstraktion
        │
        ▼
[NGEngineCore]         — Interfaces, Datentypen, Fonts, Utilities
        │
        ▼
[Arduino SDK / Drittanbieter-Libraries]
```

### Abhängigkeiten zu den Bezugs-Repos

**NGEngineCore** (`C:\LW_Q\git\SQL_NGRIMMER\NGEngineCore`)  
Stellt alle Interfaces bereit, auf denen NGEngineGames aufbaut:

- `NGIPaintableComponent` — Display-Abstraktion für alle Spiele und Effekte
- `NGIPaintableObject` — Basis-Interface für alle Sprites
- `NGIEffect` — Basis-Interface für alle visuellen Effekte
- `NGINotification` — Text-Output-Abstraktion
- `NGITestableComponent` — Test-Sequenz-Interface
- `NGCommonGraphics` — `colorRGB`, `coord2D`, Farbkonstanten
- `NGCustomFont` + konkrete Font-Klassen — Bitmap-Fonts für Score-Anzeigen

**NGEngineControl** (`C:\LW_Q\git\SQL_NGRIMMER\NGEngineControl`)  
Stellt Hardware-Treiber und Unit-Controller bereit:

- `NGCustomUnitControl` — Basis für `NGGameMachineUnitControl`
- `NGColorDotMatrix` — LED-Matrix-Treiber (primäres Display-Backend)
- `NGColorLEDStrip` — Adressierbare LED-Strips
- `NGColorDotMatrixBinaryDigit`, `NGColorDotMatrixDecimalDigit`, `NGColorDotMatrixFuse` — Rendering-Helfer für Score- und Statusanzeigen
- `NGColorDotMatrixGradientPoint` — Farbverlauf-Interpolation für Effekte
- `NGSoundMachine` + Jingles — Sound-Wiedergabe
- `NGJoystickControl`, `NGSimpleKeypad` — Eingabe-Abstraktion
- `NGSerialNotification`, `NGLCDNotification` — Notification-Implementierungen

---

## 3. Verzeichnisstruktur

```text
NGEngineGames/
├── src/               Library-Quellcode (alle .h/.cpp)
├── games/             Standalone Arduino-Sketches (.ino) pro Spiel
│   ├── ardcade/       Ardcade-spezifische Game-Sketches
│   └── gamepad/       Gamepad-spezifische Game-Sketches
├── examples/          Minimalbeispiele für einzelne Komponenten
├── projects/          Vollständige Hardware-Projekt-Sketches
│   ├── ardcade/       Ardcade-Gerät (All-in-One-Arcade-Maschine)
│   └── gamepad/       Gamepad-Gerät (Handheld Multi-Game-Controller)
├── docs/              Dokumentation (diese Datei, HighScores.md, ToDo.md)
├── library.properties Arduino Library-Metadaten
├── keywords.txt       Arduino-IDE Syntax-Highlighting
└── README.md          Kurzbeschreibung
```

---

## 4. Klassen-Hierarchie und Architektur

### 4.1 Spiel-Vererbungshierarchie

```text
NGCustomGame                            (Basis-Game-Klasse, externe Library)
  └── NGCustomColorDotMatrixGame        (fügt Display, Sprites, Score-Rendering hinzu)
        ├── NGColorDotMatrixGameDot
        ├── NGColorDotMatrixGameSnake
        ├── NGColorDotMatrixGameAsteroids
        ├── NGColorDotMatrixGameTetris
        └── NGColorDotMatrixGameBoulderdash
```

### 4.2 Sprite-Hierarchie

```text
NGCustomSprite  (implementiert NGIPaintableObject)
  ├── NGSpriteSpaceship       (Asteroids — Raumschiff)
  ├── NGSpriteLaserbeam       (Asteroids — Laserstrahl)
  ├── NGSpriteBomb            (Asteroids/Boulderdash — Bombe)
  ├── NGSpriteDiamond         (Boulderdash — Diamant)
  ├── NGSpriteBoulder         (Boulderdash — Felsbrocken)
  ├── NGSpriteDirt            (Boulderdash — Erde)
  ├── NGSpriteRocky           (Boulderdash — Rocky-Figur)
  ├── NGSpriteDot             (Dot-Spiel — Punkt)
  ├── NGSpriteHeart           (Boulderdash — Leben-Anzeige)
  └── NGSpriteNone            (transparenter Platzhalter, Null-Object)
```

### 4.3 Visuelle Effekte (implementieren NGIEffect)

```text
NGIEffect  (Interface aus NGEngineCore)
  ├── NGColorDotMatrixEffectRetroRibbons   (Farbband-Animation, 100ms)
  ├── NGColorDotMatrixEffectSnowfall       (Schneefallsimulation, 250ms)
  ├── NGColorDotMatrixEffectStarLights     (Sternflackern, 100ms)
  └── NGColorDotMatrixEffectZini           (Richtungs-Gradient-Welle, 10ms)
```

### 4.4 Hardware-Controller

| Klasse | Gerät | Beschreibung |
| --- | --- | --- |
| `NGGameMachineUnitControl` | Ardcade | Hauptcontroller für die Ardcade-Maschine. Erbt von `NGCustomUnitControl`. Verwaltet ein aktives Spiel, IR-Remote-Eingabe, Idle-Effekte, Sound-Toggle. Version: `3.1`. |
| `NGGamePad` | Gamepad | Multi-Game-Container für das Gamepad. Hält bis zu 5 `NGCustomGame`-Instanzen, routet Eingaben an das aktive Spiel. |
| `NGColorOLED` | beide | Hardware-Treiber für Adafruit SSD1331 Color-OLED. Implementiert `NGIPaintableComponent`. Alternatives Display-Backend zur LED-Matrix. |

---

## 5. Konkrete Spiele

| Klasse | Spiel | Beschreibung |
| --- | --- | --- |
| `NGColorDotMatrixGameDot` | Dot | Einfaches Fang-den-Punkt-Spiel. Ein Punkt erscheint auf der Matrix; Spieler muss ihn innerhalb eines Zeitlimits erreichen. |
| `NGColorDotMatrixGameSnake` | Snake | Klassisches Snake auf einem Grid bis 16×16. Spieler steuert eine wachsende Schlange zum Fressen von Futter. |
| `NGColorDotMatrixGameAsteroids` | Asteroids | Asteroids-Shooter mit Sprites: Raumschiff, Laserstrahl, Bombe, Diamant, Felsbrocken. Unterstützt LED-Matrix und OLED via `#define`. |
| `NGColorDotMatrixGameTetris` | Tetris | Tetris auf einem Grid bis 16×16. (ToDo: neue Tetrominos urgent) |
| `NGColorDotMatrixGameBoulderdash` | Boulderdash | Boulder-Dash-Klon mit `NGColorDotMatrixFuse` für Fuse/Timer-Mechanik. Farbkonfigurationen für Score, Leben und Fuse-Anzeigen. (ToDo: Levels urgent) |

---

## 6. NGCustomGame — Basis-Game-Klasse (extern)

Die gemeinsame Basis für alle Spiele stellt folgende Kernfunktionalität bereit:

- **State Machine:** not started → started → paused → finished
- **Eingabe-Routing:** bis zu 5 Key-Bindings, bis zu 3 Joysticks
- **Sound-Integration:** `NGSoundMachine`
- **Benachrichtigungen:** `NGINotification`
- **Timing:** konfigurierbares Step-Delay und Step-Size für Spielgeschwindigkeit
- **Spielmodi:** minimal / normal / big
- **Virtuelle Hooks:** `_doStartGame`, `_doFinishGame`, `_doProcessingLoop` (für Subklassen)

### NGCustomColorDotMatrixGame — Display-Layer

Erweitert `NGCustomGame` um display-spezifisches Rendering:

- Referenz auf `NGIPaintableComponent` (Display-Abstraktion)
- Sprite-Registry (bis zu 10 Sprites)
- `NGColorDotMatrixBinaryDigit` — binäre Score-Anzeige
- `NGDecimalPointCounter` — animierter Dezimal-Score-Counter

---

## 7. Hardware-Projekte

### Ardcade (`projects/ardcade/`)

Eine eigenständige Arcade-Maschine auf Arduino-Basis.

- **Controller:** `NGGameMachineUnitControl`
- **Spielauswahl:** compile-time `#define GAME1..5`
- **Display-Erkennung:** automatische Erkennung 10×10 (100 Pixel) vs. 16×16 (256 Pixel) LED-Strip via Analog-Pin
- **Idle-Effekte:** RetroRibbons, StarLights, Zini, Snowfall (aktiv wenn kein Spiel läuft)
- **Zusatz-Hardware:** LCD-Notification, Sound-Machine mit Digital-Potentiometer für Lautstärke

### Gamepad (`projects/gamepad/`)

Handheld Multi-Game-Controller.

- **Controller:** `NGGamePad` (mehrere Spiele zur Laufzeit wählbar)
- **Zusatz:** `NGBinaryClockUnitControl` — Binary-Clock läuft parallel zu den Spielen
- **Eingabe:** Joystick auf A8/A9, Fire-Button auf Pin 14
- **Buttons:** Spielauswahl, Clock-Farb-Toggle, Sound-Toggle

---

## 8. Externe Abhängigkeiten

### Aus dem NGEngine-Ökosystem

| Library | Bereitgestellt durch | Verwendung |
| --- | --- | --- |
| `NGIPaintableComponent` | NGEngineCore | Display-Abstraktion für alle Spiele/Effekte |
| `NGIPaintableObject` | NGEngineCore | Basis für alle Sprites |
| `NGIEffect` | NGEngineCore | Basis für alle Effekte |
| `NGINotification` | NGEngineCore | Text-Ausgabe |
| `NGCommonGraphics` | NGEngineCore | Farbtypen, Koordinaten |
| `NGCustomFont` | NGEngineCore | Bitmap-Fonts |
| `NGCustomUnitControl` | NGEngineControl | Basis für `NGGameMachineUnitControl` |
| `NGColorDotMatrix` | NGEngineControl | LED-Matrix-Treiber |
| `NGColorDotMatrixBinaryDigit` | NGEngineControl | Binäre Score-Anzeige |
| `NGColorDotMatrixDecimalDigit` | NGEngineControl | Dezimale Score-Anzeige |
| `NGColorDotMatrixFuse` | NGEngineControl | Fuse/Timer-Anzeige (Boulderdash) |
| `NGColorDotMatrixGradientPoint` | NGEngineControl | Farbverlauf (Zini-Effekt) |
| `NGSoundMachine` | NGEngineControl | Sound-Wiedergabe |
| `NGJoystickControl` | NGEngineControl | Joystick-Eingabe |
| `NGSimpleKeypad` | NGEngineControl | Tastatur-Eingabe |
| `NGMemoryObserver` | NGEngineControl | Heap-Monitoring |
| `NGSerialNotification` | NGEngineControl | Serial-Ausgabe |
| `NGLCDNotification` | NGEngineControl | LCD-Ausgabe |
| `NGColorLEDStrip` | NGEngineControl | LED-Strip-Treiber (Ardcade) |
| `NGDigitalPotentiometer` | NGEngineControl | Lautstärke-Regelung (Ardcade) |
| `NGBinaryClockUnitControl` | NGEngineControl | Binary-Clock-Integration (Gamepad) |

### Drittanbieter

| Library | Verwendet von | Zweck |
| --- | --- | --- |
| `Adafruit_SSD1331` | `NGColorOLED` | OLED-Hardware-Treiber |
| `Adafruit_GFX` | `NGColorOLED` | GFX-Basisklasse |
| `SPI` | `NGColorOLED` | SPI-Kommunikation |

---

## 9. Architektonische Schichten

```text
┌─────────────────────────────────────────────────────────┐
│  Projekt-Sketches (.ino)                                │
│  Ardcade / Gamepad / einzelne Spiel-Sketches            │
├─────────────────────────────────────────────────────────┤
│  Device-Integration-Layer                               │
│  NGGameMachineUnitControl · NGGamePad                   │
├─────────────────────────────────────────────────────────┤
│  Game-Implementation-Layer                              │
│  Dot · Snake · Asteroids · Tetris · Boulderdash         │
├─────────────────────────────────────────────────────────┤
│  Game-Engine-Layer                                      │
│  NGCustomColorDotMatrixGame · NGCustomGame              │
├─────────────────────────────────────────────────────────┤
│  Sprite-Layer                                           │
│  NGCustomSprite + 10 konkrete Sprite-Klassen            │
├─────────────────────────────────────────────────────────┤
│  Effects-Layer                                          │
│  4 NGIEffect-Implementierungen (Idle-Animationen)       │
├─────────────────────────────────────────────────────────┤
│  NGEngineControl (Hardware-Treiber, Unit-Controller)    │
├─────────────────────────────────────────────────────────┤
│  NGEngineCore (Interfaces, Typen, Fonts, Utilities)     │
├─────────────────────────────────────────────────────────┤
│  Arduino SDK / Drittanbieter-Libraries                  │
└─────────────────────────────────────────────────────────┘
```

---

## 10. Offener Backlog (ToDo.md)

| Spiel | Offener Punkt | Priorität |
| --- | --- | --- |
| Asteroids | Kometen implementieren | URGENT |
| Boulderdash | Levels implementieren | URGENT |
| Tetris | Neue Tetrominos hinzufügen | URGENT |
| — | SuperMarioBros (geplant, nicht begonnen) | offen |
| — | PacMan (geplant, nicht begonnen) | offen |
