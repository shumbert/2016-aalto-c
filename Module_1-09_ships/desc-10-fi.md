title: Laivanupotus
task_id: 09-ships
points: 4


**Tavoite:** Rakenna hieman isompi ohjelma, joka koostuu muutamasta
  funktiosta.

Tässä tehtävässä toteutetaan yksinkertainen laivanupotuspeli. Pelin
toteuttamisessa tarvitaan joitain C:n ominaisuuksia, joita ei ole
vielä käyty läpi, joten osa tarvittavista funktioista on annettu
valmiina. Sinun täytyy toteuttaa neljä funktiota saadaksesi pelin
valmiiksi.

Pelikenttä on 10x10 ruudun kokoinen, ja kukin laiva on 3 ruutua
pitkä. Koordinaatit pysty- ja vaakasuuntaan merkataan välillä 0 ja 9:
(0,0) on vasen yläruutu, ja (9,9) on oikea alaruutu. Peli päättyy kun
kaikki laivat on upotettu.

Pelikoodi on jaettu kahteen erilliseen C-kieliseen lähdetiedostoon,
joita molempia tarvitaan pelin kääntämiseen. **shiplib.c** sisältää
apufunktioita joilla käsitellään pelikenttää. Sinun täytyy kutsua
näitä funktioita osana omien tehtäväfunkitoidesi toteutusta, mutta
tätä tiedostoa ei kannata muuttaa. Lue koodin seassa olevia
kommentteja selvittääksesi miten funktiot toimivat. Tiedosto
**ships.c** sisältää funktiot jotka sinun tulee toteuttaa.

Sinun tulee listata seuraavassa kuvatut neljä funktiota. Saat pisteen
kunkin funktion toimivasta toteutuksesta.


a) Aseta laivat
---------------

Toteuta funktio `void set_ships(unsigned int num)` joka asettaa *num*
alusta pelikartalle. Asettaaksesi yhden laivan johonkin
karttapaikkaan, sinun tulee kutsua funktiota *place_ship*, jonka
parametreiksi annat laivan sijainnin ja suunnan (katso lähdekoodista
tarkempi kuvaus). Huomaa, että *place_ship* - funktio ei onnistu
mikäli yrität asettaa alusta toisen päälle, tai ulos kartta-alueelta,
joten sinun tulee tarkistaa funktion paluuarvo, jotta voit varmistua
funktion onnistumisesta.

**Vinkki:** Voit käyttää C-kirjaston funktiota
[rand()](http://linux.die.net/man/3/rand)** valitaksesi laivalle
satunnaisen sijainnin ja suunnan. Funktio palauttaa satunnaisen
kokonaisluvun, jonka voit rajoittaa haluamallesi lukualueelle
käyttämällä jakojäännös-operaatiota ('%'). Esimerkiksi `rand() % 10`
tuottaa satunnaislukuja välillä 0 ja 9.


b) Tulosta pelikenttä
---------------------

Toteuta funktio `void print_field(void)` joka tulostaa koko pelikentän
ruudulle. Mikäli pelaaja ei vielä tunne ruudun sisältöä (eli ei ole
ampunut sitä), '?' tulisi tulostaa. Mikäli ruutu on tunnettu, tuloste
voi olla yksi kolmesta vaihtoehdosta:

  * '.' jos paikassa ei ole laivaa
  * '+' jos paikassa on laivan osa johon ei ole vielä osunut (tarvitaanko
  tätä?)
  * '#' jos paikassa on laivan osa johon on osuttu.

Alussa kaikki ruudut ovat näkymättämiä, mutta ruutu muuttuu näkyväksi,
kun siihen ammutaan.

Tarvitset kahta funktiota: **is_visible(x,y)**, kertoo onko annettu
ruutu näkyvissä, ja **is_ship(x,y)**, joka kertoo mikäli ruudussa on
laiva ja onko siihen osunut. Lue *shiplib.c* - lähdekoodista tarkemmat
kuvaukset funktioista.


c) Ammu
-------

Toteuta funktio `int shoot(void)` joka kysyy kaksi etumerkitöntä
kokonaislukua käyttäjältä välilyönnillä eroteltuna. Nämä esittävät
koordinaatteja, joihin seuraavaksi ammutaan. Jos käyttäjä antaa
virheellisen syötteen, tai koordinaatit eivät ole pelialueen sisässä,
funktion tulee palauttaa -1. Jos annetussa sijainnissa on alus,
sinun tulee kutsua funktiota **hit_ship()** merkataksesi sijainnin
osutuksi ja palauttaa arvo 1. Mikäli sijainnissa ei ole alusta, sinun
tulee palauttaa arvo 0. Molemmissa tapauksissa tulee ruutu merkata näkyväksi
funktiota **checked()** kutsumalla.


d) Pelin päättyminen
--------------------

Toteuta funktio `int game_over(unsigned int num)` joka palauttaa 1,
mikäli kaikki laivat on upotettu, tai 0, mikäli kentällä on vielä
laivan osia joihin ei ole osuttu. Parametri *num* kertoo kuinka monta
laivaa kentällä on. Saat selville kunkin laivan
tilanteen käyttämällä **is_ship()** - funktiota, ja koska tiedät että
kukin laiva on 3 ruutua pitkä, tiedät kuinka monesta ruudusta tulee
löytyä osuma.
