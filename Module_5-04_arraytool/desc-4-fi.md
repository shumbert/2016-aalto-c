title: Taulukkomakroja
task_id: 04_arraytool
points: 3


**Tavoite:** Harjoittele makrojen käyttöä.

Tässä tehtävässä ei ole varsinaista .c - pääteistä tiedostoa
työstettäväksi perinteisen *main.c*:n lisäksi, vaan tehtävä tehdään
*src/arraytool.h* - otsakkeeseen. Sinne sinun tulee toteuttaa
seuraavat makrot:

**(a): CHECK(cond, msg)** joka tarkistaa loogisen ehdon *cond*, ja
  mikäli ehto ei täyty, tulostaa merkkijonon *msg*
  standarditulostevirtaan. Tämä siis on hieman kuten C-kirjastossa
  määritelty *assert*-makro, mutta ei keskeytä ohjelman
  suoritusta. Esimerkki makron käytöstä: `CHECK(5 > 10, "5 > 10
  failed\n");`

**(b): MAKE_ARRAY(type, n)** joka luo dynaamisesti varatun taulukon,
  jossa on *n* alkiota tyypiä *type*. Makro palauttaa osoittimen
  varattuun muistiin. Esimerkki makron käytöstä: `void *ptr =
  MAKE_ARRAY(int, 10);`

**(c): ARRAY_IDX(type, array, i)** joka käsittelee taulukkoa *array*
  kohdasta *i*. Taulukon alkioiden tyyppi on annettu parametrissa
  *type*. Esimerkki makron käytöstä: `ARRAY_IDX(int, ptr,
  i) = i * 2;`

Kun makrot on oikein toteutettu, oletuksena mukana tuleva *src/main.c*
varaa kokonaislukutaulukon 10:lle luvulle, alustaa sen ja tulostaa
taulukon sisällön. Funktio testaa myös CHECK-makroa. Voit toki muuttaa
main-funktiota haluamasi mukaan.
