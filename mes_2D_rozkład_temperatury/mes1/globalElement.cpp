
#include <iostream>
#include <iomanip>
#include <cmath>
#include "globalElement.h"
using namespace std;

globalElement::globalElement(double zero)
{
	this->globalH[0][0] =0;
	this->globalC[0][0] =0;
	for (int i =0 ; i<roz; i++){
	this->globalP[i] = 0;
	this->P[i] =0;




	
	}
}

void globalElement::cprzezdt(double dt){
	
	//cout<<"c/dt"<<endl;
	for(int j =0 ; j<roz;j++){
	for(int i =0 ; i<roz;i++){
	this->cdt[j][i] = this->globalC[j][i] / dt;
//cout<<cdt[j][i]<<"  ";
	}
	//cout<<endl;
	}


}
void globalElement::lastH(){
	//cout<<" H + c/dt"<<endl;
	for(int j =0 ; j<roz;j++){
	for(int i =0 ; i<roz;i++){
		this->Hcdt[j][i] = this->globalH[j][i] + this->cdt[j][i];
	//cout<<Hcdt[j][i]<<"  ";
	}
	//cout<<endl;
	}
	
	





}

void globalElement::lastP(double t0[roz]){
	double tmp =0;
	//cout<<" p = p + (C/dt) * {t0}"<<endl;
	for(int j =0 ; j<roz;j++){
		tmp =0;
		
	for(int i =0 ; i<roz;i++){
		tmp += cdt[j][i]* t0[i];
		
	}
	P[j] = globalP[j] + tmp;
	//cout<<P[j]<<"  ";
	
	}
	//cout<<endl;


}

void globalElement::gauss(int n){
	double max =0 ;
	double min = 20;
	double result[roz];
	for(int i =0 ; i<roz;i++){
	result[i] = 0;
	}
		double U[roz][roz+1];
		const double e  = 1e-12;

	
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                U[j][i] = Hcdt[j][i];
			
			}
        }

        for (int i = 0; i < n; ++i) {
            U[i][n] = P[i];
		}
        

        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (abs(U[i][i]) < e) {
					
					
                    break;
                }

                double x = -U[j][i] / U[i][i];
				
                for (int k = 0; k < n + 1; ++k) {
                    U[j][k] += x * U[i][k];
					//cout<<U[j][k]<<"  ";
                }
				//cout<<endl;
            }
		}

        for (int i = n - 1; i >= 0; --i) {
			
            double x = U[i][n];
			
            for (int j = n - 1; j >= 0; --j) {
				
                x -= U[i][j] * result[j];
				
            }
			
            if(abs(U[i][i]) < e) {
				
                break;
            }
            result[i] = x / U[i][i];
			


			//cout<<"wezel:  "<<i<<"  :  "<<  result[i]<<endl;
			w[i] =  result[i];
        }


		min = result[0];
		max = result[0];
		 for (int i = n - 1; i >= 0; --i) {
		if(result[i] >= max)
				max = result[i];
			if(result[i] <= min)
				min= result[i];
		 }
		cout<<"max temp:  " <<max<< "    min temp:    "<<min<<endl;
        

  
}









globalElement::~globalElement(void)
{
}
