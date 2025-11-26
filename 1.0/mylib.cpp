#include "mylib.h"
#include <iterator>

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
    srand(time(0));
    fr << setw(15) << left << "Pavarde" << setw(15) << "Vardas";
    for (int i = 0; i < m; i++){
        fr << setw(5) << right << "ND" << i+1;
    }
    fr << " Egzaminas" << endl;
    
    for (int i = 0; i < n; i++){
        fr << setw(7) << left << "Pavarde" << setw(8) << left << (i+1)
           << setw(6) << left << "Vardas" << setw(9) << left << (i+1);
        for (int j = 0; j < m+1; j++){
            int randomNum = rand() % 10 + 1;
            fr << setw(6) << right << randomNum;
        }
        fr << endl;
    }
    fr.close();
}

template<typename Container>
void SkaitytiIsFailo(const string& failoVardas, Container& Grupe) {
    std::ifstream fd(failoVardas);
    if (!fd.is_open()) {
        cout << "Nepavyko atidaryti failo: " << failoVardas << endl;
        return;
    }

    string eilute;
    getline(fd, eilute);

    while (getline(fd, eilute)) {
        std::istringstream iss(eilute);
        Studentas st;
        iss >> st.pav >> st.var;

        int paz;
        int sum = 0;
        while (iss >> paz) {
            st.paz.push_back(paz);
        }

        st.egz = st.paz.back();
        st.paz.pop_back();

        for (int x : st.paz) sum += x;
        if (!st.paz.empty())
            st.gal = (double)sum / st.paz.size() * 0.4 + st.egz * 0.6;
        else
            st.gal = st.egz * 0.6;

        st.paz.push_back(st.egz);
        sort(st.paz.begin(), st.paz.end());
        if (st.paz.size() % 2 != 0) {
            st.med = st.paz[st.paz.size() / 2];
        }
        else {
            st.med = (st.paz[st.paz.size() / 2] + st.paz[st.paz.size() / 2 - 1]) / 2.0;
        }

        Grupe.push_back(st);
    }
    fd.close();
}

template<typename Container>
void Strategija1(Container& studentai, Container& vargsiukai, Container& kietiakai) {
    for (const auto& studentas : studentai) {
        if (studentas.gal < 5.0) {
            vargsiukai.push_back(studentas);
        } else {
            kietiakai.push_back(studentas);
        }
    }
    IrasytiIFaila("RezA.txt", vargsiukai);
    IrasytiIFaila("RezB.txt", kietiakai);
}

template<typename Container>
void Strategija2(Container& studentai, Container& vargsiukai) {
    auto it = studentai.begin();
    while (it != studentai.end()) {
        if (it->gal < 5.0) {
            vargsiukai.push_back(*it);
            it = studentai.erase(it);
        } else {
            ++it;
        }
    }
    IrasytiIFaila("RezA.txt", vargsiukai);
    IrasytiIFaila("RezB.txt", studentai);
}

template<typename Container>
void OptimizuotaStrategija1(Container& studentai, Container& vargsiukai, Container& kietiakai) {
    std::copy_if(studentai.begin(), studentai.end(), std::back_inserter(vargsiukai),
        [](const Studentas& s) { return s.gal < 5.0; });
    
    std::copy_if(studentai.begin(), studentai.end(), std::back_inserter(kietiakai),
        [](const Studentas& s) { return s.gal >= 5.0; });
}

template<typename Container>
void OptimizuotaStrategija2(Container& studentai, Container& vargsiukai) {
    if constexpr (std::is_same_v<Container, vector<Studentas>>) {
        std::remove_copy_if(studentai.begin(), studentai.end(),
                           std::back_inserter(vargsiukai),
                           [](const Studentas& s) { return s.gal >= 5.0; });
        
        auto new_end = std::remove_if(studentai.begin(), studentai.end(),
                                    [](const Studentas& s) { return s.gal < 5.0; });
        studentai.erase(new_end, studentai.end());
    } else {
        auto it = std::remove_if(studentai.begin(), studentai.end(),
            [&vargsiukai](const Studentas& s) {
                if (s.gal < 5.0) {
                    vargsiukai.push_back(s);
                    return true;
                }
                return false;
            });
        studentai.erase(it, studentai.end());
    }
}

template<typename Container>
void Strategija3(Container& studentai, Container& vargsiukai, Container& kietiakai) {
    Container studentai_kopija1 = studentai;
    Container studentai_kopija2 = studentai;
    
    Container vargsiukai1, kietiakai1;
    double laikas1 = MatuotiLaika("1 strategija", [&]() {
        Strategija1(studentai_kopija1, vargsiukai1, kietiakai1);
    });
    
    Container vargsiukai2;
    double laikas2 = MatuotiLaika("2 strategija", [&]() {
        Strategija2(studentai_kopija2, vargsiukai2);
    });

    //cout << "1 strategija: " << std::fixed << std::setprecision(6) << laikas1 << " s" << endl;
    //cout << "2 strategija: " << std::fixed << std::setprecision(6) << laikas2 << " s" << endl;
    
    if (laikas1 < laikas2) {
        cout << "1 strategija yra greitesnė" << endl;
        OptimizuotaStrategija1(studentai, vargsiukai, kietiakai);
        IrasytiIFaila("RezA.txt", vargsiukai);
        IrasytiIFaila("RezB.txt", kietiakai);
    } else {
        cout << "2 strategija yra greitesnė" << endl;
        OptimizuotaStrategija2(studentai, vargsiukai);
        kietiakai = std::move(studentai);
        IrasytiIFaila("RezA.txt", vargsiukai);
        IrasytiIFaila("RezB.txt", studentai);
    }
    cout << "Rezultatas: Vargsiukų: " << vargsiukai.size() << ", Kietiakų: " << kietiakai.size() << endl;
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
            cout << "Vargsiukų: " << vargsiukai.size() << ", Kietiakų: " << kietiakai.size() << endl;
            break;
        }
        case 2: {
            Container vargsiukai;
            laikas = MatuotiLaika("Strategija 2 ", [&]() {
                Strategija2(studentai, vargsiukai);
            });
            cout << "Vargsiukų: " << vargsiukai.size() << ", Liko studentų: " << studentai.size() << endl;
            break;
        }
        case 3: {
            
            Container vargsiukai, kietiakai;
            laikas = MatuotiLaika("Strategija 3 ", [&]() {
                Strategija3(studentai, vargsiukai, kietiakai);
            });
            //cout << "Galutinis rezultatas: Vargsiukų: " << vargsiukai.size() << ", Kietiakų: " << kietiakai.size() << endl;
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
    fr << setw(15) << left << "Pavarde" << setw(15) << "Vardas"
       << setw(15) << "Galutinis" << endl;
    for (const auto& studentas : studentai) {
        fr << setw(15) << left << studentas.pav
           << setw(15) << studentas.var
           << setw(15) << std::fixed << std::setprecision(2) << studentas.gal << endl;
    }
    fr.close();
}

//rankinis ivedimas
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
    
    int sum = 0;
    for (int x : st.paz) sum += x;
    if (!st.paz.empty())
        st.gal = (double)sum / st.paz.size() * 0.4 + st.egz * 0.6;
    else
        st.gal = st.egz * 0.6;
    
    vector<int> temp = st.paz;
    temp.push_back(st.egz);
    sort(temp.begin(), temp.end());
    if (temp.size() % 2 != 0) {
        st.med = temp[temp.size() / 2];
    } else {
        st.med = (temp[temp.size() / 2] + temp[temp.size() / 2 - 1]) / 2.0;
    }
    
    if (st.gal < 5) {
        st.gr = "nuskriaustukai";
    } else {
        st.gr = "kietuoliai";
    }
    
    Grupe.push_back(st);
    cout << "Studento objektas saugomas adresu: " << &Grupe.back()<< endl;
    cout << "Studentas sekmingai pridetas i vektoriu!" << endl;
}

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
    
    int sum = 0;
    for (int x : st.paz) sum += x;
    if (!st.paz.empty())
        st.gal = (double)sum / st.paz.size() * 0.4 + st.egz * 0.6;
    else
        st.gal = st.egz * 0.6;
    
    vector<int> temp = st.paz;
    temp.push_back(st.egz);
    sort(temp.begin(), temp.end());
    if (temp.size() % 2 != 0) {
        st.med = temp[temp.size() / 2];
    } else {
        st.med = (temp[temp.size() / 2] + temp[temp.size() / 2 - 1]) / 2.0;
    }
    
    if (st.gal < 5) {
        st.gr = "nuskriaustukai";
    } else {
        st.gr = "kietuoliai";
    }
    
    Grupe.push_back(st);
    cout << "Studento objektas saugomas adresu: " << &Grupe.back() << endl;
    cout << "Studentas sekmingai pridetas i sarasa!" << endl;
}

// šablonų instancijavimai
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
