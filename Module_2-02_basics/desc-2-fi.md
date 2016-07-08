title: Taulukkosumma
task_id: 02_basics_2
points: 1


**Tavoite:** Harjoittele taulukon käyttöä

Toteuta funktio `int array_sum(int *array, int count)`, joka laskee
taulukon *array* alkioiden summan ja palauttaa sen
paluuarvonaan. Taulukossa olevien numeroiden määrä kerrotaan
parametrilla *count*.

Esimerkiksi seuraavan ohjelman tulisi asettaa *ret* 1110:ksi.

    :::c
    int valarray[] = { 10, 100, 1000 };
    int ret = array_sum(valarray, 3);
