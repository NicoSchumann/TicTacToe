# TicTacToe
A simple TicTacToe game with A.I. player by using the SFML-framework.

At this game I want test two manners of A.I.
At the one hand I implement the Minimax algorithm,
and on the other hand I implement an A.I. by evaluating
a bunch of randomly played games.

At a first step I coded the GUI.

And now the randomly playing A.I. works.
Here the pseudo code for the random A.I.:

For each empty field of the board:
    Play the empty field.
    Do several times:
        Play the game randomly till end.
        Evaluate the board's field.
        Sum the evaluation to the fields score.
Return the highest valuated field number.

How to compile:
run 'make' at the base directory.


deutsch:
==

Ein einfaches TicTacToe-Spiel mit KI-Spieler mit Hilfe des SFML-Frameworks.

Bei diesem Spiel will ich zwe verschiedene KI-implementierungen testen.
Zum einen eine Implementierung des Minimax-Algorithmus, und
zum Anderen durch Auswertung von Zufällig zu Ende gespielten Runden.

Als erstes habe ich die grafische Benutzerschnittstelle programmiert.

Und jetzt funktioniert auch die KI auf Zufallsbasis.
Hier der Pseudo-Code der Zufalls-KI:

Für jedes freie Feld auf dem Bord:
    Spiele dieses Feld.
    Tu einige Male:
        Spiele das Bord bis zum Ende.
        Werte den Bordzustand aus und bewerte das ursprüngliche Feld.
        Summiere den Wert zu den Bewertungspunkten des Feldes.
Gib das am höchsten bewertete Feld zurück.

Kompilieren:
Einfach 'make' im obersten Verzeichnis des Repositorys aufrufen.
(dort, wo die 'Makefile'-Datei liegt).
