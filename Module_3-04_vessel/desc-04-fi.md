title: Laiva
task_id: 04_vessel
points: 1
last_modified: 2016-03-11 (Lisätty pari sanaa osoittimista ja mallocista)


**Tavoite:** Harjoitellaan rakenteisten tietotyyppien määrittelyä ja
  peruskäyttöä.

Tässä harjoituksessa sinun tulee toteuttaa kolme asiaa: 1) määrittele
rakenteinen tietotyyppi **vessel**, joka kuvaa kuvitteellista
valtamerialusta; 2) toteuta funktio **create_vessel** joka luo uuden
instanssin määrittelemästäsi *vessel* - tietotyypistä; 3) toteuta
funktio **print_vessel** joka tulostaa *vessel* - rakenteen sisällön.

*vessel* - tietorakenteessa tulee olla seuraavat kentät. On tärkeää
 että kenttien nimet ovat kuten alla annettu, koska muuten
 *src/main.c* tai tehtävän testikoodit eivät käänny.

  * *name*: laivan nimi merkkijonona. Merkkijono tulee kopioida
    **create_vessel** - funktion parametrista *p_name*. Et voi
    sijoittaa sitä suoralla sijoitusoperaattorilla. Nimeä tulee voida
    muokata jälkeenpäin, ja siinä on oltava tilaa 30 merkille (plus 
    lopetusmerkki). Tila on varattava pinosta (stack) eikä keosta 
    (heap), eli älä käytä dynaamista muistia tähän. Jos funktion 
    parametrina annettu nimi on pidempi kuin 30 merkkiä, se tulee 
    katkaista 30 merkkiin.

  * *length*: laivan pituus double-tyyppisenä liukulukuna. Voit
    olettaa että pituus ilmaistaan metreinä (tosin asialla ei suurta
    käytännön merkitystä tässä tehtävässä).

  * *depth*: laivan syväys double-tyyppisenä liukulukuna. Tämänkin
    osalta voi olettaa että syväys ilmaistaan metreinä.

  * *crg*: laivan lasti. Tämän tulisi vastata yhtä *cargo* -
    tietorakennetta, joka on annettu *source.h* - otsakkeessa.

Sinun tulee määritellä *vessel* - rakenne *source.h* -
otsaketiedostossa, jotta muut lähdetiedostot näkevät sen.

*create_vessel* saa vastaavat parametrit kuin mitä määriteltävässä
 *vessel*-tietorakenteessa on. Sinun tulee sijoittaa nämä arvot
 luomaasi *vessel* - tyyppiseen muuttujaan. Kannattaa kiinnittää
 erityishuomiota siihen miten käsittele merkkijonoparametria
 *name*. Merkkijonosta tulee luoda kopio.

**HUOM:** *create_vessel* palauttaa paluuarvonaan kopion luomastasi
  vessel-tietorakenteesta, paluuarvo ei siis ole osoitin. Funktion
  ulkopuolella oleva koodi ei osaa vapauttaa mitään varaamaasi
  muistia, joten *malloc*:in käyttö aiheuttaa muistivuodon (ellet
  vapauta muistia saman tien, missä ei olisi hirveästi
  järkeä). Kannattaa miettiä tarvitsetko osoittimia lainkaan tässä
  tehtävässä.

*print_vessel* tulostaa annetun *vessel* - rakenteen sisällön siten
 että jokainen tietorakenteen kenttä tulostuu omalle rivilleen,
 mukaanlukien *cargo*-rakenteeseen kuuluvat kentät. Liukuluvut tulee
 tulostaa siten että niistä näytetään yksi desimaali. Esimerkiksi, kun
 edellä mainitut funktiot on toteutettu oikein, *src/main.c*:n
 esimerkkiohjelman tulisi tulostaa seuraavaa:

<pre>
Apinalaiva
180.0
8.5
Bananas
10000
1500.0</pre>
