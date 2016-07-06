title: ASCII-taulu
task_id: 08-characters-1
points: 1


**Tavoite:** Perehdytään ASCII-taulukkoon printf-tulosteiden eri
  muotoilumääreiden avulla.

Toteuta funktio `void ascii_chart(char min, char max)` joka tulostaa
annetun osan ASCII-taulukosta. Funktion tulee käydä läpi luvut
*min*:stä *max*:iin, sekä jokaiselle lukuarvolle tulostaa seuraavasti:

  * kolmen merkkiä leveä kenttä, joka tulostaa kyseisen luvun
    desimaalimuodossa. Jos numeron on alle 100, se tulee tasata
    oikealle.

  * yksi välimerkki, jonka jälkeen neljä merkkiä leveä kenttä johon
    tulostetaan sama lukuarvo heksadesimaalimuodossa. Kukin heksaluku
    vie kaksi merkkiä, ja sen eteen tulee tulostaa merkit '0x'. Mikäli
    heksaluku vie vain yhden merkin, eteen tulee sijoittaa '0' siten
    jokaisessa luvussa on aina kaksi merkkiä.

  * yksi välimerkki, jonka perään kyseistä lukua vastaava
    ASCII-merkki. Tämä vie aina vain yhden merkin verran tilaa. **Jotkut
    merkkiarvot eivät ole tulostettavissa**, eli niille ei ole
    määritelty näkyvää tulostetta. Tällaisten merkkien tilalle tulee
    tulostaa kysymysmerkki ('?'). Voi käyttää kirjastofunktiota `int
    isprint(int c)` ([man-sivu][1]) selvittääksesi onko merkki *c*
    tulostettavissa vai ei. Jos funktio palauttaa 0, merkki ei ole
    tulostettavissa.

  * Lopuksi tulosta yksi tabulaattorimerkki ('\t') ennen seuraavaa
    merkkiarvoa, paitsi jos rivillä on jo neljän luvun
    tiedot. Neljännelle luvulle sinun tulee vaihtaa riviä, eli
    tulostaa tabulaattorimerkin sijaan rivinvaihto ('\n')

[1]: http://linux.die.net/man/3/isprint "isprint manual page"

Sinun tulee siis käydä läpi edellä mainitulla tavalla kaikki lukuarvot
annetulla numerovälillä (sisältäen myös arvon *max*). Esimerkiksi
funktiokutsun *ascii_chart(28,38)* tulisi aiheuttaa seuraavanlainen
tuloste:

<pre>
 28 0x1c ?	 29 0x1d ?	 30 0x1e ?	 31 0x1f ?
 32 0x20  	 33 0x21 !	 34 0x22 "	 35 0x23 #
 36 0x24 $	 37 0x25 %	 38 0x26 &
</pre>
