#include<iostream>
using namespace std;

//relatia de compunere -> has a (1-M, 1-1)
//try catch

//NEXT TIME (s09)
//terminam toti operatorii de supraincarcat
//comparatie done
//= done
//<< done
// >> done home
// [] redone home
// ! done home
// cast done home
// ++ (pre si post) done home
// + done home
//functie
//+= done home


class Produs {
	string denumire = "";
	double pret = 0;

public:
	//de ce este nevoie de un constructor default?
	Produs() {}

	Produs(string _denumire, double _pret) {
		this->denumire = _denumire;
		this->pret = _pret;
	}

	bool operator==(const Produs& p) const {
		if (this->denumire != p.denumire) return false;
		if (this->pret != p.pret) return false;

		return true;
	}

	bool operator!=(const Produs& p) const {
		return !(*this == p);
	}

	//meth de afisare ->supraincarcarea operatorului <<

	//permit obiectele de tipul Produs care sunt utilizate in functia mentionata sa aiba acces si la zona privata a clasei Produs
	friend ostream& operator<<(ostream& out, const Produs& p);
	friend istream& operator>>(istream& in, Produs& p);
	friend class WishList;

};
//transfer prin valoare
//face o copie a acelui obiect

//transfer prin referinta
//Caz 1. ca sa modifici obiectul respectiv (si aici nu putem si const)
//Caz 2. ca sa NU mai facem acea copie pe care ne-o realizeaza transferul prin valoare(dar aici putem const, pentru ca intentia NU este de a modifica obiectul) (cu rol de optimizare)
ostream& operator<<(ostream& out, const Produs& p) {
	out << "\nDenumire: " << p.denumire;
	out << ", pret: " << p.pret;
	return out;
}

istream& operator>>(istream& in, Produs& p) {
	cout << "denumire : ";
	in >> p.denumire;

	cout << "pret : ";
	in >> p.pret;

	return in;
}

//Versiuni diferite de colectii de obiecte/referinte de tip Produs
//obiect vs referinta la obiect
//deep copy vs shallow copy

class WishList2 {
	Produs lista[100];//vector alocat static de obj de tip Produs
	int nrProduse;
	double buget;
};

class WishList3 {
	Produs* lista[100];//vector alocat static de Produs* (referinte la Produs)
	int nrProduse;
	double buget;
};

class WishList4 {
	Produs** lista;//vector alocat dinamic de Produs* (referinte la Produs)
	int nrProduse;
	double buget;
};

//relatie de tip 1-1
class WishList5 {
	Produs theCadou; //un singur Produs
	double buget;
};

//relatie de tip 1-1
class WishList6 {
	Produs* theCadou; //un singur pointer catre 1 Produs
	double buget;
};

class WishList {
	Produs* lista = nullptr;//vector alocat dinamic de obj de tip Produs
	int nrProduse = 0;
	double buget = 0;
public:
	WishList() {}

	WishList(Produs* _lista, int _nrProduse, double _buget) {
		if (_nrProduse > 0 && _lista != nullptr) {
			this->nrProduse = _nrProduse;
			this->lista = new Produs[this->nrProduse];//ce se apeleaza? (constructor fara param de nrProduse ori)
			for (int i = 0; i < this->nrProduse; i++) {
				this->lista[i] = _lista[i];//ce se apeleaza? (operator =)
			}
		}
		this->buget = _buget;
	}

	WishList(const WishList& w) {
		if (w.nrProduse > 0 && w.lista != nullptr) {
			this->nrProduse = w.nrProduse;
			this->lista = new Produs[this->nrProduse];//ce se apeleaza? (constructor fara param de nrProduse ori)
			for (int i = 0; i < this->nrProduse; i++) {
				this->lista[i] = w.lista[i];//ce se apeleaza? (operator =)
			}
		}
		this->buget = w.buget;
	}

	WishList& operator=(const WishList& w) {
		if (this != &w) {
			//destructor
			if (this->lista != nullptr) {
				delete[] this->lista;
				this->lista = nullptr;
			}
			//constructor de copiere
			if (w.nrProduse > 0 && w.lista != nullptr) {
				this->nrProduse = w.nrProduse;
				this->lista = new Produs[this->nrProduse];//ce se apeleaza? (constructor fara param de nrProduse ori)
				for (int i = 0; i < this->nrProduse; i++) {
					this->lista[i] = w.lista[i];//ce se apeleaza? (operator =)
				}
			}
			else {
				//situatia in care this avea produse dar w nu are
				this->nrProduse = 0;
				this->lista = nullptr;
			}
			this->buget = w.buget;
		}
		return *this;
	}

	~WishList() {
		if (this->lista != nullptr) {
			delete[] this->lista;
			this->lista = nullptr;
		}
	}

	friend ostream& operator<<(ostream& out, const WishList& w);
	friend istream& operator>>(istream& in, WishList& w);

	//HOME ->!!!!NU FACEM RETURN PRIN REFERINTA LA TIPURI DE DATE DE BAZA(INT/FLOAT/DOUBLE)!!! DE CE????
	//operator[] cu rol doar de consultare va intoarce mereu un obiect, si nu referinta sa
	//daca se doreste si cu rol de modificare, atunci va intoarce o referinta
	Produs& operator[](int _index) {
		while (_index < 0 || _index >= this->nrProduse) {
			try {
				throw out_of_range("indexul nu este valid!");
			}
			catch (const exception& e) {
				cout << e.what() << "Introdu alt index (valid) : ";
				cin >> _index;
			}
		}
		return lista[_index];
		
	}

	bool operator==(const WishList& w) const {
		if (this->nrProduse != w.nrProduse) return false;
		if (this->buget != w.buget) return false;

		if (this->lista == nullptr && w.lista == nullptr) return true;
		if ((this->lista == nullptr) != (this->lista == nullptr)) return false;

		for (int i = 0; i < this->nrProduse; ++i) {
			if ((this->lista)[i] != w.lista[i]) return false;
		}

		return true;

	}

	bool operator!=(const WishList& w) const {
		return !(*this == w);
	}

	bool operator!() const {
		if (this->lista == nullptr) return true;
		if (this->nrProduse == 0) return true;
		
		return false;
	}

	WishList operator+(const WishList& w) {
		WishList wNou;

		wNou.buget = this->buget + w.buget;
		wNou.nrProduse = this->nrProduse + w.nrProduse;

		wNou.lista = new Produs[this->nrProduse + w.nrProduse];

		for (int i = 0; i < this->nrProduse; i++)
			wNou.lista[i] = (this->lista)[i];
		for (int i = 0; i < w.nrProduse; i++)
			wNou.lista[i + this->nrProduse] = w.lista[i];

		return  wNou;
		
	}
	WishList operator+=(const WishList& w) {
		this->buget += w.buget;
		this->nrProduse += w.nrProduse;
		Produs* listaNoua = new Produs[this->nrProduse];

		for (int i = 0; i < this->nrProduse - w.nrProduse; i++)
			listaNoua[i] = (this->lista)[i];
		for (int i = 0; i < w.nrProduse; i++)
			listaNoua[nrProduse - w.nrProduse + i] = w.lista[i];

		delete[] this->lista;
		this->lista = listaNoua;

		return *this;
	}

	WishList operator++(int) {
		WishList copie = *this;
		cout << "introdu datale pentru produsul nou : " << endl;
		Produs produsNou;
		cin >> produsNou;
		//varianta 1
		//*this += WishList(&produsNou, 1, 0);

		//varianta 2
		Produs listaDummy[] = { produsNou };
		*this += WishList(listaDummy, 1, 0);

		return copie;
	}
	WishList operator++() {
		cout << "introdu datale pentru produsul nou : " << endl;
		Produs produsNou;
		cin >> produsNou;
		//varianta 1
		//*this += WishList(&produsNou, 1, 0);

		//varianta 2
		Produs listaDummy[] = { produsNou };
		*this += WishList(listaDummy, 1, 0);

		return *this;
	}

	operator int() const {
		return this->nrProduse;
	}
	operator double() const {
		return this->buget;
	}
	
	//returneaza o lista cu toate numele produselor
	operator string() const {
		string listaNume;
		for (int i = 0; i < this->nrProduse; ++i) {
			listaNume += this->lista[i].denumire;
			listaNume += " ";
		}

		return listaNume;
	}
};

ostream& operator<<(ostream& out, const WishList& w) {
	out << "\nNr produse: " << w.nrProduse;
	out << "\nProduse: ";
	for (int i = 0; i < w.nrProduse; i++)
		out << w.lista[i];
	out << "\nBuget: " << w.buget;
	return out;
}

istream& operator>>(istream& in,  WishList& w) {
	cout << "nr produse : ";
	in >> w.nrProduse;

	cout << "buget : ";
	in >> w.buget;

	if (w.nrProduse > 0) w.lista = new Produs[w.nrProduse];
	else w.lista = nullptr;

	for (int i = 0; i < w.nrProduse; i++) {
		cout << "date pentru produs " << i + 1<< endl;

		in >> w.lista[i];
	}

	return in;
}

int main() {
	Produs p1("Stilou", 500);
	////p1.afisare();
	//cout << p1;// ostream << Produs
	Produs p2("Pix", 200);
	Produs p3("Ciocolata", 150);
	Produs v[] = { p1,p2,p3 };//ce se apeleaza?(constructor copiere)
	WishList w(v, 3, 1200);
	//cout << w;
	WishList w2(v , 2 , 1200);
	//cout << w2;
	cout << "\n-------------- operator [] ---------\n";
	Produs p4;
	p4 = w[-1];//operatorul index[] extrage obiectul de pe index-ul primit ca parametru
	cout << p4;
	////operator binar (WishList [] int)
	////obligatoriu se implementeaza in clasa printr-o functie membra

	////TO DO HOME: DE REMODELAT MECANISMUL DE APEL OPERATOR INDEX[] 
	////UTILIZATORUL REINTRODUCE INDEXUL PANA CE ACESTA ESTE VALID
	//try {
	//	w[-1] = p3;//daca implementez operatorul si cu rol de modificare (adica intoarce o referinta si modifica in lista de obiecte/produse ale lui WishList w)
	//	cout << w;
	//}
	//catch (exception ex) {
	//	//to do in situatia in care metoda a fost apelata cu input neconform
	//	cout << endl << ex.what();//echivalent cu un getMesaj()
	//}


	//cout << "\n-------------- operator == ---------\n";
	//const string egal = w2 == w ? "sunt egale" : "nu sunt egale";
	//cout << egal;
	//cout << "\n-------------- operator ! ---------\n";
	//cout << !w;
	//cout << "\n-------------- operator >> ---------\n";
	///*WishList w3;
	//cin >> w3;
	//cout << w3;*/
	//cout << "\n-------------- operator + ---------\n";
	//cout << w + w2;
	//cout << "\n-------------- operator += ---------\n";
	//w += w2;
	//cout << w;

	/*cout << "\n-------------- operator ++ (post) ---------\n";
	cout << "\n__inainte__";
	cout << w++;
	cout << "\n__dupa__";
	cout << w;

	cout << "\n-------------- operator ++ (pre) ---------\n";
	cout << "\n__inainte__";
	cout << ++w;
	cout << "\n__dupa__";
	cout << w;*/

	/*cout << "\n-------------- cast int ---------\n";
	cout << static_cast<int>(w);

	cout << "\n-------------- cast double ---------\n";
	cout << static_cast<double>(w);

	cout << "\n-------------- cast string ---------\n";
	cout << static_cast<string>(w);*/
	return 0;
}