#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Curs {
	static int generator;
protected:
	const int id;
	string titlu;
	string instructor;
	int durataTotala;
	map<int, int> progesStudenti;
public:
	virtual string getTipCurs() = 0;
	virtual double getPretFinal() { return 0; }
	// in aceata versiune fata de cea din subiectul Magazin am optat pentru o implementare in clasa de baza a metodei de afisare pe care ulterior
	// o voi suprascrie cu cea am adaugat in clasele derivate
	// abia acum mi am dat seama ca pot face asta ca sa nu mai repet cod MY BAD!!!! recomand sa folositi versinea asta pentru a salva timp
	virtual void afis(ostream& ost) {
		ost << "ID: " << id << endl;
		ost << "Titlu: " << titlu << endl;
		ost << "Instructor: " << instructor << endl;
		ost << "Durata: " << durataTotala << endl;
		ost << "Tip curs: " << getTipCurs() << endl;
	}
	Curs() :id(++generator) {};
	Curs(string _titlu , string _instructor , int _durataTotala) :id(++generator) {
		this->titlu = _titlu;
		this->instructor = _instructor;
		this->durataTotala = _durataTotala;
	};

	friend ostream& operator<<(ostream& ost, Curs& c) {
		c.afis(ost);
		return ost;
	}
	virtual ~Curs() = default;
};

class CursGratuit : public Curs {
	string categorie;
public:
	CursGratuit() : Curs() {};
	CursGratuit(string _categorie) : Curs() { this->categorie = _categorie; }
	string getTipCurs() override {
		return "gratuit";
	}
	double getPretFinal() override {
		return 0;
	}
	void afis(ostream& ost) override {
		Curs::afis(ost);
		ost << "Categorie : " << this->categorie << endl;
	}
	bool estePopular() {
		return (this->progesStudenti).size() > 5;
	}
};
class CursPremium : public Curs {
	double pret;
	int nivelDificultate;
public:
	CursPremium() : Curs() {};
	CursPremium(double _pret , int _nivelDificultate) : Curs() {
		this->pret = _pret; 
		this->nivelDificultate = _nivelDificultate;
	}
	string getTipCurs() override {
		return "premium";
	}
	double getPretFinal() override {
		return this->pret;
	}
	void afis(ostream& ost) override {
		Curs::afis(ost);
		ost << "Pret : " << this->pret << endl;
		ost << "Nivel dificultate : " << this->nivelDificultate << endl;
	}
};

class CursCertificat : public Curs {
	double pret;
	int notaMinima;
	double pretCertificat;
public:
	CursCertificat() : Curs() {};
	CursCertificat(double _pret, int _notaMinima , double _pretCertificat) : Curs() {
		this->pret = _pret;
		this->notaMinima = _notaMinima;
		this->pretCertificat = _pretCertificat;
	}
	string getTipCurs() override {
		return "certificat";
	}
	double getPretFinal() override {
		return this->durataTotala > 30 ? (this->pret + this->pretCertificat) * .8 : (this->pret + this->pretCertificat);
	}
	void afis(ostream& ost) override{
		Curs::afis(ost);
		ost << "Pret : " << this->pret << endl;
		ost << "Nota minima : " << this->notaMinima << endl;
		ost << "Pret Certificat : " << this->pretCertificat << endl;
	}
};

class Platforma
{
	vector<Curs*> cursuri;
	map<string, int> inscrieriPeInstructor;
public:
	Platforma()
	{
	}

	~Platforma()
	{
		for (auto curs : this->cursuri) delete curs;
	}

	Platforma& operator+(Curs* c) {
		(this->cursuri).push_back(c);
		return *this;
	}

};






int main() {
	return 0;
}