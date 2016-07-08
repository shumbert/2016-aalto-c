title: Laske aakkoset
task_id: 06_strbasic_1
points: 1


**Tavoite:** Ensituntuman hankkiminen merkkijonoihin.

Kirjoita funktio `int count_alpha(const char *str)` joka laskee
aakkoskirjainten määrän annetussa merkkijonossa (*str*). Voit käyttää
hyväksesi funktiota **int
[isalpha](http://linux.die.net/man/3/isalpha)(int character)**, joka
on määritelty *<ctype.h>* - otsakkeessa. Funkio kertoo onko annettu
merkki kirjainmerkki välillä A-Z (palauttaa nollasta poikkeavan
arvon), vai ei (palauttaa 0:n). Toteuttamasti funktion tulee siis
palauttaa kirjainmerkkien lukumäärä annetussa merkkijonossa.
