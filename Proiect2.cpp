#if 1
#include <iostream>
#include <queue>
//#include "vld.h"
using namespace std;


class Matrice {
	unsigned int noduri, muchii;
	int **mat;
	
public:
	Matrice() {
		noduri = 0;
		muchii = 0;
		mat = NULL;
	};
	Matrice(unsigned int n,unsigned int m,int **matrix)
	{
		noduri = n;
		muchii = m;
		mat = new int*[noduri];
		for (int i = 0; i < noduri; i++)
			mat[i] = new int[noduri]();
		for (int i = 0; i < noduri; i++)
			for (int j = 0; j < noduri; j++)
				mat[i][j] = matrix[i][j];
	}
	Matrice(const Matrice &p)
	{
		noduri = p.noduri;
		muchii = p.muchii;
		mat = new int*[noduri];
		for (int i = 0; i < noduri; i++)
			mat[i] = new int[noduri];
		for (int i = 0; i < noduri; i++)
			for (int j = 0; j < noduri; j++)
				mat[i][j] = p.mat[i][j];
	}
	~Matrice() 
	{
		if (mat) {
			for (int i = 0; i < noduri; i++)
				delete[] mat[i];
			delete[] mat;
			
		}
	}
	friend class Graf_Orientat;
	friend ostream &operator<<(ostream &output, const Matrice &M);
	friend istream &operator>>(istream &input, Matrice &M);
	friend ostream &operator<<(ostream &output, const Graf_Orientat &G);
	friend istream &operator>>(istream &input, Graf_Orientat &G);
	Matrice &operator=(const Matrice &c);
};

istream &operator>>(istream  &input, Matrice &M) {
	if (M.noduri == 0) {
		cout << "Dimensiune matrice: ";
		input >> M.noduri;
		cout << endl;
		cout << "Muchii: ";
		input >> M.muchii;
	}
	int x, y;

	M.mat = new int*[M.noduri];
	for (int i = 0; i < M.noduri; i++)
		M.mat[i] = new int[M.noduri]();


	cout << "Introduceti muchiile: ";
	for (int i = 0; i < M.muchii; i++)
	{
		input >> x >> y;
		M.mat[x][y] = 1;
	}
	return input;
}

ostream &operator<<(ostream &output, const Matrice &M) {
	output << "\nMatricea de adiacenta:\n";
	for (int i = 0; i < M.noduri; i++)
	{
		for (int j = 0; j < M.noduri; j++)
			output << M.mat[i][j] << " ";
		output << endl;
	}
	return output;
}

Matrice & Matrice::operator=(const Matrice &p)
{
	noduri = p.noduri;
	muchii = p.muchii;
	mat = new int*[noduri];
	for (int i = 0; i < noduri; i++)
		mat[i] = new int[noduri];
	for (int i = 0; i < noduri; i++)
		for (int j = 0; j < noduri; j++)
			mat[i][j] = p.mat[i][j];

	return *this;

}

class Vector {
	int *v, dim;

public:
	Vector() {
		dim = 0;
		v = NULL;
	};
	Vector(unsigned int d,int *vec)
	{
		dim = d;
		v = new int[dim];
		
		for (int i = 0; i < dim; i++)
				v[i] = vec[i];
	}
	Vector(const Vector &p)
	{
		dim = p.dim;
		v = new int[dim];
		for (int i = 0; i < dim; i++)
			v[i] = p.v[i];
	}
	~Vector()
	{
		if(v) delete[] v;
	}
	friend class Lista;
	friend ostream &operator<<(ostream &output, const Vector &V);
	friend istream &operator>>(istream  &input, Vector &V);
	friend ostream &operator<<(ostream &output, const Lista &G);
	friend istream &operator>>(istream  &input, Lista &G);
	Vector &operator=(const Vector &c);
};

istream &operator>>(istream  &input, Vector &V) {
	if (V.dim == 0) {
		cout << "Dimensiune vector: ";
		input >> V.dim;
	}
	V.v = new int[V.dim];
	int x;
	cout << "Introduceti valorile: ";
	for (int i = 0; i < V.dim; i++)
	{
		cin >> x;
		V.v[i] = x;
	}
	return input;
}

ostream &operator<<(ostream &output, const Vector &V) {
	output << "Vector : ";
	for (int i = 0; i < V.dim; i++)
		output << V.v[i] << " ";
	cout << endl;
	return output;

}

Vector & Vector::operator=(const Vector &p)
{
	dim = p.dim;
	v = new int[dim];
	for (int i = 0; i < dim; i++)
		v[i] = p.v[i];

	return *this;

}

class Lista {
	int noduri;
	Vector *l;
public:
	Lista() {
		noduri = 0;
		l = NULL;
	}
	Lista(int n) {
		noduri = n;
		l = NULL;
	}
	Lista(Lista &p) {
		noduri = p.noduri;
		l = new Vector[noduri];
		for (int i = 0; i < noduri; i++)
			l[i] = p.l[i];
	}
	~Lista() {
		delete[] l;
	}
	friend class Graf_Neorientat;
	friend ostream &operator<<(ostream &output, const Graf_Neorientat &G);
	friend istream &operator>>(istream  &input, Graf_Neorientat &G);
	friend ostream &operator<<(ostream &output, const Lista &G);
	friend istream &operator>>(istream  &input, Lista &G);

};
istream &operator>>(istream  &input, Lista &G) {
	if (G.noduri == 0) {
		cout << "Nr Noduri: ";
		input >> G.noduri;
	}
	G.l = new Vector[G.noduri];

	for (int i = 0; i < G.noduri; i++)
	{
		cout << "Vectorul nodului " << i << ": ";
		input >> G.l[i];
	}
	return input;
}

ostream &operator<<(ostream &output, const Lista &G) {
	//output << "Nr Noduri: ";
	output << G.noduri<< endl;
	

	for (int i = 0; i < G.noduri; i++)
		output<<"Vectorul "<<i << G.l[i];
	return output;

}

class Graf {
protected:
	int nr_noduri;
public:
	Graf() { nr_noduri = 0; };
	Graf(int nod) { nr_noduri = nod; };
	Graf(Graf& p) { nr_noduri = p.nr_noduri; };
	~Graf() {};

	virtual void afis() = 0;

};

class Graf_Neorientat: public Graf {
	int nr_muchii;
	Lista L;

public:
	Graf_Neorientat(void) :Graf() {
		nr_muchii = 0;
	};

	Graf_Neorientat(int n, int m) :Graf(n) {
		nr_muchii = m;
	};

	Graf_Neorientat(Graf_Neorientat &p) {
		nr_muchii = p.nr_muchii;
		nr_noduri = p.nr_noduri;
		L = p.L;
	};

	~Graf_Neorientat() {};

	friend ostream &operator<<(ostream &output, const Graf_Neorientat &G);
	friend istream &operator>>(istream  &input, Graf_Neorientat &G);
	Graf_Neorientat &operator=(const Graf_Neorientat &c);
	void afis() {
		cout << "Nr Muchii: ";
		cout << nr_muchii << endl;;
		cout << "Nr Noduri: ";
		cout << nr_noduri << endl;
		cout << L;
		cout << endl;
	}

};

istream &operator>>(istream  &input, Graf_Neorientat &G) {
	cout << "Nr Noduri: ";
	input >> G.nr_noduri;
	cout << "Nr Muchii: ";
	input >> G.nr_muchii;

	
	G.L.noduri = G.nr_noduri;
	input >> G.L;
	return input;
}

ostream &operator<<(ostream &output, const Graf_Neorientat &G) {
	output << "Nr Noduri: ";
	output << G.nr_noduri << endl;
	output << "Nr Muchii: ";
	output << G.nr_muchii << endl;;

	output << G.L;
	output << endl;
	return output;

}


Graf_Neorientat & Graf_Neorientat::operator=(const Graf_Neorientat &p)
{
	nr_muchii = p.nr_muchii;
	nr_noduri = p.nr_noduri;
	L = p.L;
	return *this;
}

class Graf_Orientat: public Graf {
	int nr_muchii;
	Matrice A;
public:
	Graf_Orientat(void):Graf() {
		nr_muchii = 0;
	};

	Graf_Orientat(int n,int m):Graf(n) {
		nr_muchii = m;
	};

	Graf_Orientat(Graf_Orientat &p) {
		A = p.A;
		nr_muchii = p.nr_muchii;
		nr_noduri = p.nr_noduri;
	};

	~Graf_Orientat() {};

	void tati()
	{
		for (int i=0; i < nr_noduri; i++)
		{
			cout << endl << i << ": ";
			for (int j=0; j < nr_noduri; j++)
				if (A.mat[j][i] == 1)cout <<j<<" ";
		}
	}
	friend ostream &operator<<(ostream &output, const Graf_Orientat &G);
	friend istream &operator>>(istream  &input, Graf_Orientat &G);
	Graf_Orientat &operator=(const Graf_Orientat &c);
	void afis() {
		cout << "Nr Muchii: ";
		cout << nr_muchii << endl;;
		cout << "Nr Noduri: ";
		cout << nr_noduri << endl;
		cout << A;
		cout << endl;
	}
};

istream &operator>>(istream  &input, Graf_Orientat &G) {
	cout << "Nr Noduri: ";
	input >> G.nr_noduri;
	cout << "Nr Muchii: ";
	input >> G.nr_muchii;
	
	G.A.muchii = G.nr_muchii;
	G.A.noduri = G.nr_noduri;
	input >> G.A;
	return input;
}

ostream &operator<<(ostream &output, const Graf_Orientat &G) {
	output << "Nr Noduri: ";
	output << G.nr_noduri << endl;
	output << "Nr Muchii: ";
	output << G.nr_muchii << endl;;
	
	output << G.A;
	output << endl;
	return output;

}


Graf_Orientat & Graf_Orientat::operator=(const Graf_Orientat &p)
{
	nr_muchii = p.nr_muchii;
	nr_noduri = p.nr_noduri;
	A = p.A;
	return *this;
}




int main() {
	
	Graf_Orientat graf1,graf2;
	cin >> graf1;
	graf1.afis();
	graf2 = graf1;
	graf2.tati();
	
	return 0;
}
#endif