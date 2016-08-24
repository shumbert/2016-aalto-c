title: Base64
task_id: 03_base64
points: 2


**Tavoite**: Harjoitusta tiedostoon lukuun ja kirjoitukseen, sekä
  bittioperaatioita.

**HUOM**: Tämä saattaa olla kierroksen vaikein tehtävä. Jos olet
  epävarma siitä miten tehtävää kannattaa lähteä ratkaisemaan,
  kannattaa ehkä katsoa ensin muita tehtäviä, ja palata sitten tähän.

Base64-koodausta käytetään kun binäärisisältöä pitää muuttaa
tekstimuotoon, esimerkiksi tiedoston sisällyttämiseksi vaikkapa
sähköpostiviestiin. Tässä harjoituksessa sinun tulee toteuttaa
funktiot **to_base64 (a)**, joka lukee tiedoston yhdestä tiedostosta
ja kirjoittaa sen toiseen tiedostoon Base64-koodatussa muodossa; sekä
**from_base64 (b)**, joka tekee käänteisen operaation, eli lukee
Base64-koodatun tiedoston ja kirjoittaa sen alkuperäisessä muodossaan
tiedostoon. Toisin sanoen, kun funktiot toimivat oikein, ja niitä
kutsutaan peräkkäin, lopputulokseksi pitäisi tulla täsmälleen sama
tiedosto kuin mistä lähdettiin liikkeelle.

Base64-koodauksen idea on, että lähteenä oleva tiedosto tai merkkijono
muutetaan 6-bittisiin yksiköihin, jotka esitetään tulostettavilla
merkeillä (A-Z, a-z, 0-9, +, /). Tämä voidaan tehdä esimerkiksi niin,
että otetaan lähteestä kolme 8:n bitin numeroa (eli yhteensä 24 bittiä)
ja muutetaan ne neljäksi 6-bitin numeroksi (edelleen 24
bittiä). Bittikombinaatio pysyy siis täsmälleen samana, mutta se
jaetaan eri "tavuihin" toisella tavalla. Kukin 6-bittinen luku
muutetaan kirjainmerkiksi [tämän taulukon] avulla. Samalla
[Wikipedia]-sivulla on myös hyödyllisiä diagrammeja, jotka
havainnollistavat koodauksen ideaa.

[tämän taulukon]: http://en.wikipedia.org/wiki/Base64#Examples
[Wikipedia]: http://en.wikipedia.org/wiki/Base64

On mahdollista, että lähdetiedoston pituus ei ole kolmella
jaollinen. Tällöin puuttuvat bitit oletetaan 0:ksi, ja kokonaan
käyttämättömien 6-bittisten merkkien paikalle merkataan täytemerkiksi
'='. [Wikipedia] antaa tästäkin esimerkin.

Wikipedia-sivulla on myös muuta taustaa ja lisätietoa
Base64-koodauksesta. Algoritmista on olemassa erilaisia variaatioita,
mutta noudatamme alkuperäistä, RFC 1421:ssä määriteltyä formaattia,
eli seuraavasti:

  * **Kunkin koodatun rivin tulee olla 64 merkkiä pitkä**, paitsi
    viimeisen rivin, joka voi olla lyhyempi. Tässä tehtävässä käytämme
    yksinkertaista Unix-rivinvaihtoa ('\n'), emmekä "CRLF"-yhdistelmää
    monien muiden toteutusten tapaan. Viimeisellä rivillä **ei ole**
    rivinvaihtomerkkiä.

  * **Kaikkien rivien pituuden tulee olla 4:llä jaollinen**. Tarpeen
    mukaan viimeisen rivin loppuun täytyy lisätä **täytemerkkejä**
    ('='), jotta tämä ehto täyttyy.

Molemmat funktiot palauttavat paluuarvonaan tiedostosta luettujen
merkkien määrän, tai -1, mikäli tiedoston käsittelyssä tapahtui virhe.

**Lisävinkkejä to_base64 - toteutukseen:**

  * On suositeltavaa, että aloitat testaamisen lyhyillä
    lähdetiedostoilla ja yksinkertaisilla merkkijonoilla, kuten
    esimerkiksi "Man", joka annetaan Wikipedian esimerkissä. Sen
    jälkeen kasvatat testitiedoston pituutta asteittain ja tarkistat
    että saat odotetun lopputuloksen. Vasta kun olet itse vakuuttunut
    algoritmin toimivuudesta, se kannattaa lähettää TMC:lle.

  * Aloita vaikkapa tarvittavien binäärioperaatioiden
    toteuttamisesta. Niiden hahmotteluun kynä ja paperi saattavat olla
    hyödyllisiä. Tarvitset ainakin bittien
    siirto-operaattoria. Binäärilaskutoimitus ottaa siis sisään kolme
    8-bittistä (char) arvoa, ja sen tulisi tuottaa neljä 6-bittistä arvoa
    (esimerkiksi char, jossa kaksi ylintä bittiä ovat aina 0).

  * Kun olet saanut neljä 6-bittistä lukuarvoa, ne tulee muuntaa
    tulostettavaksi ASCII-merkiksi. Tehtäväpohjan mukana tulee
    merkkijono (eli merkkitaulukko) '*encoding*', jossa on kaikki 64
    Base64-merkkiä ovat oikeassa järjestyksessä. Tästä taulukosta on
    varmastikin hyötyä.

  * Vasta kun bittien pyörittely, ja muunnos Base64-merkeiksi näyttää
    toimivan, lisää lopuksi tarvittava täytemerkkien käsittely ja
    tulosteen jako 64:n merkin riveihin.

Kuten aina, kannattaa käyttää *src/main.c* - tiedostoa testaamiseen,
ennenkuin lähetät ratkaisusi TMC:hen.
