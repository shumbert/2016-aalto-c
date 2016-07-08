title: Laske merkkijonot
task_id: 06_strbasic_2
points: 1


**Tavoite:** Harjoitellaan merkkijonofunktioiden käyttöä (harjoituksen
  voi myös tehdä ilman niitä).

Toteuta funktio `int count_substr(const char *str, const char *sub)`
joka laskee kuinka monta kertaa merkkijono *sub* esiintyy
merkkijonossa *str*, ja palauttaa lukumäärän
paluuarvonaan. Esimerkiksi kun kutsutaan `count_substr("one two one
twotwo three", "two")`, funktion tulisi palauttaa 3, koska "two"
esiintyy ensimmäisessä merkkijonossa 3 kertaa. Huomaa että
esimerkiksi välilyönneillä ei ole mitään erikoisvirkaa merkkijonossa,
ne ovat merkkejä siinä missä muutkin.

**Vihje:** Funktio *strstr* saattaa olla avuksi. Voit myös käsitellä
  merkkijonon osia, kun siirrät (esimerkiksi funktiolle annettavan)
  osoittimen haluttuun kohtaan keskelle merkkijonoa. Tällöin
  esimerkiksi kutsuttu merkkijonofunktio ei käsittele osoitinta
  edeltäviä merkkejä.
