#include "mylib.h"

#include <unistd.h>
#include <iostream>

    
int main() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    std::cout << "RUNNING FROM: " << cwd << std::endl;
    int konteinerioPasirinkimas, strategijosPasirinkimas;
    int testuKiekis = 5;
    cout << "Pasirinkite konteinerio tipą:\n";
    cout << "1 - Vektorius\n";
    cout << "2 - Sarasas\n";
    cout << "Jūsų pasirinkimas: ";
    cin >> konteinerioPasirinkimas;
    
    // Strategijos pasirinkimas
    cout << "\nPasirinkite skaidymo strategiją:\n";
    cout << "1 - Strategija 1 (skaidymas į du konteinerius)\n";
    cout << "2 - Strategija 2 (skaidymas su trynimu)\n";
    cout << "3 - Strategija 3 (efektyvus skaidymas)\n";
    cout << "Jūsų pasirinkimas: ";
    cin >> strategijosPasirinkimas;
    
    // Failo generavimas/skaitymas
    string fpav;
    int n, m;
    int s;
    cout << "\nAr norite sukurti atsitiktinius studentų sąrašus? Taip - (1), Ne - (2): ";
    cin >> s;
    
    if(s == 1){
        cout << "Kiek studentų norite? ";
        cin >> n;
        cout << "Kiek namų darbų pažymių? ";
        cin >> m;
        cout << "Generuojamas failas..." << endl;
        StudentuSarG(n, m);
        fpav = "studentai.txt";
        cout << "Failas 'studentai.txt' sugeneruotas" << endl;
    }
    
    // Testavimo ciklas
    vector<double> visiLaikai;
    
    if (konteinerioPasirinkimas == 1) {
        // Testavimas su vektoriumi
        cout << "\n=== TESTAVIMAS SU VEKTORIUMI ===" << endl;
        vector<Studentas> studentai;
        int pas;
        cout << "Nuskaityti duomenis iš failo - (1), Ivesti duomenis ranka - (2): ";
        cin >> pas;
        if (pas == 1){
            cout << "Įveskite failo pavadinimą: ";
            cin >> fpav;
            SkaitytiIsFailo(fpav, studentai);
        } else{
            int kiek;
            cout << "Kiek studentu norite ivesti? ";
            cin >> kiek;
            for (int i = 0; i < kiek; i++) {
                cout << "\nIvedamas " << i+1 << " studentas:" << endl;
                RanksinisIvedimas(studentai);
            }
        }
        for (int i = 0; i < testuKiekis; i++) {
            cout << "\n--- Testas " << (i + 1) << " ---" << endl;
            
            double laikas = VykdytiStrategija<vector<Studentas>>(studentai, strategijosPasirinkimas);
            visiLaikai.push_back(laikas);
        }
    }
    else if (konteinerioPasirinkimas == 2) {
        // Testavimas su sąrašu
        cout << "\n=== TESTAVIMAS SU SĄRAŠU ===" << endl;
        list<Studentas> studentai;
        int pas;
        cout << "Nuskaityti duomenis iš failo - (1), Ivesti duomenis ranka - (2): ";
        cin >> pas;
        if (pas == 1){
            cout << "Įveskite failo pavadinimą: ";
            cin >> fpav;
            SkaitytiIsFailo(fpav, studentai);
        } else{
            int kiek;
            cout << "Kiek studentu norite ivesti? ";
            cin >> kiek;
            for (int i = 0; i < kiek; i++) {
                cout << "\nIvedamas " << i+1 << " studentas:" << endl;
                RanksinisIvedimas(studentai);
            }
        }
        for (int i = 0; i < testuKiekis; i++) {
            cout << "\n--- Testas " << (i + 1) << " ---" << endl;
            
            double laikas = VykdytiStrategija<list<Studentas>>(studentai, strategijosPasirinkimas);
            visiLaikai.push_back(laikas);
        }
    }
    else {
        cout << "Netinkamas pasirinkimas. Naudojamas vektorius." << endl;
        for (int i = 0; i < testuKiekis; i++) {
            cout << "\n--- Testas " << (i + 1) << " ---" << endl;
            vector<Studentas> studentai;
            SkaitytiIsFailo(fpav, studentai);
            
            double laikas = VykdytiStrategija<vector<Studentas>>(studentai, strategijosPasirinkimas);
            visiLaikai.push_back(laikas);
        }
    }
    

    cout << "-----------------------------------" << endl;
    double suma = 0.0;
    for (int i = 0; i < testuKiekis; i++) {
        cout << "Testas " << (i + 1) << ": " << std::fixed << std::setprecision(6) << visiLaikai[i] << " s" << endl;
        suma += visiLaikai[i];
    }
    cout << endl;
    cout << "-----------------------------------" << endl;
    cout << "Vidutinis laikas: " << std::fixed << std::setprecision(6) << (suma / testuKiekis) << " s" << endl;
    cout << "Bendras laikas: " << std::fixed << std::setprecision(6) << suma << " s" << endl;
    
    return 0;
}
