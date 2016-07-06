title: Pallo
task_id: 07-geometry-3
points: 1


**Tavoite:** Jatketaan edelleen samalla teemalla, mutta tällä kertaa
  tulosteen määrittelyyn tarvitaan erillistä funktiota.

Toteuta funktio `void draw_ball(unsigned int radius)` joka tulostaa
ASCII-neliön, jonka sisällä tähtimerkeistä ('*') muodostettu täytetty
ympyrä.

Laatikon pituus ja leveus on **(2 * radius + 1)**, missä *radius* on
funktion saama parametri. Toisinsanoen laatikko on juuri riittävän suuri
sisältääkseen ympyrän, jonka säde on *radius* - parametrissa annettu
arvo.

Tehtäväpohjassa on apufunktio *distance* jota voit käytää hyväksi
ympyrän piirtämiseen. Funktio palauttaa koordinaattien (x,y)
etäisyyden origosta, eli kun **distance(x,y) <= radius**, koordinaatti
(x,y) on ympyrän sisällä, kun ympyrän keskipiste on (0,0).

Mikäli ruutu on ympyrän sisällä, tulosta merkki '*'. Mikäli ruutu on
ympyrän ulkopuolella, tulosta merkki '.'.

Esimerkiksi kun kutsutaan *draw_ball(3)*, ruudulle pitäisi tulla:

<pre>
...*...
.*****.
.*****.
*******
.*****.
.*****.
...*...</pre>

**Vinkki:** for-silmukan ei aina tarvitse alkaa nollasta, vaan
  iteroitava muuttuja voi sisältää myös negatiivisia arvoja (mikäli
  tietotyyppi sallii sen)
