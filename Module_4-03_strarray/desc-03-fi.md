title: Merkkijonotaulukko
task_id: 03_strarray
points: 4


**Tavoite:** Harjoittele dynaamisesti varattavan taulukon käyttöä
  dynaamisesti varattavien merkkijonojen kanssa

Tässä harjoituksessa käsitellään taulukkoa, jossa on osoittimia
merkkijonoihin, jotka on varattu dynaamisesti. Taulukon viimeinen
alkio merkitään NULL-osoittimella, toisin sanoen tyhjässä taulukossa on
siinäkin yksi alkio, nimittäin kyseinen NULL-osoitin.

Sinun tulee toteuttaa seuraavat funktiot:


a) Alusta taulukko
----------------------

Toteuta funktio *init_array*, joka varaa tilan ja alustaa
merkkijonotaulukon siten, että siinä on ensimmäisenä alkiona
NULL-osoitin.

Toteuta lisäksi funktio *free_strings* joka vapauttaa taulukkoon
tallennettujen merkkijonojen käyttämän tilan, sekä osoitintaulukon
itsessään. Tässä tehtäväkohdassa merkkijonoja ei vielä ole taulukkoon
tallennettu, mutta kannatta huomioida funktiota toteuttaessa, että
seuraavissa kohdissa taulukkoon tulee myös merkkijonoja.

Tehtävän testit käyttävät *free_strings* - funktiota tilan
vapauttamiseen, joten se kannattaa toteuttaa heti alussa, koska muuten
muistivuodoista johtuvat Valgrind-virheet estävät tehtävien läpäisyn.


b) Lisää merkkijono
----------------

Toteuta funktio *add_string* joka lisää annetun merkkijonon
taulukkoon. Huomaa että parametrina tuleva merkkijono on `const char
*` - tyypiä, mutta taulukon jäsenten tulee olla muokattavissa. Siksi
pelkkä osoittimen kopiointi ei riitä, vaan sinun tulee kopioida koko
merkkijono sille varattuun tilaan. Kun muutat taulukon kokoa, muista
että sen lopusta tulee aina löytyä NULL-osoitin.


c) Muuta pieniksi
---------------------

Toteuta funktio *make_lower* joka muuntaa kaikki taulukon
merkkijonoissa olevat kirjainmerkit pieniksi kirjaimiksi. Tässähän
voit käyttää hyväksi *[tolower]* - funktiota, joka muuntaa annetun
merkin.

[tolower]: http://linux.die.net/man/3/tolower


d) Järjestä taulukko
----------------

Toteuta funktio *sort_strings* joka järjestää taulukossa olevat
merkkijonot aakkosjärjestykseen. Voit olettaa että *[strcmp]* -
funktiota tuottaa oikean järjestyksen. Muista että *strcmp* palauttaa
sekä pienempiä että suurempia arvoja kuin 0, riippuen merkkijonojen
keskinäisestä järjestyksestä: kun vertailuoperaatio on negatiiivinen,
ensimmäisen merkkijonon tulee sijoittua ennen jälkimmäistä (ja
päinvastoin).

[strcmp]: http://linux.die.net/man/3/strcmp

Olet myös harjoitellut alkioiden järjestämistä kierroksella 2. Voit
todennäköisesti käyttää jossain määrin hyväksi silloin toteuttamaasi
algoritmia.
