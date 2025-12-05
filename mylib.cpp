#include "mylib.h"
#include <iterator>
#include <algorithm>
#include <functional>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <random>

using namespace std;

double MatuotiLaika(const string& operacijosPavadinimas, std::function<void()> operacija) {
    auto start = std::chrono::high_resolution_clock::now();
    operacija();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << operacijosPavadinimas << ": " << duration.count() << " s" << endl;
    return duration.count();
}

void StudentuSarG(int n, int m){
    std::ofstream fr("studentai.txt");
    if(!fr){
        std::cout << "Nepavyko sukurti studentai.txt\n";
        return;
    }
    std::srand(std::time(nullptr));

    fr << std::left << std::setw(15) << "Pavarde"
       << std::setw(15) << "Vardas";

    for(int i = 0; i < m; i++)
        fr << std::setw(6) << ("ND" + std::to_string(i+1));

    fr << std::setw(10) << "Egzaminas\n";

    for(int i = 0; i < n; i++){
        fr << std::left << std::setw(15) << ("Pavarde" + std::to_string(i+1))
           << std::setw(15) << ("Vardas" + std::to_string(i+1));

        for(int j = 0; j < m; j++)
            fr << std::setw(6) << (std::rand() % 11);

        fr << std::setw(10) << (std::rand() % 11) << "\n";
    }
}

template<typename Container>
void SkaitytiIsFailo(const std::string& failas, Container& Grupe){

    std::ifstream fd(failas);
    if (!fd.is_open()) {
        std::cout << "Nepavyko atidaryti failo: " << failas << "\n";
        return;
    }

    std::string line;
    std::getline(fd, line);

    while (std::getline(fd, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        Studentas st;
        st.readFromStream(iss);

        if (!st.pav.empty())
            Grupe.push_back(std::move(st));
    }
}

template<typename Container>
void Strategija1(Container& studentai, Container& vargsiukai, Container& kietiakai) {
    // Rezervuojame vietą vektoriams
    if constexpr (std::is_same_v<Container, vector<Studentas>>) {
        vargsiukai.reserve(studentai.size());
        kietiakai.reserve(studentai.size());
    }
    
    for (const auto& studentas : studentai) {
        if (studentas.gal < 5.0) {
            vargsiukai.push_back(studentas);
        } else {
            kietiakai.push_back(studentas);
        }
    }
}

template<typename Container>
void Strategija2(Container& studentai, Container& vargsiukai) {
    if constexpr (std::is_same_v<Container, vector<Studentas>>) {
        vargsiukai.reserve(studentai.size() / 2);
    }
    
    // Sukuriame atskirą konteinerį darbui, kad nepakeistume originalaus
    Container studentai_darbui = studentai;
    
    auto it = studentai_darbui.begin();
    while (it != studentai_darbui.end()) {
        if (it->gal < 5.0) {
            vargsiukai.push_back(*it);
            it = studentai_darbui.erase(it);
        } else {
            ++it;
        }
    }
    
    // Atnaujiname originalų konteinerį
    studentai = std::move(studentai_darbui);
}

template<typename Container>
void OptimizuotaStrategija2(Container& studentai, Container& vargsiukai) {
    // Rezervuojame vietą vargsiukų vektoriui
    if constexpr (std::is_same_v<Container, vector<Studentas>>) {
        vargsiukai.reserve(studentai.size() / 2);
    }
    
    // Sukuriame atskirą konteinerį darbui
    Container studentai_darbui = studentai;
    
    auto it = std::remove_if(studentai_darbui.begin(), studentai_darbui.end(),
        [&vargsiukai](const Studentas& s) {
            if (s.gal < 5.0) {
                vargsiukai.push_back(s);
                return true;
            }
            return false;
        });
    studentai_darbui.erase(it, studentai_darbui.end());
    

}

template<typename Container>
void OptimizuotaStrategija1(Container& studentai, Container& vargsiukai, Container& kietiakai) {
    // Rezervuojame vietą vektoriams
    if constexpr (std::is_same_v<Container, vector<Studentas>>) {
        vargsiukai.reserve(studentai.size());
        kietiakai.reserve(studentai.size());
    }
    
    std::copy_if(studentai.begin(), studentai.end(), std::back_inserter(vargsiukai),
        [](const Studentas& s) { return s.gal < 5.0; });
    
    std::copy_if(studentai.begin(), studentai.end(), std::back_inserter(kietiakai),
        [](const Studentas& s) { return s.gal >= 5.0; });
}


template<typename Container>
void Strategija3(Container& studentai, Container& vargsiukai, Container& kietiakai) {
    auto it = std::partition(studentai.begin(), studentai.end(),
          [](const Studentas &s) {
              return s.gal >= 5.0;
          });
    
    kietiakai.insert(kietiakai.end(),
                     std::make_move_iterator(studentai.begin()),
                     std::make_move_iterator(it));
    
    vargsiukai.insert(vargsiukai.end(),
                      std::make_move_iterator(it),
                      std::make_move_iterator(studentai.end()));

    studentai.clear();

    cout << "Rezultatas: Vargsiukų: " << vargsiukai.size()
         << ", Kietiakų: " << kietiakai.size() << endl;
}

template<typename Container>
double VykdytiStrategija(Container& studentai, int strategija) {
    double laikas = 0.0;
    
    switch(strategija) {
        case 1: {
            Container vargsiukai, kietiakai;
            laikas = MatuotiLaika("Strategija 1 ", [&]() {
                Strategija1(studentai, vargsiukai, kietiakai);
            });
            // Įrašome į failus
            IrasytiIFaila("RezA.txt", vargsiukai);
            IrasytiIFaila("RezB.txt", kietiakai);
            cout << "Vargsiukų: " << vargsiukai.size()
                 << ", Kietiakų: " << kietiakai.size() << endl;
            break;
        }
        case 2: {
            Container vargsiukai;
            laikas = MatuotiLaika("Strategija 2 ", [&]() {
                Strategija2(studentai, vargsiukai);
            });
            // Įrašome į failus
            IrasytiIFaila("RezA.txt", vargsiukai);
            IrasytiIFaila("RezB.txt", studentai);
            cout << "Vargsiukų: " << vargsiukai.size()
                 << ", Liko studentų: " << studentai.size() << endl;
            break;
        }
        case 3: {
            Container vargsiukai, kietiakai;
            laikas = MatuotiLaika("Strategija 3 ", [&]() {
                Strategija3(studentai, vargsiukai, kietiakai);
            });
            // Įrašome į failus
            IrasytiIFaila("RezA.txt", vargsiukai);
            IrasytiIFaila("RezB.txt", kietiakai);
            cout << "Vargsiukų: " << vargsiukai.size()
                 << ", Kietiakų: " << kietiakai.size() << endl;
            break;
        }
        default:
            cout << "Netinkama strategija!" << endl;
            break;
    }
    
    return laikas;
}

template<typename Container>
void IrasytiIFaila(const string& failoVardas, const Container& studentai) {
    std::ofstream fr(failoVardas);
    if (!fr.is_open()) {
        cout << "Klaida: nepavyko atidaryti failo " << failoVardas << endl;
        return;
    }
    
    fr << std::setw(15) << std::left << "Pavarde"
       << std::setw(15) << "Vardas"
       << std::setw(15) << "Galutinis"
       << std::endl << std::endl;
    
    for (const auto& studentas : studentai) {
        fr << std::setw(15) << std::left << studentas.pav
           << std::setw(15) << studentas.var
           << std::setw(15) << std::fixed << std::setprecision(2) << studentas.gal
           << std::endl;
    }
    fr.close();
}

// Rankinis įvedimas vektoriui
void RanksinisIvedimas(vector<Studentas>& Grupe) {
    Studentas st;
    cout << "Iveskite studento pavarde: ";
    cin >> st.pav;
    cout << "Iveskite studento varda: ";
    cin >> st.var;
    
    cout << "Iveskite namu darbu pazymius (baigti ivesdami -1): ";
    int paz;
    while (cin >> paz && paz != -1) {
        if (paz >= 0 && paz <= 10) {
            st.paz.push_back(paz);
        } else {
            cout << "Netinkamas pazymys! Iveskite skaiciu nuo 0 iki 10: ";
        }
    }
    
    cout << "Iveskite egzamino pazymi: ";
    cin >> st.egz;
    
    // Apskaičiuojame galutinį balą
    int sum = 0;
    for (int x : st.paz) sum += x;
    if (!st.paz.empty())
        st.gal = (double)sum / st.paz.size() * 0.4 + st.egz * 0.6;
    else
        st.gal = st.egz * 0.6;
    
    // Apskaičiuojame medianą
    vector<int> temp = st.paz;
    temp.push_back(st.egz);
    sort(temp.begin(), temp.end());
    if (temp.size() % 2 != 0) {
        st.med = temp[temp.size() / 2];
    } else {
        st.med = (temp[temp.size() / 2] + temp[temp.size() / 2 - 1]) / 2.0;
    }
    
    // Nustatome grupę
    if (st.gal < 5) {
        st.gr = "nuskriaustukai";
    } else {
        st.gr = "kietuoliai";
    }
    
    Grupe.push_back(std::move(st));
    cout << "Studento objektas saugomas adresu: " << &Grupe.back() << endl;
    cout << "Studentas sekmingai pridetas i vektoriu!" << endl;
}

// Rankinis įvedimas sąrašui
void RanksinisIvedimas(list<Studentas>& Grupe) {
    Studentas st;
    cout << "Iveskite studento pavarde: ";
    cin >> st.pav;
    cout << "Iveskite studento varda: ";
    cin >> st.var;
    
    cout << "Iveskite namu darbu pazymius (baigti ivesdami -1): ";
    int paz;
    while (cin >> paz && paz != -1) {
        if (paz >= 0 && paz <= 10) {
            st.paz.push_back(paz);
        } else {
            cout << "Netinkamas pazymys! Iveskite skaiciu nuo 0 iki 10: ";
        }
    }
    
    cout << "Iveskite egzamino pazymi: ";
    cin >> st.egz;
    
    // Apskaičiuojame galutinį balą
    int sum = 0;
    for (int x : st.paz) sum += x;
    if (!st.paz.empty())
        st.gal = (double)sum / st.paz.size() * 0.4 + st.egz * 0.6;
    else
        st.gal = st.egz * 0.6;
    
    // Apskaičiuojame medianą
    vector<int> temp = st.paz;
    temp.push_back(st.egz);
    sort(temp.begin(), temp.end());
    if (temp.size() % 2 != 0) {
        st.med = temp[temp.size() / 2];
    } else {
        st.med = (temp[temp.size() / 2] + temp[temp.size() / 2 - 1]) / 2.0;
    }
    
    // Nustatome grupę
    if (st.gal < 5) {
        st.gr = "nuskriaustukai";
    } else {
        st.gr = "kietuoliai";
    }
    
    Grupe.push_back(std::move(st));
    cout << "Studento objektas saugomas adresu: " << &Grupe.back() << endl;
    cout << "Studentas sekmingai pridetas i sarasa!" << endl;
}

// Šablonų instancijavimai
template void SkaitytiIsFailo<vector<Studentas>>(const string& failoVardas, vector<Studentas>& Grupe);
template void SkaitytiIsFailo<list<Studentas>>(const string& failoVardas, list<Studentas>& Grupe);

template void Strategija1<vector<Studentas>>(vector<Studentas>& studentai, vector<Studentas>& vargsiukai, vector<Studentas>& kietiakai);
template void Strategija1<list<Studentas>>(list<Studentas>& studentai, list<Studentas>& vargsiukai, list<Studentas>& kietiakai);

template void Strategija2<vector<Studentas>>(vector<Studentas>& studentai, vector<Studentas>& vargsiukai);
template void Strategija2<list<Studentas>>(list<Studentas>& studentai, list<Studentas>& vargsiukai);

template void Strategija3<vector<Studentas>>(vector<Studentas>& studentai, vector<Studentas>& vargsiukai, vector<Studentas>& kietiakai);
template void Strategija3<list<Studentas>>(list<Studentas>& studentai, list<Studentas>& vargsiukai, list<Studentas>& kietiakai);

template void OptimizuotaStrategija1<vector<Studentas>>(vector<Studentas>& studentai, vector<Studentas>& vargsiukai, vector<Studentas>& kietiakai);
template void OptimizuotaStrategija1<list<Studentas>>(list<Studentas>& studentai, list<Studentas>& vargsiukai, list<Studentas>& kietiakai);

template void OptimizuotaStrategija2<vector<Studentas>>(vector<Studentas>& studentai, vector<Studentas>& vargsiukai);
template void OptimizuotaStrategija2<list<Studentas>>(list<Studentas>& studentai, list<Studentas>& vargsiukai);

template double VykdytiStrategija<vector<Studentas>>(vector<Studentas>& studentai, int strategija);
template double VykdytiStrategija<list<Studentas>>(list<Studentas>& studentai, int strategija);

template void IrasytiIFaila<vector<Studentas>>(const string& failoVardas, const vector<Studentas>& studentai);
template void IrasytiIFaila<list<Studentas>>(const string& failoVardas, const list<Studentas>& studentai);
