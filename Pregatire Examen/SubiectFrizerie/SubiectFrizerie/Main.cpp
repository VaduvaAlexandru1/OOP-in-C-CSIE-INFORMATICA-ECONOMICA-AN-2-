#include <iostream>
#include <cstring>
#include <unordered_map>
using namespace std;

class Serviciu {
	
public : virtual int calculPret() = 0;
};

class Tuns : public Serviciu {
	int nr = 0;
	int pret = 50;
public:
	Tuns(){}
	Tuns(int _nr) : Serviciu() { this->nr = _nr; }
	int calculPret() {
		return nr * pret;
	}
	friend class Frizerie;

};

class Frezat : public Serviciu {
	int nr = 0;
	int pret = 70;
public:
	Frezat(){}
	Frezat(int _nr) : Serviciu() { this->nr = _nr; }
	int calculPret() {
		return nr * pret;
	}
	friend class Frizerie;

};

class Barbierit : public Serviciu {
	int nr = 0;
	int pret = 40;
public:
	Barbierit(){}
	Barbierit(int _nr) : Serviciu() { this->nr = _nr; }
	int calculPret() {
		return nr * pret;
	}
	friend class Frizerie;
};

enum tipFrizerie {
	salon,
	clasica,
	barbershop
};

enum tipServicii {
	tuns, frezat, barbierit
};
const char* tipFrizerieToString(tipFrizerie tip);

class Frizerie {
	static int lungimeMinimaDenumire;
	const int id;
	static int generator;
	char* denumire;
	int nrAngajati;
	Tuns t;
	Frezat f;
	Barbierit b;
	Serviciu* servicii[3] = {&t , &f , &b};
protected:
	tipFrizerie tip;
public:

	Frizerie() : id(++generator) {}
	Frizerie(const char* _denumire , tipFrizerie _tip , int _nrAngajati) : id(++generator) {
		int len = strlen(_denumire) + 1;

		if (len < lungimeMinimaDenumire) {
			this->denumire = nullptr;
		}
		else {
			this->denumire = new char[len];
			strcpy_s(this->denumire, len, _denumire);
		}
		this->tip = _tip;
		this->nrAngajati = _nrAngajati;
	}
	Frizerie(const Frizerie& f): id(f.id) {
		int len = strlen(f.denumire) + 1;

		if (len < lungimeMinimaDenumire) {
			this->denumire = nullptr;
		}
		else {
			this->denumire = new char[len];
			strcpy_s(this->denumire, len, f.denumire);
		}
		this->tip = f.tip;
		this->nrAngajati = f.nrAngajati;
	}
	int calculTotal() {
		int total = 0;
		for (int i = 0; i < 3; i++)
			total += servicii[i]->calculPret();
		return total;
	}

	static void setLungimeMinimaDenumire(int len) {
		lungimeMinimaDenumire = len;
	}

	void setDenumire(const char* den) {
		delete[] this->denumire;
		this->denumire = new char[strlen(den) + 1];
		strcpy_s(this->denumire, strlen(den) + 1, den);
	}

	//const pentru a nu fi modificat la get
	const char* getDenumire() {
		return this->denumire;
	}

	friend ostream& operator<<(ostream& ost, const Frizerie& f) {
		ost << "Denumire : " << f.denumire << endl;
		ost << "Tip : " << tipFrizerieToString(f.tip) << endl;
		ost << "Nr angajati : " << f.nrAngajati << endl;
		return ost;
	}

	friend istream& operator>>(istream& ist, Frizerie& f) {
		const int MAXLEN = 100;
		char buffer[MAXLEN];
		ist.getline(buffer, MAXLEN);
		delete[] f.denumire;
		f.denumire = new char[strlen(buffer) + 1];
		strcpy_s(f.denumire, strlen(buffer) + 1, buffer);
		return ist;
	}

	Frizerie& operator += (tipServicii serviciu) {
		switch (serviciu) {
		case tuns: (this->t).nr++;
			break;
		case frezat: (this->f).nr++;
			break;
		case barbierit: (this->b).nr++;
			break;
		default:return *this;
		}
		return *this;
	}
	Frizerie& operator -= (tipServicii serviciu) {
		switch (serviciu) {
		case tuns: (this->t).nr != 0 ? (this->t).nr-- : 0;
			break;
		case frezat: (this->f).nr != 0 ? (this->f).nr-- : 0;
			break;
		case barbierit: (this->b).nr != 0 ? (this->b).nr-- : 0;
			break;
		default:return *this;
		}
		return *this;
	}
};

const char* tipFrizerieToString(tipFrizerie tip) {
	switch (tip) {
	case salon: return "salon";
	case clasica: return "clasica";
	case barbershop: return "barbershop";
	default: return "anonim";
	};
}

int Frizerie::generator = 0;
int Frizerie::lungimeMinimaDenumire = 4;

unordered_map<tipServicii, int> preturi = {
	{tuns , 50},
	{frezat , 70},
	{barbierit , 40}
};

int getPretServiciu(tipServicii tip) {
	return preturi[tip];
}

int main() {
	Frizerie f1;
	Frizerie f2("La mihai", tipFrizerie::barbershop, 3);
	Frizerie f3 = f2;
	Frizerie::setLungimeMinimaDenumire(5);
	f3.setDenumire("E1 Saloon");
	cout << f3.getDenumire() << endl;
	//cout << f2;
	//cin >> f2;
	//cout << f2;
	f2 += tuns;
	cout << f2.calculTotal();
	return 0;
}