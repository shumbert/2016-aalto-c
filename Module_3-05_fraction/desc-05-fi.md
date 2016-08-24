title: Murtoluku
task_id: 05_fraction
points: 4


Nyt harjoitellaan abstraktin datatyypin tekemistä toteuttamalla uusi
numerotyyppi, murtoluku ([fraction]), joka koostuu *osoittajasta*
(numerator) ja *nimittäjästä* (denominator). Esimerkiksi 2/3 ja 4/6
ovat murtolukuja, joissa 2 ja 4 ovat osittajia, ja 3 ja 6
nimittäjiä. Nämä murtoluvut ovat myös yhtä suuria. Määrittelemme uuden
tietotyypin **Fraction** esittämään murtolukuja.

[fraction]: http://en.wikipedia.org/wiki/Fraction_(mathematics)

Tässä tehtävässä sinun tulee toteuttaa seuraavat funktiot. Kustakin
funktiokokonaisuudesta saa yhden pisteen, ja tehtävä on siten
kokonaisuudessaan neljän pisteen arvoinen.

Tehtävässä annetaan otsake *fraction.h*, joka määrittelee julkisen
rajapinnan, jonka kautta murtolukuja käsitellään. Sinun tulee
toteuttaa funktiot ja tarvitsemasi tietorakenteet tiedostoon
*fraction.c*.


(a) Aseta arvo
---------------

Toteuta funktio `Fraction* setFraction(unsigned int numerator,
unsigned int denominator)` joka varaa uuden murtoluvun dynaamisesti
keosta ja asettaa sen esittämään lukua, jonka osoittaja ja nimittäjä
parametreissa annetaan. Funktion tulee palauttaa luotu murtoluku (eli
osoitin siihen).

Lisäksi sinun tulee toteuttaa seuraavat yksinkertaiset funktiot:

  * `void freeFraction(Fraction* f)` joka vapauttaa murtoluvulle
    varatun muistin.

  * `unsigned int getNum(const Fraction *f)` joka palauttaa annetun
    murtoluvun osoittajan.

  * `unsigned int getDenom(const Fraction *f)` joka palauttaa annetun
    murtoluvun nimittäjän.


(b) Vertaile arvoja
--------------------

Toteuta funktio `int compFraction(const Fraction *a, const
Fraction *b)` joka palauttaa -1, mikäli murtoluku *a* on pienempi kuin
*b*, 0 mikäli murtoluvut ovat yhtä suuria, tai 1, mikäli murtoluku *a*
on suurempi kuin *b*. Funktion tulee toimia oikein myös silloin kun
nimittäjät ovat erisuuria.

**Huom:** Seuraavia tehtäväkohtia koskevat testit
  käyttävät tätä toteutustasi testaamaan funktioiden toimintaa. Siksi
  sinun tulee toteuttaa tämä tehtäväkohta oikein, ennenkuin siirryt
  tehtäväkohtiin (c) ja (d).


(c) Summalasku
----------------

Toteuta funktio `Fraction *add(const Fraction *a, Fraction *b)` joka
laskee murtolukujen *a* ja *b* summan, ja palauttaa tuloksena syntyvän
uuden murtoluvun paluuarvonaan. Palautettava tulos on uusi
murtolukuobjekti, joka varataan dynaamisesti. Funktion tulee toimia
oikein myös silloin kun summattavien lukujen nimittäjät poikkeavat
toisistaan. Lopputulosta ei tarvitse supistaa käyttämään pienintä
mahdollista nimittäjää.

**Vinkki:** kannattaa aloittaa muuntamalla summattavat murtoluvut
  sellaisiksi, että ne käyttävät samaa nimittäjää.


(d) Supista murtoluku
------------------

Toteuta funktio `void reduce(Fraction *val)`

joka supistaa annetun murtoluvun pienimpään mahdolliseen
nimittäjään. Esimerkiksi jos *val* esittää murtolukua 3/6, sen tulisi
supistua murtoluvuksi 1/2. Pienimmän nimittäjän etsiminen onnistuu
hakemalla pienin yhteinen tekijä osoittajalle ja
nimittäjälle. Tehtäväpohjasta löytyy valmiiksi annettu funktio
`unsigned int gcd(unsigned int u, unsigned int v)` jonka avulla tämä
onnistuu. (funktion toteutus on otettu
[wikipediasta](http://en.wikipedia.org/wiki/Binary_GCD_algorithm))
