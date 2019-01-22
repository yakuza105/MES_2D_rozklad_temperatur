#include "wyznacznik4x4.h"

#include <iostream>
using namespace std;



wyznacznik4x4::wyznacznik4x4(void)
{
}


wyznacznik4x4::~wyznacznik4x4(void)
{
}

double wyznacznik4x4::wyznacznik(double tab[4][4]){
	double det;


	det = tab[0][0]*tab[1][1]*tab[2][2]*tab[3][3] + tab[0][0]*tab[1][2]*tab[2][3]*tab[3][1] + tab[0][0]*tab[1][3]*tab[2][1]*tab[3][2];
	det += tab[0][1]*tab[1][0]*tab[2][3]*tab[3][2] + tab[0][1]*tab[1][2]*tab[2][0]*tab[3][3] + tab[0][1]*tab[1][3]*tab[2][2]*tab[3][0];
	det += tab[0][2]*tab[1][0]*tab[2][1]*tab[3][3] + tab[0][2]*tab[1][1]*tab[2][3]*tab[3][0] + tab[0][2]*tab[1][3]*tab[2][0]*tab[3][1];
	det += tab[0][3]*tab[1][0]*tab[2][2]*tab[3][1] + tab[0][3]*tab[1][1]*tab[2][0]*tab[3][2] + tab[0][3]*tab[1][2]*tab[2][1]*tab[3][0];
	det += 0 -tab[0][0]*tab[1][1]*tab[2][3]*tab[3][2] - tab[0][0]*tab[1][2]*tab[2][1]*tab[3][3] - tab[0][0]*tab[1][3]*tab[2][2]*tab[3][1];
	det += 0 - tab[0][1]*tab[1][0]*tab[2][2]*tab[3][3] - tab[0][1]*tab[1][2]*tab[2][3]*tab[3][1] - tab[0][1]*tab[1][3]*tab[2][0]*tab[3][2];
	det += 0 -tab[0][2]*tab[1][0]*tab[2][3]*tab[3][1] - tab[0][2]*tab[1][1]*tab[2][0]*tab[3][3]  - tab[0][2]*tab[1][3]*tab[2][1]*tab[3][0];
	det += 0 - tab[0][3]*tab[1][0]*tab[2][1]*tab[3][2] - tab[0][3]*tab[1][1]*tab[2][2]*tab[3][0] - tab[0][3]*tab[1][2]*tab[2][0]*tab[3][1];
	return det;

}