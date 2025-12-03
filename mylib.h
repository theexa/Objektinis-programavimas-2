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
    std::string var;
    std::string pav;
    std::vector<int> paz;
    int egz;
    double gal;
    double med;
    std::string gr;
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
