#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "mylib.h"
#include <sstream>

/* ================================
   Getteriai ir setteriai
   ================================ */
TEST_CASE("getteriai ir setteriai") {
    Studentas s;

    s.setVardas("Vard");
    s.setPavarde("Pav");
    s.setPazymiai({10, 9, 8});
    s.setEgzaminas(9);

    CHECK(s.getVardas() == "Vard");
    CHECK(s.getPavarde() == "Pav");
    CHECK(s.getPazymiai().size() == 3);
    CHECK(s.getPazymiai()[0] == 10);
    CHECK(s.getEgzaminas() == 9);
}

/* ================================
   Default konstruktorius
   ================================ */
TEST_CASE("default konstruktorius") {
    Studentas s;

    CHECK(s.getEgzaminas() == 0);
    CHECK(s.getPazymiai().empty());
    CHECK(s.getGalutinis() == doctest::Approx(0.0));
    CHECK(s.getMediana() == doctest::Approx(0.0));
}

/* ================================
   Copy konstruktorius
   ================================ */
TEST_CASE("copy konstruktorius") {
    Studentas s1;
    s1.setVardas("Vardenis");
    s1.setPavarde("Pavardenis");
    s1.setPazymiai({5, 6, 7});
    s1.setEgzaminas(8);
    s1.computeResults();

    Studentas s2(s1);

    CHECK(s2.getVardas() == "Vardenis");
    CHECK(s2.getPavarde() == "Pavardenis");
    CHECK(s2.getPazymiai().size() == 3);
    CHECK(s2.getPazymiai()[1] == 6);
    CHECK(s2.getEgzaminas() == 8);
    CHECK(s2.getGalutinis() == doctest::Approx(s1.getGalutinis()));
    CHECK(s2.getMediana() == doctest::Approx(s1.getMediana()));
}

/* ================================
   Copy assignment operatorius
   ================================ */
TEST_CASE("copy assignment operatorius") {
    Studentas s1;
    s1.setVardas("Vardas");
    s1.setPavarde("Pavarde");
    s1.setPazymiai({9, 9});
    s1.setEgzaminas(10);
    s1.computeResults();

    Studentas s2;
    s2.setVardas("Vardelis");
    s2.setPavarde("Pavardelis");
    s2.setPazymiai({1});
    s2.setEgzaminas(2);

    s2 = s1;

    CHECK(s2.getVardas() == "Vardas");
    CHECK(s2.getPavarde() == "Pavarde");
    CHECK(s2.getPazymiai().size() == 2);
    CHECK(s2.getPazymiai()[0] == 9);
    CHECK(s2.getEgzaminas() == 10);
    CHECK(s2.getGalutinis() == doctest::Approx(s1.getGalutinis()));
    CHECK(s2.getMediana() == doctest::Approx(s1.getMediana()));
}

/* ================================
   Operator <<
   ================================ */
TEST_CASE("operator<<") {
    Studentas s;
    s.setVardas("Vard");
    s.setPavarde("Pav");
    s.setPazymiai({10, 9});
    s.setEgzaminas(8);
    s.computeResults();

    std::ostringstream oss;
    oss << s;

    std::string out = oss.str();
    CHECK_FALSE(out.empty());
    CHECK(out.find("Vard") != std::string::npos);
    CHECK(out.find("Pav") != std::string::npos);
}
