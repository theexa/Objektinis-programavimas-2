#include "mylib.h"
using namespace std;

std::ostream& operator<<(std::ostream& out, const Studentas& stud) {
    out << std::left
        << std::setw(15) << stud.pav
        << std::setw(15) << stud.var
        << std::fixed << std::setprecision(2)
        << std::setw(10) << stud.gal
        << std::setw(10) << stud.med
        << std::setw(20) << stud.gr;

    return out;
}

std::istream& operator>>(std::istream& in, Studentas& stud) {
    std::cout << "\n--- Naujo studento ivedimas ---\n";

    std::cout << "Iveskite pavarde: ";
    in >> stud.pav;

    std::cout << "Iveskite varda: ";
    in >> stud.var;

    stud.paz.clear();
    int pazymys;

    std::cout << "Iveskite pazymius (baigti -1):\n";
    while (true) {
        std::cout << "Pazymys: ";
        in >> pazymys;

        if (!in) {
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Neteisinga ivestis.\n";
            continue;
        }

        if (pazymys == -1) break;
        if (pazymys >= 0 && pazymys <= 10)
            stud.paz.push_back(pazymys);
        else
            std::cout << "Pazymys turi buti 0-10!\n";
    }

    std::cout << "Iveskite egzamino pazymi: ";
    while (!(in >> stud.egz) || stud.egz < 0 || stud.egz > 10) {
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Klaida! Egzaminas turi buti 0-10: ";
    }

    stud.computeResults(); // perskaičiuojam galutinį
    return in;
}
