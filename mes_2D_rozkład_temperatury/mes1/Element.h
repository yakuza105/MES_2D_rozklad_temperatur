#ifndef Element_h
#define Element_h

using namespace std;

class Element {
public:
	double dl;
	int id[4];
	int sciana[4];
	double j[4][2][2];
	double det[4];
	double wktNx[4][4];
	double wktNy[4][4];
	double tabx[4][4][4];
	double taby[4][4][4];
	double calkaxplusy[4][4];
	double N2[4][4];
	double NrazyNtrans[4][4][4];
	double NrazyNtrans2[4][4][4];
	double lokalneH[4][4];
	double lokalneC[4][4];
	double wektorp[4][4];
	

	Element() {
		for(int i =0 ; i<4 ;i++){
		j[i][0][0] =0;
		j[i][0][1] =0;
j[i][1][0] =0;
		j[i][1][1] =0;
		}


	};
};

#endif