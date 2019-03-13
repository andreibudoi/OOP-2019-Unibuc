#if 1
#include <iostream>
#include <queue>
//#include "vld.h"
using namespace std;


class Graf {

	int noduri;
	int muchii;

	int **matrice;

	void dfs(int vf, int *visited, int index, bool print);
	void bfs(int vf, int *visited, int index, bool print);

public:

	friend ostream &operator<<(ostream &output, const Graf &G);
	friend istream &operator>>(istream  &input, Graf &G);

	void isConnected();

	void ConnectedComponents();

	void afisMatDrum();

	Graf operator+(const Graf& G);

};

void Graf::dfs(int vf, int *visited, int index, bool print)
{
	visited[vf] = index;
	if (print)cout << vf << " ";
	int i;
	for (i = 0; i < this->noduri; i++)
		if (this->matrice[vf][i] == 1 && visited[i] == 0)
			dfs(i, visited, index, print);
}

void Graf::bfs(int vf, int *visited, int index, bool print)
{
	queue <int> coada;
	int i;
	coada.push(vf);
	visited[vf] = index;

	while (!coada.empty())
	{
		vf = coada.front();
		coada.pop();
		if (print) cout << vf << " ";
		for (i = 0; i < this->noduri; i++)
			if (this->matrice[vf][i] == 1 && visited[i] == 0)
			{
				coada.push(i);
				visited[i] = index;
			}
	}
}


void Graf::isConnected()
{
	int *visited = new int[this->noduri]();
	bool ok = 1;
	this->bfs(0, visited, 1, 0);
	for (int i = 0; i < this->noduri; i++)
		if (visited[i] == 0) {
			ok = 0;
			break;
		}
	if (ok == 1)cout << "\nGraful este conex!\n";
	else cout << "\nGraful NU este conex!\n";
	delete[] visited;
}

void Graf::ConnectedComponents()
{
	int *visited = new int[this->noduri]();
	int index = 1;

	for (int i = 0; i < this->noduri; i++)
		if (visited[i] == 0) {
			cout << endl << index << ": ";
			dfs(i, visited, index, 1);
			index++;
		}

	delete[] visited;

}

void Graf::afisMatDrum()
{
	int **matDrum = new int*[this->noduri];
	for (int i = 0; i < this->noduri; i++)
		matDrum[i] = new int[this->noduri]();
	//memcpy(matDrum, this->matrice, this->noduri * sizeof(int*));
	for (int i = 0; i < this->noduri; i++)
	{
		for (int j = 0; j < this->noduri; j++)
			if (this->matrice[i][j] == 1)matDrum[i][j] = 1;
		
	}

	for (int k = 0; k < this->noduri; ++k)
		for (int i = 0; i < this->noduri; ++i)
			for (int j = 0; j < this->noduri; ++j)
				if (i != j && matDrum[i][j] == 0 && matDrum[i][k] == 1 && matDrum[k][j] == 1)
					matDrum[i][j] = 1;

	cout << endl << "Matricea drumurilor:" << endl;
	for (int i = 0; i < this->noduri; i++)
	{
		for (int j = 0; j < this->noduri; j++)
			cout << matDrum[i][j] << " ";
		cout << endl;
	}

	for (int i = 0; i < this->noduri; i++)
		delete[] matDrum[i];
	delete[] matDrum;
}

Graf Graf::operator+(const Graf& G) {
	Graf graf;


	int nr = 0;
	graf.noduri = this->noduri;
	graf.matrice = new int*[graf.noduri];
	for (int i = 0; i < graf.noduri; i++)
		graf.matrice[i] = new int[graf.noduri]();
	int i, j;
	for (i = 0; i < graf.noduri; i++)
		for (j = 0; j < graf.noduri; j++)
			if (G.matrice[i][j] == 1 || this->matrice[i][j] == 1) {
				graf.matrice[i][j] = 1;
				nr++;
			}
	graf.muchii = nr;

	return graf;

}


istream &operator>>(istream  &input, Graf &G) {
	cout << "Nr. noduri si muchii: ";
	input >> G.noduri >> G.muchii;
	cout << endl;
	int x, y;

	G.matrice = new int*[G.noduri];
	for (int i = 0; i < G.noduri; i++)
		G.matrice[i] = new int[G.noduri]();

	cout << "Introduceti muchiile: ";
	for (int i = 0; i < G.muchii; i++)
	{
		input >> x >> y;
		G.matrice[x][y] = G.matrice[y][x] = 1;
	}
	return input;
}

ostream &operator<<(ostream &output, const Graf &G) {
	output << "\nMatricea de adiacenta:\n";
	for (int i = 0; i < G.noduri; i++)
	{
		for (int j = 0; j < G.noduri; j++)
			output << G.matrice[i][j] << " ";
		output << endl;
	}
	return output;
}




int main() {
	Graf graf1, graf2, graf3;
	cin >> graf1;
	cout << graf1;

	graf1.afisMatDrum();
	
	graf1.isConnected();
	graf1.ConnectedComponents();
	
	cin >> graf2;
	cout << graf2;
	graf3 = graf1 + graf2;
	cout << graf3;
	
	return 0;
}
#endif