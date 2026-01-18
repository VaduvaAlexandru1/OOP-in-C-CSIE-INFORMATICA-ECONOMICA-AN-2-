#include <iostream>
#include <string>	
#include <vector>
#include <map>
using namespace std;

class Marfa {
	static int generator;
	const string id;
protected:
	string nume;
	double pretUnitar;
	int anFabricatie;
	string tara;
	int indiceCalitate = 1;
public:
	Marfa(): id(to_string(++generator)) {}
	Marfa(string _nume , double _pretUnitar , int _anFabricatie , string _tara , int _indiceCalitate) : id(to_string(++generator)) {
		this->nume = _nume;
		this->pretUnitar = _pretUnitar;
		this->anFabricatie = _anFabricatie;
		this->tara = _tara;
		this->indiceCalitate = _indiceCalitate;
	}
	virtual string getTipTransport() = 0;
	virtual double getPretFinalTransport() { return pretUnitar; }
	virtual void afis(ostream& ost){
		ost << "Cod : " << this->id << endl;
		ost << "Nume : " << this->nume << endl;
		ost << "Pret unitar : " << this->pretUnitar << endl;
		ost << "An Fabricatie : " << this->anFabricatie << endl;
		ost << "tara : " << this->tara << endl;
		ost << "indiceCalitate : " << this->indiceCalitate << endl;
	}
	friend ostream& operator<<(ostream& ost, Marfa& m) {
		m.afis(ost);
		return ost;
	}
	string getId() const {
		return this->id;
	}

	string getTara() {

		return this->tara;
	}
	int getIndiceCalitate() {
		return this->indiceCalitate;
	}
	virtual ~Marfa() = default;

	
};

class MarfaGenerala : public Marfa {
	double greutate;
	double volum;
public:
	MarfaGenerala() : Marfa(){}
	MarfaGenerala(double _greutate , double _volum , string _nume, double _pretUnitar, int _anFabricatie, string _tara, int _indiceCalitate) 
		: Marfa(_nume, _pretUnitar, _anFabricatie, _tara, _indiceCalitate) {
		this->greutate = _greutate;
		this->volum = _volum;
	}
	string getTipTransport() override {
		return "naval";
	}

	double getPretFinalTransport() override {
		if (greutate > 1000)
			return this->pretUnitar * 1.2;
		return this->pretUnitar;
	}

	void afis(ostream& ost) override {
		Marfa::afis(ost);
		ost << "Greutate : " << this->greutate << endl;
		ost << "Volum : " << this->volum << endl;
	}
};

class MarfaPerisabila : public Marfa {
	double temperaturaDepozitare;
	int durataValabilitate;
public:
	MarfaPerisabila() : Marfa() {}
	MarfaPerisabila(double _temperaturaDepozitare, int _durataValabilitate, string _nume, double _pretUnitar, int _anFabricatie, string _tara, int _indiceCalitate) 
		: Marfa(_nume, _pretUnitar, _anFabricatie, _tara, _indiceCalitate) {
		this->temperaturaDepozitare = _temperaturaDepozitare;
		this->durataValabilitate = _durataValabilitate;
	}
	string getTipTransport() override {
		return "aerian";
	}

	double getPretFinalTransport() override {
		return this->pretUnitar * 1.5;
	}
	void afis(ostream& ost) override {
		Marfa::afis(ost);
		ost << "Temperatura : " << this->temperaturaDepozitare << endl;
		ost << "Durata : " << this->durataValabilitate << endl;
	}
};

int Marfa::generator = 0;

class MarfaDigitala : public MarfaGenerala {
	string codLicenta;
public:
	MarfaDigitala() : MarfaGenerala() {}
	MarfaDigitala(string _codLicenta ,  string _nume, double _pretUnitar, int _anFabricatie, string _tara, int _indiceCalitate) 
		: MarfaGenerala(0 , 0 , _nume, _pretUnitar, _anFabricatie, _tara, _indiceCalitate) {
		this->codLicenta = _codLicenta;
	}
	string getTipTransport() override {
		return "electronic";
	}

	double getPretFinalTransport() override {
		return this->pretUnitar * .6;
	}
	void afis(ostream& ost) override {
		MarfaGenerala::afis(ost);
		ost << "Cod licenta : " << this->codLicenta << endl;
	}
};

class Firma {
	vector<Marfa*> marfuri;
	map<string, int> tranzactiiPeTari;
	double profitTotal;
public:
	Firma() {};

	void adaugaMarfa(Marfa* m) {
		for (auto marfa : marfuri)
			if (m->getId() == marfa->getId()) return;
		marfuri.push_back(m);
	}

	void exporta(string cod, int cantitate) {
		for (auto& marfa : marfuri) {
			if (marfa->getId() == cod) {
				this->profitTotal += cantitate * marfa->getPretFinalTransport();
				this->tranzactiiPeTari[marfa->getTara()] += cantitate * marfa->getPretFinalTransport();
			}
		}
	}

	void genereazaRaportCalitatePiete(vector<string> coduriExportate) {
		map<string, int> cantitate;
		map<string, int> indicePeTari;
		map<string, int> cantitatePeTari;


		for (auto& cod : coduriExportate) {
			for (auto& marfa : marfuri) {
				if (cod == marfa->getId())
					cantitate[cod]++;
			}
		}

		for (auto& pair : cantitate) {
			for (auto& marfa : marfuri) {
				if (pair.first == marfa->getId()) {
					indicePeTari[marfa->getTara()] += marfa->getIndiceCalitate();
					cantitatePeTari[marfa->getTara()] += 1;
				}
			}
		}

		for (auto& pair : indicePeTari) {
			double medie = (double)pair.second / cantitatePeTari[pair.first];
			cout << "TARA : " << pair.first << endl;
			cout << "MEDIE : " << medie << endl;
			cout << "PRODUSE AFERENTE : " << endl;
			for (auto& marfa : marfuri) {
				if (marfa->getIndiceCalitate() > medie && (marfa->getTara() == pair.first))
					cout << *marfa << endl;
			}
		}

		
	}

	friend vector<Marfa*> operator/=(const Firma& f , double pretMaxim) {
		vector<Marfa*> marfuriIeftine;
		for (int i = 0; i < f.marfuri.size(); i++)
			if (f.marfuri[i]->getPretFinalTransport() <= pretMaxim)
				marfuriIeftine.push_back(f.marfuri[i]);
		return marfuriIeftine;
	}
	friend ostream& operator<<(ostream& ost, Firma& f) {
		for (auto marfa : f.marfuri) {
			ost << *marfa;
		}
		return ost;
	}
	~Firma() {
		for (auto m : marfuri) delete m;
	}
};
int main() {
	
	Marfa* m1 = new MarfaGenerala(
		1200,          // greutate
		3.5,           // volum
		"Ciment",      // nume
		50.0,          // pret unitar
		2023,          // an fabricatie
		"Romania",     // tara
		4              // indice calitate
	);

	Marfa* m2 = new MarfaGenerala(
		800,
		1.2,
		"Lemn",
		30.0,
		2022,
		"Austria",
		3
	);

	Marfa* m3 = new MarfaPerisabila(
		-5.0,          // temperatura depozitare
		14,            // durata valabilitate
		"Carne",
		100.0,
		2024,
		"Germania",
		5
	);

	Marfa* m4 = new MarfaDigitala(
		"LIC-XYZ-123",
		"Software ERP",
		500.0,
		2025,
		"USA",
		5
	);


	cout << *m1 << endl;
	cout << "Tip transport: " << m1->getTipTransport() << endl;
	cout << "Pret final: " << m1->getPretFinalTransport() << endl << endl;

	cout << *m2 << endl;
	cout << "Tip transport: " << m2->getTipTransport() << endl;
	cout << "Pret final: " << m2->getPretFinalTransport() << endl << endl;

	cout << *m3 << endl;
	cout << "Tip transport: " << m3->getTipTransport() << endl;
	cout << "Pret final: " << m3->getPretFinalTransport() << endl << endl;

	cout << *m4 << endl;
	cout << "Tip transport: " << m4->getTipTransport() << endl;
	cout << "Pret final: " << m4->getPretFinalTransport() << endl << endl;

	delete m1;
	delete m2;
	delete m3;
	delete m4;

	Firma f;

	cout << "--------------- Firma ----------------" << endl;
	f.adaugaMarfa(new MarfaGenerala(
		1200, 3.5, "Ciment", 50.0, 2023, "Romania", 4
	));

	f.adaugaMarfa(new MarfaGenerala(
		800, 1.2, "Lemn", 30.0, 2022, "Austria", 3
	));

	f.adaugaMarfa(new MarfaPerisabila(
		-5.0, 14, "Carne", 100.0, 2024, "Germania", 5
	));

	f.adaugaMarfa(new MarfaDigitala(
		"LIC-XYZ-123", "Software ERP", 500.0, 2025, "USA", 5
	));
	f.adaugaMarfa(new MarfaGenerala(
		500, 1.0, "Fier", 40.0, 2021, "Romania", 2
	));

	f.adaugaMarfa(new MarfaGenerala(
		700, 2.0, "Otel", 70.0, 2024, "Romania", 6
	));

	f.adaugaMarfa(new MarfaPerisabila(
		-2.0, 10, "Lactate", 60.0, 2024, "Germania", 4
	));

	
	//cout << f;
	vector<string> coduri = { "1", "5", "6", "3", "7" };
	f.genereazaRaportCalitatePiete(coduri);

	return 0;
}