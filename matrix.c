#include<iostream>
#include<stdlib.h> 
#include<ctime>
using namespace std;


int ** matrix (int zeilen, int spalten, int loesung, int minvalue, int maxvalue) {
	int ** m;
	int sumvalue = maxvalue - minvalue;
	m = new int*[zeilen];
	for (int i = 0; i < zeilen; i++) {
		m[i] = new int[spalten];
	}
	if (loesung) {
		
	}
	else {
		srand((int) time(0)); //generiert nur ca alle 5 sekunden neue random matrix
		for (int i = 0; i < zeilen; i++) {
			for (int j = 0; j < spalten; j++) {
				m[i][j] = rand() % sumvalue + minvalue;
			}
		}
	}
	return m;
}

void printmatrix (int ** matrix, int zeilen, int spalten) {
	for (int i = 0; i < zeilen; i++) {
		for (int j = 0; j < spalten; j++) {
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}


int main() { //test funktion, einfach die oberen funktionen ins programm übernehmen
	int zeilen = 4;
	int spalten = 4;
	int minvalue = 1;
	int maxvalue = 15;
	int ** m = matrix(zeilen, spalten, 0, minvalue, maxvalue);
	printmatrix(m, zeilen, spalten);
}