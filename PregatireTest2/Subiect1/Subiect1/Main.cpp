#include <iostream>
using namespace std;

class Produs {
	const int id;
	string denumire;
	int stoc;
	double pret;

public:
	Produs(int _id, string _denumire, int _stoc, double _pret) :id(_id) {
		this->denumire = _denumire;
		this->stoc = _stoc;
		this->pret = _pret;
	}
	Produs() : id(0), denumire(""), stoc(0), pret(0.0) {}


	Produs(const Produs& p , int idNou) : id(idNou) {
		this->denumire = p.denumire;
		this->stoc = p.stoc;
		this->pret = p.pret;
	}

	Produs& operator=(const Produs& p) {
		if (this != &p) {
			this->denumire = p.denumire;
			this->stoc = p.stoc;
			this->pret = p.pret;
		}
		return *this;
	}

	Produs& operator+=(int newStoc) {
		if (newStoc <= 0) return *this;
		this->stoc += newStoc;
		return *this;
	}
	friend Produs operator+(int _stoc, const Produs& p);
	friend ostream& operator<<(ostream& out, const Produs& p);
	friend class Magazin;

};
Produs operator+(int _stoc, const Produs& p) {
	Produs copie = p;
	copie += _stoc;
	return copie;
}

ostream& operator<<(ostream& out , const Produs& p) {
	out << "ID : " << p.id << endl;
	out << "Denumire : " << p.denumire << endl;
	out << "Stoc : " << p.stoc << endl;
	out << "Pret : " << p.pret << endl;
	return out;
}

class Magazin {
	int nrProduse;
	Produs* produse;
public :
	Magazin() {
		this->nrProduse = 0;
		this->produse = nullptr;
	}

	Magazin(int _nrProduse, Produs* _produse) {

		if (_nrProduse > 0) this->nrProduse = _nrProduse;
		else this->nrProduse = 0;

		if (_produse != nullptr && _nrProduse > 0) {
			this->produse = new Produs[_nrProduse];
			for (int i = 0; i < _nrProduse; i++)
				this->produse[i] = _produse[i];
		}
		else {
			this->produse = nullptr;
		}
	}
	~Magazin() {
		delete[] produse;
	}

	float vanzari() {
		double sumaVanzari = 0;
		for (int i = 0; i < this->nrProduse; i++) {
			sumaVanzari += (this->produse)[i].stoc * (this->produse)[i].pret;
		}
		return 0.1 * sumaVanzari;
	}

	float operator-(float nr) {
		return this->vanzari() - nr;
	}


};



int main() {
	Produs p1(12, "pix", 10, 150), p2(p1 , 13);
	p1 += 10;
	p1 = 10 + p2;
	cout << p1;
	cout << "----------------------------------" << endl;
	Produs lista[2] = { p1, p2 };
	Magazin m1(2, lista);

	float chirie = 200;
	if (m1 - chirie > 0) cout << "Magazinul nu este in pierdere";
	m1++;


	return 0;
}