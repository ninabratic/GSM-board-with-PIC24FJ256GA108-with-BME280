# GSM-board-with-PIC24FJ256GA108-with-BME280

Senzor može da radi preko I2C i preko SPI komunikacije. Za potrebe ovog projekta izabrali smo I2C komunikaciju, brzinu smo podesili na 400 kHz. Za I2C protokol potrebne su dve
žice za komunikaciju, a to su SDA i SCL. Koristili smo I2C1 port, odnosno pinove RG2 (SCL1) i RG3 (SDA1) i podesili ih kao ulazne pinove. I2C komunikacijski protokol sa 
hardverske strane zahteva korišćenje dva pull-up otpornika, kako bi se obezbedio stabilan visoki logicki nivo prilikom prenosa podataka i kloka, što je odrađeno na pločici.
Na osnovu memorijske mape samog čipa je izvršeno prikupljanje podataka sa senzora nakon čega je izvršena njihova obrada kako bi se dobili što tačniji rezultati.

Komunikacija mikrokontrolera i modema realizovana je preko pet funkcija. Svaka funkcija
predstavlja jedno stanje i sadrži tačno određene AT instrukcije. Unutar svakog stanja uključuje se
tajmer koji definiše tačno koliko sme jedno stanje da se izvršava. Ovo je implementirano u cilju
da ukoliko modem ne prepozna poruku ili vrati komandu koju mikrokontroler ne očekuje bude
omogućeno vraćanje programa u početno stanje. Svakom stanju je bitno dodeliti dovoljno vremena
za njegovo izvršavanje. Vreme koje je potrebno određenom stanju da se izvrši zavisi od vrste AT
komandi. Preporuka koliko je vremena potrebno za pravilno izvršavanje određene AT komande
može se potražiti u katalogu modema (eng. Datasheet).
