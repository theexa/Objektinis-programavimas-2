# Objektinis-programavimas-2
## Programos spartos analizė v1.1
Laiko testavimas atliktas lyginant struktūros ir klasės veikimą <br>
naudotas `std::vector` , o failai studentas100000.txt ir studentas1000000.txt bei greičiausia trečia strategija. 
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
| **Struct**  | 3          |               | 0.604047             | 3.231659           |
|             | -O1        |               | 2.321                |              |
|             | -O2        |               | 2.392                |              |
|             | -O3        |               | 2.501                |              |
| **Class**   | 3          | 432,448          | 0.033299             | 0.346694           |
|             | -O1        | 99,664           | 0.003863             | 0.042368           |
|             | -O2        | 99,632           | 0.003901             | 0.041854           |
|             | -O3        | 115,696          | 0.003834             | 0.041370           |

### Išvados:
* `struct` veikia greičiau nei `class` beveik visais atvejais išskyrus -O3 su 1MLN failu 
* Po optimizacijos skirtumai tarp `class` ir `struct` sumažėja 
* Optimizavus labiau pagreitėja `class` laikai, o `struct` suletėja
* `.exe` failo dydis mažėja naudojant -O1 ir -O2, tačiau -O3 vėl padidėja
* failo dydis nesiskiria nau naudojamo duomenų kiekio
---
## Programos aprašymas v1.2
---
### Pridėta rule of three: <br>
  * `Copy konstruktorius` <br>
  *  `Copy assignment operatorius` <br>
  *  `Destruktorius `<br>
  
---
### Įvesties ir išvesties metodai: <br>
* #### Įvesties metodai: <br>
  - `RanksinisIvedimas()`- naudojamas duomenų įvedimui ranka su `operator>>` <br>
  - `SkaitytiIsFailo(const std::string& failas, Container& Grupe)` - naudojamas duomenų nuskaitymui iš failo , Copy konstruktorius `push_back`  <br>
  - `StudentuSarG(int n, int m)`- naudojamas automatiniam duomenų generavimui failuose (nenaudoja studentų klasės) <br>
* #### Išvesties metodai: <br>
  -`IrasytiIFaila(const string& failoVardas, const Container& studentai`- skirtas duomenų išvedimui į failą <br>
---
