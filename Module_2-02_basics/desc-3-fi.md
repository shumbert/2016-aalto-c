title: Taulukon lukija
task_id: 02_basics_3
points: 1


**Tavoite:** Lisäharjoittelua taulukon käytöstä yhdessä *scanf*:n kanssa.

Toteuta funktio `int array_reader(int *vals, int n)` joka lukee
käyttäjältä kokonaislukuja *vals*-muuttujan osoittamaan
taulukkoon. Taulukon tarvitsema tila on jo valmiiksi varattu, ja
parametri *n* kertoo taulukon maksimikoon. Numerot voi lukea
*scanf*-funktiota käyttäen siten että niiden välissä on rivivaihto tai
väli, tai mikä tahansa ns. whitespace-merkki, joka toimii
oletusarvoisesti scanf-syötteen erottimena.

Mikäli käyttäjä ei syötä numeroa (mikä nähdään scanf-paluuarvosta),
taulukko ja funktion suoritus loppuu. Funktion tulee palauttaa
taulukon lopullinen koko, joka siis voi olla pienempi kuin *n*, mutta
ei koskaan suurempi.

Alla esimerkki siitä kuinka funktiota voi testata:

    :::c
    int array[10];
    int n = array_reader(array, 10);
    printf("%d numbers read\n", n);
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }

Esimerkiksi seuraava syöte lukee taulukkoon neljä numeroa, ja lopettaa
sen jälkeen, kun viides arvo on viivamerkki.

<pre>
<font color="red">5 8 2 7 -</font></pre>
