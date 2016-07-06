title: Salaviesti
task_id: 08-characters-2
points: 1


**Tavoite:** Lisää merkkien pyörittelyä, jotta ASCII-merkistön
  toiminta tulee tutuksi. Samalla pientä johdattelua merkkijonoihin
  (jotka tulevat seuraavassa modulissa).

Toteuta funktio `void secret_msg(int msg)` joka purkaa ja salaa
annetun viestin soveltaen yksinkertaista algoritmia. Salaviestit on
numeroitu kokonaisluvulla, joka annetaan funktion parametrilla
*msg*.

Voit hakea salaviestin merkkejä yksi kerrallaan käyttäen
funktiota `char get_character(int msg, unsigned int cc)`, joka on
annettuna harjoituspohjassa (kyseinen funktio on toteutettu käyttäen
taulukoita ja merkkijonoja, jotka tulevat vastaan vasta seuraavassa
modulissa.). Parametri *msg* kertoo mistä viestistä on
kysymys, ja on sama arvo, jonka olet saanut *secret_msg* - kutsun
mukana. *cc* on haettavan merkin järjestysluku. Funktio palauttaa
paluuarvonaan kyseisen merkin.

Viestin sisältämät merkit on numeroitu nollasta alkaen. Sinun tulee
kutsua *get_character* - funktiota kullekin viestille useamman kerran,
kasvattaen aina merkkilaskuria, kunnes funktio palauttaa 0, mikä
tarkoittaa että viesti on lopussa.

Kun luet merkkejä, sinun tulee purkaa salaus ja **tulostaa kukin
merkki ruudulle**, kunnes 0-merkki tulee vastaan. 0-merkkiä ei
tulosteta.

Salauksenpurku-algoritmi on seuraavanlainen: vähennät saamasi
merkkiarvon desimaaliluvusta 158, eli 158 - *m*, missä *m* on
*get_character* - funktiolta saamasi merkkiarvo. Tämän
laskutoimituksen tulos tulostetaan siis merkkinä (ei esimerkiksi
desimaalilukuna).

Voit testata funktiota viesteillä, jotka on numeroitu 0:ksi ja 1:ksi
*src/main.c*:ssä. Jos funktio toimii, näiden salaviestien tulisi
muuntua lyhyiksi englanninkielisiksi lauseiksi. TMC-tarkistuksissa
käytetään myös muita merkkijonoja.
