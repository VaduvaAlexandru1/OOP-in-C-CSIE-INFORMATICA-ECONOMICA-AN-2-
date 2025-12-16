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

	Produs(const Produs& p , int idNou) : id(idNou) {
		this->denumire = p.denumire;
		this->stoc = p.stoc;
		this->pret = p.pret;
	}

	Produs operator=(const Produs& p) {
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


int main() {
	Produs p1(12, "pix", 10, 150), p2(p1 , 13);
	p1 += 10;
	p1 = 10 + p2;
	cout << p1;
	return 0;
}