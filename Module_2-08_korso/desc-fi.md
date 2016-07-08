title: Korsoraattori
task_id: 08_korso
points: 1


**Tavoite:** Lisää tuntumaa merkkijonojen pyörittelyyn. Tämä harjoitus
  on tribuutti legendaariselle [Korsoraattori]-palvelulle.

[Korsoraattori]: http://korsoraattori.evvk.com

Toteuta funktio `void korsoroi(char *dest, const char *src)`, joka
korsoroi annetun merkkijonon *src* ja kirjoittaa muutetun merkkijonon
osoitteeseen *dest*. Merkkijono muutetaan korsoksi seuraavalla tavalla:

  * Jokainen "ks" alkuperäisessä merkkijonossa tulee muuttaa "x":ksi
    kohdemerkkijonossa.
  * Jokainen "ts" alkuperäisessä merkkijonossa tulee muuttaa "z":ksi
    kohdemerkkijonossa.
  * Joka kolmannen alkuperäisessä merkkijonossa olevan sanan jälkeen
    tulee lisätä ylimääräinen sana "niinku" kohdemerkkijonoon.
  * Joka neljännen alkuperäisessä merkkijonossa olevan sanan jälkeen
    tulee lisätä ylimääräinen sana "totanoin" kohdemerkkijonoon.

Sanaeroittimena käytetään välilyöntiä (' '). Sinun ei tarvitse lisätä
mitään viimeisen alkuperäisen sanan jälkeen, ja voit olettaa että
kohdemerkkijonossa *dest* on varattuna riittävästi tilaa. Voit lisäksi
olettaa että kaikki kirjaimet ovat pieniä kirjaimia.

Esimerkiksi merkkijonosta "yksi auto valui itsekseen ilman kuljettajaa mäkeä
alas" tulee "yxi auto valui niinku izexeen totanoin ilman
kuljettajaa niinku mäkeä alas".
