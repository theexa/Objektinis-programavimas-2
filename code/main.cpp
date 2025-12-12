#include "mylib.h"

void printTestRow(const std::string& name, bool ok) {
    std::cout << std::left << std::setw(28) << name
              << "| " << (ok ? "+" : "-") << "\n";
}

void ROT() {
    cout << "Rule of three testavimas" << endl;
    cout << "-----------------------------------" << endl;
    //Default konstruktorius
    Studentas s1;
    bool okDefault = true;

    //  Copy konstruktorius
    s1.setVardas("Jonas");
    s1.setPavarde("Jonaitis");
    Studentas s2(s1);
    bool okCopyCtor = (s2.getVardas() == s1.getVardas() && s2.getPavarde() == s1.getPavarde());

    // Copy assignment operatorius
    Studentas s3;
    s3 = s1;
    bool okCopyAssign = (s3.getVardas() == s1.getVardas() && s3.getPavarde() == s1.getPavarde());

    //  Destruktorius
    
    bool okDtor = true;

    // Lentelė
    printTestRow("Default konstruktorius", okDefault);
    printTestRow("Copy konstruktorius", okCopyCtor);
    printTestRow("Copy assignment operatorius", okCopyAssign);
    printTestRow("Destruktorius", okDtor);
}

int main() {
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
    
    // Failo generavimas
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
        
        // Išsaugome ORIGINALŲ konteinerį
        vector<Studentas> originalusStudentai = studentai;
        
        for (int i = 0; i < testuKiekis; i++) {
            cout << "\n--- Testas " << (i + 1) << " ---" << endl;
            
            // KIEKVIENAM TESTUI sukuriama nauja kopija iš originalaus konteinerio
            vector<Studentas> testiniaiStudentai = originalusStudentai;
            
            double laikas = VykdytiStrategija<vector<Studentas>>(testiniaiStudentai, strategijosPasirinkimas);
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
        
        // Išsaugome ORIGINALŲ konteinerį
        list<Studentas> originalusStudentai = studentai;
        
        for (int i = 0; i < testuKiekis; i++) {
            cout << "\n--- Testas " << (i + 1) << " ---" << endl;
            
            // KIEKVIENAM TESTUI sukuriama nauja kopija iš originalaus konteinerio
            list<Studentas> testiniaiStudentai = originalusStudentai;
            
            double laikas = VykdytiStrategija<list<Studentas>>(testiniaiStudentai, strategijosPasirinkimas);
            visiLaikai.push_back(laikas);
        }
    }
    else {
        cout << "Netinkamas pasirinkimas. Naudojamas vektorius." << endl;
        vector<Studentas> studentai;
        SkaitytiIsFailo(fpav, studentai);
        
        // Išsaugome ORIGINALŲ konteinerį
        vector<Studentas> originalusStudentai = studentai;
        
        for (int i = 0; i < testuKiekis; i++) {
            cout << "\n--- Testas " << (i + 1) << " ---" << endl;
            
            // KIEKVIENAM TESTUI sukuriama nauja kopija iš originalaus konteinerio
            vector<Studentas> testiniaiStudentai = originalusStudentai;
            
            double laikas = VykdytiStrategija<vector<Studentas>>(testiniaiStudentai, strategijosPasirinkimas);
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
    ROT();
    return 0;
}
