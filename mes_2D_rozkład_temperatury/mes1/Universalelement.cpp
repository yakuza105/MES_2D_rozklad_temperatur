#include <iostream>
#include "Universalelement.h"
using namespace std;

Universalelement::Universalelement(double E , double ni){
	for(int j =0 ; j<4 ;j++){
	for(int i =0 ; i<4 ;i++){
		this->N[j][i]= 0;
		this->Nni[j][i]= 0;
		this->NE[j][i]= 0;
	}
	}
	this->E = E;
	this->ni = ni;
	this->pktc[0][0]= -E;
	this->pktc[0][1]= -ni;
	this->pktc[1][0]= E;
	this->pktc[1][1]= -ni;
	this->pktc[2][0]= E;
	this->pktc[2][1]= ni;
	this->pktc[3][0]= -E;
	this->pktc[3][1]= ni;
	


}

void Universalelement::tab3(){


	cout<<pktc[0][1]<<endl;
	cout<<"N                                              E                                                       ni"<<endl;
	for(int i =0 ; i<4 ;i++){
		//tabela n1 n2 n3 n4 dla kazdego el 
		N[i][0]=0.25*(1-pktc[i][0])*(1-pktc[i][1]);
		N[i][1]=0.25*(1+pktc[i][0])*(1-pktc[i][1]);
		N[i][2]=0.25*(1+pktc[i][0])*(1+pktc[i][1]);
		N[i][3]=0.25*(1-pktc[i][0])*(1+pktc[i][1]);
		
		// table pohodnych funkcji kszta³tu po ksi i eta 
		NE[i][0] = -0.25*(1-pktc[i][1]);
		Nni[i][0] = -0.25*(1-pktc[i][0]);
		NE[i][1] = +0.25*(1-pktc[i][1]);
		Nni[i][1] = -0.25*(1+pktc[i][0]);
		NE[i][2] = 0.25*(1+pktc[i][1]);
		Nni[i][2] = 0.25*(1+pktc[i][0]);
		NE[i][3] = -0.25*(1+pktc[i][1]);
		Nni[i][3] = 0.25*(1-pktc[i][0]);

		// wyswietlanie trzech tabeli 
		
		//cout<<N[i][0]<<"  "<<N[i][1]<<"  "<<N[i][2]<<"  "<<N[i][3]<<"      "<<NE[i][0]<<"  "<<NE[i][1]<<"  "<<NE[i][2]<<"  "<<NE[i][3]<<"      "<<Nni[i][0]<<"  "<<Nni[i][1]<<"  "<<Nni[i][2]<<"  "<<Nni[i][3]<<endl;

	}





		
	}






