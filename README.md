# Objektinis-programavimas-2
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
