# Buildsystem

Dieses Dokument erklärt den Umgang mit dem Buildsystem CMake innerhalb dieses Projekts.

## Struktur

Das Projekt ist so aufgebaut, dass sich alle Source-Dateien im Verzeichnis ```src``` befinden.
Jedes Unterverzeichnis in ```src``` repräsentiert eine eigenständige Komponente.
Diese können entweder als eine Bibliothek oder eine Executeable realisiert werden.

In der Datei ```CMakeLists.txt``` werden die zwei Variable ```PROJ_LIBRARIES``` und ```PROJ_EXEC``` gesetzt.

```PROJ_LIBRARIES``` beinhaltet alle Unterverzeichnisse aus ```src```, die als Bibliothek gebaut werden sollen.

```PROJ_EXEC``` beinhaltet alle Unterverzeichnisse aus ```src```, die als Executeable gebaut werden sollen.

### Executeable hinzufügen

Um eine neue Executeable zum Projekt hinzuzufügen, muss ein neues Verzeichnis unter ```src``` angelegt werden.
Das Verzeichnis muss mindestens eine Source-Datei mit einer ```main()``` und eine ```CMakeLists.txt``` beinhalten.
Als Beispiel hierfür kann das Verzeichnis ```src/generator``` und deren ```CMakeLists.txt``` als
Template herangezogen werden.
Die ```CMakeLists.txt``` spezifiziert hierbei lediglich den Name der zu bauenden Anwendung und mit welchen Bibliotheken
sie gelinkt werden soll.

Nun muss der Name des Verzeichnisses noch der Variablen ```PROJ_EXEC``` hinzugefügt werden.
Danach sollte ein sauberer **Rebuild** durchgeführt werden.
Die neue ausführbare Datei sollte nun unter ```build/src/<Verzeichnis-Name>``` zu finden sein.

### Bibliothek hinzufügen

Um eine neue Bibliothek zum Projekt hinzuzufügen, muss ein neues Verzeichnis unter ```src``` angelegt werden.

**Anmerkung:** Umfasst die Bibliothek **nur** Header-Dateien, brauchen keine weiteren Schritte durchgeführt zu werden.

Das Verzeichnis muss mindestens eine Source-Datei beinhalten, um erfolgreich gebaut werden zu können. 
Nun muss der Name des Verzeichnisses noch der Variablen ```PROJ_LIBRARIES``` hinzugefügt werden.
Danach sollte ein sauberer **Rebuild** durchgeführt werden.
Die neue Bibliothek sollte nun unter ```build/src/``` zu finden sein. Ihr Name lautet gleich wie ihr Verzeichnis.

Projekteigene Bibliotheken können zu Executeables gelinkt werden, indem einfach der Verzeichnisname der Bibliotheken
im ```target_link_libraries()``` Schritt des Executeable Builds angegeben werden. Siehe auch Abschnitt **Executeable hinzufügen**.

## Build starten

Um einen Build zu starten müssen die Abhängigkeiten für das Projekt installiert sein.
Dafür unter Ubuntu/Debian einfach das Skript ```script/get-linux-deps.sh``` ausführen.

Um nun das Projekt zu bauen müssen die folgenden Befehle ausgeführt werden:

```shell
cd <path-to-repo>
mkdir build
cd build
cmake ..
make
```

## Rebuild

Um einen sauberen Rebuild durchzuführen muss einfach das Verzeichnis ```build``` gelöscht und dann die Schritte
aus dem Kapitel **Build Starten** wiederholt werden.

```shell
cd <path-to-repo>
rm -rf build
mkdir build
cd build
cmake ..
make
```
