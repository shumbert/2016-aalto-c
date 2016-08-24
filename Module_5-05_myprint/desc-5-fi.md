title: Kokonaislukutulostin
task_id: 05_myprint
points: 1


**Tavoite**: Harjoitellaan vaihtuvan mittaisten parametrilistojen
  käyttöä.

Toteuta funktio **myprint** joka tulostaa vaihtuvan määrän
kokonaislukuja standarditulostevirtaan noudatten parametrinaan
saamaansa muotoilumäärittelyä. Funktio voi siis saada vaihtuvan määrän
parametreja: **ensimmäinen parametri on aina (muuttumaton)
merkkijono**, joka määrittelee tulosteen ulkoasun, kuten *printf*:kin
tekee. Sitä seuraa kokonaislukuja (int), joiden määrä riippuu
muotoilumerkkijonosta, ja siinä olevien '&' - merkkien
määrästä. Funktiossamme '&' toimii muotoilumääreenä, ja se tulee
korvata kyseisellä kohdalla parametrilistassa olevalla
kokonaisluvulla. Toteutamme siis yksinkertaistetun version
*printf*-funktiosta. Koska tulostamme vain kokonaislukuja, mitään
lisämääreitä korvattavaan merkkiin ei tarvita.

Esimerkiksi tämä on yksi hyväksyttävä tapa kutsua funktiota:
`myprint("Number one: &, number two: &\n", 120, 1345);`

**Funktion tulee palauttaa kokonaisluku**, joka kertoo kuinka monta
  muotoilumäärettä funktiossa oli.

Tässä tehtävässä C-lähdetiedostot *myprint.c* ja *myprint.h* ovat
kokonaan tyhjiä, ja sinun tulee täyttää ne kokonaan itse. Kannattaa
siis lukea tehtävänanto ja mukana tuleva main-funktio tarkkaan, jotta
funktion nimi ja muut määrittelyt menevät oikein.

Jos toteutuksesi toimii oikein, oletuksena mukana tuleva main-funktio
tulostaa seuraavaa:

<pre>
Hello!
Number: 5
Number one: 120, number two: 1345
Three numbers: 12 444 5555
I just printed 3 integers</pre>

**Vinkki:** Muistutuksena, että *[strchr]* palauttaa osoittimen
  seuraavaan kohtaan merkkijonossa, jossa annettu merkki
  esiintyy. *[fputc]*:n avulla voit tulostaa yhden merkin kerrallaan,
  myös standarditulostevirtaan. Näistä funktioista saattaa olla hyötyä.

[strchr]: http://linux.die.net/man/3/strchr
[fputc]: http://linux.die.net/man/3/fputc
