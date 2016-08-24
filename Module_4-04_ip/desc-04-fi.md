title: IP-otsake
task_id: 04_ip
points: 4


**Tavoite:** Harjoittele binäärioperaatioita

IP-protokollaa käytetään miltei kaikessa tämän päivän
Internet-kommunikaatiossa. [Wikipediassa] on tiivis perustietopaketti
IP-protokollasta ja sen ominaisuuksista. Internetissä tieto kulkee
paketeissa, joiden alussa on 20 tavua pitkä *IP-otsake*. [Otsakkeen
rakenne] on dokumentoitu wikipedia-artikkelissa. Otsakkeessa on
haluttu pakata tarvittava tieto mahdollisimman tiiviseen tilaan
kommunikoinnin tehostamiseksi, joten 16- ja 8-bittisten kenttien
lisäksi otsakkeessa on kenttiä jotka vievät tai yhden tai muutaman
bitin.

[Wikipediassa]: http://en.wikipedia.org/wiki/IPv4
[Otsakkeen rakenne]: http://en.wikipedia.org/wiki/IPv4#Header

Tehtävänäsi on toteuttaa funktio, joka rakentavat *struct
ipHeader*:ssa annetuista otsaketiedoista 20 tavun mittaisen
pakettiotsakkeen, ja toisaalta funktio, joka purkaa pakettiotsakkeen
helpommin käsiteltävään edellä mainittuun C-tietorakenteeseen. Koska
osa otsakkeen kentistä vie tilaa vain muutaman bitin, joudut
soveltamaan binäärioperaatioita osaan otsakekentistä.

Et voi vain kopioida tietorakennetta otsakkeeksi sellaisenaan, koska
bittikentät eivät siirtyisi oikein. Lisäksi C saattaa lisätä
tietorakenteen kenttien väleihin tyhjiä alueita (padding), joten
varsinainen tietorakenne vie enemmän kuin 20 tavua tilaa muistista.

Wikipedia-artikkelissä olevaa IP-otsaketta esittävää diagrammia
luetaan seuraavasti: kukin rivi esittää 4 tavun (eli oktetin) alueen
otsakkeesta. Kuvan vasemmassa laidassa ja ylälaidassa lasketaan näitä
oktetteja, jotka yhteenlaskemalla tiedät kuinka monta tavua otsakkeen
alkuun pitäisi lisätä jotta pääset käsittelemään kyseistä kohtaa
otsakkeessa. Esimerkiksi *protocol*-kenttä löytyy 9:n tavun
kohdalta. Jos tavuista muodostettu taulukko *buffer* esittää
otsaketta, saat *protocol*-kentän lausekkella `buffer[9]`.

Mukana tulevat tiedostot sisältävät valmiiksi toteutetut funktiot
*printIp* ja *hexdump*, joita voit käyttää *main.c* - tiedostossa
testataksesi toteutustasi.

**Lisävinkkejä:**

  * Esimerkiksi alussa oleva **Version** - kenttä on vain 4 bittiä
    pitkä. Se tarkoittaa että versio voi saada pelkästään arvoja 0:sta
    15:een. Pitäisi siis miettiä miten tavun yläpäähän puristetut
    bitit saadaan konvertoitua normaaliksi C-kokonaisluvuksi, joka
    esittää lukua 0:n ja 15:n välillä.

  * **IHL-kenttä** esittää IP-otsakkeen kokonaispituutta koodattuna
    neljään bittiin, mutta kenttä esittää pituuden neljän tavun
    yksikköinä. C-rakenteessa pituus esitetään kuitenkin
    tavuina. Esimerkiksi IHL-kentässä oleva bittiyhdistelmä 0110 (eli
    desimaalina 6) tarkoittaa siis otsakkeen pituutena 6*4 = 24 tavua.

  * Kannattaa kiinnittää huomiota C:n **[laskujärjestykseen]**
    binäärioperaatioiden osalta. Bittisiirto-operaatiot `<<` ja `>>`
    lasketaan esimerkiksi aritmeettisten operaattoreiden (esim. '+' ja
    '-') jälkeen. Käytä siis sulkeita silloin kun niitä tarvitaan.

[laskujärjestykseen]: http://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B#Operator_precedence

  * Tietoliikenneprotokollissa 16-bittiset numerot koodataan
    ns. **big-endian - tavujärjestykseen**. Tämä tarkoittaa, että kun
    lukua ajatellaan kahden tavun yhdistelmänä, lukualueen eniten
    merkitsevä tavu sijoitetaan muistiin (ja edelleen
    tietoliikennepakettiin) ensiksi, ja vähemmän merkitsevä tavu sen
    jälkeen. Joudut sijoittamaan tällaiset luvut otsakkeeseen tavu
    kerrallaan, koska useat järjestelmät (mm. Intel-pohjaiset)
    käyttävät sisäisesti päinvastaista tavujärjestystä, eli suora
    kopiointi tuottaa väärän tuloksen.
