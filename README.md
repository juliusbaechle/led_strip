# led_strip
Led Streifen der von zwei Arduino Nano betrieben wird. Dieser kann mit Bluetooth gesteuert werden und hat ein Mikrofon für auf Musik reagierende Effekte.

Der 1. Arduino übernimmt nur die Effekte und bekommt vom 2. Arduino die genauen Daten wie Effekt, Farbe, Richtung,...
An den 2. Arduino ist ein Bluetooth Modul und 2 Mikrofone angeschlossen. Davon ist ein Mikrofon für die Aufnahme der Musik und eins für das Erkennen von klatschen (bei 2 maligem klatschen schaltet sich der Streifen aus/ein).

Für dieses Projekt brauchte ich fast ein Jahr (studiere "neben diesem Projekt"). In dieser Zeit arbeitete ich 4 Versionen heraus. Diese starteten mit einer unübersichtlichen Version mit normalen Effekten. Diese schrieb ich deutlich besser und übersichtlicher.
Version 3 war mit auf Musik reagierenden Effekten, Version 4 spaltete dies auf 2 Arduinos auf.
Besonders viel Zeit brauchte ich für das herausfiltern des Beats. Diese Aufgabe löste ich mit der FFT (Fast Fourier Transformation) (Siehe arduino_2/beat/getBeat()).

Verwendete Teile:
  LED - Streifen: 5m WS2812b 60Led's/m 5050SMD
  Bluetooth Modul: HC - 05
  Netzteil: 20A, 5V (jede Led braucht bei sattem weiß 60mA, also insgesamt bei 300 leds 18A)
  1. Mikrofon: https://de.gearbest.com/development-boards/pp_75530.html?wid=1433363&currency=EUR&vip=4275440&gclid=Cj0KCQjwnZXbBRC8ARIsABEYg6DAVj4klgGvm_FK7SffO8b9GuHlMoG62-gpR9um7N3DPtw4AhxALiwaAuAdEALw_wcB
  2. Mikrofon: https://eckstein-shop.de/Adafruit-Electret-Microphone-Amplifier-MAX9814-with-Auto-Gain-Control?curr=EUR&gclid=Cj0KCQjwnZXbBRC8ARIsABEYg6Be5oasw_1sZAome6iuzRh2w_e5OefY3upOmmmHYqdvGxQYTThdKPEaAk-SEALw_wcB
  2x Arduino Nano
  2x Arduino Nano "breakout shield": https://www.ebay.de/i/122968008677?chn=ps
  Kabel (am besten rot (+5V), schwarz (ground) und weiß (Datenkabel))
  Schrauben und Gummipuffer um die Bauteile auf einem Brett zu befestigen
