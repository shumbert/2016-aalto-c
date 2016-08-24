title: Luolapeli
points: 5
task_id: 04_dungeon


Konsolipohjaiset luolapelit ovat olleet merkittävä peligenre viime
vuosikymmeninä. Tällaisia pelejä ovat esimerkiksi [Rogue], [Nethack]
tai [Angband]. Vaikka Xbox- ja iPad-sukupolvi on pitkälti unohtanut
nämä pelit, palaamme hetkeksi tämän mainion pelityypin pariin.

[Rogue]: http://en.wikipedia.org/wiki/Rogue_(video_game)
[Nethack]: http://www.nethack.org
[Angband]: http://rephial.org

Tässä, hieman isommassa tehtävässä toteutetaan köyhän miehen versio
luolaseikkailupelistä. Toteutettavasta pelistä tulee puuttumaan
runsaasti esikuviensa ominaisuuksia, mutta voit tehtävän ratkaistuasi
toki jatkaa pelin kehittämistä eteenpäin.

Harjoituspohja sisältää enemmän valmista ohjelmakoodia kuin aiemmat
tehtävät, ja monet funktioista on annettu jo valmiina. Sinun tulee
vain toteuttaa toimivan pelin tarvitsemat puuttuvat funktiot alla
olevien tehtäväkohtien mukaisesti. *src* - hakemisto sisältää
seuraavat ohjelmamodulit:

  * **main.c** sisältää pelin pääsilmukan, joka pyytää käyttäjältä
    komentoa ja siirtää pelaajaa, sekä pelin sisältämiä hirviöitä
    eteenpäin vastaavasti.

  * **mapgen.c** rakentaa pelin luolaston huoneineen ja niitä
    yhdistävine käytävineen.

  * **userif.c** sisältää käyttöliittymätominnalisuuden, kuten kartan
    piirtämisen ruudulle, sekä käyttäjän syötteeseen
    reagoimisen. Oletuskonfiguraatiossa pelaaja näkee viiden ruudun
    päähän, eikä tietystikään pysty näkemään seinien taakse. Voit
    halutessasi muuttaa näitä ominaisuuksia vaikuttamatta testien
    tuloksiin.

  * **monster.c** sisältää hirviöiden toimintalogiikan. Peli on
    vuoropohjainen: aina kun pelaaja liikkuu, kaikki kartalla olevat
    hirviöt liikkuvat niinikään pohjautuen algoritmeihin jotka tulet
    toteuttamaan. Suurin osa tässä tehtävässä toteutettavista
    funktioista tulee olemaan tässä tiedostossa.

  * **dungeon.h** sisältää ohjelman vaatimat määrittelyt, kuten
    tarvittavat tietorakenteet, sekä modulien välisten julkisten
    funktioiden rajapintamäärittelyt. Otsakkeessa ei siis ole kaikkia
    em. tiedostojen funktioita, koska osa funktioista on yksityisiä
    kyseiselle ohjelmamodulille.

Pelin pääasialliset tietorakenteet ovat seuraavat: **Game** sisältää
pelitilanteen kokonaisuudessaan, ja näitä tietorakenteita on vain yksi
kerrassaan pelin aikana. Tietorakenteessa on esimerkiksi viittaus
pelikarttaan, sekä dynaaminen taulukko joka sisältää hirviöt. **Map**
sisältää varsinaisen kartan kaksiulotteisessa taulukossa. **Creature**
sisältää yhden hirviön tiedot, joita sisältyy *Game* - rakenteessa
olevaan taulukkoon useita. *numMonsters* kertoo kuinka monta oliota
tässä dynaamisessa taulukossa on.

Mukana tuleva tehtäväpohja sisältää lisää tietoa esimerkiksi
yksittäisten funktioiden toiminnasta. Voit muuttaa tehtäväkoodia
monella tapaa vaikuttamatta tarkistusten lopputulokseen: voit
esimerkiksi lisätä uuden tyyppisiä hirviöitä, vaihtaa kartan
esitystapaa, muuttaa hirviöiden ominaisuuksia, jne. kunhan et muuta
tai poista mukana tulevia tietorakenteiden kenttiä, joihin saatetaan
viitata TMC-testeissä. Nämä testit keskittyvät vain muutamaan
funktioon alla kuvattujen tehtäväkohtien mukaisesti. Muita funktioita
voit muuttaa vapaasti.

Peli käynnistetään ajamalla käännöksen tuottama *src/main* -
tiedosto. Tämä ei kuitenkaan tee mitään järkevää ennenkuin olet
toteuttanut tehtävän vaatimat funktiot.

Alla on "kuvakaappaus" pelistä, jossa kaikki tehtäväkohdat on
toteutettu. Hirviö 'D' lähestyy pelihahmoa '*' vasemmalta. '#' kuvaa
seinää ja '.' lattiaa jota pitkin voi kävellä. Pelaajan nykyiset ja
maksimi-osumapisteet (hit points) kerrotaan kartan alapuolella, jossa
sijaitsee myös paikka komennolle.

<pre>
    ...    
   ##.##   
   #...#   
   #...#  #
####...##..
..D..*.....
###########
           
           
           
           
HP: 12(12)
command &gt;</pre>
	    
Pelissä on seuraavat komennot:

  * `n`: siirry pohjoiseen (ylös)
  * `s`: siirry etelään (alas)
  * `e`: siirry itään (oikealle)
  * `w`: siirry länteen (vasemmalle)
  * `q`: poistu pelistä

Sinun tulee painaa enter:iä kunkin komennon jälkeen. Komentoja voi
muuttaa tai lisätä: TMC-testit eivät välitä niistä.

Monet testit on toteutettu käyttäen valmiiksi tallennettua karttaa
tiedostossa *test/testmap*. Tätä tiedostoa ei kannata muuttaa, koska
se vaikuttaisi paikallisiin testeihin, mutta ei palvelimen
suorittamiin testeihin.
	    	    
a) Voinko liikkua?
----------------------		

Toteuta funktio `int isBlocked(Game *game, int x, int y)` joka
palauttaa 0, mikäli kyseinen sijainti kartalla on vapaa liikkumiseen,
eli siinä ei ole seinää, eikä hirviötä. Mikäli liikkuminen kyseiseen
kohtaan ei ole mahdollista edellä mainituista syistä, funktio
palauttaa jonkun nollasta poikkeavan arvon. Funktion tulee palauttaa
nollasta poikkeava arvo myös silloin, kun kyseinen sijainti sijaitsee
kartan rajojen ulkopuolella. Useat seuraavista funktioista hyötyvät
tämän funktion käytöstä. Funktio tulee toteuttaa tiedostoon
*userif.c*.
	    
b) Luo hirviöt
---------------------		

Toteuta funktio `void createMonsters(Game *game)` joka luo
*opts.numMonsters* hirviötä ja sijoittaa ne satunnaisiin pisteisiin
kartalla. Voit käyttää [rand] - funktiota satunnaisten pisteiden
generointiin. Hirviön voi sijoittaa vain paikkaan joka ei ole seinä,
ja jossa ei ole jo ennestään hirviötä (eli kuten funktio *isBlocked*
kertoo). Alusta kukin luotu hirviö asianmukaisesti antamalla niille
nimi, karttasymbolimerkki, osumapisteet, jne. Hirviöllä tulee olla
enemmän kuin 0 osumapistettä, ja alussa osumapisteitä (*hp*) tulee
olla maksimimäärä (*maxhp*). Muutoin voit asettaa hirviön ominaisuudet
haluamallasi tavalla, kunhan nimi on asetettu ja karttasymboli on
jokin kirjain.

[rand]: http://linux.die.net/man/3/rand

c) Siirry kohti pelaajaa
------------------

Toteuta funktio `void moveTowards(Game *game, Creature
*monst)` joka siirtää hirviötä *monst* yhden askeleen kohti
pelaajaa. Oletuksena annettu pelilogiikka toimii siten, että hirviö
käyttää tätä funktiota siirtyäkseen kohti pelaajaa, ellei sillä ole
alhaiset osumapisteet (jolloin se yrittää karkuun). TMC-testi
tarkistaa seuraavat kriteerit:

  * Jos mahdollista, hirviön ja pelaajan välisen etäisyyden tulee
    vähentyä kutsun seurauksena

  * Hirviö ei voi siirtyä kerrallaan enempää kuin yhden askeleen kartalla

  * Hirviö ei voi siirtyä seinän päälle

  * Hirviö ei voi olla samassa ruudussa toisen hirviön kanssa

  * Hirviö ei voi sijaita samassa ruudussa pelihahmon kanssa

Näiden rajoitteiden sisällä voit toteuttaa liikkumisalgoritmin
haluamallasi tavalla. Voit olettaa että hirviöillä on taikavoimia,
joilla he aistivat pelaajan sijainnin myös seinien läpi.

d) Karkaa pelaajalta
---------------

Toteuta funktio `void moveAway(Game *game, Creature *monst)`, joka
siirtää hirviötä *monst* yhden askeleen poispäin pelaajan
hahmosta. Oletusarvoisesti tätä funktiota kutsutaan kun hirviö on
vähällä kuolla, eli sillä on vähän osumapisteitä. Testi tarkistaa
seuraavat asiat:

  * Jos mahdollista, hirviön ja pelaajan välisen etäisyyden tulee
    kasvaa kutsun seurauksena

  * Hirviö ei voi siirtyä kerrallaan enempää kuin yhden askeleen kartalla

  * Hirviö ei voi siirtyä seinän päälle

  * Hirviö ei voi olla samassa ruudussa toisen hirviön kanssa

  * Hirviö ei voi sijaita samassa ruudussa pelihahmon kanssa

Näiden rajoitteiden sisällä voit toteuttaa liikkumisalgoritmin
haluamallasi tavalla.

e) Hirviön toiminta
--------------------

Funktio `void monsterAction(Game *game)` käy läpi jokaisen elossa
olevan hirviön ja suorittaa niillä jonkin toimenpiteen. Mikäli hirviö
on pelaajan viereisessä ruudussa, sen tulee hyökätä pelaajan kimppuun
käyttäen *attack* - funktio-osoittimen määräämää
toiminnallisuutta. Muussa tapauksessa sen tulee liikkua johonkin
suuntaan käyttäen *move* - funktio-osoittimen määräämää
toiminnallisuutta. Kuollut hirviö (HP == 0 tai vähemmän) ei tee
mitään.

*Creature*-rakenteessa olevat funktio-osoittimet *attack* ja *move*
 määrittävät mitä hirviö kussakin tilanteessa tekee. Mikäli jompi
 kumpi osoittimista on NULL, hirviö ei kyseisessä tilanteessa tee
 mitään.

Sinun tulee siis asettaa funktio-osoittimiin sopivat hyökkäys- ja
liikkumisfunktiot kun luot hirviöitä. Tehtäväpohja sisältää yhden
hyökkäystoiminnon, mutta voit määritellä muitakin.
