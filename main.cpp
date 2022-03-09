#include <iostream>
#include "PtrCStringVector.h"


/**
  @mainpage Kolokwium z Podstaw Programowania 2 dnia 7 VI 2021

  Zasady ogolne:
  --------
  1. Zanim cokolwiek Panstwo zrobia prosze o uzupelnienie swoich danych w pliku: @ref main.cpp, dane te to:
      - @ref FIRSTNAME
      - @ref SURNAME
      - @ref MAIL
      - @ref BOOK_ID (nr albumu)
  2. Kolokwium nie da się nie zdać - jest traktowane jako punkty, które się sumują do reszty, nie będzie poprawki grupowej!
  3. W trakcie kolokwium nalezy miec wlaczona kamerke i nie miec sluchawek, kto będzie bez kamery to o 1/3 punktów mniej.
  4. Wyslana paczka ma sie bezwzglednie kompilowac na systemie Linux.
     - Jak ktos nie ma linuxa moze uzyc narzedzia: http://administrare.kis.agh.edu.pl:12345 (konieczny VPN AGH)
     i na nim zarejestrowac sie, ale jako nick powinien byc **numer albumu**, aczkolwiek prosze tez uzupelnic pozostale dane (imie, nazwisko, mail).
     - Aby wyslac zadanie nalezy wybrac konkurs (_kolokwium pp2_), problem (_kolokwium_), oraz jezyk programowania (_c++_), prosze zalaczyc obydwa pliki _PtrCStringVector.h, PtrCStringVector.cpp_, jak na obrazku:
        @image html domjudge.png
        @image latex domjudge.png
  5. Kolokwium z zalozenia bedzie sprawdzane automatycznie, przez testy jednostkowe dostepne w pliku: PtrCStringVectorTests.cpp,
     dlatego poza kompilowaniem prosze aby nie crashowalo na zadnym tescie, jesli tak sie dzieje to brane pod uwage jest tylko tyle testow ile ich przechodzi do momentu crasha.
  6. Mam program antyplagiatowy, dlatego prosze pracowac samodzielnie!
     Osoby ktore udostepniaja swoje rozwiazania rowniez beda mialy kare!
  7. *Dobrze jakby nie bylo warningow kompilacji (flagi: `-Wall -Wextra -pedantic -Werror`, a dla hardcorów jeszcze:  `-Weffc++`)
  8. Punkty beda odejmowane za wycieki pamieci (jest podpiety `valgrind`)
  9. Zakres materiału: wykłady [1, 10]
  10. Niewykluczone jest sprawdzanie reczne - zaleznie od prowadzacego dana grupe.
      Dlatego prosze wykorzystac zapas czasu aby doprowadzic kod do porzadku nie tylko do dzialania.
  _________
  Szczegolowa tresc kolokwium znajda Panstwo w opisie metod klasy: @ref PtrCStringVector
*/

/// @todo Uzupelnij swoje dane:
constexpr const char* const FIRSTNAME = "Piotr";
constexpr const char* const SURNAME   = "Sokołowski";
constexpr const char* const MAIL    = "student[at]student.agh.edu.pl";
constexpr const char* const BOOK_ID = "123456";
constexpr const char* const teacherMail = "bazior[at]agh.edu.pl"; // change if not correct

void validateStudentsInfo();


int main()
{
    std::cout << "Hello " << FIRSTNAME << " " << SURNAME << "!" << std::endl;
    return 0;
}


constexpr inline size_t compileTimeStrlen(const char* text) noexcept
{
    return (*text ? 1+compileTimeStrlen(text+1) : 0);
}

constexpr inline size_t compileTimeCountFirstDigits(const char* text) noexcept
{
    return (*text && ('0'<=*text && *text<='9') ? 1+compileTimeCountFirstDigits(text+1) : 0);
}

constexpr inline bool compileTimeIsDigit(const char* text) noexcept
{
    return compileTimeStrlen(text) == compileTimeCountFirstDigits(text);
}

void validateStudentsInfo()
{
    static_assert(compileTimeStrlen(FIRSTNAME) > 2, "You must input your first name!");
    static_assert(compileTimeStrlen(SURNAME) > 2, "You must input your surname!");

    static_assert(compileTimeStrlen(BOOK_ID) > 1, "You must input your student book id!");
    static_assert(compileTimeIsDigit(BOOK_ID), "You student book id should consist only digits, shouldn't it?!");

    static_assert(compileTimeStrlen(MAIL) > 3, "You must input your mail (preferred not gmail)!");
}
