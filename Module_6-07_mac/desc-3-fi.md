title: MAC-otsake
points: 2
task_id: 03_mac


**Tavoite:** Kerrataan binäärioperaatioita.

Matalan tason protokollat pyrkivät tyypillisesti hyödyntämään
tarvittavan tilan tehokkaasti, jotta protokolla aiheuttaisi
mahdollisimman vähän turhaa tietoliikennettä. Tällä kertaa
keskitytään 802.11 MAC-otsakkeeseen (eli WiFi-protokollaan) ja
erityisesti otsakkeen kahteen ensimmäiseen tavuun, eli "Frame
Control" - osioon.

802.11 - otsakeesta löytyy tietoa esimerkiksi [täältä], joskin
vastaava tieto löytyy myös muualtakin webistä. Frame Control -
kentistä löytyy tarkempi kaavia kuvasta numerolla "3.3" kyseisellä
sivulla (skrollaa hieman alaspäin). Tarvitset kaaviokuvaa parsiaksesi
tehtävän vaatimat Frame Control - kentät.

[täältä]: http://mrncciew.com/2014/09/27/cwap-mac-header-frame-control/


a) Parsi otsake
------------------

Toteuta seuraavat funktiot, jotka kukin lukevat ja palauttavat yhden
kentän MAC-otsakkeesta. Parsiaksesi kentät sinun tulee poimia
vastaavat bitit MAC-otsakkeesta, esimerkiksi bittisiirtoja ja muita
binäärioperaatioita käyttäen ja palauttaa lukuarvot seuraavassa
kuvatun mukaisesti.

Kaikki funktiot saavat parametrikseen osoittimen otsakkeen alkuun.

  * `get_proto_version` joka palauttaa protokollaversion (Protocol
    Version) otsakkeesta, eli sen tulee palauttaa arvoja välillä 0 - 3.
  
  * `get_type` joka palauttaa Type - kentän arvon (välillä 0 - 3)

  * `get_subtype` joka palauttaa Subtype - kentän arvon (välillä 0 - 15)

  * `get_to_ds`, `get_from_ds`, `get_retry`, `get_more_data` jotka
    palauttavat kyseisten lipukkeiden arvon otsakkeessa. Funktiot
    voivat palauttaa jonkun nollasta poikkeavan arvon mikäli kyseinen
    bitti on asetettu, tai 0 jos kyseinen bitti ei ole asetettu.
	

b) Kirjoita otsake
----------------

Toteuta seuraavat funktiot, joiden avulla tuotetaan otsake (tai osa siitä):

  * `set_proto_version` joka asettaa Protocol Version kentän
    *version* - parametrin ilmaisemalla tavalla.

  * `set_type` joka asettaa Type - kentän funktion parametrissa ilmaistulla
    tavalla.

  * `set_subtype` joka asettaa Subtype - kentän funktion parametrissa
    ilmaistulla tavalla.

  * `set_to_ds`, `set_from_ds`, `set_retry`, `set_more_data`, jotka
    asettavat kyseiset lipukebitit joko päälle tai pois sen
    perusteella onko parametrina annettu 0 (pois päältä) tai nollasta
    poikkeava arvo (päällä).

Kutakin funktiota kutsuttaessa vain kyseinen osa otsakkeesta saa
muuttua, ja muiden kenttien sisällön tulee säilyä ennallaan.
