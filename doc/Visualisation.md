## Visualisierung TSP

* reicht eine 2D Darstellung?
* bei allen Techniken stellt sich die Frage wie performant sie bei sehr vielen Knoten sind

### 1. Vektorgrafik
* [SVG-Datei](https://de.wikipedia.org/wiki/Scalable_Vector_Graphics#Beispiel) erstellen
* lässt sich mit Browsern und Bildbearbeitungsprogrammen betrachten

Für Video:
* in PNG-Datei konvertieren
* von PNG in MKV/MP4/... konvertieren

Quelle: [imonad.com](http://imonad.com/tsp/traveling-salesman-problem-visualization/)

### 2. openGL
* kleine openGL Anwendung schreiben, die eine Knoten- und Kantenliste zeichnet
* auch nicht sehr aufwändig (hatte ich im Bachelor)
* wir haben alle Gestaltungsmöglichkeiten
* können Leistung der Grafikkarte nutzen
* hilfreiche Frameworks/Libraries:
  * [FreeGLUT](http://freeglut.sourceforge.net)

### 3. Gnuplot
* Kommandozeilentool zum visualisieren von 2D- und 3D-Daten: [Gnuplot](http://www.gnuplot.info)
* wurde [hier](http://www9.in.tum.de/praktika/awbs_info_general/gnuplot.html) schon mal für das TSP umgesetzt
* eine Datei, die GNUPLOT verarbeiten kann lässt sich recht einfach erstellen
* kann anschließend auch als *.png oder *.svg gespeichert werden
* müsste getestet werden, wie performant das Programm bei einer sehr hohen Anzahl von Knoten ist
* sieht nicht so hübsch aus

### 4. Python Matplotlib
* sehr mächtig (da Python)
* ähnliche Ausgaben wie Gnuplot und Matlab
* stark konfigurierbar
