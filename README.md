# Reaction-Captcha-Game

## Grundlegende Funktionsweise
Reaction-Captcha-Game ist ein Reaktionsspiel.
Zuerst erscheint ein Bild des KITTI-Datensatzes. Der KITTI-Datensatz ist ein Datensatz an dem autonomes Fahren von
neuronalen Netzen gelernt wird. Deshalb enthält er verschiedene Bilder von Verkehrssituationen.
Im Spielmodus 1 erscheint nach 1 - 2 Sekunden eine rote Box um ein Verkehrsteilnehmer.
Diese muss so schnell wie möglich angeklickt werden.
Im Spielmodus 2 erscheint um alle Verkehrsteilnehmer eine blaue Box.
Nach 1 - 2 Sekunden wird eine Box rot, welche ebenfalls so schnell wie möglich angeklickt werden muss. Danach muss
der Klick noch mit der Leertaste bestätigt werden.

Falls die Box nicht getroffen wurde oder 3 Sekunden vergangen sind, erhält man für das jeweilige Bild 5 Sekunden Strafzeit.

Im Menü kann vor Spielbeginn der Name, die Anzahl der Bilder und die Sequenz des KITTI-Datensatzes festgelegt werden.
Nach Durchspielen aller Bilder erscheint ein Feedback mit den besten Reaktionszeiten und der Durchschnittszeit.

## Setup
Um das Programm zu starten, stellen Sie sicher, dass Sie die erforderliche Umgebung und Abhängigkeiten eingerichtet haben. Das Spiel ist in C++ geschrieben und verwendet die OpenCV-Bibliothek für die Bildverarbeitung. Führen Sie die folgenden Schritte aus:

1. Stellen Sie sicher, dass OpenCV korrekt in Ihrer Entwicklungsumgebung installiert ist.
2. Platzieren Sie den Datenordner im Wurzelverzeichnis des Projekts oder konfigurieren Sie den Pfad in der [Config](src/Config.cpp) Datei.
3. Kompilieren Sie das Programm mit einem C++-Compiler, der C++17 oder höher unterstützt.
4. Starten Sie das kompilierte Programm. Sie werden aufgefordert, ihre Eingaben im Menü vorzunehmen.
5. Folgen Sie den Anweisungen auf dem Bildschirm, um das Spiel zu spielen.


## Implementierung
Das Spiel besteht aus verschiedenen Komponenten, die zusammenarbeiten, um das Gameplay zu ermöglichen. Hier ist eine Übersicht über die wichtigsten Bestandteile:

- **Menu**: Das Menü ist die erste Schnittstelle mit dem Benutzer, wo der Spieler seinen Namen eingeben kann und die Anzahl der Bilder, die Sequenz und den Spielmodus wählt. Dabei wird zuerst mithilfe einer Template-Funktion der InputChecker-Klasse überprüft, ob der richtige Datentyp eingegeben wurde. Falls dies der Fall ist, wird außerdem noch überprüft ob der Datentyp sinnvoll ist.
Bei falschen Eingaben werden die Funktionen erneut aufgerufen.

- **InputChecker**: Der Inputchecker checkt den Datentyp und gibt mit seinen Funktionen 1 oder 0 zurück, wenn der Datentyp passt.

- **GameHandler**: Diese Klasse handhabt den Spielablauf. D.h. sie erstellt einen smarten Pointer der auf den jeweiligen
Spielmodus verweist. Anschließend geht es in eine for-Schleife für alle Bilder hinein. In dieser wird zuerst der Klickstatus
auf NO_CLICK gesetzt und für Spielmodus 2 die Variable spaceBarPress auf 0. Anschließend wird das Bild geladen, welches in
der for-Schleife definiert wurde. Danach werden die Boxen geladen, wobei immer nur die Boxen für das jeweilige Bild geladen
werden, was perfomancetechnisch Vorteile bietet. Danach wird das Bild angezeigt und ggf. für Spielmodus 2 die Box aktualisiert.
Danach wird die Callback Maus-Funktion gestartet. Anschließend kommt die Logik für die Zeit, welche eigentlich in den TimeHandler
sollte. Am Ende werden die Zeiten und das zugehörige Bild jeweils in Arrays gepusht und die jeweilige Klickzeit auf die Standardausgabe angezeigt.
Nachdem die for-Schleife beendet ist, werden die Fenster geschlossen und innerhalb der Funktion giveFeedback(),
welche auch in eine andere Klasse gehört, die besten 3 Zeiten und die Durschnittszeit ausgegeben.

- **GameMode1 und GameMode2**: Diese Klassen definieren die Funktionen die der GameHandler aufruft. Die formatSequence() und formatImage()-Funktionen
formatieren einen Integer als String, während die Funktionen setBoxFolderPath() und setImagePath() die Pfade bzw. die Dateien für die Sequenz setzen.
Die loadBoundingBox()-Funktion war größenteils schon vorgegeben. Nur hinzufügt wurde der Check ob der Frame-Index gleich dem Bild ist.
Die Funktion loadImage() und chooseRandomBox() bzw. chooseRandomDelay() sind selbsterklärend. Die Funktion display() zeigt das Bild,
wartet 1 - 2 Sekunden und zeigt dann eine targetBox an. Die setupCallback()-Funktion nutzt eine Lambda-Funktion um das Event des Mausklicks
zu überprüfen.

- **Config**: In der Config-Datei werden die Pfade zu dem Bilderordner und dem Ordner für die Labels mithilfe eines CMake-Makros festgelegt.

- **BoundingBox**: Diese Klasse gibt eine Box zurück, die für das Spiel benötigt wird.

- **Meinung**: Aufgrund zeittechnischer Probleme habe ich es nur geschafft den Code bis zu diesem Stand zu optimieren.
 Die einzelnen Funktionen in einzelne Klassen zu tun, war zeitlich nicht möglich. Desweiteren gibt es noch viel Auslagerungspotenzial
hinsichtlich SRP (z.B. targetBox für beide Spielmodi, Zeit innerhalb TimeHandler, mouseHandler, ImageHandler etc.).



