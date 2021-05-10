# C Programmieraufgabe SoSe 2021

Ziel dieser Aufgabe ist es, ein _Auto-Tuning Framework_ zu implementieren.

Auto-Tuning bezeichnet eine Technik zur Optimierung von Programmen. Die Benutzenden übergeben dem Framework:

- einen Algorithmus, der generisch in Performance-kritischen Parametern implementiert ist (z.B. Anzahl Threads, Tile Größen, etc.)
- eine Beschreibung der Performance-kritischen Parameter (a.k.a. _Tuningparameter_) bestehend aus Name, Wertebereich und ggf. Abhängigkeiten zu anderen Parametern (z.B. Anzahl Threads teilt Anzahl Tiles)

Der Tuner durchläuft anschließend die folgenden 3 Phasen:
1. **Generation**-Phase:  Der Tuner iteriert über alle möglichen Parameterbelegungen (a.k.a. _Konfigurationen_) und prüft, ob diese die vom Benutzer angegebenen Abhängigkeiten erfüllen.
2. **Storage**-Phase:     Während der Tuner über die Parameterbelegungen iteriert, werden alle _gültigen Konfigurationen_, also diejenigen die die Abhängigkeiten erfüllen, gespeichert.
3. **Exploration**-Phase: Der Tuner benutzt eine sog. _Suchtechnik_, um eine gültige Konfiguration auszuwählen. Die Laufzeit des Algorithmus unter Verwendung dieser Konfiguration wird gemessen und an die Suchtechnik zurückgegeben. Die Suchtechnik wählt dann eine neue gültige Konfiguration, deren Laufzeit gemessen wird. Dies wird solange wiederholt, bis eine vom Benutzer definierte _Abbruchbedingung_ eintritt (z.B. es wurden 500 Konfigurationen getestet).

In diesem Repository finden Sie die Datei `atf_hpcc.pdf`, in der Sie weitere Informationen zu einer Implementierung eines Auto-Tuning Frameworks finden. Wir empfehlen Ihnen sich das Paper vor Bearbeitung der Aufgabe durchzulesen.

**Aufgabenstellung**: Laden Sie sich das vorgefertigte C Projekt aus diesem Repository herunter (`git clone git@zivgitlab.uni-muenster.de:b_koep01/c-cpp-sose-2021.git`). Implementieren Sie ein Auto-Tuning Framework in den Dateien `atf.h` und `atf.c` (bitte ändern Sie nur diese beiden Dateien), indem Sie die Phasen Generation, Storage und Exploration in dieser Reihenfolge implementieren. Nutzen Sie das beigefügte `Makefile`, um das Projekt zu übersetzen und Ihre Implementierung zu testen (Details dazu finden Sie in den Abschnitten Generation, Storage, und Exploration). Es ist vorgesehen das Projekt auf einem Linux Rechner zu übersetzen..

**Wichtiger Hinweis**: Bitte ändern Sie nur die Dateien `atf.h` und `atf.c`. Die Aufgabe gilt als bestanden, wenn der Test `make test_final` erfolgreich ausgeführt wird. Abgaben, die nicht auf einem Linux-Rechner der Uni (z.B. `zivlts1.uni-muenster.de`) kompilieren, gelten automatisch als _nicht bestanden_. Sollten Sie Fragen zur Aufgabenstellung haben, öffnen Sie bitte ein Issue in diesem Repository.

## Aufgabe 1: Generation

Implementieren Sie die Generation-Phase des Auto-Tuning Frameworks in der Datei `atf.c`. Gehen Sie dazu wie folgt vor:

- Implementieren Sie die Methode `tp_t create_tp(char* name, int min, int max, constraint_t constraint)`:
   
   Initialisieren Sie ein struct vom Typ `tp_t` mit den Informationen eines neuen Tuningparameters: der Name `name`, der Wertebereich `[min, max]`, und die Abhängigkeiten zu anderen Parametern `constraint`. Der Typ `tp_t` is bereits in `atf.h` implementiert. Der Typ von Abhängigkeiten ist `constraint_t`: Funktionen, die bis zu 10 Parameterwerte entgegennehmen und true zurückgeben, falls die Parameterwerte die Abhängigkeiten erfüllen. Sie finden ein Beispiel für eine Abhängigkeit in `test_generation.c` in Zeile 19. Sie können davon ausgehen, dass die Abhängigkeiten eines Parameters immer nur zu Parametern bestehen, die vor diesem Parameter definiert wurden. 

- Implementieren Sie die Methode `void generate_search_space(tp_t* parameters, int num_parameters, search_space_t* search_space)`:

   Iterieren Sie über alle möglichen Parameterbelegungen für die Parameter in `parameters` (`num_parameters` gibt die Anzahl der Parameter an). Benutzen Sie die Methode `print_configuration`, die in `atf.c` bereits implementiert ist, um die _gültigen_ Konfigurationen auszugeben. Den Parameter `search_space` können Sie zunächst ignorieren.
   
- Testen Sie Ihre Implementierung, indem Sie `make test_generation` im Projektordner ausführen. Sie können mit der Storage-Phase fortfahren, wenn Sie die folgende Ausgabe sehen:

    ```
        N  TS1  TS2
       16    1    1
       16    2    1
       16    2    2
       16    4    1
       16    4    2
       16    4    3
       16    4    4
       16    8    1
       16    8    2
       16    8    3
       16    8    4
       16    8    5
       16    8    6
       16    8    7
       16    8    8
       16   16    1
       16   16    2
       16   16    3
       16   16    4
       16   16    5
       16   16    6
       16   16    7
       16   16    8
       16   16    9
       16   16   10
       16   16   11
       16   16   12
       16   16   13
       16   16   14
       16   16   15
       16   16   16
    ```

## Aufgabe 2: Storage

Erweitern Sie Ihren Code aus Aufgabe 1 um die Speicherung des Suchraums (Storage-Phase). Gehen Sie dazu wie folgt vor:

- Erweitern Sie das struct `search_space_t` in `atf.h` um geeignete Attribute zur Speicherung des Suchraums. Das Feld `size` soll unverändert in dem struct erhalten bleiben und nach der Generierung des Suchraums die Suchraumgröße enthalten, also die Anzahl der gültigen Konfigurationen.

- Passen Sie Ihre Implementierung von `generate_search_space` aus Aufgabe 1 so an, dass die gültigen Konfigurationen nun nicht mehr auf der Konsole ausgegeben werden, sondern im struct `search_space_t` abgespeichert werden.

- Implementieren Sie die Methode `configuration_t get_config(search_space_t* search_space, int index)` in `atf.c`:

  Implementieren Sie die Methode `get_config` passend für Ihre gewählte Repräsentation des Suchraums in `search_space_t`. Die Methode soll einen Pointer auf einen Suchraum und einen Index übergeben bekommen und die entsprechende Konfiguration aus dem Suchraum zurückliefern. Der Aufruf von `get_config` mit dem Suchraum aus Aufgabe 1 und Index `2` sollte z.B. die Konfiguration `N=16, TS1=2, TS2=2` zurückgeben.

- Implementieren Sie die Methode `void free_search_space(search_space_t* search_space)` in `atf.c`:

  Geben Sie den Speicher, den Sie in `generate_search_space` zur Speicherung des Suchraums dynamisch alloziert haben, wieder frei.
  
- Testen Sie Ihre Implementierung, indem Sie `make test_storage` im Projektordner ausführen. Sie können mit der Exploration-Phase fortfahren, wenn Sie die folgende Ausgabe sehen:

  `Die Storage-Phase wurde erfolgreich implementiert!`

## Aufgabe 3: Exploration

Erweitern Sie Ihren Code aus Aufgabe 2 um die Durchsuchung des Suchraums (Exploration-Phase). Gehen Sie dazu wie folgt vor:

- Implementieren Sie die Methode `explore_search_space` in `atf.c`:
  
  Die Methode hat folgende Signatur:
  
  ```
  void explore_search_space(search_space_t* search_space, cost_function_t cost_function,
                            SEARCH_STRATEGY search_strategy, ABORT_TYPE abort_type, int abort_value,
                            configuration_t* best_config, int* cost)
  ```
  
  Sie erwartet einen Pointer auf einen Suchraum, eine sog. `cost_function`, der eine Konfiguration zur Laufzeitmessung übergeben werden kann, eine Suchstrategie (`EXHAUSTIVE` oder `RANDOM`, weitere Details dazu unten), eine Abbruchbedingung bestehend aus Typ (`EVALUATIONS`, `SECONDS`, `MINUTES`, oder `HOURS`, weitere Details dazu unten) und Wert, und zwei Pointer, in die die beste gefundene Konfiguration, sowie deren Laufzeit geschrieben werden soll.
  
  Implementieren Sie die Methode so, dass sowohl beide Suchstrategien (`EXHAUSTIVE` und `RANDOM`) und alle vier Abbruchbedingungen (`EVALUATIONS`, `SECONDS`, `MINUTES` und `HOURS`) unterstützt werden. Weitere Informationen dazu finden Sie in `atf.h` ab Zeile 39.
  
  **Tipp:** Es kann hilfreich sein eine Hilfsausgabe für jede getestete Konfiguration in der Konsole zu machen, die die bisher vergangene Zeit, die getesteten Konfiguraitonen, etc. ausgibt. So können Sie einfacher prüfen, ob Ihre Implementierung wie gewünscht funktioniert.
  
- Testen Sie Ihre Implementierung, indem Sie `make test_exploration` im Projektordner ausführen. Sie können mit dem finalen Test `make test_final` fortfahren, wenn Sie die folgende Ausgabe sehen:

  `Die Exploration-Phase wurde erfolgreich implementiert!`
