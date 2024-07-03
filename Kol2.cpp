#include "Wybor.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace std;

#ifdef Kol_2

class Wlasciciel {};

class Samochod {
protected:
	char m_tablicarejestracyjna[7] = {};
	int m_przebieg;
	bool m_stan;
	Wlasciciel* m_wlasciciel;
    static Samochod* instancja_wzorcowa;
    static constexpr double WART_POCZ = 10000.0;

public:
    void setPrzebieg(int przebieg)
    {
        if (przebieg < 0)
        {
            throw invalid_argument("ERROR! przebieg samochodu mniejszy od 0");
        }
        m_przebieg = przebieg;
    }

    int getPrzebieg() const
    {
        return m_przebieg;
    }

  /*
    void setStan(bool stan)
    {
        m_stan = stan;
    }

    bool getStan() const
    {
        return m_stan;
    }
  */

    Samochod(const char* rejestracja, double przebieg, bool stan, Wlasciciel* wlasciciel) {
        strcpy_s(m_tablicarejestracyjna, rejestracja);
        setPrzebieg(przebieg);
        m_stan = stan;
        m_wlasciciel = wlasciciel;
    };

    Samochod() {
        if (!instancja_wzorcowa) 
        {
            throw runtime_error("ERROR! brak wzorcowego samochodu");
        }
        strcpy_s(m_tablicarejestracyjna, instancja_wzorcowa->m_tablicarejestracyjna);
        m_przebieg = instancja_wzorcowa->m_przebieg;
        m_stan = instancja_wzorcowa->m_stan;
        m_wlasciciel = instancja_wzorcowa->m_wlasciciel;
    };

    virtual double obliczZasieg() const
    {
        return 800.0;
    }

    operator double()
    {
        double WSP_SPARW;
        if (m_stan == true)
        {
            WSP_SPARW = 1.0;
        }
        else
        {
            WSP_SPARW = 0.2;
        }
        double wartosc = (WART_POCZ - 0.2 * m_przebieg) * WSP_SPARW;
        if (wartosc < 400.0)
        {
            wartosc = 400.0;
        }
        return wartosc;
    }

    bool operator!=(const Samochod& porownywany) const 
    {
        return abs(m_przebieg - porownywany.m_przebieg) > 20 or m_stan != porownywany.m_stan;
    }
};

class SamochodElektryczny : public Samochod
{
protected:
    int m_stanbaterii;

public:
    SamochodElektryczny(const char* rejestracja, int przebieg, bool stan, Wlasciciel* wlasciciel, int bateria)
        : Samochod(rejestracja, przebieg, stan, wlasciciel)
    {
        if (bateria < 0)
        {
            m_stanbaterii = 0;
        }
        else if (bateria > 100)
        {
            m_stanbaterii = 100;
        }
    };

    double obliczZasieg() const override
    {
        if (m_stan == false)
        {
            throw logic_error("ERROR! pojazd niedopuszczony do ruchu");
        }
        else
        return 2.5 * m_stanbaterii;
    }

    operator double()
    {
        double WSP_SPARW;
        if (m_stan == true)
        {
            WSP_SPARW = 1.0;
        }
        else
        {
            WSP_SPARW = 0.2;
        }
        double wartosc = 0.7 * (WART_POCZ - 0.2 * m_przebieg) * WSP_SPARW;
        if (wartosc < 400.0)
        {
            wartosc = 400.0;
        }
        return wartosc;
    }
};

Samochod* Samochod::instancja_wzorcowa = nullptr;

int main()
{
    return 0;
}

#endif
