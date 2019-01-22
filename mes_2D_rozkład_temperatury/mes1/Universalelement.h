//#pragma once
#ifndef Universalelement_h
#define Universalelement_h
using namespace std;
class Universalelement
{
public:
	//Universalelement();
	double N[4][4];
	double NE [4][4];
	double Nni [4][4];
	double E;
	double ni;
	double pktc[4][2];
	
	

	Universalelement(double E , double ni );
	void tab3();

	//~Universalelement(void);
};
#endif