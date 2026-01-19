#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
using namespace std;

class Carte {
	static int generatorCarte;
	int codCarte;
	string autor;
	string titlu;
public:
	Carte() : codCarte(++generatorCarte){}
	Carte(string _autor , string _titlu) : codCarte(++generatorCarte) {
		this->autor = _autor;
		this->titlu = _titlu;
	}
	Carte(const Carte& c) : codCarte(c.codCarte){
		if (this != &c) {
			this->autor = c.autor;
			this->titlu = c.titlu;
		}
	}
	string getTitlu() const {
		return this->titlu;
	}

	string getAutor() const{
		return this->autor;
	}

	int getCodCarte() const {
		return this->codCarte;
	}

	void setTitlu(string _titlu) {
		this->titlu = _titlu;
	}

	void setAutor(string _autor) {
		this->autor = _autor;
	}
	friend ostream& operator<<(ostream& ost, const Carte& c) {
		ost << "COD : " << c.getCodCarte() << endl;
		ost << "TITLU : " << c.getTitlu() << endl;
		ost << "AUTOR : " << c.getAutor() << endl;
		return ost;
	}
};

class Sala {
	static int generatorSala;
	const int idSala;
	string numeSala;
	map<Carte*, int> carti;
public:
	Sala() :idSala(++generatorSala) {};
	Sala(string _numeSala) :idSala(++generatorSala) {
		this->numeSala = _numeSala;
	};

	string getNumeSala() const {
		return this->numeSala;
	}

	int getIdSala() const {
		return this->idSala;
	}

	void setNumeSala(string _numeSala) {
		this->numeSala = _numeSala;
	}

	void adaugaCarte(Carte* carte, int cantitate) {
		//facem o copie pentru a evita dangling pointer
		for (auto& pair : carti) {
			if ((pair.first)->getCodCarte() == carte->getCodCarte()){
				carti[pair.first] += cantitate;
				return;
			}
				
		}
		Carte* copie = new Carte(*carte);
		carti[copie] += cantitate;
	}
	// returneaza cantitatea sau 0 daca nu exista cartea (daca nu exista => cantitate 0)
	int operator[](int _codCarte ) {
		for (auto& pair : carti) {
			if ((pair.first)->getCodCarte() == _codCarte)
				return pair.second;
		}
		return 0;
	}

	 Sala& operator-=(int _codCarte) {
		 for (auto pair = carti.begin(); pair != carti.end(); ++pair) {
			 if (pair->first->getCodCarte() == _codCarte){
				 delete pair->first;
				 carti.erase(pair);
				 return *this;
			 }

		 }
		 return *this;
	 }

	 int operator()() {
		 int max = 0;
		 for (auto& carte : carti) {
			 if (max < carte.second) {
				 max = carte.second;
			 }
		 }
		 cout << "MAXIM EXEMPLARE : " << max << endl;
		 cout << "CARTILE CU NR MAXIM EXEMPLARE : " << endl;
		 for (auto& carte : carti) {
			 if (carte.second == max) {
				 cout << *(carte.first) << endl;
			 }
		 }
		 return max;
	 }

	friend ostream& operator<<(ostream& ost, const Sala& s) {
    ost << "ID SALA : " << s.getIdSala() << endl;
    ost << "NUME SALA : " << s.getNumeSala() << endl;
    ost << "CARTILE EXISTENTE IN SALA : " << endl;

    for (auto& pair : s.carti) {
        ost << "\tCOD : " << pair.first->getCodCarte() << endl;
        ost << "\tTITLU : " << pair.first->getTitlu() << endl;
        ost << "\tAUTOR : " << pair.first->getAutor() << endl;

        ost << "\tCANTITATE : " << pair.second << endl;
        ost << endl; 
    }

    return ost;
}

	~Sala() {
		for (auto& pair : carti) {
			delete pair.first;
		}
	}
};

int Carte::generatorCarte = 0;
int Sala::generatorSala = 0;

int main() {

	// cream carti
	Carte c1("Orwell", "1984");
	Carte c2("Dostoievski", "Crima si pedeapsa");
	Carte c3("Tolkien", "Stapanul inelelor");

	// cream sala
	Sala s("Sala Principala");

	// adaugam carti
	s.adaugaCarte(&c1, 5);
	s.adaugaCarte(&c2, 3);
	s.adaugaCarte(&c3, 5);

	// adaugam din nou aceeasi carte (testeaza cumularea)
	s.adaugaCarte(&c1, 2);

	cout << "=== AFISARE SALA ===\n";
	cout << s << endl;

	// test operator[]
	cout << "Exemplare pentru cartea cu cod "
		<< c1.getCodCarte() << " : "
		<< s[c1.getCodCarte()] << endl;

	// test operator()
	cout << "\n=== MAXIM EXEMPLARE ===\n";
	s();

	// test stergere carte
	cout << "\n=== STERGEM CARTEA " << c2.getCodCarte() << " ===\n";
	s -= c2.getCodCarte();

	cout << "\n=== AFISARE DUPA STERGERE ===\n";
	cout << s << endl;

	// scriere in fisier
	ofstream fout("sala.txt");
	if (fout.is_open()) {
		fout << s;
		fout.close();
	}

	return 0;
}
