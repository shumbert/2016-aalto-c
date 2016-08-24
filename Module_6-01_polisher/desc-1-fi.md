title: Koodinsiistijä
points: 3
task_id: 01_polisher


**Tavoite:** Palautellaan mieliin merkkijonojen käsittelyä

Toteuta koodinsiistijä C-kielisille ohjelmille, joka poistaa kommentit
ja korjaa rivien sisennykset ohjelmalohkojen mukaisesti.

a) Lue tiedosto
---------------

Toteuta funktio `char *read_file(const char *filename)`, joka lukee
annetun tiedoston dynaamisesti varattuun muistiin. Funktio palauttaa
osoittimen muistilohkoon joka sisältää luetun tiedoston, tai NULL jos
tiedoston avaamisessa sattuu virhe.

b) Poista kommentit
---------------------

Toteuta funktio `char *remove_comments(char *input)`, joka poistaa
C-kommentit ohjelmasta, joka on tallennettu osoitteeseen
*input*. Huomaa että kyseessä on dynaamisesti varattu puskuri, eli se
joka (a)-kohdassa varattiin. Funktio palautaa osoittimen kommenteista
siivottuun ohjelmaan. Voit joko varata uuden muistilohkon muokattua
ohjelmaa varten, tai muokata ohjelmaa suoraan *input* - parametrissa
saamassasi muistissa.

Muistutuksena vielä C:n kommenttisäännöt, jotka sinun pitää siivota:

  * Komenttilohkot, jotka alkavat merkeillä `/*` ja päättyvät
    merkkeihin `*/`. Nämä lohkot voivat olla usean rivin
    pituisia. Sinun tulee poistaa vain nämä lohkot: jos esimerkiksi
    lohkon loppua seuraa rivinvaihto, se jää edelleen ohjelmaan.

  * Rivikommentit, jotka alkavat merkeillä `//` ja päättyvät
    rivinvaihtoon.

Funktiota kutsuva ohjelma on vastuussa vain siitä osoittimesta, jonka
funktio palauttaa. Jos varaat uutta muistia funktion sisällä, sinun
tulee huolehtia tarpeettoman muistin vapauttamisesta.

c) Sisennä koodi
-----------------

(**Huom:** Tämä tehtäväkohta saattaa olla vaikeampi kuin kaksi edellistä,
sekä jotkut seuraavista tehtävistä. Jos tuntuu vaikealta, palauta
kaksi edellistä kohtaa TMC:hen, jotta saat niistä pisteet ja palaa
myöhemmin tähän tehtävään jos aikaa jää)

Toteuta funktio `char *indent(char *input, const char *pad)`, joka
lisää tarvittavat sisennyket *input* - puskurin sisältämään koodiin,
ja palauttaa osoittimen muokattuun ohjelmaan
paluuarvonaan. Sisennystyyli annetaan merkkijonona parametrissa *pad*:
parametri voi sisältää esimerkiksi merkkijonon, jossa on neljä
välilyöntiä, jolla ilmaistaan että sisennyksen tapahtuvat neljän
askelilla. Yhtälailla parametri voi sisältää mitä muuta tahansa:
*pad* - parametrin sisältöä toistetaan rivin alkuun yhtä monta kertaa
kuin sisennystasoja kyseisellä rivillä on. Mikäli rivillä on olemassa
oleva, välimerkkeistä tai tabeja koostuva sisennys, se tulee unohtaa,
ja korjata sisennys *pad* - parametrissa ilmaistun kaltaiseksi.

Voit olettaa että uusi ohjelmalohko alkaa aina aaltosululla `{` ja
loppuu aina aaltosulkuun `}`, ja muita sisennyssääntöjä ei
ole. Sisennystaso kasvaa vasta aaltosulkumerkin jälkeen ja loppuu
ennen lohkon lopettavaa aaltosulkua.

Kuten aiemmassakin kohdassa, mikäli päädyt varaamaan uuden puskurin
muokattavaa merkkijonoa varten, funktion tulee vapauttaa tarpeeton
muisti. Kutsuva funktio pitää huolen vain siitä muistilohkosta, joka
palautetaan paluuarvossa. Kannattaa huomioida myös että sisennetty
ohjelma saattaa tarvita enemmän muistia kuin alkuperäinen.

Alla on esimerkki, jossa sisennysfunktio on ajettu
tehtäväpohjassa olevalle *'src/testfile.c'* - tiedostolle. Esimerkissä
on käytetty neljää välilyöntiä *pad* - parametrissa. Kuten aina,
kannattaa ensi testata ohjelmaasi käyttäen src/main.c:tä, ennenkuin
lähetät sen TMC:n käsiteltäväksi.

    :::c
    // This is a test file
    int main(void) {
        /* comment
        block */
        printf("juu\n");
        while (1)
        {
            // Another comment
            while (2) {
                printf("jaa\n");
            }
        }
    }
