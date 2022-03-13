--------------------------------------------------------------------------------------
Inhalt
--------------------------------------------------------------------------------------

* Beschreibung und Nutzung
* Ausführbare Dateien
* Aufruf
* Bedienung
* Konfiguration
* Bekannte Bugs
* Kontakt

--------------------------------------------------------------------------------------
Beschreibung und Nutzung
--------------------------------------------------------------------------------------

Simplelster Raytracer. Von Konrad Höffner im Rahmen des CG - Praktikums 2006 an der Uni Leipzig zu Übungszwecken programmiert.

Quellcode / Visual C++ 6.0 Projekt und unter Windows ausführbare Dateien sind enthalten.

Macht damit was auch immer ihr wollt. Quellcodeklau ist ausdrücklich erwünscht, es gibt natürlich keine Garantie für garnichts und ich habe C++ auch gerade erst gelernt, es werden also viele Fehler drin sein. Einiges ist teilweise von anderen übernommen. Die Vektorklassen Vector3d.h/cpp könnten nützlich sein und die Schnittberechungsklassen 3DMath.cpp/h.

--------------------------------------------------------------------------------------
Ausführbare Dateien
--------------------------------------------------------------------------------------

- raytracer_fx.exe - mit Spiegelung und Transparenz
- raytracer_nofx.exe - ohne Spiegelung und Transparenz

--------------------------------------------------------------------------------------
Aufruf
--------------------------------------------------------------------------------------

- ohne Parameter -> Einlesen der Standardszene "abgabeszene.xml"
- "raytracer_(no)fx szenendateiname" -> einlesen der angegebenen Szene

Nach Starten des Programmes sieht man die Vorschau, welche eine OpenGl - Ansicht der Szene ohne Lichteffekte zeigt. Auch die Octrees sind in der Vorschau sichtbar.

--------------------------------------------------------------------------------------
Bedienung
--------------------------------------------------------------------------------------

Pfeiltasten  -Bewegen nach Links / Rechts  / Vorne / Hinten (sehr kleine Schrittweite)

Enter - Raytracen


--------------------------------------------------------------------------------------
Konfiguration
--------------------------------------------------------------------------------------
Aktivierung/Deaktivierung von Vorschau/Reflexion und Transparenz erfordern eine Änderung von #defines in der Header - Datei stdafx.h und eine anschließende Neukompilierung.

--------------------------------------------------------------------------------------
Bekannte Bugs
--------------------------------------------------------------------------------------
- Brechung ist nicht vollständig implementiert
- Beleuchtung im Kelch in der Standardszene sieht merkwürdig aus
-> irgendwas mit den Normalen scheint dort nicht zu stimmen
- Spiegelung sieht merkwürdig aus -> keine Ahnung, ob das korrekt ist
- Das Raytracing - Fenster darf nicht den Fokus verlieren, ansonsten wird das Rendering abgebrochen.
Das Windows - Fenster basiert auf einem Tutorial von nehe.gamedev.net und wurde auf SingleBuffering umgestellt. Da dieser Teil des Quellcodes nicht von uns ist haben wir auch keine Ahnung, wie man das beheben kann.
- Unter Visual Studio 2005 lassen sich Iteratoren nicht dekrementieren. Der Versuch führt zum Absturz. Kompilieren lässt es sich nur unter Entfernung des folgenden Codefragmentes in der Datei BoundingBox.cpp:

--------------------------------------------------------------------------------------

    for(list<BoundingBox*>::iterator itBox=kindBoxen.begin();itBox!=kindBoxen.end();itBox++)
		{		
			...
			if((*itBox)->dreiecke.empty())
			{
				// Ab hier Entfernen bei Visual C++ 8
				BoundingBox* pBox = *itBox;
				itBox--;
				kindBoxen.remove(pBox);
				// Bis hier hin Entfernen bei Visual C++ 8
			} else
			...
--------------------------------------------------------------------------------------

Müsste allerdings eine Verringerung der Performance mit sich bringen.

--------------------------------------------------------------------------------------
Kontakt
--------------------------------------------------------------------------------------

Mail an <computergrafikpraktikum@streber24.de>.

Ich musste zum Programmieren dieses Raytracers C++ erst erlernen (verwendete Programmiersprache war vorgeschrieben), bin also für jegliche konstruktive Kritik und Hilfe dankbar.
