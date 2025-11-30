Határidőnapló
Ez egy C nyelvben írt parancssoros menüvezérelt határidőnapló program specifikációja. A programnak
tudni kell az eseményeket létrehozni, módosítani, törölni, fájlban tárolni, fájlból visszatölteni. Az
események közt lehet keresni. Egy adott naphoz, héthez, hónaphoz tartozó eseményeket meg kell
tudnia a programnak jeleníteni időrend szerint.
A program indítása
A programnak egy indítási paramétere van, ami opcionális. A felhasználó megadhatja, hogy milyen fájlt
használjon a program adatbázisnak. Ha nem ad meg semmit a felhasználó, az alapértelmezett fájlba
lesz mentve az adat. Ha létezik a paraméternek megadott fájl, az betöltésre kerül a program indításakor
és ezt fogja a program használni amíg fut. Ha nem létezik, a program automatikusan létrehozza a fájlt,
és ugyanúgy használni fogja. Indításkor a program megjeleníti a főmenüt.
Példa:
hataridonaplo hn1.csv
hataridonaplo
Navigáció
A program menüvezérelt. A program a főmenüből indul, azon keresztül pedig más menüket meg lehet
nyitni. Minden menü (főmenüt beleértve) leírja a lehetséges műveleteket, amiket el lehet végezni az
adott menüben. Legyen az másik menübe lépés, vagy egy menü-specifikus művelet (például
események listázása esetén törlés sorszám alapján). Minden menüből kell hogy lehessen visszalépni.
Adatbázis
A program alapértelmezetten a hataridonaplo.csv fájlba menti az eseményeket CSV formátumban
minden kilépéskor, új sor karakterekkel elválasztva. Ezt a fájlt is olvassa be indításkor, kivéve ha a
felhasználó megadott mást. Minden sor egy eseményt reprezentál, minden oszlop (pontosvesszőkkel
elválasztva) egy külön tulajdonságot. Minden sorban kell hogy legyen pontosan 4 pontosvessző. A
felhasználó nem befolyásolhatja ezt.
Az első oszlop a dátum. Második az időpont. Harmadik a hely, ez opcionális. Negyedik a megnevezés.
Ötödik a megjegyzés, ami szintén opcionális.
Példa:
2025-11-02;23:59;Otthon;Specifikacio beadas;
2025-11-05;16:40;Bajai autobusz palyaudvar;Busz pestre;Megyunk vissza koliba
2025-11-18;18:00;;Pusztulas;csak a teremto menthet meg minket
Menük
Főmenü
Ez a legelső menü amit a program megjelenít. Innen tudunk más menükbe eljutni. Más célt nem
szolgál.
Műveletek: események listázása (menü), új esemény létrehozása (menü).
Események listázása
Az összes eseményt kilistázza ez a menü időrendi sorrendben alapértelmezetten. Ha a keresés be van
kapcsolva (a felhasználó ráment a keresésre, beírta a keresendő szöveget és visszatért erre a menüre),
csak azok az események lesznek megjelenítve, ahol az esemény cím (megnevezés) tartalmazza a
keresendő szöveget.
Műveletek: keresés, esemény kiválasztása sorszám alapján
Esemény
Egy adott eseményt jelenítünk meg ezzel a menüvel. Minden tulajdonságát kilistázzuk.
Műveletek: módosítás, törlés
Új esemény létrehozása
Új eseményt hozunk létre ezzel a menüvel.
Műveletek: hozzáad
Hetek
Ez a menü kilistázza az eddigi mentett események alapján az összes hetet. Ezek közül lehet választani
egyet, ahol az összes esemény ki lesz listázva.
Műveletek: hét, esemény kiválasztása sorszám alapján
Hónapok
Ez a menü kilistázza az eddigi mentett események alapján az összes hónapot. Ezek közül lehet
választani egyet, ahol az összes esemény ki lesz listázva.
Műveletek: hónap, esemény kiválasztása sorszám alapján