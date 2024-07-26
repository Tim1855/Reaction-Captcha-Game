# Reaction-Captcha-Game
Reaction-Captcha-Game ist ein Reaktionsspiel, bei dem rote Kästchen so schnell wie möglich angeklickt werden müssen.

## Setup
Der Datenordner sollte sich im Wurzelverzeichnis des Projekts befinden. Alternativ kann der Pfad manuell in der [Config](src/Config.cpp) Datei geändert werden.

## Implementierung
Das Spiel besteht aus verschiedenen Komponenten, die zusammenarbeiten, um das Gameplay zu ermöglichen. Hier ist eine Übersicht über die wichtigsten Bestandteile:

- **Menu**: Das Menü ist die erste Schnittstelle mit dem Benutzer, wo der Spieler seinen Namen eingeben kann und die Anzahl der Bilder, die Sequenz und den Spielmodus wählt. Nach diesen Einstellungen wird das Spiel gestartet.

- **GameHandler**: Diese Klasse handhabt den Spielablauf. Sie initialisiert das Spiel basierend auf den Eingaben des Benutzers im Menü und steuert den Spielprozess, einschließlich des Ladens der Bilder und der Bounding Boxes.

- **GameMode1 und GameMode2**: Diese Klassen definieren spezifische Spielmodi. In GameMode1 muss der Spieler eine einzige, zufällig hervorgehobene rote Box so schnell wie möglich anklicken. GameMode2 erfordert, dass der Spieler auf eine rote Box klickt, die nach einer zufälligen Verzögerung farblich verändert wird.

- **Config**: In der Config-Datei werden Pfade zu wichtigen Ressourcen wie dem Bilderordner und dem Ordner für Bounding Boxes festgelegt.

- **BoundingBox und Image**: Diese Klassen helfen beim Laden und Verarbeiten der Bild- und Box-Daten, die für das Spiel benötigt werden.

## Anleitung zum Starten des Programms
Um das Programm zu starten, stellen Sie sicher, dass Sie die erforderliche Umgebung und Abhängigkeiten eingerichtet haben. Das Spiel ist in C++ geschrieben und verwendet die OpenCV-Bibliothek für die Bildverarbeitung. Führen Sie die folgenden Schritte aus:

1. Stellen Sie sicher, dass OpenCV korrekt in Ihrer Entwicklungsumgebung installiert ist.
2. Platzieren Sie den Datenordner im Wurzelverzeichnis des Projekts oder konfigurieren Sie den Pfad in der [Config](src/Config.cpp) Datei.
3. Kompilieren Sie das Programm mit einem C++-Compiler, der C++11 oder höher unterstützt.
4. Starten Sie das kompilierte Programm. Sie werden aufgefordert, Ihre Eingaben im Menü vorzunehmen.
5. Folgen Sie den Anweisungen auf dem Bildschirm, um das Spiel zu spielen.

