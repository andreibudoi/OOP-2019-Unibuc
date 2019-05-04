#if 1
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Plata
{
protected:
	static int TVA;
	string date;
	double val;
public:
	Plata() {
		val = 0.0;
	}
	Plata(string d, double v) {
		date = d;
		val = v;
	}
	Plata(Plata &p) {
		date= p.date;
		val = p.val;
	}
	virtual ~Plata() {}

	static int getTVA() { return TVA; }
	static void modifyTVA(int x) { TVA = x; }

	virtual void afis() = 0;

};

int Plata::TVA = 19;

class Numerar: public Plata
{
public:
	void afis() {
		cout << "Plata cash la data " << date << " in valoare de " << val << " lei" << endl;
	}
	Numerar(void) :Plata() {}
	Numerar(string d, double v):Plata(d, v){}
	Numerar(Numerar &p) {
		date = p.date;
		val = p.val;
	}
	~Numerar(){}
	
	friend istream &operator>>(istream  &input, Numerar &N);
	

};

istream &operator>>(istream  &input, Numerar &N) {
	cout << "NUMERAR:" << endl;
	cout << "Data (ZZ.LL.AAAA): ";
	input >> N.date;
	cout << "Suma: ";
	input >> N.val;
	return input;
}

class Cec : public Plata
{
	string nume;
public:
	void afis() {
		cout << "Plata cec la data " << date << " in valoare de " << val << " lei realizata de "<<nume << endl;
	}
	Cec():Plata(){}
	Cec(string d, double v, string n) :Plata(d, v) { nume = n; }
	Cec(Cec &p) {
		date = p.nume;
		val = p.val;
		nume = p.nume;
	}
	~Cec(){}
	friend istream &operator>>(istream &input, Cec &N);
	


};

istream &operator>>(istream &input, Cec &N)
{
	cout << "CEC:" << endl;
	cout << "Data (ZZ.LL.AAAA): ";
	input >> N.date;
	cout << "Suma: ";
	input >> N.val;
	cout << "Nume: ";
	input >>N.nume;
	return input;

}

class Card :public Plata
{
	string nume;
	string nr_card;
public:
	void afis() {
		cout << "Plata card la data " << date << " in valoare de " << val << " lei realizata de " << nume<<" cu cardul "<<nr_card<<endl;
	}
	Card() :Plata() {}
	Card(string d, double v, string n) :Plata(d, v) { nume = n; }
	Card(Card &p) {
		date = p.nume;
		val = p.val;
		nume = p.nume;
		nr_card = p.nr_card;
	}
	~Card() {}
	friend istream &operator>>(istream &input, Card &N);

};

istream &operator>>(istream &input, Card &N)
{
	cout << "CARD:" << endl;
	cout << "Data (ZZ.LL.AAAA): ";
	input >> N.date;
	cout << "Suma: ";
	input >> N.val;
	cout << "Nume: ";
	input >>N.nume;
	cout << "Nr Card: ";
	input >> N.nr_card;

	return input;

}


template <class T>
class Gestiune {
	int index;
	vector<T*> lista;
public:
	Gestiune() { index = 0; }
	~Gestiune() {}
	Gestiune(T *p) {
		lista.push_back(&p);
		index++;
	}
	Gestiune(Gestiune<T> &p) {
		lista = p.lista;
		index = p.index;
	}
	
	
	Gestiune<T>& operator+= (T &x) {
		lista.push_back(&x);
		index++;
		return *this;
	}

	void afisaj() {
		
		Card *A;
		Cec *B;
		Numerar *C;

		for (int i = 0; i < lista.size(); i++)
		{
			try{
			A = dynamic_cast<Card*>(lista[i]);
			B = dynamic_cast<Cec*>(lista[i]);
			C = dynamic_cast<Numerar*>(lista[i]);

			if (A)
				A->afis();
			
			if (B)
				B->afis();
			
			if (C)
				C->afis();
			
			}
			catch (bad_cast& bc)
			{
				cerr << bc.what() << '\n';
			}
		}
	}

};

template<>
class Gestiune <char*>
{
	int index;
	vector<string>lista;
public:
	Gestiune() { index = 0; }
	~Gestiune() {}
	Gestiune(string p) {
		lista.push_back(p);
		index++;
	}
	Gestiune(Gestiune<char*> &p) {
		lista = p.lista;
		index = p.index;
	}

	Gestiune<char*>& operator+= (string x) {
		lista.push_back(x);
		index++;
		return *this;
	}

	void afisaj() {
		
		for (int i = 0; i < lista.size(); i++)
			cout<<lista[i]<<endl;
	}
};

int main()
{
	Cec n1;
	Card n2;
	cin >> n1 >> n2;
	
	Gestiune<Plata> P;
	Gestiune<char*> C;
	P += n1;
	P += n2;
	
	P.afisaj();
	C += "Andrei";
	C += "Budoi";
	C.afisaj();

	cout << Plata::getTVA() << endl;

	Plata::modifyTVA(20);

	cout << Cec::getTVA() << endl;
	
	return 0;
}
#endif