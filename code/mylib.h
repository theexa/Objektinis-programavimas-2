#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <string>
#include <random>
#include <limits>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <functional>
#include <iterator>
#include <algorithm>
#include <functional>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <random>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::list;
using std::setw;
using std::left;
using std::sort;
using std::right;
using std::function;

class Studentas {
private:
    std::string pav;
    std::string var;
    std::vector<int> paz;
    int egz{0};
    double gal{0.0};
    double med{0.0};
    std::string gr;

public:
    //Konstruktorius
    Studentas() : pav(""), var(""), paz{}, egz(0), gal(0.0), med(0.0), gr("") {}

    //Konstruktorius su parametrais
    Studentas(std::string p, std::string v, std::vector<int> pz, int e)
        : pav(std::move(p)), var(std::move(v)), paz(std::move(pz)), egz(e) {
        computeResults();
    }
    
    //Kopijavimo konstruktorius (Rule of Three - 1)
    Studentas(const Studentas& other)
        : pav(other.pav), var(other.var), paz(other.paz),
          egz(other.egz), gal(other.gal), med(other.med), gr(other.gr) {}
    
    //Priskyrimo operatorius (Rule of Three - 2)
    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            pav = other.pav;
            var = other.var;
            paz = other.paz;
            egz = other.egz;
            gal = other.gal;
            med = other.med;
            gr = other.gr;
        }
        return *this;
    }
    
    //Destruktorius (Rule of Three - 3)
    ~Studentas() {
        pav.clear();
        var.clear();
        paz.clear();
        egz = 0;
        gal = 0.0;
        med = 0.0;
        gr.clear();
    }
    
    // Getteriai ir setteriai
    inline const std::string getPavarde() const { return pav; }
    inline const std::string getVardas() const { return var; }
    inline std::vector<int> getPazymiai() const { return paz; }
    inline int getEgzaminas() const { return egz; }
    inline double getGalutinis() const { return gal; }
    inline double getMediana() const { return med; }
    inline std::string getGrupe() const { return gr; }
    
    inline void setPavarde(const std::string& p) { pav = p; }
    inline void setVardas(const std::string& v) { var = v; }
    inline void setPazymiai(const std::vector<int>& p) {
        paz = p;
        computeResults();
    }
    inline void setEgzaminas(int e) {
        egz = e;
        computeResults();
    }

    //Operatoriai
    friend std::ostream& operator<<(std::ostream& out, const Studentas& stud);
    friend std::istream& operator>>(std::istream& in, Studentas& stud);
    
    // Metodai
    void readFromStream(std::istream& is) {
        if (!(is >> pav >> var)) return;

        paz.clear();
        int value;
        std::vector<int> nums;

        std::string line;
        std::getline(is, line);
        std::istringstream iss(line);

        while (iss >> value)
            nums.push_back(value);

        if (!nums.empty()) {
            egz = nums.back();
            nums.pop_back();
        } else {
            egz = 0;
        }

        paz = std::move(nums);
        computeResults();
    }

    void computeResults() {
        int sum = 0;
        for (int p : paz) sum += p;

        if (!paz.empty())
            gal = (sum / static_cast<double>(paz.size())) * 0.4 + egz * 0.6;
        else
            gal = egz * 0.6;

        std::vector<int> tmp = paz;
        tmp.push_back(egz);
        std::sort(tmp.begin(), tmp.end());

        if (!tmp.empty()) {
            if (tmp.size() % 2 == 1)
                med = tmp[tmp.size() / 2];
            else
                med = (tmp[tmp.size() / 2] + tmp[tmp.size() / 2 - 1]) / 2.0;
        } else {
            med = 0.0;
        }

        gr = (gal < 5.0 ? "nuskriaustukai" : "kietuoliai");
    }

    // Palyginimo operatoriai
    bool operator<(const Studentas& other) const {
        return pav < other.pav || (pav == other.pav && var < other.var);
    }
    
    bool operator>(const Studentas& other) const {
        return other < *this;
    }
    
    bool operator==(const Studentas& other) const {
        return pav == other.pav && var == other.var && gal == other.gal;
    }
    
    bool operator!=(const Studentas& other) const {
        return !(*this == other);
    }
};

void StudentuSarG(int n, int m);
double MatuotiLaika(const string& operacijosPavadinimas, function<void()> operacija);
template<typename Container>
void SkaitytiIsFailo(const string& failoVardas, Container& Grupe);

template<typename Container>
void Strategija1(Container& studentai, Container& vargsiukai, Container& kietiakai);
template<typename Container>
void Strategija2(Container& studentai, Container& vargsiukai);
template<typename Container>
void Strategija3(Container& studentai, Container& vargsiukai, Container& kietiakai);

template<typename Container>
double VykdytiStrategija(Container& studentai, int strategija);
template<typename Container>
void IrasytiIFaila(const string& failoVardas, const Container& studentai);

void RanksinisIvedimas(vector<Studentas>& Grupe);
void RanksinisIvedimas(list<Studentas>& Grupe);

template<typename Container>
void OptimizuotaStrategija1(Container& studentai, Container& vargsiukai, Container& kietiakai);
template<typename Container>
void OptimizuotaStrategija2(Container& studentai, Container& vargsiukai);
