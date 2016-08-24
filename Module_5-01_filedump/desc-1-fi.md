title: Tiedostodumppi
task_id: 01_filedump
points: 2


**Tavoite:** Harjoitellaan tiedoston lukemista

Toteuta funktiot '*textdump*' ja '*hexdump*' jotka lukevat annettua
tiedostoa (jonka nimi in *filename* - parametrissa) ja tulostavat
tiedoston sisällön ruudulle. Molempien funktioiden tulee palauttaa
paluuarvonaan luettujen tavujen määrä, tai -1 mikäli tiedoston
avaamisessa sattui virhe. Sinun tulee tulostaa tiedostot seuraavissa
formaateissa:

**Kohdassa (a)** tulostetaan tiedoston sisältö merkkeinä. Mikäli
  tiedostossa tulee vastaan merkki jota ei voi tulostaa (eli funktio
  *[isprint]* palauttaa epätoden arvon), ruudulle tulee tulostaa
  merkki '?', muussa tapauksessa tulostetaan tiedostosta luettu
  merkki.

[isprint]: http://linux.die.net/man/3/isprint

**Kohdassa (b)** tulostetaan tiedoston sisältö heksadumppina: kukin
  tiedostossa oleva tavu tulostetaan kahden merkin pituisessa
  heksadesimaalimuodossa siten että alle 0x10:n oleviin lukuihin
  lisätää 0 eteen. Kunkin luvun perässä on yksi välimerkki, ja
  kullakin rivillä tulee olla enintään 16 merkkiä, jonka jälkeen
  siirrytään seuraavalle riville. Myös rivin viimeistä merkkiä seuraa
  välimerkki. Tässä esimerkki tulosteesta:

<pre>
0e 54 65 65 6d 75 20 54 65 65 6b 6b 61 72 69 30 
30 30 30 30 41 00 00 14 45 4c 45 43 2d 41 31 31 
30 30 00 00 00 00 00 00 00 </pre>
