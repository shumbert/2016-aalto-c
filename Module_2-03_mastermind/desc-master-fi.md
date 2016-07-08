title: Mastermind
task_id: 03_mastermind
points: 1


**Tavoite:** Lisää harjoitusta taulukkojen käsittelystä.


Toteuta funktio `void mastermind(const int *solution, const int
*guess, char *result, unsigned int len)` joka vertaa
kokonaislukutaulukkoa *guess* taulukkoon *solution*. Molemmat taulukot
sisältävät *len* kokonaislukua välillä 0 ja 9. Funktio tuottaa
merkkitaulukon *result*, jossa on niin ikään *len* merkkiä
seuraavaasti:

  * Jos taulukoissa *solution* ja *guess* on sama numero N:nnessä
    taulukon paikassa, kyseinen paikka *result* - taulukossa merkataan
    '+' - merkillä.

  * Jos taulukossa *guess* on sellainen numero N:nnessä paikassa, joka
    sijaitsee jossain toisessa kohdassa *solution* - taulukossa,
    kyseinen paikka *result* - taulukossa asetetaan merkiksi '*'.

  * Jos N:s paikka taulukossa *guess* sisältää numeron, jota ei
    esiinny lainkaan taulukossa *solution*, kyseinen paikka *result* -
    taulukossa merkataan merkillä '-'.

Huomaa että taulukkoja *solution* ja *guess* ei kuulu muokata
funktiossa, kun taas taulukko *result* on sellainen jonka funktio
kirjoittaa.

Esimerkiksi kun *len* on 6, *solution* on { 2, 6, 6, 3, 5, 3} ja
*guess* on {4, 5, 6, 1, 8, 9}, funktio asettaa *result* taulun
sisältämään arvot {'-', '*', '+', '-', '-', '-'}.

*main*-funktio tiedostossa main.c toteuttaa yksinkertaisen
 [Mastermind]-pelin, jolla voi testata toteutustasi.

[Mastermind]: http://en.wikipedia.org/wiki/Mastermind_(board_game)
