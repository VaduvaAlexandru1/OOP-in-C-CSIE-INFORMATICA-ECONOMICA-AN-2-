#include <iostream>
#include <vector>
using namespace std;

class Angajat {
	static int marcaGenerator;
	const int marca;
	string nume;
public:
	Angajat() : marca(++marcaGenerator) {}
	Angajat(string _nume) : marca(++marcaGenerator) { this->nume = _nume; }
	Angajat(const Angajat& a) : marca(a.marca) { this->nume = a.nume; }

	int getMarca() const {
		return this->marca;
	}
	string getNume() const {
		return this->nume;
	}

	void setNume(string _nume) {
		this->nume = _nume;
	}
	friend ostream& operator<<(ostream& ost, const Angajat& a) {
		ost << "MARCA : " << a.marca << endl;
		ost << "NUME : " << a.nume << endl;
		ost << "SALARIU : " << a.calculSalariu();
		return ost;
	}
	virtual double calculSalariu() const = 0;
	virtual ~Angajat() = default;
};

class Inginer : public Angajat {
	int numarOre;
	double salariuOrar;
	int spor;
public:
	Inginer() : Angajat(){}
	Inginer(string _nume, int _numarOre, double _salariuOrar, int _spor) : Angajat(_nume) {
		this->numarOre = _numarOre;
		this->salariuOrar = _salariuOrar;
		this->spor = _spor;
	}
	Inginer(const Inginer& i) : Angajat(i) {
		this->numarOre = i.numarOre;
		this->salariuOrar = i.salariuOrar;
		this->spor = i.spor;
	}

	//getter
	int getNumarOre() const {
		return this->numarOre;
	}
	int getSpor() const {
		return this->spor;
	}
	double getSalariuOrar() const {
		return this->salariuOrar;
	}

	//setter
	void setNumarOre(int _numarOre) {
		this->numarOre = _numarOre;
	}
	void setSpor(int _spor) {
		this->spor = _spor;
	}
	void setSalariuOrar(double _salariuOrar) {
		this->salariuOrar = _salariuOrar;
	}
	//calcul salariu
	double calculSalariu() const override {
		return (this->salariuOrar * this->numarOre) * (1 + (double)spor / 100);
	}

};
class Muncitor : public Angajat {
	int numarPiese;
	double manoperaPerPiesa;
public:
	Muncitor() : Angajat() {};
	Muncitor(string _nume , int _numarPiese , double _manoperaPerPiesa) : Angajat(_nume) {
		this->numarPiese = _numarPiese;
		this->manoperaPerPiesa = _manoperaPerPiesa;
	};
	Muncitor(const Muncitor& m) : Angajat(m) {
		this->numarPiese = m.numarPiese;
		this->manoperaPerPiesa = m.manoperaPerPiesa;
	}
	//getter
	int getNumarPiese() const {
		return this->numarPiese;
	}
	double getManoperaPerPiesa() const {
		return this->manoperaPerPiesa;
	}

	//setter
	void setNumarPiese(int _numarPiese) {
		this->numarPiese = _numarPiese;
	}
	void setManoperaPerPiesa(double _manoperaPerPiesa) {
		this->manoperaPerPiesa = _manoperaPerPiesa;
	}

	//calcul salariu
	double calculSalariu() const override {
		return this->manoperaPerPiesa * this->numarPiese;
	}

};

void afisareStat(vector<Angajat*> angajati) {
	for (auto& angajat : angajati) {
		if (dynamic_cast<Inginer*>(angajat)) cout << "I : ";
		else if (dynamic_cast<Muncitor*>(angajat)) cout << "M : ";
		cout << angajat->getMarca()<<", "<<angajat->getNume()<<", " << angajat->calculSalariu() << endl;
	}
}

int Angajat::marcaGenerator = 0;

int main() {
	// Creăm vectorul de angajați
	vector<Angajat*> angajati;

	// Adăugăm câțiva Ingineri
	angajati.push_back(new Inginer("Ion Popescu", 160, 50, 10)); 
	angajati.push_back(new Inginer("Maria Ionescu", 150, 60, 15));

	// Adăugăm câțiva Muncitori
	angajati.push_back(new Muncitor("Gheorghe Vasilescu", 200, 5.5));  
	angajati.push_back(new Muncitor("Ana Marinescu", 150, 6.0));

	// Apelăm funcția de afișare
	afisareStat(angajati);

	// Eliberăm memoria alocată dinamic
	for (auto a : angajati) {
		delete a;
	}

	return 0;
}