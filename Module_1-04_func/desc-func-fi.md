title: Vektorifunktio
task_id: 04_func
points: 1


**Tavoite:** perehtyä funktion kirjoittamiseen ja toisten
kirjastofunktioiden kutsumiseen.

Toteuta funktio nimeltään **vectorlength** joka laskee annetun
kolmiulotteisen vektorin pituuden. Funktio saa kolme parametria, jotka
esittävät vektorin alkioita eri ulottuvuuksissa. Funktio palauttaa
vektorin pituuden. Kaikki luvut tulee käsitellä double-tyyppisinä liukulukuesityksinä.

Mikäli vektorilaskut ovat ehtineet unohtua, esimerkiksi [Wikipediassa]
kerrotaan laskukaava. Tarvitset siis esimerkiksi neliöjuurilaskua,
joka ei sisälly C-kielen perusoperaattoreihin, vaan sitä varten on
[sqrt] - funktio matematiikkakirjastossa, jota sinun tulee
kutsua. [pow] - funktiolla voi laskea potenssilaskuja. Katso tarkemmat
tiedot funktioista linkitetyiltä manuaalisivuilta.

[Wikipediassa]: https://fi.wikipedia.org/wiki/Vektori
[sqrt]: http://linux.die.net/man/3/sqrt
[pow]: http://linux.die.net/man/3/pow

Toteuta funktio *source.c* - tiedostoon. Tiedostossa on annettu
valmiiksi viittaus *math.h* - otsaketiedostoon jossa
matematiikkafunktiot on määritelty, mutta tässä tehtävässä
joudut kirjoittelemaan kaiken muun itse. *Ohjelma ei aluksi edes
käänny, ennenkuin olet toteuttanut vähintäänkin funktion rungon.*
