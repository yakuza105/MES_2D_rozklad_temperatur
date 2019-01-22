#include <iostream>

#include "Node.h"
#include "Element.h"
#include "GlobalData.h"
#include "Grid.h"
#include "Universalelement.h"
#include "wyznacznik4x4.h"
#include "globalElement.h"

using namespace std;

Grid::Grid(GlobalData data) {
	ND = new Node[data.nh];
	EL = new Element[data.ne];
	k = data.k;
	alfa = data.alfa;
	cp = data.cp;
	ro = data.ro;
	t8 = data.t8;
	t0 = data.t0;
	dt = data.dt;
	cout<<k<<"  " <<alfa<<endl;
	


	double db = data.B / (data.nB - 1);
	double dh = data.H / (data.nH - 1);

	double podanie = 0;
	int licznik = -1;

	for (int i = 0; i < data.nh; i++) {
		licznik++;
		if (licznik == data.nH) {
			licznik = 0;
			podanie += db;
			cout << endl;
		}

		if (i == licznik || licznik == 0 || licznik == data.nH - 1 || i > data.nh - data.nH)ND[i].status = 1;

		ND[i].y = (i % (int)data.nH)*dh;
		ND[i].x = podanie;

		cout << i << ": x-" << ND[i].x << " y-" << ND[i].y << " s-" << ND[i].status << "       ";

	}

	/////////////////////////////////
	cout << endl;
	int rawEl = data.nH;
	licznik = -1;
	int dodaj = 0;

	for (int i = 0; i < data.ne; i++) {
		licznik++;
		if (licznik == rawEl-1) {
			licznik = 0;
			dodaj++;
		}
		EL[i].id[0] = i + dodaj;
		EL[i].id[1] = i + data.nB  + dodaj;
		EL[i].id[2] = EL[i].id[1] + 1;
		EL[i].id[3] = EL[i].id[0] + 1;

		cout << "El " << i << ": " << EL[i].id[0] << " " <<
			EL[i].id[1] << " " <<
			EL[i].id[2] << " " <<
			EL[i].id[3] << endl;
		
		if(ND[EL[i].id[3]].status == ND[EL[i].id[0]].status && ND[EL[i].id[3]].status ==1 ) EL[i].sciana[0] =1 ; 
		else EL[i].sciana[0] =0 ;
		if(ND[EL[i].id[0]].status == ND[EL[i].id[1]].status && ND[EL[i].id[0]].status ==1 ) EL[i].sciana[1] =1 ; 
		else EL[i].sciana[1] =0 ;
		if(ND[EL[i].id[1]].status == ND[EL[i].id[2]].status && ND[EL[i].id[1]].status ==1) EL[i].sciana[2] =1 ; 
		else EL[i].sciana[2] =0 ;
		if(ND[EL[i].id[2]].status == ND[EL[i].id[3]].status && ND[EL[i].id[2]].status ==1) EL[i].sciana[3] =1 ; 
		else EL[i].sciana[3] =0 ;
		EL[i].dl=data.B / (data.nB - 1);


	}
	/*cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
	for(int g =0 ; g<4;g++){
			cout<<EL[1].sciana[g]<<"  " ;
		}
		cout<<endl;
		*/
	
	Universalelement e((0.577),0.577);
	e.tab3();
	
	globalElement g(0.0);
	double wt0[r];
	for(int i = 0 ; i<r ; i++){
		wt0[i] = t0;
	}
	Grid::jakobian(e.Nni, e.NE, data.ne );

	//Grid::transpozycja(e.N);
	cout<<data.nh<<"!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
	Grid::ca³kowanie(data.ne);
	Grid::warunki(data.ne);
	Grid::calka2(alfa,data.ne);
	Grid::calkaC(data.ne,e.N,cp,ro);
	Grid::lokaleH(data.ne);
	Grid::globalH(data.ne, g.globalH ,g.globalC);
	Grid::wektorP(data.ne,alfa,t8, g.globalP);
	g.cprzezdt(dt);
	cout<<"dla iteracji 0"<<endl;
	g.lastH();
	g.lastP(wt0);
	for(int i= 0; i<36;i++){
	//cout<<"dla iteracji"<< i <<endl;
	g.gauss(r);
	g.lastH();
	g.lastP(g.w);
	}

}
void Grid::warunki(int roz){
	for(int i =0 ; i<roz; i++){
		for(int j =0 ; j<4; j++){
			EL[i].N2[0][j] =0;
			EL[i].N2[1][j] =0;
			EL[i].N2[2][j] =0;
			EL[i].N2[3][j] =0;

		}}





	for(int i =0 ; i<roz; i++){
	if(EL[i].sciana[0] == 1){
		double e[2] = {-1,-1};
		double n[2] ={0.577,-0.577};
		EL[i].N2[0][0]=0.25*(1-e[0])*(1-n[0]);
		EL[i].N2[0][1]=0.25*(1+e[0])*(1-n[0]);
		EL[i].N2[0][2]=0.25*(1+e[0])*(1+n[0]);
		EL[i].N2[0][3]=0.25*(1-e[0])*(1+n[0]);
		EL[i].N2[1][0]=0.25*(1-e[1])*(1-n[1]);
		EL[i].N2[1][1]=0.25*(1+e[1])*(1-n[1]);
		EL[i].N2[1][2]=0.25*(1+e[1])*(1+n[1]);
		EL[i].N2[1][3]=0.25*(1-e[1])*(1+n[1]);
		//cout<<"jestem tu"<<endl;

	}
	if(EL[i].sciana[1] == 1){
		double e[2] = {-0.577,0.577};
		double n[2] ={-1,-1};
		if(EL[i].sciana[0] == 0){
		EL[i].N2[0][0]=0.25*(1-e[0])*(1-n[0]);
		EL[i].N2[0][1]=0.25*(1+e[0])*(1-n[0]);
		EL[i].N2[0][2]=0.25*(1+e[0])*(1+n[0]);
		EL[i].N2[0][3]=0.25*(1-e[0])*(1+n[0]);
		EL[i].N2[1][0]=0.25*(1-e[1])*(1-n[1]);
		EL[i].N2[1][1]=0.25*(1+e[1])*(1-n[1]);
		EL[i].N2[1][2]=0.25*(1+e[1])*(1+n[1]);
		EL[i].N2[1][3]=0.25*(1-e[1])*(1+n[1]);
		//cout<<"jestem tu"<<endl;
		}
		else{
		EL[i].N2[2][0]=0.25*(1-e[0])*(1-n[0]);
		EL[i].N2[2][1]=0.25*(1+e[0])*(1-n[0]);
		EL[i].N2[2][2]=0.25*(1+e[0])*(1+n[0]);
		EL[i].N2[2][3]=0.25*(1-e[0])*(1+n[0]);
		EL[i].N2[3][0]=0.25*(1-e[1])*(1-n[1]);
		EL[i].N2[3][1]=0.25*(1+e[1])*(1-n[1]);
		EL[i].N2[3][2]=0.25*(1+e[1])*(1+n[1]);
		EL[i].N2[3][3]=0.25*(1-e[1])*(1+n[1]);
		//cout<<"jestem tu else"<<endl;

	}
	}
	if(EL[i].sciana[2] == 1){
		double e[2] = {1,1,};
		double n[2] ={-0.577,0.577};
		if(EL[i].sciana[0] == 0 && EL[i].sciana[1] == 0){
		EL[i].N2[0][0]=0.25*(1-e[0])*(1-n[0]);
		EL[i].N2[0][1]=0.25*(1+e[0])*(1-n[0]);
		EL[i].N2[0][2]=0.25*(1+e[0])*(1+n[0]);
		EL[i].N2[0][3]=0.25*(1-e[0])*(1+n[0]);
		EL[i].N2[1][0]=0.25*(1-e[1])*(1-n[1]);
		EL[i].N2[1][1]=0.25*(1+e[1])*(1-n[1]);
		EL[i].N2[1][2]=0.25*(1+e[1])*(1+n[1]);
		EL[i].N2[1][3]=0.25*(1-e[1])*(1+n[1]);
		//cout<<"jestem tu"<<endl;
		
		
		
		}
		else{
			EL[i].N2[2][0]=0.25*(1-e[0])*(1-n[0]);
		EL[i].N2[2][1]=0.25*(1+e[0])*(1-n[0]);
		EL[i].N2[2][2]=0.25*(1+e[0])*(1+n[0]);
		EL[i].N2[2][3]=0.25*(1-e[0])*(1+n[0]);
		EL[i].N2[3][0]=0.25*(1-e[1])*(1-n[1]);
		EL[i].N2[3][1]=0.25*(1+e[1])*(1-n[1]);
		EL[i].N2[3][2]=0.25*(1+e[1])*(1+n[1]);
		EL[i].N2[3][3]=0.25*(1-e[1])*(1+n[1]);
			//cout<<"jestem tu else"<<endl;

	}
	}
	if(EL[i].sciana[3] == 1){
		double e[2] = {0.577 ,-0.577};
		double n[2] ={1,1};
		if(EL[i].sciana[0] == 0 && EL[i].sciana[1] == 0 &&EL[i].sciana[2] == 0 ){
		EL[i].N2[0][0]=0.25*(1-e[0])*(1-n[0]);
		EL[i].N2[0][1]=0.25*(1+e[0])*(1-n[0]);
		EL[i].N2[0][2]=0.25*(1+e[0])*(1+n[0]);
		EL[i].N2[0][3]=0.25*(1-e[0])*(1+n[0]);
		EL[i].N2[1][0]=0.25*(1-e[1])*(1-n[1]);
		EL[i].N2[1][1]=0.25*(1+e[1])*(1-n[1]);
		EL[i].N2[1][2]=0.25*(1+e[1])*(1+n[1]);
		EL[i].N2[1][3]=0.25*(1-e[1])*(1+n[1]);
		EL[i].N2[2][1]=0;
		EL[i].N2[2][2]=0;
		EL[i].N2[2][3]=0;
		EL[i].N2[3][0]=0;
		EL[i].N2[3][1]=0;
		EL[i].N2[3][2]=0;
		EL[i].N2[3][3]=0;
		//cout<<"jestem tu"<<endl;
		
		}
		else{
			EL[i].N2[2][0]=0.25*(1-e[0])*(1-n[0]);
		EL[i].N2[2][1]=0.25*(1+e[0])*(1-n[0]);
		EL[i].N2[2][2]=0.25*(1+e[0])*(1+n[0]);
		EL[i].N2[2][3]=0.25*(1-e[0])*(1+n[0]);
		EL[i].N2[3][0]=0.25*(1-e[1])*(1-n[1]);
		EL[i].N2[3][1]=0.25*(1+e[1])*(1-n[1]);
		EL[i].N2[3][2]=0.25*(1+e[1])*(1+n[1]);
		EL[i].N2[3][3]=0.25*(1-e[1])*(1+n[1]);
			//cout<<"jestem tu else"<<endl;
	}
	}

	if(EL[i].sciana[0] == 0 && EL[i].sciana[1] == 0 && EL[i].sciana[2] == 0 && EL[i].sciana[3] == 0){

		EL[i].N2[0][0]=0;
		EL[i].N2[0][1]=0;
		EL[i].N2[0][2]=0;
		EL[i].N2[0][3]=0;
		EL[i].N2[1][0]=0;
		EL[i].N2[1][1]=0;
		EL[i].N2[1][2]=0;
		EL[i].N2[1][3]=0;
		EL[i].N2[2][1]=0;
		EL[i].N2[2][2]=0;
		EL[i].N2[2][3]=0;
		EL[i].N2[3][0]=0;
		EL[i].N2[3][1]=0;
		EL[i].N2[3][2]=0;
		EL[i].N2[3][3]=0;
		//cout<<"jestem tu"<<endl;
	
	}
	
	}
	//cout<<EL[0].N2[3][3]<<endl;





}
void Grid::calka2(double alfa , int roz ){
	//int ymp =1;
	for(int p = 0 ; p<roz ; p++){
		//cout<<"dla elementu "<<p<<endl;
		for(int g =0 ; g<4;g++){
			//cout<<"dla pkt ca³kowania"<<g<<endl;
for(int j =0 ; j<4;j++){
	EL[p].lokalneH[g][j] = 0;
	
	for(int i =0 ; i<4;i++){
		EL[p].NrazyNtrans[g][j][i] = 0;
		EL[p].NrazyNtrans[g][j][i] = EL[p].N2[g][i] *EL[p].N2[g][j] * (EL[p].dl/2) * alfa ;
		//cout<<EL[p].NrazyNtrans[g][j][i]<<"  ";
		
	//	cout<<EL[p].NrazyNtrans2[g][j][i]<<"  ";
		//cout<<ymp<<endl;
		
			}
	//cout<<EL[p].N2[g][j]<<" ";
	
	
		}
//cout<<endl;

	}
}






}


void Grid::calkaC(int roz, double N[4][4],double cp, double ro){

	for(int p = 0 ; p<roz ; p++){
		//cout<<"dla elementu "<<p<<endl;
		for(int g =0 ; g<4;g++){
			//cout<<"dla pkt ca³kowania"<<g<<endl;
for(int j =0 ; j<4;j++){
	EL[p].lokalneC[g][j] = 0;
	for(int i =0 ; i<4;i++){
		
	
	
		EL[p].NrazyNtrans2[g][j][i] = (N[g][i]*N[g][j]) * (cp* ro * (1/EL[p].det[0]));
		//cout<<EL[p].NrazyNtrans2[g][j][i]<<"  ";
	
		
			}	
	
	//cout<<endl;
		}

	}
			
}

	


}
void Grid::lokaleH(int roz){

	
		for(int p = 0 ; p<roz ; p++){
			//cout<<"element:"<<p<<endl;
		for(int g =0 ; g<4;g++){
for(int j =0 ; j<4;j++){
	for(int i =0 ; i<4;i++){

		EL[p].lokalneH[g][j] += EL[p].NrazyNtrans[i][g][j];
		//suma C po punktach calkowania dla kazdego elementy
		EL[p].lokalneC[g][j] += EL[p].NrazyNtrans2[i][g][j];

}
	//cout<<EL[p].lokalneH[g][j]<<"  ";
	
}
//cout<<endl;
		}
		//cout<<endl;
		}
		for(int p = 0 ; p<roz ; p++){
			//cout<<"element"<<p<<endl;
		for(int j =0 ; j<4;j++){
	for(int i =0 ; i<4;i++){

		EL[p].lokalneH[j][i] += EL[p].calkaxplusy[j][i];
		//cout<<EL[p].lokalneH[j][i]<<"  " ;

	}
	//cout<<endl;
		}
	
		}





}		
void Grid::wektorP(int roz, double alfa ,double t8 , double globalP[r]){
	//double GlobalP[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(int p = 0 ; p < roz ; p++){
		EL[p].wektorp[0][0] =0;
		EL[p].wektorp[0][1] =0;
		EL[p].wektorp[0][2] =0;
		EL[p].wektorp[0][3] =0;
		//cout<<"dla elementu:"<<p<<endl;
			
			for(int i =0 ; i<4 ; i++){
				
				if(EL[p].sciana[0]==1){
					EL[p].wektorp[0][0] += (EL[p].N2[0][i] + EL[p].N2[1][i]); 
				}
			 if(EL[p].sciana[1]==1){
					if(EL[p].sciana[0]==1){
						EL[p].wektorp[0][1] += (EL[p].N2[2][i] + EL[p].N2[3][i]); 

					}
					else
						EL[p].wektorp[0][1] += (EL[p].N2[0][i] + EL[p].N2[1][i]); 
				}
				if(EL[p].sciana[2]==1){
					if(EL[p].sciana[0]==1 ||EL[p].sciana[1]==1  ){
						EL[p].wektorp[0][2] += (EL[p].N2[2][i] + EL[p].N2[3][i]); 

					}
					else
						EL[p].wektorp[0][2] += (EL[p].N2[0][i] + EL[p].N2[1][i]); 
				}
					 if(EL[p].sciana[3]==1){
						if(EL[p].sciana[0]==1 ||EL[p].sciana[1]==1 || EL[p].sciana[2]==1  ){
						EL[p].wektorp[0][3] += (EL[p].N2[2][i] + EL[p].N2[3][i]); 

					}
					else
						EL[p].wektorp[0][3] += (EL[p].N2[0][i] + EL[p].N2[1][i]); 
					}

			}
			for(int i =0 ; i<4 ; i++){
			EL[p].wektorp[0][i] = EL[p].wektorp[0][i]* alfa *t8* (EL[p].dl/2); //;
		//	cout<<EL[p].wektorp[0][i]<<"  ";
			}	



		
		// global P
			for(int i =0 ; i<4;i++){

				globalP[EL[p].id[i]] += EL[p].wektorp[0][i];
		
	}
	
	
	//cout<<endl;
	}
	//cout<<"globalP"<<endl;
	//for(int i =0 ; i<16;i++){
	//	cout<<globalP[i]<<"  ";
	//cout<<endl;
	//}
	


}


void Grid::transpozycja(double tab[4][4]){
	double tabtr[4][4];
	for(int j =0 ; j<4;j++){
	for(int i =0 ; i<4;i++){
	
		tabtr[j][i] = tab[i][j];
		cout<<tabtr[j][i]<<"  "; 

	}
	cout<<endl;
	}



}

void Grid::mnozeniemaciezy(double tab[4][4], double tab2[4][4], double tab3[4][4][4]){
	//double newtab[4][4];
	for(int p =0 ; p<4; p++){
		//cout<<"pkt ca³kowania: "<<p<<endl;
	for(int j =0 ; j<4;j++){
	for(int i =0 ; i<4;i++){
		tab3[p][j][i] = tab[p][i] * tab2[p][j]; 
		
//cout<<tab3[p][j][i]<<"  ";


	}
	//cout<<endl;

	}
}
	





}
void Grid::ca³kowanie(int roz){
	
	double wyznacznik; 
	for(int h =0 ; h<roz;h++){
	for(int j =0 ; j<4;j++){
	for(int i =0 ; i<4;i++){
		EL[h].calkaxplusy[j][i] =0;
	}}}
	for(int h =0 ; h<roz;h++){
	for(int p =0 ; p<4;p++){
	for(int j =0 ; j<4;j++){
	for(int i =0 ; i<4;i++){
		EL[h].calkaxplusy[j][i] += (EL[h].tabx[p][j][i] +  EL[h].taby[p][j][i]) * (1/EL[h].det[0]) *k ;
		
	//cout<<EL[0].calkaxplusy[j][i]<<"  ";
	
	}
	//cout<<endl;
	
	}
	//cout<<"next"<<endl;
	
	}
	}

}


void Grid::jakobian(double ni[4][4] ,double E[4][4] , int roz ){
	double tmp=0;
	//size_t El = sizeof(EL) / sizeof(EL[0]);
	for(int p = 0 ; p<roz ; p++){
	for(int j =0 ; j<4;j++){
	for(int i =0 ; i<4;i++){
			EL[p].j[j][0][0]+= ni[j][i] * ND[EL[p].id[i]].y;	
			EL[p].j[j][0][1]+= E[j][i] * ND[EL[p].id[i]].y;	
			EL[p].j[j][1][0] += ni[j][i] * ND[EL[p].id[i]].x;	
			EL[p].j[j][1][1] += E[j][i] * ND[EL[p].id[i]].x;	

			
			
	}
	EL[p].j[j][1][0] = -EL[p].j[j][1][0];
	EL[p].j[j][0][1] = -EL[p].j[j][0][1];
	//wyznacznik jakobianu
	EL[p].det[j] = EL[p].j[j][0][0]*EL[p].j[j][1][1] - EL[p].j[j][0][1]*EL[p].j[j][1][0];
	//odwrotny wyznacznik 
	EL[p].det[j] = 1/EL[p].det[j];



	}
	}
	for(int p =0 ; p<roz; p++){
	for(int j =0 ; j<2; j++){
	for(int i =0 ; i<2; i++){
		//wyswietl jackobian 
		//cout<<" "<<EL[p].j[1][j][i]; 
	}
	//cout<<endl;
	}
	}
	//obliczanie i wyswietlanie waktora N po x i N po y
	for(int p =0 ; p<roz; p++){
	//cout<<" wyznacznik: "<<EL[p].det[0]; 
	for(int j =0 ; j<4; j++){
		//cout<<"dla "<<j<<"pkt ca³kowania:";
	for(int i =0 ; i<4 ; i++){
		EL[p].wktNx[j][i] = EL[p].det[0] * EL[p].j[0][0][0] * E[j][i] + EL[p].det[0] * EL[p].j[0][0][1] * E[j][i]; 
		EL[p].wktNy[j][i] = EL[p].det[0] * EL[p].j[0][1][0] * ni[j][i] + EL[0].det[0] * EL[p].j[0][1][1] * ni[j][i]; 
		//cout<<"po y   "<<EL[0].wktNx[j][i];
		
	}
	
	}
	
	//cout<<endl;
	}
	//wektor x wektor^t
	for(int i =0 ; i<roz ; i++){
		//cout<<"element: "<<i<<endl;
		
	//cout<<"wektor x wektor ^t"<<endl;
	Grid::mnozeniemaciezy(EL[i].wktNx, EL[i].wktNx, EL[i].tabx);
	//cout<<"wektor y wektor ^t"<<endl;
	Grid::mnozeniemaciezy(EL[i].wktNy, EL[i].wktNy,EL[i].taby);
	}
	




	
	}
//global h i global c
void Grid::globalH(int roz ,double globalH[r][r],double globalC[r][r] ){
	//double globalH[16][16];
	//double globalC[16][16];
	for(int j =0 ; j<r;j++){
			for(int i =0 ; i<r;i++){
				globalH[j][i] = 0;
				globalC[j][i] = 0;
			}}

	for(int p = 0 ; p<roz ; p++){
		for(int j =0 ; j<4;j++){
			for(int i =0 ; i<4;i++){

				globalH[EL[p].id[j]][EL[p].id[i]] += EL[p].lokalneH[j][i];
				//global C
				globalC[EL[p].id[j]][EL[p].id[i]] += EL[p].lokalneC[j][i];
				//cout<<EL[p].id[j] <<" "<<EL[p].id[i]<<endl;

			}
			
		}
	}
	for(int j =0 ; j<r;j++){
			for(int i =0 ; i<r;i++){
			//	cout<<globalH[j][i]<<"  ";
	
			
			}
	
	//cout<<endl;
	}


}



