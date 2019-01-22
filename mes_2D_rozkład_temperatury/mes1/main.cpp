#include <iostream>
#include <string>
#include "GlobalData.h"
#include "Node.h"
#include "Element.h"
#include "Grid.h"
#include "calka.h"
#include "Universalelement.h"

using namespace std ;


void main(){

	GlobalData data("data.txt");
	Grid grid(data);
	
	

	double x,y;
	x =0.55555555555;
	y = 0.88888888888;
	double wsp[2] = {-0.577,0.577};
	double wsp3[3] = {-0.7745 , 0, 0.7745};
	double w31[3] = {x,y,x};
	
	double w[2] = {1,1};
	double wynik = 0;
	double wynik2 = 0;
	int liczba2 =3 ;
	int liczba =2; 
	
	
	calka c;
	wynik = c.oblicz(wsp3,w31,3.0,wynik);
	//cout<<wynik<<endl;

	
	
	system("pause");
}


