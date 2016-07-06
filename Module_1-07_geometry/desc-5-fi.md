title: Kertotaulu
task_id: 07-geometry-1
points: 1


**Tavoite:** Totuttele sisäisiin silmukoihin ja tulostuksen muotoiluun

Toteuta funktio *multi_table* joka tulostaa määrätyn kokoisen
kertotaulun taulukkomuodossa. Kertotaulun vaakakoko annetaan
parametrissa *xsize* ja pystykoko parametrissa *ysize*. Kertotaulun
vasen yläkulma alkaa luvusta 1. Kunkin luvun tulee käyttää neljän
merkin verran tilaa ruudulta, ja numerot tulee tasata
oikealle. Jokaisen rivin (mukaanlukien viimeinen rivi) tulee päättyä
rivinvaihtoon ('\n'). Esimerkiksi funktiokutsun *multi_table(4,5)*
tulisi saada aikaan seuraavanlainen tuloste:

<pre>
   1   2   3   4
   2   4   6   8
   3   6   9  12
   4   8  12  16
   5  10  15  20</pre>
