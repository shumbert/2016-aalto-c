title: Järjestely
task_id: 04_sort
points: 1


**Tavoite:** Lisää taulukkoharjoittelua, tällä kertaa alkoiden
  järjestelyä.

Toteuta funktio `void sort(int *start, int size)` joka järjestää
annetussa taulukossa (*start*) olevat kokonaisluvut nousevaan
suuruusjärjestykseen (pienimmästä suurimpaan). Voit käyttää
esimerkiksi *valintalajittelua* (selection sort): aloita etsimällä
taulukon pienin alkio, ja vaihda sen paikkaa taulukon ensimmäisen
alkion kanssa. Sitten tarkastelen lopputaulukkoa toisesta alkiosta
eteenpäin, ja jälleen vaihdan lopputaulukon pienimmän alkion taulukon
toisen alkion kanssa. Näin jatkat kolmanteen ja neljänteen alkioon,
kunnes koko taulukko on käyty läpi, jolloin taulukon alkiot ovay
oikeassa järjestyksessä. Testaa funktiota erilaisilla ja erikokoisilla
kokonaislukutaulukoilla,
