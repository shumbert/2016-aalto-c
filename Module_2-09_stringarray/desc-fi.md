title: Merkkijonotaulukko
task_id: 09_stringarray
points: 2


**Tavoite:** Kurkistetaan taulukkoihin, joiden jäsenet ovat
  merkkijonoja (eli taulukot ovat käytännössä kaksiulotteisia)

Myös merkkijonoja voi käyttää taulukoissa. Koska merkkijono on
merkeistä muodostuva taulukko, merkkijonotaulukko on taulukko
merkkijonoja, joista kukin on taulukko merkkejä. Tässä tehtävässä
käsitellään merkkijonotaulukkoa, jossa taulukon loppu ilmaistaan
NULL-osoittimella.


a) Tulosta merkkijonotaulukko
---------------------

Toteuta funktio `void print_strarray(char *array[])`, joka tulostaa
jokaisen merkkijonon taulukossa *array* omalle rivilleen (eli jokaisen
merkkijonon lopussa on rivinvaihto). Funktion parametrin esitysmuoto
saattaa näyttää uudenlaiselta: Parametri *array* esittää taulukkoa,
jonka kukin alkio on tyyppiä `char *`. Käytät siis kutakin taulukon
alkiota kuten merkkijonoa, esimerkiksi osana lausekkeita tai
printf-funktion parametrinä. Muista että taulukon loppu merkitään
NULL-osoittimella.


b) Muunna merkkijono taulukoksi
----------------------------

Toteuta funktio `void str_to_strarray(char* string, char** arr)` joka
muuntaa parametrinaan saamansa merkkijonon *string* taulukoksi
merkkijonoja (muuttujaan *arr*). Alkuperäinen merkkijono voi sisältää
useita välilyönnillä erotettuja sanoja, ja funktion tehtävänä jakaa
merkkijono siten, että kukin välilyönnillä erotettu sana muodostaa
oman alkionsa taulukossa. Muista erottelun jälkeen kunkin merkkijonon
tulee päättyä nollamerkkiin, sekä lisäksi taulukon tulee päättyä
NULL-osoittimeen.

Kaksiulotteisia taulukoita ei ole vielä käsitelty, mutta kun `arr[i]`
esittää merkkijonoa edellä kuvatun kaltaisessa taulukossa, pääset
käsiksi kyseisen merkkijonon j:nteen merkkiin merkinnällä `arr[i][j]`,
joko merkin kirjoittamista tai lukemista varten.
