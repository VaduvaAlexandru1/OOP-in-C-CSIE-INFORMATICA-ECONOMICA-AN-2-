#include <iostream>
#include <string>
using namespace std;

class Om {
public:
	virtual void afisare() = 0;
	virtual float calculSalariu() = 0;
};

class Angajat : public Om{
protected:
	string nume = "Anonim";
	float salariuDeBaza = 0;
public:
	Angajat() {};
	Angajat(string _nume, float _salariuDeBaza) {
		this->nume = _nume;
		this->salariuDeBaza = _salariuDeBaza;
	}
	Angajat(const Angajat& a) {
		this->nume = a.nume;
		this->salariuDeBaza = a.salariuDeBaza;
	}
	Angajat& operator=(const Angajat& a) {
		if (this != &a) {
			this->nume = a.nume;
			this->salariuDeBaza = a.salariuDeBaza;
		}
		return *this;
	}
	void afisare() override {
		cout << *this;
	}
	float calculSalariu() override {
		return this->salariuDeBaza;
	}
	friend ostream& operator<<(ostream& out, const Angajat& a);
};

class Manager : public Angajat {
private:
	int subordonati = 0;
public:
	Manager() : Angajat() {};
	Manager(string _nume , float _salariu , int _subordonati) : Angajat(_nume , _salariu) {
		this->subordonati = _subordonati;
	}
	Manager(const Manager& m) : Angajat(m) {
		this->subordonati = m.subordonati;
	}
	void afisare() override {
		cout << *this;
	}
	float calculSalariu() override {
		return Angajat :: calculSalariu() + 100 * this->subordonati;
	}
	friend ostream& operator<<(ostream& out, const Manager& a);

};

class Paznic : public Angajat {
private:
	int nrZileNoapte = 0;
	static float sporNoapte;
public:
	Paznic() : Angajat(){}
	Paznic(string _nume, float _salariu, int _nrZileNoapte) : Angajat(_nume, _salariu) {
		this->nrZileNoapte = _nrZileNoapte;
	}
	Paznic(const Paznic& p) : Angajat(p) {
		this->nrZileNoapte = p.nrZileNoapte;
	}
	Paznic& operator=(const Paznic& p) {
		if (this != &p) {
			Angajat::operator=(p);
			this->nrZileNoapte = p.nrZileNoapte;
		}
		return *this;
	}
	void afisare() override {
		cout << *this;
	}
	float calculSalariu() override {
		return Angajat::calculSalariu() + this->nrZileNoapte * (1 + sporNoapte) * salariuDeBaza / 20;
	}
	friend ostream& operator<<(ostream& out, const Paznic& p);

};

float Paznic::sporNoapte = 0.2;

ostream& operator<<(ostream& out, const Angajat& a) {
	out << "Nume : " << a.nume << endl;
	out << "Salariu de baza : " << a.salariuDeBaza << endl;

	return out;
}

ostream& operator<<(ostream& out, const Manager& m) {
	out << (Angajat)m;
	out << "Nr subordonati : " << m.subordonati << endl;

	return out;
}

ostream& operator<<(ostream& out, const Paznic& p) {
	out << (Angajat)p;
	out << "Nr zile noapte : " << p.nrZileNoapte << endl;

	return out;
}
int main() {
	// 1️ Creăm obiecte concrete
	Angajat a1("Angajat Gigel", 1000);
	Manager m1("Manager Gigel", 1000, 10);
	Paznic p1("Paznic Gigel", 1000, 3);

	// 2️ Calcul salariu individual
	cout << "\nSalariu Angajat: " << a1.calculSalariu() << endl;
	cout << "Salariu Manager: " << m1.calculSalariu() << endl;
	cout << "Salariu Paznic: " << p1.calculSalariu() << endl;

	// 3️ Total salarii folosind vector de OBIECTE 
	Angajat v[] = { a1, m1, p1 };
	float totalSalariiObiecte = 0;
	for (int i = 0; i < 3; i++) {
		totalSalariiObiecte += v[i].calculSalariu(); //  object slicing!
	}
	cout << "\nTotal salarii (vector de obiecte): " << totalSalariiObiecte << endl;

	// 4️ Total salarii folosind vector de POINTERI 
	Angajat* vp[] = { &a1, &m1, &p1 };
	float totalSalariiPointeri = 0;
	for (int i = 0; i < 3; i++) {
		totalSalariiPointeri += vp[i]->calculSalariu(); // polimorfismul funcționează
	}
	cout << "Total salarii (vector de pointeri): " << totalSalariiPointeri << endl;

	// 5️ Polimorfism cu clasa abstractă
	Om* o1 = &a1;
	Om* o2 = &m1;
	Om* o3 = &p1;

	cout << "\nAfisare prin pointeri la Om:" << endl;
	o1->afisare();
	o2->afisare();
	o3->afisare();

	return 0;
}

class c {
	int a;
public:
	void init(int nr = 0) { a = nr; }
	int inc() { return a++; }
};

typedef int(c::* PM);