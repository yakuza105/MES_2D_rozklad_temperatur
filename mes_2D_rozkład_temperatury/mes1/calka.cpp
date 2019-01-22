#include "calka.h"
#include <iostream>

using namespace std;

calka::calka( )
{
	
	
}

calka::~calka(void)
{
}

double calka::f(double x , double y){

	return  2 * x *x *y *y +6 *x + 5;

}
double calka::oblicz(double wsp[], double w[] ,double liczba , double wynik  ){
	for(int j =0 ; j<liczba ;j++){
		for(int i =0 ; i<liczba ;i++){
			wynik += f(wsp[i],wsp[j]) * w[i]*w[j];
	}

	}
	
	//cout<<wynik<<endl;
	return wynik;
}


