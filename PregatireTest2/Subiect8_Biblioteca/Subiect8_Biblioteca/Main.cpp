#include <iostream>
#include <stdexcept>
using namespace std;

class Carte {
	const unsigned int cod;
	static int generator;
	string titlu = "Anonim";
	unsigned int nrPagini = 0;
	unsigned int anAparitie = 0;
	float pret = 0;

public:
	Carte(int _cod = 0) : cod(_cod != 0 ? _cod : ++generator) {};
	Carte(int _cod, string _titlu, unsigned int _nrPagini, unsigned int _anAparatie, float _pret) : cod(_cod) {
		this->titlu = _titlu;
		this->nrPagini = _nrPagini;
		this->anAparitie = _anAparatie;
		_pret > 0 ? this->pret = _pret : 0;
	}
	Carte(const Carte& c) : cod(c.cod) {
		this->titlu = c.titlu;
		this->nrPagini = c.nrPagini;
		this->anAparitie = c.anAparitie;
		c.pret > 0 ? this->pret = c.pret : 0;
	}

	Carte& operator=(const Carte& c) {
		if (this == &c)
			return *this;

		titlu = c.titlu;
		nrPagini = c.nrPagini;
		anAparitie = c.anAparitie;
		pret = c.pret;

		return *this;
	}


	friend ostream& operator<<(ostream& out, const Carte& c);
	friend int operator+(const Carte& c1, const Carte& c2);
	friend bool operator<=(int nr , const Carte& c);
	friend class Biblioteca;

};

ostream& operator<<(ostream& out, const Carte& c) {
	out << "COD : " << c.cod << endl;
	out << "Titlu : " << c.titlu << endl;
	out << "Nr pagini : " << c.nrPagini << endl;
	out << "An aparitie : " << c.anAparitie << endl;
	out << "Pret : " << c.pret << endl;

	return out;
}

int operator+(const Carte& c1, const Carte& c2) {
	return c1.nrPagini + c2.nrPagini;
}

bool operator<=(int nr , const Carte& c) {
	return nr <= c.nrPagini;
}

int Carte::generator = 0;

class Biblioteca {
	string nume;
	Carte* carti;
	int nrCarti;
public:
	Biblioteca() {};
	Biblioteca(string _nume, Carte* _carti, int _nrCarti) {
		this->nume = _nume;
		this->nrCarti = _nrCarti;
		
		this->carti = new Carte[this->nrCarti];
		for (int i = 0; i < this->nrCarti; ++i)
			(this->carti)[i] = _carti[i];
	}
	~Biblioteca() {
		delete[] carti;
	}

	friend ostream& operator<<(ostream& out , const Biblioteca& b);

	void stergeCarte(string numeCarte) {
		int poz = -1;

		for (int i = 0; i < this->nrCarti && poz != -1; ++i)
			if ((this->carti)[i].titlu == numeCarte)
				poz = i;
		
		if (poz == -1) throw runtime_error("Cartea nu a fost gasita : " + numeCarte);

		Carte* copieCarti = new Carte[nrCarti - 1];

		for (int i = 0, j = 0; i < this->nrCarti; ++i)
			if (i != poz) copieCarti[j++] = (this->carti)[i];

		delete[] this->carti;

		this->carti = copieCarti;
		this->nrCarti--;
	}

	operator double() const {
		double pretMediu = 0;
		for (int i = 0; i < this->nrCarti; ++i) pretMediu += (this->carti)[i].pret;
		return pretMediu;
	}

	bool operator!=(string numeCarte) {
		for (int i = 0; i < this->nrCarti; ++i)
			if ((this->carti)[i].titlu == numeCarte) return false;
		return true;
	}
}; 
ostream& operator<<(ostream& out , const Biblioteca& b) {
	out << "NUME : " << b.nume << endl;
	for (int i = 0; i < b.nrCarti; ++i) out << "CARTE NR." << i + 1 << endl << b.carti[i] << endl;

	return out;
}

int main() {
	Carte c1(102, "Crima si pedeapsa", 358, 2009, 45.5), c2(105);
	Carte carti[10];
	int totalPagini = c1 + c2;
	cout << c1;
	cout << totalPagini << endl;
	if (100 <= c1) cout << "Cartea are cel putin 100 pagini" << endl;

	//Biblioteca
	Biblioteca b1("Universitara", carti, 5);
	try {
		b1.stergeCarte("Crima si pedeapsa");
	}
	catch (const runtime_error& err){
		cout << "Eroare " << err.what() << endl;
	}
	cout << b1;

	double pretMediu = b1;
	cout << "Pret mediu : " << pretMediu << endl;

	//ORIGINAL : cout << (b1 != "Crima si pedeapsa") , am adaugat un ternar ca sa ofer un output mai explicit 
	cout << ((b1 != "Crima si pedeapsa") ? "true" : "false");
	return 0;
}