# Objektinis-programavimas-2
### Naudojimosi instrukcija 
#### Diegimo instrukcija 
1. Atsisiųskite visus failus.
2. Nukopijuokite projekto direktoriją į savo kompiuterį bei sukurkite build direktoriją <br>
    ```
   cd /Users/yourname/Desktop/MyProject
   mkdir build
   cd build
   ```
3. Su Cmake generuojame reikalingus projekto failus <br>
   ```
   cd ..
   ```
4. Jei su Xcode:
    ```
   cmake -G Xcode .. 
   ```
5. Sukompiliuojame kodą ir sukuriame failą <br>
   ```
   cmake --build . --config Release
   ```
6. Jei su Xcode, atsidarome ir 'pastatome':
   ```
   open StudentSorter.xcodeproj
   ```
    ⌘B
7. Paleidziame programą:
    ```
   ./StudentSorter
   ```
---
#### Kaip naudotis:
1. Paleidžiame programą;
2. Pasirenkame konteinerio tipą;
3. Pasirenkame skaidymo strategija;
4. Pasirenkame ar norime kurti atsitiktinius failus:
4.1.  Jei taip pasirenkame kiek studentų norime;<br>
4.2.  Sukuriamas failas;<br>
5. Pasirenkame kaip programa gaus duomenis:<br>
5.1  Nuskaitymas iš failo; <br>
   Įvedame failo pavadinimą, iš kurio bus nuskaitomi duomenys;<br>
5.2  Įvedimas ranka; <br>
   Įvedame kiek studentų norėsime, ir tada jų duomenis (vardą, pavardę, pažymius, egzamino pažymį); <br>
6. Programa atlieka testavimą;
7. Gauname rezultatų failus: RezA - vidurkiai <5; RezB - vidurkiai >=5;
---
## Atnaujinimai:
### v0.1
Sukūrėme studentų programą, kuri skaičiuoja studentų galutinius vidurkį pagal formulę: <br>
*Galutinis balas = 0.4 x namų darbų rezultatai + 0.6 x egzamino įvertinimas.* <br>
Taip pat galime pasirinkti studentų duomenis įvedinėsime ranka, nuskaitysime iš failo, ar sugeneruosime atsitiktinius. Rezultatai išvedami į failus.

### v0.2
Sukurtas studentų failų generatorius. Be to pridėta funkcija kuri suskaido studentus į dvi grupes, pirma - kurių galutinis pažymys >=5, antra - kurių galutinis pažymys <5. Taip pat pridėtas rikiavimas, pagal vartotojo pasirinktą kriterijų. Funkcijos skirtingos dalys (funkcijos, struktūros ir t.t.) perkeltos į atskirus failus pagal jų paskirtį.
### v0.3
Pridėjome galimybe vartotojui pasirinkti su kokiais konteineriais jis nori, kad programa dirbtų. Taip pat pridėta galimybė pasižiurėti objekto saugojimo vietą. Ir atlikome spartos analizę su skirtingais konteinerių tipais ir duomenų kiekiais.
### v1.0
Pridėjome galimybę vartotojui pasirinkti studentų skaidymo strategiją (iš trijų galimų).
### v1.1
Pridejome klases

---
## Testavimai:
### Testavimo sistemos parametrai
CPU: Apple M3 <br>
RAM: 16GB <br>
HDD: SSD 512GB <br>
### Testavimo aprašymas
Programos testavimo metu buvo naudojami tokie failai:<br>
* 1000 studentų - stud1000.txt
* 10000 studentų - stud10000.txt
* 100000 studentų - stud100000.txt
* 1000000 studentų - stud1000000.txt
* 10000000 studentų - stud10000000.txt <br>

Testavimo failao sudetis - Vardas, Pavardė, 5 Namų darbų pažymiai ir egzamino pažymys.<br>
Testavimo laiko tikslumui, programa duomenis apdorojo penkis kartus, lentelėje yra pateikti testavimo laikų vidurkiai.

---
## Programos spartos analizė v1.1
Laiko testavimas atliktas lyginant struktūros ir klasės veikimą <br>
naudotas `std::vector` , o failai stud100000.txt ir stud1000000.txt bei greičiausia trečia strategija. 
## Rezultatai
### stud100000.txt 
| Realizacija | Konteineris | Strategija | Skaidymo laikas |
|:------------|:------------|:----------:|----------------:|
| **Struct**  | Vector      | 3          | 0.604047        |
| **Class**   | Vector      | 3          | 0.033299        |

### stud1000000.txt
| Realizacija | Konteineris | Strategija | Skaidymo laikas |
|:------------|:------------|:----------:|----------------:|
| **Struct**  | Vector      | 3          | 3.231659        |
| **Class**   | Vector      | 3          | 0.346694        |

---
## Spartos analizė su flag'ais 
### Skaidymo laikas pagal realizaciją, strategiją ir failo dydį

| Realizacija | Strategija | .exe dydis bytes | Skaidymo laikas 100k | Skaidymo laikas 1M |
|:------------|:----------:|-----------------:|---------------------:|-------------------:|
| **Struct**  | 3          | 352,684          | 0.604047             | 3.231659           |
|             | -O1        | 91,756           | 0.048356             | 3.374444           |
|             | -O2        | 79,427           | 0.046632             | 2.921511           |
|             | -O3        | 95,753           | 0.045941             | 3.030021           |
| **Class**   | 3          | 432,448          | 0.033299             | 0.346694           |
|             | -O1        | 99,664           | 0.003863             | 0.042368           |
|             | -O2        | 99,632           | 0.003901             | 0.041854           |
|             | -O3        | 115,696          | 0.003834             | 0.041370           |

### Išvados:
* `class` veikia greičiau nei `struct` visais atvejais 
* `.exe` failo dydis mažėja naudojant -O1 ir -O2, tačiau -O3 vėl padidėja
* failo dydis nesiskiria nau naudojamo duomenų kiekio
---

### Tyrimas pagal strtegijas:
#### Strategijos:
* 1 strategija - Bendro studentai konteinerio skaidymas (rūšiavimas) į du naujus to paties tipo konteinerius: "vargšiukų" ir "kietiakų". Tokiu būdu tas pats studentas yra dvejuose konteineriuose: bendrame studentai ir viename iš suskaidytų (vargšiukai arba kietiakai);
* 2 strategija - Bendro studentų konteinerio skaidymas (rūšiavimas) panaudojant tik vieną naują konteinerį: "vargšiukai". Tokiu būdu, jei studentas yra vargšiukas, jį turime įkelti į naująjį "vargšiukų" konteinerį ir ištrinti iš bendro studentai konteinerio. Po šio žingsnio studentai konteineryje liks vien tik kietiakai;
* 3 strategija -  Bendro studentų konteinerio skaidymas (rūšiavimas) panaudojant greičiausiai veikianti 1 arba 2 strategiją  įtraukiant į ją "efektyvius" darbo su konteineriais metodus;

#### 1 strategija:
| Failas             | Vector     | List       | 
|:-------------------|:-----------|:-----------|
| stud1000.txt       | 0.003783 s | 0.003418 s | 
| stud10000.txt      | 0.020030 s | 0.017691 s | 
| stud100000.txt     | 0.183826 s | 0.172933 s | 
| stud1000000.txt    | 1.857563 s | 1.741430 s | 
| stud10000000.txt   | 20.71244 s | 25.20513 s | 
#### 2 strategija:
| Failas             | Vector     | List       | 
|:-------------------|:-----------|:-----------|
| stud1000.txt       | 0.027172 s | 0.003165 s | 
| stud10000.txt      | 0.017346 s | 0.017650 s | 
| stud100000.txt     | 0.166716 s | 0.171667 s | 
| stud1000000.txt    | 1.670181 s | 1.658064 s | 
| stud10000000.txt   | 19.51229 s | 19.28886 s | 
#### 3 strategija:
| Failas             | Vector     | List       |
|:-------------------|:-----------|:-----------|
| stud1000.txt       | 0.009725 s | 0.009525 s |
| stud10000.txt      | 0.035253 s | 0.037783 s | 
| stud100000.txt     | 0.623918 s | 0.658467 s | 
| stud1000000.txt    | 3.202424 s | 3.167428 s | 
| stud10000000.txt   | 38.14171 s | 36.28952 s | 
### Rezultatai:
Antra strategija buvo greičiausia tiek su vector tiek su list type konteineriais. Vector konteineris dažnu atveju buvo greitesnis 
### Konteinerių spartos analizė
#### Tyrimas su vector tipo konteineriu:
| Failas             | Failo kūrimas | Duomenų nuskaitymas | Studentų rūšiavimas | Duomenų skaidymas | Išvedimas į failus (<5) | Išvedimas į failus >=5) |
|:-------------------|:--------------|:--------------------|:--------------------|:------------------|:------------------------|:------------------------|
| stud1000.txt       | 0.003123 s    | 0.003993 s          | 0.00093 s           | 0.000344 s        | 0.00089 s               | 0.00120 s               |
| stud10000.txt      | 0.020273 s    | 0.040446 s          | 0.00702 s           | 0.003318 s        | 0.00839 s               | 0.01164 s               |
| stud100000.txt     | 0.198215 s    | 0.404583 s          | 0.06672 s           | 0.033983 s        | 0.08366 s               | 0.11289 s               |
| stud1000000.txt    | 1.922578 s    | 4.082662 s          | 0.66037 s           | 0.398755 s        | 0.80252 s               | 1.13977 s               |
| stud10000000.txt   | 21.73358 s    | 33.01044 s          | 6.46142 s           | 3.008542 s        | 7.20668 s               | 12.7480 s               |

#### Tyrimas su list tipo konteineriu:
| Failas             | Failo kūrimas | Duomenų nuskaitymas | Studentų rūšiavimas | Duomenų skaidymas | Išvedimas į failus (<5) | Išvedimas į failus >=5) |
|:-------------------|:--------------|:--------------------|:--------------------|:------------------|:------------------------|:------------------------|
| stud1000.txt       | 0.003295 s    | 0.004071 s          | 0.00023 s           | 0.000333 s        | 0.00103 s               | 0.00119 s               |
| stud10000.txt      | 0.024072 s    | 0.040726 s          | 0.00284 s           | 0.003214 s        | 0.00873 s               | 0.01233 s               |
| stud100000.txt     | 0.201635 s    | 0.401682 s          | 0.03419 s           | 0.034260 s        | 0.08066 s               | 0.11291 s               |
| stud1000000.txt    | 1.887777 s    | 4.066808 s          | 0.64677 s           | 0.386003 s        | 0.80637 s               | 1.12884 s               |
| stud10000000.txt   | 21.74144 s    | 39.98160 s          | 6.05281 s           | 3.257018 s        | 7.20628 s               | 12.8282 s               |

### Rezultatų išvedimo pavyzdys 
<img width="524" height="126" alt="Screenshot 2025-10-30 at 19 15 48" src="https://github.com/user-attachments/assets/82c56d05-7f4d-4ebc-a4ea-948e3aa18886" />
<br>

### Tyrimo rezultatai

Tiriant konteinerių spartą su skirtingais duomenų kiekiais, rezultatai buvo labai panašūs.
