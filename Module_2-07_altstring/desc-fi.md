title: Uusi merkkijono
task_id: 07_altstring
points: 4


**Tavoite:** Kuinka merkkijonofunktiot on toteutettu? Tämä harjoitus
  saattaa valottaa asiaa.


Tässä tehtävässä luomme uudenlaisen merkkijonon, joka ei lopukkaan
'\0' - merkkiin, kuten normaalit merkkijonot, vaan loppumerkkinä
käytetäänkin risuaitaa ('#'). Tästä johtuen joudumme toteuttamaan
perinteiset merkkijonofunktiot uudestaan.

Huomaa, että *<string.h>*:ssa määritellyt merkkijonofunktiot **eivät
toimi tässä tehtävässä**, koska '\0' - merkki ei enää toimimaan
merkkijonon lopetusmerkkinä.


a) Tulosta merkkijono
------------------

Toteuta funktio `void es_print(const char *s)` joka tulostaa annetun
uudentyyppisen merkkijonon ruudulle. Merkkijono loppuu siis '#' -
merkkiin, jota ei pidä tulostaa. Esimerkiksi seuraavanlainen
merkkijono: 

    :::c
    char *str = "Auto ajoi#kilparataa";

tulostuu näin:

<pre>
Auto ajoi</pre>


b) Merkkijonon pituus
-------------------

Toteuta funktio `unsigned int es_length(const char *s)` joka palauttaa
merkkijonon *s* merkkien lukumäärän. Merkkijonon päättävää risuaitaa
ei lasketa mukaan.


c) Merkkijonon kopiointi
-----------------

Toteuta funktio `int es_copy(char *dst, const char *src)` joka kopioi
merkkijonon *src* paikkaan *dst*. Funktio palauttaa kopioitujen
merkkien lukumäärän, poislukien merkkijonon päättävä '#' -
merkki. Funktion tulee kopioida lähde merkkijono vain ensimmäiseen
'#' - merkkiin asti, ja kopioinnin jälkeen myös *dst*:een kopioidun
kohdemerkkijonon tulee päättyä risuaitaan. Voit käyttää aiemmin
toteuttamaasi *es_print* - funktiota testaamaan toimiiko kopiointi
oikein.


d) Merkkijonon pilkkominen
----------------------

Toteuta funktio `char *es_token(char *s, char c)`, joka katkaisee
merkkijonon *s* kun ensimmäinen parametrin *c* esittämä merkki tulee
vastaan. Kyseinen kohta merkkijonosta muutetaan siis lopetusmerkiksi,
eli risuaidaksi. Funktio palauttaa osoittimen korvattua merkkia
**seuraavaan merkkiin**, mistä alkuperäinen merkkijono jatkuisi. Näin
ollen, kun funktiota kutsutaan useaan kertaan, käyttäen paluuarvoa
aina uudestaan parametrina osoittamaan jäljellä olevan merkkijonon
alkuun, voidaan alkuperäinen merkkijono pilkkoa useaksi osaksi.

Mikäli *c*:n osoittamaa merkkiä ei löydy, tulee funktion palauttaa
NULL (joka määritelty `<stddef.h>` - otsakkeessa). Huomaa myös että
funktio muokkaa alkuperäistä merkkijonoa, eikä siitä esimerkiksi
oteta kopiota.

Esimerkiksi kun kutsutaan `es_token(str, ',')` tällaiselle merkkijonolle:

    :::c
    char *str = "aaa,bbb,ccc#ddd,eee";

merkkijono muuttuu seuraavanlaiseksi:

<pre>
"aaa#bbb,ccc#ddd,eee"</pre>

ja funktio palauttaa osoittimen kohtaan, josta "bbb" alkaa. Huomaa
myös että '#'-merkin jälkeisiä pilkkumerkkejä ei vaihdeta, koska
funktio lopettaa '#'-merkkiin (ellei parametriksi anneta osoitinta
kohtaan, josta "ddd" alkaa).
