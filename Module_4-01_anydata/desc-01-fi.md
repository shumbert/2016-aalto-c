title: Jokudata
task_id: 01_anydata
points: 2


**Tavoite:** Hankkia tuntumaa unioneiden käsittelyyn

Tässä tehtävässä määritellään uusi tietotyyppi *AnyData*, joka voi
pitää sisällään joko tavun (eli *char*), kokonaisluvun (*int*) tai
*double* - tyyppisen liukuluvun. *AnyData* - tietotyyppi määritellään
*typedef* määritelmän avulla, mikä on hyvä huomioida kun tietotyyppiä
käytetään.

*AnyData* on rakenteinen tietotyyppi joka koostuu kahdesta kentästä:
 *type* on enumeraatio, joka kertoo mikä kolmesta edellä mainitusta
tyypistä rakenteeseen on kulloinkin tallennettu, sekä *value* on
unionirakenne, johon on tallennettu kyseisen tyyppinen arvo. Näet
otsakkeesta *anydata.h* kuinka tyyppi on tarkalleen ottaen
määritelty. Lisäksi *type* - kenttään voi olla tallennettu arvo
*UNDEF*, mikäli rakenteeseen ei ole vielä tallennettu mitää arvoa.
	    
Toteuta seuraavat osat:

a) Aseta arvo
---------------

Toteuta funktiot *setByte*, *setInt* ja *setDouble* jotka palauttavat
uuden AnyData-tyyppisen objektin paluuarvonaan, perustuen annettuun
tyyppiin ja arvoon, joka kyseisen funktion parametrissa on annettu.

b) Tulosta arvo
-----------------

Toteuta funktio *printValue* joka tulostaa *AnyData*:n tallentaman
arvon. Tulostusformaatti riippuu muuttujaan asetetun arvon
tyypistä. Varsinaiseen tulostukseen sinun täytyy käyttää yhtä
*anydata.c*:ssä valmiiksi annetuista funktioista (*printByte*,
*printInt* tai *printDouble*), riippuen muuttujaan tallennetun arvon
tyypistä.
