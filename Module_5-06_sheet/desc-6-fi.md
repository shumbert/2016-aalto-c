title: Taulukkolaskenta
task_id: 05_sheet
points: 4


**Tavoite**: Harjoitellaan funktio-osoittimien käyttöä. Samalla
sivutaan muita aiemmin käsiteltyjä aiheita, kuten tyyppimäärittelyjä,
unioneita, kaksiulotteisia taulukoita, jne.

Tässä tehtävässä toteutetaan kaksiulotteinen
taulukkolaskentaohjelma. Taulukon kukin solu voi olla kolmessa
tilassa: a) määrittelemätön, eli solulla ei ole sisältöä; b) solussa
on vakiomuotoinen *double* - tyyppinen lukuarvo; c) solussa on
funktio, joka suorittaa laskutoimituksen parametrinaan saaman alueen
yli taulukossa.

Jälkimmäisessä tapauksessa taulukkoon sijoitetaan siis käytännössä
funktio-osoitin, joka suorittaa halutun laskutoimituksen. Kaikki
tällaiset funktiot saavat kaksi koordinaattia parametrinaan:
laskettavan alueen vasemman ylänurkan koordinaatit, ja laskettavan
alueen oikean alanurkan koordinaatit. Funktioiden tulee palauttaa
*double*-tyyppinen paluuarvo, joka tullaan näyttämään taulukon
kyseisessä kohdassa.

Tehtäväpohjassa on seuraavia valmiiksi määriteltyjä funktioita, joita
kutsutaan *src/main.c* - tiedostosta. Tässäkin tehtävässä on
suositeltavaa, että testaat ohjelmaa main-funktiota käyttäen ennenkuin
lähetät sen TMC:lle tarkistettavaksi.

  * *parse_command* lukee käyttäjältä komennon jonka seurauksena
    taulukkoon voidaan kirjoittaa joko staattinen lukuarvo, tai yksi
    kolmesta mukana tulevasta funktiosta. Koordinaatit ilmaistaan
    kahdella kirjainmerkillä komennon alussa. Esimerkiksi `AA 6`
    asettaa vasemman ylänurkan arvoksi 6, ja `BA sum CC EE` laskee
    ruutuun (1,0) summan 3x3-kokoisen alueen yli välillä (2,2) ja
    (4,4).

  * *print_sheet* tulostaa taulukon nykytilan.

Huomaa, että yllä mainitut funktiot eivät toimi oikein ennenkuin olet
toteuttanut muutamia muita funktioita seuraavassa olevan tehtävänannon
mukaisesti.

Sinun tulee toteuttaa alla mainitut tehtäväkohdat annetussa järjestyksessä:

(a) Taulukon luominen ja vapauttaminen
--------------------------------------------

Toteuta seuraavat funktiot:

  * **create_sheet** joka varaa taulukon tarvitseman muistin, eli
    *Sheet* tietorakenteen ja siitä viitattavan kaksiulotteisen taulukon.

  * **free_sheet** joka vapauttaa kaiken muistin jonka
    *create_sheet()* varasi

  * **get_cell** joka palauttaa osoittimen parametreissa osoitettuun
    soluun taulukossa. Funktion tulee olla turvallinen, mikäli sitä
    yritetään kutsua taulukon yli osoittavilla indekseillä. Tällöin
    tulee palauttaa NULL, sen sijaan että ohjelma esimerkiksi kaatuisi
    tai heittäisi Valgrind-virheitä.

Testit tulevat käyttämään hyväkseen näitä funktioita, joten tämä osio
pitää toteuttaa ensin hyväksytysti, jotta seuraavat voidaan
tehdä. Kannattaa myös tehdä TMC-palautus, ennenkuin siirryt seuraavaan
kohtaan.

(b) Solun arvon asettaminen
-------------------------------------

Toteuta seuraavat funktiot:

  * **set_value** joka asettaa *double* - tyyppisen arvon annettuun
    paikkaan taulukossa.

  * **set_func** joka asettaa annetun funktion parametreineen, eli
    funktio-osoittimen annettuun paikkaan taulukossa.

Kummankin funktion tulee olla turvallisia yli taulukon menevillä
indekseillä. Kun indeksoidaan yli taulukon, funktiot eivät tee mitään.


(c) Solun arvon määrittely
---------------------------

Toteuta funktio **eval_cell** joka palauttaa *double* - tyyppisen
arvon riippuen annetun solun sisällöstä. Jos solun tyyppi on VALUE,
funktio palauttaa vain tämän arvon. Jos tyyppi on FUNC, kyseistä
funktiota kutsutaan sille tallennettuja parametreja käyttäen, ja
funktion tuottama tulos palautetaan. Jos solun tyyppi on UNSPEC, tai
jos funktiota kutsutaan parametreilla jotka osoittavat taulukon yli,
palautetaan vakio *NAN* (not-a-number), joka on määritelty *math.h* -
otsakkeessa. (*Huom: jos haluat testata onko jonkun muuttujan arvo
NAN, sinun tulee käyttää [isnan] - makroa*).


[isnan]: http://linux.die.net/man/3/isnan

(d) Kolme funktiota taulukkolaskentaan
---------------------------------

Toteuta funktiot, joilla lasketaan annetun alueen suurin arvo (max),
annetulla alueella olevien lukujen summa, ja annetulla alueella
määriteltyjen solujen lukumäärä.

  * **maxfunc** palauttaa suurimman arvon annetun vasemman yläkulman
    ja oikean alakulman välisellä alueella. Mikäli alueella on
    määrittelemättömiä soluja, tai taulukon ulkopuolella olevia
    koordinaatteja, ne tulee ohittaa.

  * **sumfunc** palauttaa annetulla alueella olevien lukujen
    summan. Määrittelemättömät solut ja ulkopuolella olevat
    koordinaatit tulee sivuuttaa.

  * **countfunc** palauttaa niiden solujen lukumäärän annetulla
    alueella, joilla on jokin määritelty arvo (joko staattinen numero,
    tai funktion määräämä).

Näitä funktioita kutsutaan *eval_cell* funktiosta sen mukaan, mitä
taulukkoon on talletettu.

Kannattaa huomioida, että funktioiden käsittelemällä alueella voi olla
staattisten arvojen lisäksi myös toisia funktioita. Jos solu sisältää
funktion, sen arvo tulee määrittää osana laskutoimitusta. Toisin
sanoen, yllä mainituissa funktioissa kannattaa sisäisesti käyttää
*eval_cell* funktiota, joka tarvittaessa kutsuu edelleen toisia
funktioita aiemmin määritellyn mukaisesti.
