# Genetic Algorithm

Beispiel für eine Implementierung eines genetischen Algorithmus für das TSP mit Erklärngen:
* http://www.theprojectspot.com/tutorial-post/applying-a-genetic-algorithm-to-the-travelling-salesman-problem/5

## Zusammenfassung

Lösungsansatz Genetische Algorithmen am Beispiel TSP

Pseudocode:

```
Generiere zufällige Startpopulation
Solange (Abbruchbedingung nicht erfüllt){
	Berechne die Fitness der einzelnen Individuen
	Nach Fitness Selektieren und Nachkommen berechnen
	Wende genetische Operatoren an
}
Ergebnis: bestes Individuen aus der Population
```

**Startpopulation:**

Eine Population stellt mehrere Individuen dar (ein Individuum ist eine Tour)
In einer Population sind immer gleichviele Individuen vorhanden z.B. 10 da 10 Rechner vorhanden sind
Der Startpunkt der Tour sollte immer der gleiche sein.
Frage: wie erhalten wir die erste Population um damit weiter arbeiten zu können? Nach welchem Such/Selektions Algorithmus arbeiten wir? Es muss auf jeden Fall zufällig sein.

**Die Abbruchbedingung kann sein:**

1. Ein Wert (Weglänge) welches akzeptabel ist
1. Eine feste Anzahl von generierten Populationen
1. Es ist keine Verbesserung mehr vorhanden

**Fitness berechnen:**

Könnte die Länge des gesamten Weges sein

**Nachkommen berechnen Anhand der Fitness:**

* Crossover Verfahren
* Die Tour in mehrere Bereiche aufteilen und über Kreuz vertauschen
* UniformCross
* Beim tauschen die gleichen Streckenteile beibehalten und den Rest über Kreuz vertauschen oder zufällig vertauschen (vorsicht... Es muss eine Tour am Ende entstehen)

* Schlechte Lösungsansàtze mit schlechter Fitnesswertung bestrafen um bei der Mutation effektiver berechnen zu können

* Genetische Operatoren anwenden(Mutation)
* Nicht zwingend notwendig.... Denke ich
* Zufälliger Tausch von Streckenabschnitten um ganz andere Lösungsansätze zu erhalten.

Insgesamt denke ich das alle Individuen innerhalb einer Population sich vereinen sollen. Da die Hälfte für die neue Population weg fällt können wir die 5 Besten Individuen aus der letzten Population weiter mitnehmen.
