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

struct Studentas {
    std::string pav;
    std::string var;
    std::vector<int> paz;
    int egz{0};
    double gal{0.0};
    double med{0.0};
    std::string gr;

    Studentas() = default;

    explicit Studentas(std::istream& is) {
        readFromStream(is);
    }

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
        } else egz = 0;

        paz = std::move(nums);
        computeResults();
    }

    void computeResults() {
        int sum = 0;
        for (int p : paz) sum += p;

        if (!paz.empty())
            gal = (sum / (double)paz.size()) * 0.4 + egz * 0.6;
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
        } else med = 0.0;

        gr = (gal < 5.0 ? "nuskriaustukai" : "kietuoliai");
    }

    ~Studentas() = default;
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
