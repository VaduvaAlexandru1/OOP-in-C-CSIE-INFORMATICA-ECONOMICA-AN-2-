#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

class Produs {
	static int generator;
protected:
	const string cod;
	string nume;
	double pret;
	map<string, int> stocPeMarimi{
		{"S" , 0},
		{"M" , 0},
		{"L" , 0},
		{"XL" , 0}
	};
public:
	Produs() :cod(to_string(++generator)) {};
	Produs(string _nume , double _pret) :cod(to_string(++generator)) {
		this->nume = _nume;
		this->pret = _pret;
	};
	//default virtual deconstructor
	virtual ~Produs() = default;
	virtual string getCategorie() = 0;
	virtual double getPretFinal() { return pret; }
	virtual void print(ostream& ost) = 0;
	friend class Magazin;
};
int Produs::generator = 0;

class Tricou : public Produs{
	string producator;
public:
	Tricou():Produs() {};
	Tricou(string _producator , string _nume , float _pret) : Produs(_nume , _pret){
		this->producator = _producator;
	}
	string getCategorie(){
		return "tricou";
	}

	int stocTotal() {
		int total = 0;
		for (const auto& item : this->stocPeMarimi) {
			total += item.second;
		}
		return total;
	}

	double getPretFinal() override {
		return stocTotal() > 100 ? this->pret * .9 : this->pret;
	}
	void print(ostream& ost) override {
		ost << "Cod : " << this->cod << endl;
		ost << "Nume : " << this->nume << endl;
		ost << "Pret : " << this->pret << endl;
		ost << "Producator : " << this->producator << endl;
		ost << "Stoc marime S : " << this->stocPeMarimi["S"] << endl;
		ost << "Stoc marime M : " << this->stocPeMarimi["M"] << endl;
		ost << "Stoc marime L : " << this->stocPeMarimi["L"] << endl;
		ost << "Stoc marime XL : " << this->stocPeMarimi["XL"] << endl;

	}
	
};
class Pantaloni : public Produs {
	string culoare;
public:
	Pantaloni() :Produs() {};
	Pantaloni(string _culoare, string _nume, float _pret) : Produs(_nume, _pret) {
		this->culoare = _culoare;
	}
	string getCategorie() {
		return "pantaloni";
	}

	double getPretFinal() override {
		return this->pret;
	}
	void print(ostream& ost) override{
		ost << "Cod : " << this->cod << endl;
		ost << "Nume : " << this->nume << endl;
		ost << "Pret : " << this->pret << endl;
		ost << "Culoare : " << this->culoare << endl;
		ost << "Stoc marime S : " << this->stocPeMarimi["S"] << endl;
		ost << "Stoc marime M : " << this->stocPeMarimi["M"] << endl;
		ost << "Stoc marime L : " << this->stocPeMarimi["L"] << endl;
		ost << "Stoc marime XL : " << this->stocPeMarimi["XL"] << endl;
	}
};
class Jacheta : public Produs {
public:
	Jacheta() :Produs() {};
	Jacheta(string _nume, float _pret) : Produs(_nume, _pret) {}
	string getCategorie() {
		return "Jacheta";
	}

	double getPretFinal() override {
		return this->pret > 1200 ? this->pret * 1.15 : this->pret;
	}

	void print(ostream& ost) override {
		ost << "Cod : " << this->cod << endl;
		ost << "Nume : " << this->nume << endl;
		ost << "Pret : " << this->pret << endl;
		ost << "Stoc marime S : " << this->stocPeMarimi.at("S") << endl;
		ost << "Stoc marime M : " << this->stocPeMarimi.at("M") << endl;
		ost << "Stoc marime L : " << this->stocPeMarimi.at("L") << endl;
		ost << "Stoc marime XL : " << this->stocPeMarimi.at("XL") << endl;
	}
};

ostream& operator<<(ostream& ost, Produs& p) {
	p.print(ost);
	return ost;
}
class Magazin {
	vector<Produs*> produse;
	map<string, int> vanzariPeMarimi{
		{"S" , 0},
		{"M" , 0},
		{"L" , 0},
		{"XL" , 0}
	};
public:
	Magazin() {};
	~Magazin() {
		for (auto p : produse) delete p;
	}
	void adaugaProdus(Produs* p) {
		produse.push_back(p);
	}

	friend ostream& operator<<(ostream& ost ,const Magazin& m) {
		ost << "Produse" << endl;
		for (auto produs : m.produse) {
			ost << *produs << endl;
		}
		ost << "Vanzari pe marimi : " << endl;
		ost << "Vanzari marime S : " << m.vanzariPeMarimi.at("S") << endl;
		ost << "Vanzari marime M : " << m.vanzariPeMarimi.at("M") << endl;
		ost << "Vanzari marime L : " << m.vanzariPeMarimi.at("L") << endl;
		ost << "Vanzari marime XL : " << m.vanzariPeMarimi.at("XL") << endl;
		return ost;
	}
	Magazin& operator()(string cod, string marime, int cantitate) {
		for (auto produs : this->produse) {
			if (produs->cod == cod) {
				if (produs->stocPeMarimi[marime] < cantitate) {
					cout << "Stoc insuficient" << endl;
					return *this;
				}
				produs->stocPeMarimi[marime] -= cantitate;
			//DE SPECIFICAT : consider ca proful a gresit aici , map ul de vanzari trebuia sa fie <string , double> deoarece 
			//getPretFinal() returneaza un double , iar acum la calculul vanzarilor totale valoarea va fi trunchiata prin conversie explicita
			//map ul fiind specificat de exercitiu ca find <string , int>
				vanzariPeMarimi[marime] += (int) produs->getPretFinal() * cantitate;
			}
		}
		return *this;

	}

	void reaprivizionare(string cod, string marime, int cantitate) {
		for (auto produs : this->produse) {
			if (produs->cod == cod) {
				produs->stocPeMarimi[marime] += cantitate;
			}
		}
	}
	map<string , string> genereazaRaportEchilibru() {
		map<string, string> raport;
		for (auto produs : produse) {
			int stocTotal = 0;
			for (auto& marime : produs->stocPeMarimi) {
				stocTotal += marime.second;
			}
			for (auto& marime : produs->stocPeMarimi) {
				if ((double)marime.second / stocTotal > .5) raport[produs->cod] = marime.first;
			}
		}
		return raport;
	}
};

int main() {
	Tricou* t = new Tricou("smecheru", "gucci", 2000);
	Magazin m;
	m.adaugaProdus(t);
	cout << m << endl;
	m.reaprivizionare("1", "M", 23);
	m.reaprivizionare("1", "XL", 100);
	cout << m << endl;
	m("1", "M", 2);
	cout << m << endl;
	cout << "--------------------Raport-------------------------" << endl;
	map<string, string> raport = m.genereazaRaportEchilibru();
	for (const auto& pair : raport) {
		cout << "Cod : " << pair.first << " => " << "Marime :" << pair.second << endl;
	}
	return 0;
}