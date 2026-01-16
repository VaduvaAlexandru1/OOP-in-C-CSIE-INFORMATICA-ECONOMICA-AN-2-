#include <iostream>
using namespace std;

enum tipCarte
{
	A , B , C
};

class Carte {
	const int isbn;
	static int generator;
	string titlu = "Fara Titlu";
	string primulAutor = "Anonim";
	tipCarte tip = A;
	int numarExemplare = 0;
	float pret = 0;
public:
	Carte(): isbn(++generator){}
	Carte(string _titlu , string _primulAutor , int _numarExemplare , float _pret) : isbn(++generator) {
		this->titlu = _titlu;
		this->primulAutor = _primulAutor;
		_numarExemplare > 0 ? this->numarExemplare = _numarExemplare : this->numarExemplare = 0;
		_pret > 0 ? this->pret = _pret : this->pret = 0;
	}
	Carte& operator=(const Carte& c) {
		if (this == &c) return *this;
		this->titlu = c.titlu;
		this->primulAutor = c.primulAutor;
		c.numarExemplare > 0 ? this->numarExemplare = c.numarExemplare : this->numarExemplare = 0;
		c.pret > 0 ? this->pret = c.pret : this->pret = 0;
	}
	friend ostream& operator<<(ostream& out, const Carte& c);

	explicit operator int() const {
		return this->numarExemplare;
	}
};

int Carte::generator = 0;

ostream& operator<<(ostream& out , const Carte& c) {
	out << "TITLU : " << c.titlu << endl;
	out << "PRIMUL AUTOR : " << c.primulAutor << endl;
	out << "NUMAR EXEMPLARE : " << c.numarExemplare << endl;
	out << "PRET : " << c.pret << endl;
	return out;
}

class Librarie {
	string nume;
	Carte* vectorCarti;
	int nrCarti;
public:
	Librarie() {};
	Librarie(string _nume, Carte* _vectorCarti , int _nrCarti) {
		this->nume = _nume;
		this->nrCarti = _nrCarti;
		if (_vectorCarti != nullptr && _nrCarti > 0) {
			this->vectorCarti = new Carte[_nrCarti];
			for (int i = 0; i < _nrCarti; i++) {
				this->vectorCarti[i] = _vectorCarti[i];
			}
		}
		else {
			this->vectorCarti = nullptr;
			this->nrCarti = 0;
		}
	}

	friend ostream& operator<<(ostream& out, const Librarie& l);

	void adaugaCarte(const Carte& c) {
		Carte* copieCarti = new Carte[this->nrCarti + 1];

		for (int i = 0; i < nrCarti; i++) {
			copieCarti[i] = (this->vectorCarti)[i];
		}
		copieCarti[this->nrCarti] = c;
		delete[] this->vectorCarti;
		this->vectorCarti = copieCarti;
		this->nrCarti++;
	}

	~Librarie() {
		delete[] this->vectorCarti;
	}
};

ostream& operator<<(ostream& out, const Librarie& l) {
	out << "NUME : " << l.nume;
	for (int i = 0; i < l.nrCarti; ++i) {
		out << "CARTE NR." << i + 1 << " : " << endl;
		out << l.vectorCarti[i] << endl;
	}

	return out;
}
int main() {
	Carte c1("Crima si pedeapsa", "Dostoevsky", 10, 45.5);
	Carte vectorCarti[10];
	cout << c1;
	cout << (int)c1;

	Librarie l1("Carturesti", vectorCarti, 5);
	cout << l1;

	l1.adaugaCarte(c1);

	cout << l1;
	return 0;
}