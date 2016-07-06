title: Kolmio
task_id: 07-geometry-2
points: 1


**Tavoite**: Lisää harjoittelua sisäkkäisillä silmukoilla, sekä
  tutustumista ehtolausekkeisiin.


Toteuta funktio *draw_triangle* joka piirtää neliömäisen
ASCII-laatikon, jonka sisällä on kolmio.

Laatikon tulee olla *size* merkkiä levä ja korkea, ja se tulee jakaa
vasemman alakulman ja oikean yläkulman välillä siten, että vasemman
yläkulman puoli täytetään merkeillä '.' (piste) ja oikean alakulman
puoli merkeillä '#' (risuaita). Ensimmäisellä rivillä tulee olla yksi
risuaita oikeassa yläkulmassa ja viimeisen rivin tulee täyttyä
risuaidoista. Kaikkien rivien (mukaanlukien viimeinen rivi) tulee
päättyä rivinvaihtomerkkiin ('\n').

Kun kutsutaan *draw_triangle(5)*, tulisi tulla tällainen tuloste:

<pre>
....#
...##
..###
.####
#####
</pre>
