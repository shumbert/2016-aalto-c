title: Laskin
task_id: 05-calc-2
points: 1


**Tavoite:** Harjoittele ehtorakenteita yhdessä syötteen ja tulosteen
  kanssa.

Toteuta funktio *simple_math*, joka kysyy kolmiosaisen syötteen
käyttäjältä: numeron, operaattorin, ja numeron. Operaattorin tulee
olla yksi seuraavista merkeistä: '+', '-', '*' tai '/'. Jos jotain
muuta merkkiä yritetään käyttää operaattorina, funktion tulee tulostaa
merkkijono `ERR`. Numerot ovat **liukulukuja**.

Mikäli käyttäjän syöte ei noudata oikeanlaista
numero-operaattori-numero - rakennetta, funktion tulee niinikään
tulostaa `ERR`. Kun hyväksytty syöte on annettu, funktion tulee
tulostaa annetun laskutoimituksen tulos **yhden desimaalin
tarkkuudella**.

Seuraavassa esimerkki ohjelman mahdollisesta syötteestä ja tulosteesta:

<pre>
<font color="red">8 - 2</font>
6.0

<font color="red">8.3 / 5.1</font>
1.6

<font color="red">-3.456 - 2.31</font>
-5.8
</pre>

**Vinkki:** Kiinnitä huomiota merkkivakioiden käyttöön, ja siihen
  kuinka yksittäisiä merkkejä käytetään esimerkiksi *scanf* - funktion
  yhteydessä.
